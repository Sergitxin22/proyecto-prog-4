//
// Created by Dani on 26/05/2025.
//


#include "../headers/netcommandrequest.h"
#include <string.h>

int NetCommandRequest::counter = 10;

NetCommandRequest::NetCommandRequest(const char* commandString){
    this->id = counter;
    this->counter++;
    this->timeStamp = 5;
    this->command = new char[strlen(commandString) + 1];
    strcpy(this->command, commandString);
}

NetCommandRequest::~NetCommandRequest(){
    delete [] this->command;
}

long NetCommandRequest::getTimeStamp(){
    return this->timeStamp;
}
int NetCommandRequest::getId(){
    return this->id;
}

char* NetCommandRequest::getCommand(){
    return this->command;
}

//Serializar
// [int id][long timeStamp][int cmdLength][char cmdBytes...]
// 4 bytes , 8 bytes, 4 bytes , lo que sea


void NetCommandRequest::serialize(char* buffer){
    //id
    memcpy(buffer, &id, sizeof(id));
    buffer += sizeof(id);

    // timestamp
    memcpy(buffer, &timeStamp, sizeof(timeStamp));
    buffer += sizeof(timeStamp);

    //Longitud del comando
    int cmdLength = strlen(command); //NO INCLUYE CARACTER NULO
    memcpy(buffer, &cmdLength, sizeof(cmdLength));
    buffer += sizeof(cmdLength);

    //Comando
    memcpy(buffer, command,cmdLength);

}



//Deseralizar

void NetCommandRequest::deserialize(char* buffer){
    //ID
    memcpy(&id,buffer,sizeof(id));
    //Posicionamos el puntero 4 bytes alante.
    buffer  += sizeof(id);

    //Timestamp
    memcpy(&timeStamp, buffer, sizeof(timeStamp));
    buffer += sizeof(timeStamp);

    //Tamaño del comando
    int cmdLength = 0;
    memcpy(&cmdLength, buffer,sizeof(cmdLength));
    buffer += sizeof(cmdLength);

    //Comando
    delete[] this->command;
    this->command = new char[cmdLength + 1];
    memcpy(this->command,buffer,cmdLength);
    this->command[cmdLength] = '\0';



}










