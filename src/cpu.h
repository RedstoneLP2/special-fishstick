#include "common.h"

class Cpu
{

private:

    Registers cpuRegisters;
    MemoryManager systemRam;
    uint16_t getOperantBytes();

public:
    Cpu(MemoryManager);
    ~Cpu();
    void setStatusFlag(unsigned);
    void lda(char);
    void ldx(char);
    void ldy(char);
    void sta(uint16_t);
    void stx(uint16_t);
    void sty(uint16_t);
    void jsr(uint16_t);
    void bne(int8_t);
    void jmp(uint16_t);
    void jmp(int8_t);
    void clc();
    void cld();
    void cli();
    void clv();
    void pha();
    void pla();
    void rts();
    void dec();
    void inc();
    void printRegisters();
    void printMemoryLocation(int);
    void* getMemory();
    void reset();
    void run();

};
