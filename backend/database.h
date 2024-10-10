#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include "Product.h"
#include "User.h"

class Database {
public:
    Database();
    void connect();
    
    // Methods for managing products
    void addProduct(const Product& product);
    std::vector<Product> getProducts() const;

    // Methods for managing users
    void addUser(const User& user);
    std::vector<User> getUsers() const;

private:
    std::vector<Product> products;
    std::vector<User> users;
};

#endif // DATABASE_H
