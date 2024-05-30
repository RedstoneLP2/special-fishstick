#include "common.h"

class MemoryManager
{
private:
    void* memory;
    uint8_t inputBuffer;
    uint8_t outputBuffer;
    uint16_t lastAddress;
    ioHandler* iohandler;
    bool MEMWRITE; // true if writing, false otherwise
    bool MEMREAD; // true if reading, false otherwise
public:
//    MemoryManager();
    MemoryManager(int,ioHandler*);
    ~MemoryManager();

    void* getMemory();
    void writeMem(uint16_t,uint8_t);
    void writeMem(uint16_t,uint16_t);
    void startWrite();
    void endWrite();
    void startRead();
    void endRead();
    uint8_t readMem(uint16_t);
    uint8_t readDevMem(uint16_t);
    void writeDevMem(uint16_t, uint8_t);
    uint8_t* GetMemoryLocation(uint16_t);
};



