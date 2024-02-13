#include "ram.h"

Ram::Ram(int size)
{
    memory = calloc(1,size);
}
Ram::Ram()
{
    Ram(16384);
}

Ram::~Ram()
{
    //free(memory);
}

void* Ram::getMemory(){
    return memory;
}