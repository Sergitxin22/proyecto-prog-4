//
// Created by Dani on 26/05/2025.
//

#ifndef TEST_SERIALIZACION_H
#define TEST_SERIALIZACION_H

#include "../headers/status.h"
#include <iostream>
#include <string.h>


int main(){

  Status s1(5,"Carpeta creada correctamente");
  int outputLength = strlen(s1.getOutput());
  int size = sizeof(int) + sizeof(int) + outputLength;
  char* buffer = new char[size];
  s1.serialize(buffer);
  Status s2(3);
  s2.deserialize(buffer);
  std::cout << "Output: " << s2.getOutput() << std::endl;
  std::cout << "Status: " <<  s1.getStatus() << std::endl;
  delete[] buffer;
 }


#endif //TEST_SERIALIZACION_H
