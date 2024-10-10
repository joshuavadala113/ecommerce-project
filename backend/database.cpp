#include "database.h"
#include <iostream>

Database::Database() {}

void Database::connect() {
    // Simulating database connection
    std::cout << "Database connected successfully." << std::endl;
}

void Database::addProduct(const Product& product) {
    products.push_back(product);
}

std::vector<Product> Database::getProducts() const {
    return products;
}

void Database::addUser(const User& user) {
    users.push_back(user);
}

std::vector<User> Database::getUsers() const {
    return users;
}
