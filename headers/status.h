#ifndef STATUS_H
#define STATUS_H

// La clase de Status se utiliza para proporcionar una salida de comando más avanzada.
// Además de devolver un código de estado, devuelve un mensaje de salida.
class Status {
    private:
    int status; //4 bytes
    char* output; // Bytes desconocidos

    public:
    Status(int status, const char* output);
    Status(int status); // Status con output vacío
    Status(const Status &status);
    ~Status();

    int getStatus() const;
    const char* getOutput() const;
    int isOutputEmpty() const;

    void serialize(char* buffer);
    void deserialize(char* buffer);
};

#endif