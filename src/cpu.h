#include "common.h"

class Cpu
{

private:

    Registers cpuRegisters;
    MemoryManager systemRam;
    uint16_t getOperantBytes();
    uint16_t Opcode_Length;

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
    void reset();
    void run();

};
