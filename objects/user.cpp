#include "../headers/user.h"
#include <cstring>

User::User(int id, const char* name) {
    this->id = id;
    this->name = new char[strlen(name) + 1];
    strcpy((char *) this->name, name);
}

User::~User() {
    delete[](this->name);
}

int User::getID() const {
    return this->id;
}

const char* User::getName() const {
return this->name;
}
    
int User::isAdmin() {
    return false;
}

void User::setName(const char* name) {
    delete(this->name);
    this->name = new char[strlen(name) + 1];
    strcpy((char *) this->name, name);
}