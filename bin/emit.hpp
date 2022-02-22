// header file containing the interface for the Emitter class
#include <iostream>

using namespace std;
class Emitter
{
public:
    string fullPath;
    string header;
    string code;

    Emitter()
    {
        header = "";
        code = "";
    }
    Emitter(string path);

    void emit(string codepiece);

    void emitLine(string codepiece);

    void headerLine(string codepiece);

    void writeFile();
};