#include <string>
#include "protlib.hh"

int bigToLittle(unsigned char buffer[], int n){
    int i;
    int result = (int)buffer[0]<<(n-1)*8;
    for (i=1;i<4;i++){
        result = result | (int)buffer[i]<<(n-1-i)*8;
    }
    return result;
}

unsigned int readIndexFile(unsigned char * buffer, char sizeOfBuffer, FILE * indexFile){
    fread(buffer,1,sizeOfBuffer,indexFile);
    unsigned int returnLittle = bigToLittle(buffer,sizeOfBuffer);
    return returnLittle;
}


std::string charToString(char* a, int size) 
{ 
    int i; 
    std::string s = ""; 
    for (i = 0; i < size; i++) { 
        s = s + a[i]; 
    } 
    return s; 
} 
