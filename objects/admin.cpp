#include "../headers/admin.h"
#include <cstring>

Admin::Admin(int id, const char* name): User(id, name) {}

Admin::~Admin() {}

int Admin::getID() const {
    return this->id;
}

const char* Admin::getName() const {
return this->name;
}
    
int Admin::isAdmin() {
    return true;
}