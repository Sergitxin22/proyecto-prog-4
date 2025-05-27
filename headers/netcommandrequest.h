//
// Created by Dani on 26/05/2025.
//

#ifndef COMMANDREQUEST_H
#define COMMANDREQUEST_H



class NetCommandRequest {

private:
    static int counter;
    int id; //4 bytes
    long timeStamp;  //8 bytes
    //
    char* command;
public:
    //Constructor
    NetCommandRequest(const char* commandString);
    //Destructor
    ~NetCommandRequest();
    //Getter for timeStamp
    long getTimeStamp();
    int getId();
    char* getCommand();
    void serialize(char* buffer);
    void deserialize(char* buffer);


};



#endif //COMMANDREQUEST_H
