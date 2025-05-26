#ifndef ADMIN_H
#define ADMIN_H
#include "user.h"

// La clase de Status se utiliza para proporcionar una salida de comando más avanzada.
// Además de devolver un código de estado, devuelve un mensaje de salida.
class Admin: public User {
    public:
    Admin(int id, const char* name);
    ~Admin();

    int getID() const;
    const char* getName() const;
    virtual int isAdmin();
};

#endif