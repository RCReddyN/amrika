#include <fstream>
#include<iostream>
#include "emit.hpp"

Emitter::Emitter(string path){
    fullPath = path;
    header = "";
    code = "";
}

void Emitter::emit(string codepiece){
    code += codepiece;
}

void Emitter::emitLine(string codepiece){
    code += codepiece + '\n';
}

void Emitter::headerLine(string codepiece){
    header += codepiece + '\n';
}

void Emitter::writeFile(){
    ofstream outputFile(fullPath);
    outputFile << header;
    outputFile << code;
    outputFile.close();
}