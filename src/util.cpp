#include "util.h"
void hello_World(Cpu core){
    core.lda('H');
    core.sta(ushort(0x5000));
    core.lda('e');
    core.sta(ushort(0x5000));
    core.lda('l');
    core.sta(ushort(0x5000));
    core.lda('l');
    core.sta(ushort(0x5000));
    core.lda('o');
    core.sta(ushort(0x5000));
    core.lda(' ');
    core.sta(ushort(0x5000));
    core.lda('W');
    core.sta(ushort(0x5000));
    core.lda('o');
    core.sta(ushort(0x5000));
    core.lda('r');
    core.sta(ushort(0x5000));
    core.lda('l');
    core.sta(ushort(0x5000));
    core.lda('d');
    core.sta(ushort(0x5000));
    core.lda('!');
    core.sta(ushort(0x5000));
    core.lda('\n');
    core.sta(ushort(0x5000));
    //std::cout << "------------"<<std::endl;
    //core.printMemoryLocation(0x5000);
}

void loadfile(char* filename,void* memory){
	FILE *ptr_fp;

	if((ptr_fp = fopen(filename, "rb"))==NULL)
	{
		exit(1);
	}
	fseek(ptr_fp, 0L, SEEK_END);
    int fileSize = ftell(ptr_fp);
    rewind(ptr_fp);

	if(fread(((char*)memory)+(0xFFFF-fileSize)+1, fileSize, 1, ptr_fp) != 1)
	{
		exit( 1 );
	}
	fclose(ptr_fp);
}