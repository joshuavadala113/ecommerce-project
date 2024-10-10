#include "user.h"
#include <cpprest/json.h>

User::User(int id, const std::string& username, const std::string& password)
    : id(id), username(username), password(password) {}

int User::getId() const { return id; }

std::string User::getUsername() const { return username; }

std::string User::toJSON() const {
    web::json::value user_json;
    user_json[U("id")] = web::json::value::number(id);
    user_json[U("username")] = web::json::value::string(username);

    return user_json.serialize();
}
