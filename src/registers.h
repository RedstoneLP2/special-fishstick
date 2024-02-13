#include <iostream>
#include <format>
#include <bitset>
#include <cstdint>


const struct
{
    const unsigned Negative = 7;
    unsigned Overflow = 6;
    unsigned Unused = 5;
    unsigned Break = 4;
    unsigned DecimalMode = 3;
    unsigned InterruptDisable = 2;
    unsigned Zero = 1;
    unsigned Carry = 0;
} ProcessorStatusFlags;

class Registers
{
    public:
        Registers();
        ~Registers();
        std::string toString();

        std::bitset<16> ProgramCounter;
        std::bitset<8> StackPointer;
        std::bitset<8> ProcessorStatus;
        std::bitset<8> Accumulator;
        std::bitset<8> XIndex;
        std::bitset<8> YIndex;
};

