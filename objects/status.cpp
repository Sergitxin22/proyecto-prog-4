#include "../headers/status.h"

#include <bits/fs_fwd.h>

#include "cstring"

Status::Status(int status, const char* output) {
    this->status = status;
    this->output = new char[strlen(output) + 1];
    strcpy((char *) this->output, output);
}

Status::Status(int status) {
    this->status = status;
    this->output = NULL;
}

Status::~Status() {
    delete[](this->output);
}

int Status::getStatus() const {
    return this->status;
}

const char* Status::getOutput() const {
    return this->output;
}

int Status::isOutputEmpty() const {
    if (this->output == NULL) {
        return true;
    }
    return false;
}


void Status::serialize(char* buffer) {
    //Copiamos el status
    memcpy(buffer,&status,sizeof(status));
    buffer += sizeof(status);  //Avanzamos el puntero.

    //Ahora, copiamos el tamaño del output, ya que tenemos que saberlo para poder reconstruirlo.
    int outputLength = strlen(output); //No incluye el caracter nulo
    memcpy(buffer,&outputLength,sizeof(output));
    buffer += sizeof(outputLength); //Avantamos el puntero.

    //Copiamos en el buffer el comando.
    memcpy(buffer,output,outputLength);

}
void Status::deserialize(char* buffer) {
    memcpy(&status,buffer,sizeof(status));
    buffer += sizeof(status);

    int outputLength;
    memcpy(&outputLength,buffer,sizeof(outputLength));
    buffer += sizeof(outputLength);

    //Copiamos el output
    delete [] this->output;
    this->output = new char[outputLength + 1];
    memcpy((char* )this->output,buffer,outputLength);
    buffer[outputLength] = '\0';

}

