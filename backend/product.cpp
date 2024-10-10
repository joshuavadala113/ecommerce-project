#include "product.h"
#include <cpprest/json.h>

Product::Product(int id, const std::string& name, double price)
    : id(id), name(name), price(price) {}

int Product::getId() const { return id; }

std::string Product::getName() const { return name; }

double Product::getPrice() const { return price; }

std::string Product::toJSON() const {
    web::json::value product_json;
    product_json[U("id")] = web::json::value::number(id);
    product_json[U("name")] = web::json::value::string(name);
    product_json[U("price")] = web::json::value::number(price);

    return product_json.serialize();
}
