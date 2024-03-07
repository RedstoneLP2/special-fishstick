#include "common.h"

class ioHandler
{
private:
    WINDOW* ioWindow;
    WINDOW* debugWindow;
public:
    void printHeader();
    void printIoString(std::string);
    void printIoChar(char);
    void printDebugString(std::string);
    void printDebugChar(char);
    ioHandler();
    ~ioHandler();
    char handleInput();
};