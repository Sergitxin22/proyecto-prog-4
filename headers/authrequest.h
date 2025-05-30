#ifndef AUTH_REQUEST_H
#define AUTH_REQUEST_H

class AuthRequest {
private:
    char username[30];
    char password[30];

public:
    AuthRequest(); // Default
    AuthRequest(const char* user, const char* pass);

     char* getUsername() ;
     char* getPassword() ;

    void serialize(char* buffer) const;
    void deserialize(const char* buffer);
};

#endif
