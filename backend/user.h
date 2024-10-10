#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    User(int id, const std::string& username, const std::string& password);
    int getId() const;
    std::string getUsername() const;
    std::string toJSON() const;

private:
    int id;
    std::string username;
    std::string password;
};

#endif // USER_H
