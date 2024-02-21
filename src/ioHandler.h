#include "common.h"

class ioHandler
{
private:
    WINDOW* ioWindow;
    WINDOW* debugWindow;
public:
    void printHeader();
    void printString(std::string);
    void printChar(char);
    ioHandler();
    ~ioHandler();
    char handleInput();
};