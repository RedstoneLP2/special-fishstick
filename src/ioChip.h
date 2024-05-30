#include "common.h"

class ioChip
{
private:
    MemoryManager* mm;
    ioHandler* iohandler;

    void print();
public:
    ioChip(MemoryManager*,ioHandler*);
    ~ioChip();
    void run();
    void sendkey(uint8_t);
};