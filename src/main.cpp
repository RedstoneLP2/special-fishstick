#include "common.h"

int main(int argc, char const *argv[])
{
    MemoryManager memory = MemoryManager(65535);
    Cpu core = Cpu(memory);
    loadfile("./sample/tmp/eater.bin",memory.getMemory());
    core.reset();
    for (int i = 0; i < 150; i++)
    {
        //core.printRegisters();
        core.run();
        //std::cout << "-------------------"<<std::endl;
    }

    core.printMemoryLocation(0x01E0);
    core.printMemoryLocation(0x01F0);
    core.printMemoryLocation(0x0200);
    core.printRegisters();
    //hello_World(core);
    return 0;
}
