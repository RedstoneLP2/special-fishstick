#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
class MemoryManager
{
private:
    void* memory;
public:
    MemoryManager(int);
    MemoryManager();
    ~MemoryManager();

    void* getMemory();
    void writeMem(uint16_t,uint8_t);
    void writeMem(uint16_t,uint16_t);
    uint8_t* GetMemoryLocation(uint16_t);
};



