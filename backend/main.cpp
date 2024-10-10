#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <iostream>
#include "product.h"
#include "user.h"
#include "database.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

Database db;

void handle_get(http_request request) {
    auto paths = uri::split_path(uri::decode(request.relative_uri().path()));

    if (paths.empty()) {
        request.reply(status_codes::BadRequest, U("Invalid request"));
        return;
    }

    // Handle products request
    if (paths[0] == U("products")) {
        json::value response_data;
        json::value products_array = json::value::array();

        auto products = db.getProducts();
        for (size_t i = 0; i < products.size(); ++i) {
            products_array[i] = json::value::parse(products[i].toJSON());
        }

        response_data[U("products")] = products_array;
        request.reply(status_codes::OK, response_data);
    } 
    // Handle users request
    else if (paths[0] == U("users")) {
        json::value response_data;
        json::value users_array = json::value::array();

        auto users = db.getUsers();
        for (size_t i = 0; i < users.size(); ++i) {
            users_array[i] = json::value::parse(users[i].toJSON());
        }

        response_data[U("users")] = users_array;
        request.reply(status_codes::OK, response_data);
    } else {
        request.reply(status_codes::BadRequest, U("Invalid endpoint"));
    }
}

void handle_post(http_request request) {
    auto paths = uri::split_path(uri::decode(request.relative_uri().path()));
    
    if (paths.empty()) {
        request.reply(status_codes::BadRequest, U("Invalid request"));
        return;
    }

    // Handle product creation
    if (paths[0] == U("products")) {
        request.extract_json().then([&](json::value json_data) {
            try {
                int id = json_data[U("id")].as_integer();
                std::string name = json_data[U("name")].as_string();
                double price = json_data[U("price")].as_double();

                Product new_product(id, name, price);
                db.addProduct(new_product);
                
                request.reply(status_codes::Created, U("Product created"));
            } catch (const std::exception& e) {
                request.reply(status_codes::BadRequest, U("Error creating product"));
            }
        }).wait();
    }
    // Handle user creation
    else if (paths[0] == U("users")) {
        request.extract_json().then([&](json::value json_data) {
            try {
                int id = json_data[U("id")].as_integer();
                std::string username = json_data[U("username")].as_string();
                std::string password = json_data[U("password")].as_string();

                User new_user(id, username, password);
                db.addUser(new_user);
                
                request.reply(status_codes::Created, U("User created"));
            } catch (const std::exception& e) {
                request.reply(status_codes::BadRequest, U("Error creating user"));
            }
        }).wait();
    } else {
        request.reply(status_codes::BadRequest, U("Invalid endpoint"));
    }
}

int main() {
    uri_builder uri(U("http://localhost:8080/api"));
    auto addr = uri.to_uri().to_string();
    listener l(addr);

    // Database setup
    db.connect();
    db.addProduct(Product(1, "Laptop", 1200.99));
    db.addUser(User(1, "admin", "password123"));

    // Setup routes
    l.support(methods::GET, handle_get);
    l.support(methods::POST, handle_post);

    try {
        l
            .open()
            .then([&l](){ std::wcout << U("Server is listening at: ") << l.uri().to_string() << std::endl; })
            .wait();

        std::string line;
        std::getline(std::cin, line); // Wait for user to press enter
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}
