#include "common.h"

int RunCpu(Cpu core){
    for (int i = 0; i < 150; i++)
    {
        //core.printRegisters();
        core.run();
        //std::cout << "-------------------"<<std::endl;
    }
}

int RunACIA(ioChip core){
    for (int i = 0; i < 150; i++)
    {
        //core.printRegisters();
        core.run();
        //std::cout << "-------------------"<<std::endl;
    }
}


int main(int argc, char const *argv[])
{
    MemoryManager memory = MemoryManager(65535);
    Cpu core = Cpu(memory);
    ioChip ACIA = ioChip(memory);
    loadfile("./sample/tmp/eater.bin",memory.getMemory());
    core.reset();
    std::thread cpu (RunCpu,core);
    std::thread acia (RunACIA,ACIA);

    cpu.join();
    acia.join();

    //hello_World(core);
    return 0;
}
