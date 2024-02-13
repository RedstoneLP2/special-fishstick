#include <iostream>
#include <stdlib.h>
class Ram
{
private:
    void* memory;
public:
    Ram(int);
    Ram();
    ~Ram();

    void* getMemory();
};



