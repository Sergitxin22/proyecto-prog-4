#ifndef USER_H
#define USER_H

// La clase de Status se utiliza para proporcionar una salida de comando más avanzada.
// Además de devolver un código de estado, devuelve un mensaje de salida.
class User {
    protected:
    int id;
    const char* name;

    public:
    User(int id, const char* name);
    ~User();

    int getID() const;
    const char* getName() const;
    virtual int isAdmin();

    void setName(const char* name);
    void setID(int id);
};

#endif