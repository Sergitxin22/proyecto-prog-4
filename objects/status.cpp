#include "../headers/status.h"
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

