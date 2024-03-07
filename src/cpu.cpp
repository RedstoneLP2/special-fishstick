#include "common.h"

Cpu::Cpu(MemoryManager SystemRam, ioHandler* io){
    cpuRegisters = Registers();
    systemRam = SystemRam;
    Opcode_Length = 0;
    iohandler = io;
    reset();
}

Cpu::~Cpu(){
    //cpuRegisters.~Registers();
}

void Cpu::reset(){
    std::string upper = std::bitset<8>(*(systemRam.GetMemoryLocation(0xFFFC))).to_string();
    std::string lower = std::bitset<8>(*(systemRam.GetMemoryLocation(0xFFFD))).to_string();
    std::bitset<16> resetvector (lower+upper);
    //std::cout << resetvector.to_string()<<std::endl;
    cpuRegisters.ProgramCounter = resetvector.to_ulong();
    cpuRegisters.StackPointer = 0xFF;
    //processorstatus reset!
    for (size_t i = 0; i < 8; i++)
    {
        if (i == ProcessorStatusFlags.Unused){
            if (!cpuRegisters.ProcessorStatus.test(i))
            {
                cpuRegisters.ProcessorStatus[i].flip();
            }
        }else if (cpuRegisters.ProcessorStatus.test(i))
        {
            cpuRegisters.ProcessorStatus[i].flip();
        }
    }
    cpuRegisters.Accumulator = 0;
    cpuRegisters.XIndex = 0;
    cpuRegisters.YIndex = 0;

}

void Cpu::run(){
    sleep(SPEED);
    if (Opcode_Length>0){
        Opcode_Length--;
        return;
    }
    uint8_t opcode = *((uint8_t*)systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter));
    /*
    std::cout<<"opcode: "<<std::setfill('0')<<std::setw(2)<<std::hex<<std::bitset<8>(opcode).to_ulong()<<std::endl;
    std::cout<<"parameter01: "<<std::setfill('0')<<std::setw(2)<<std::hex<<std::bitset<8>(*(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1))).to_ulong()<<std::endl;
    std::cout<<"parameter02: "<<std::setfill('0')<<std::setw(2)<<std::hex<<std::bitset<8>(*(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+2))).to_ulong()<<std::endl;
    */
    //                      0x 1    6
    //                      0b 0001 0110
    //
    //  Adrressing mode     0b 1010 0000
    //                      0b 0000 0101
    //                      0b 101
    //std::bitset<16> opcode (opcode);
    switch (opcode)
    {// special cases!
    case uint8_t(0x20):
        jsr(getOperantBytes());
        Opcode_Length+=6;
        break;
    case uint8_t(0x60):
        rts();
        Opcode_Length+=6;
        break;
    case uint8_t(0x48):
        pha();
        Opcode_Length+=3;
        break;
    case uint8_t(0x68):
        pla();
        Opcode_Length+=4;
        break;
    case uint8_t(0xD0):
        bne(*(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1)));
        Opcode_Length+=2;
        break;
    case uint8_t(0x3a):
        dec(&cpuRegisters.Accumulator);
        break;
    default:
        {
        std::bitset<3> addressingMode ((opcode<<3)>>5);
        std::bitset<2> instructionGroup ((opcode<<6)>>6);
        std::bitset<3> instruction ((opcode>>5));
        uint8_t* address;
        // Opcode addresss
        if (instructionGroup==std::bitset<2>(0b01))
        {
            switch (addressingMode.to_ulong())
            {
            case ulong(0x00):   // (Zeropage,X)
                // TODO: (Zeropage, X)
                break;
            case ulong(0x01):   // Zeropage
                // TODO: Zeropage
                break;
            case ulong(0x02):   // Immediate
                address = (systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1));
            {
                uint8_t value = *address;
            }
                cpuRegisters.ProgramCounter+=1;
                Opcode_Length+=2;
                break;
            case ulong(0x03):   // Absolute
                address = (systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1));
                cpuRegisters.ProgramCounter+=2;
                Opcode_Length+=4;
                break;
            case ulong(0x04):   // (Zeropage), Y
                // TODO: (Zeropage), Y
                break;
            case ulong(0x05):   // Zeropage, X
                // TODO: Zeropage, X
                break;
            case ulong(0x06):   // Absolute, Y
                address = (systemRam.GetMemoryLocation(getOperantBytes()+cpuRegisters.YIndex));
                cpuRegisters.ProgramCounter+=2;
                Opcode_Length+=4;
                break;
            case ulong(0x07):   // Absolute, X
                address = (systemRam.GetMemoryLocation(getOperantBytes()+cpuRegisters.XIndex));
                cpuRegisters.ProgramCounter+=2;
                Opcode_Length+=4;
                break;
            default:
                break;
            }
        }else if (instructionGroup==std::bitset<2>(0b10) or instructionGroup==std::bitset<2>(0b00))
        {
            switch (addressingMode.to_ulong())
            {
            case ulong(0x00):   // immediate
                address = (systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1));
                break;
            case ulong(0x01):   // Zeropage
                // TODO: Zeropage
                break;
            case ulong(0x02):   // accumulator
                address = &cpuRegisters.Accumulator;
                break;
            case ulong(0x03):   // Absolute
                address = (systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1));
                cpuRegisters.ProgramCounter+=2;
                Opcode_Length+=4;
                break;
            case ulong(0x05):   // Zeropage, X
                // TODO: Zeropage, X
                break;
            case ulong(0x07):   // Absolute, X
                address = (systemRam.GetMemoryLocation(getOperantBytes()+cpuRegisters.XIndex));
                cpuRegisters.ProgramCounter+=2;
                Opcode_Length+=4;
                break;
            default:
                ulong test = addressingMode.to_ulong();
                break;
            }
        }

        // Opcodes
        if (instructionGroup==std::bitset<2>(0b01))
        {
        switch (instruction.to_ulong())
            {
            case ulong(0x00):   // ORA
                ora((uint8_t*) address);
                break;
            case ulong(0x01):   // AND
                and_(*address);
                break;
            case ulong(0x02):   // EOR
                eor_(*address);
                break;
            case ulong(0x03):   // ADC
                adc((uint8_t*)address);
                break;
            case ulong(0x04):   // STA
            {
                uint16_t test = *((uint16_t*) address);
                sta(*((uint16_t*) address));
                break;
            }
            case ulong(0x05):   // LDA
                lda(*address);
                break;
            case ulong(0x06):   // CMP
                cmp((uint8_t*)address);
                break;
            case ulong(0x07):   // SBC
                sbc((uint8_t*)address);
                break;
            default:
                break;
            }
        }else if (instructionGroup==std::bitset<2>(0b10))
        {
            switch (instruction.to_ulong())
            {
            case ulong(0x00):   // ASL
                asl(address);
                break;
            case ulong(0x01):   // ROL
                rol(address);
                break;
            case ulong(0x02):   // LSR
                lsr(address);
                break;
            case ulong(0x03):   // ROR
                ror(address);
                break;
            case ulong(0x04):   // STX
                stx(*((uint16_t*) address));
                break;
            case ulong(0x05):   // LDX
                ldx(*address);
                break;
            case ulong(0x06):   // DEC
                dec(address);
                break;
            case ulong(0x07):   // INC
                inc(address);
                break;
            default:
                break;
            }
        }else if (instructionGroup==std::bitset<2>(0b00))
        {
            switch (instruction.to_ulong())
            {
            case ulong(0x01):   // BIT
                bit((uint8_t*)address);
                break;
            case ulong(0x02):   // JMP
                jmp((uint16_t)*address);
                break;
            case ulong(0x03):   // JMP (abs)
                jmp(*(uint16_t*)address);
                break;
            case ulong(0x04):   // STY
                sty(*((uint16_t*) address));
                break;
            case ulong(0x05):   // LDY
                ldy(*address);
                break;
            case ulong(0x06):   // CPY
                cpy((uint8_t*)address);
                break;
            case ulong(0x07):   // CPX
                cpx((uint8_t*)address);
                break;
            default:
                break;
            }
        }
    }
        break;
    }

/*
    switch (opcode)
    {
    case uint8_t(0xAD):
        {
            uint16_t* address = (uint16_t*)systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1);
            char value = *address;
            lda(value);
            cpuRegisters.ProgramCounter++;
            cpuRegisters.ProgramCounter++;
            Opcode_Length=4;
        }
        break;
    case uint8_t(0xA9):
        {
            //char value = *(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1));
            lda(value);
            cpuRegisters.ProgramCounter++;
            Opcode_Length=2;
        }
        break;
    case uint8_t(0xAE):
        ldx(value);
        Opcode_Length=4;
        break;
    case uint8_t(0xA0):
        ldy(*(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1)));
        Opcode_Length=2;
        cpuRegisters.ProgramCounter++;
        break;
    case uint8_t(0x8D):
        sta(getOperantBytes());
        cpuRegisters.ProgramCounter++;
        cpuRegisters.ProgramCounter++;
        Opcode_Length=5;
        break;
    case uint8_t(0x85):
        sta(0x0000+(uint8_t) *(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1)));
        cpuRegisters.ProgramCounter++;
        Opcode_Length=4;
        break;
    case uint8_t(0x99):
        sta(getOperantBytes()+cpuRegisters.YIndex);
        cpuRegisters.ProgramCounter++;
        cpuRegisters.ProgramCounter++;
        Opcode_Length=5;
        break;
    case uint8_t(0xb9):
        lda(getOperantBytes()+cpuRegisters.YIndex);
        cpuRegisters.ProgramCounter++;
        cpuRegisters.ProgramCounter++;
        Opcode_Length=4;
        break;
    case uint8_t(0x8E):
        stx(getOperantBytes());
        cpuRegisters.ProgramCounter++;
        cpuRegisters.ProgramCounter++;
        Opcode_Length=5;
        break;
    case uint8_t(0x8C):
        sty(getOperantBytes());
        cpuRegisters.ProgramCounter++;
        cpuRegisters.ProgramCounter++;
        Opcode_Length=5;
        break;
    case uint8_t(0x20):
        {
            uint16_t value = getOperantBytes();
            //std::cout<<"value "<<std::setfill('0')<<std::setw(4)<<std::hex<<std::bitset<16>(value).to_ulong()<<std::endl;
            jsr(value);
            Opcode_Length=6;
        }
        break;
    case uint8_t(0x60):
        {
            rts();
            Opcode_Length=6;
        }
        break;
    case uint8_t(0x29):
        {
            char value = *(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1));
            and_(value);
            cpuRegisters.ProgramCounter++;
            Opcode_Length=2;
        }
    case uint8_t(0x49):
        {
            char value = *(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1));
            eor_(value);
            cpuRegisters.ProgramCounter++;
            Opcode_Length=2;
        }
    case uint8_t(0x48):
        pha();
        Opcode_Length=3;
        break;
    case uint8_t(0x68):
        pla();
        Opcode_Length=4;
        break;
    case uint8_t(0x3A):
        dec();
        Opcode_Length=2;
        break;
    case uint8_t(0x88):
        dey();
        Opcode_Length=2;
        break;
    case uint8_t(0xc8):
        iny();
        Opcode_Length=2;
        break;
    case uint8_t(0xD0):
        {
            int8_t value = *(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1));
            bne(value);
            Opcode_Length=2;
        }
        break;
    case uint8_t(0xf0):
        {
            int8_t value = *(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1));
            beq(value);
            Opcode_Length=2;
        }
        break;
    case uint8_t(0x10):
        {
            int8_t value = *(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1));
            bpl(value);
            Opcode_Length=2;
        }
        break;
    case uint8_t(0x90):
        {
            int8_t value = *(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1));
            bcc(value);
            Opcode_Length=2;
        }
        break;
    case uint8_t(0x30):
        {
            int8_t value = *(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1));
            bmi(value);
            Opcode_Length=2;
        }
        break;
    case uint8_t(0x4c):
        {
            jmp(getOperantBytes());
            Opcode_Length=3;
            break;
        }
    case uint8_t(0xd8):
        cld();
        Opcode_Length=2;
        break;
    case uint8_t(0x58):
        cli();
        Opcode_Length=2;
        break;
    case uint8_t(0xC9):
        {
            int8_t value = *(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1));
            cmp(value);
            Opcode_Length=2;
            cpuRegisters.ProgramCounter++;
        }
        break;
    case uint8_t(0xAA):
        tax();
        Opcode_Length=2;
        break;
    case uint8_t(0x0A):
        asl((uint8_t*)value);
        Opcode_Length=2;
        break;
    default:
        std::string error = std::format("Unimplemented Instruction: %x\n",opcode);
        (*iohandler).printString(error);
        //std::cout<< "Unimplemented Instruction: "<< std::setfill ('0') << std::setw(2) << std::hex<<std::bitset<8>(opcode).to_ulong() << std::endl;
        //printRegisters();
        break;
    }
*/
    cpuRegisters.ProgramCounter++;
}

uint16_t Cpu::getOperantBytes(){
        std::string upper = std::bitset<8>(*(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1))).to_string();
        std::string lower = std::bitset<8>(*(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+2))).to_string();
        std::bitset<16>value(lower+upper);
        return (uint16_t)value.to_ulong();
}

void Cpu::printRegisters(){
    (*iohandler).printDebugString(cpuRegisters.toString());
}

void Cpu::printMemoryLocation(int memoryLocation){
    // 0x5000 - 0x5010
    
    uint8_t* baseAddress = (systemRam.GetMemoryLocation(memoryLocation));
    std::cout<< "     00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F"<<std::endl;
    std::cout << std::setfill('0')<<std::setw(4) << std::hex << memoryLocation<< " ";
    for (uint8_t* address = baseAddress; address <= baseAddress+0x0F; address++){
        std::cout << std::setfill ('0') << std::setw(2) << std::hex<<std::bitset<8>(*address).to_ulong()<< " ";
    }
    std::cout<<std::endl;
}

void Cpu::setStatusFlag(unsigned Flag){
    if (!cpuRegisters.ProcessorStatus.test(Flag))
    {
        cpuRegisters.ProcessorStatus[Flag].flip();
    }
}
void Cpu::unSetStatusFlag(unsigned Flag){
    if (cpuRegisters.ProcessorStatus.test(Flag))
    {
        cpuRegisters.ProcessorStatus[Flag].flip();
    }
}

void Cpu::ora(uint8_t* value){

}

void Cpu::adc(uint8_t* value){

}

void Cpu::sbc(uint8_t* value){
    
}

void Cpu::rol(uint8_t* value){
    
}

void Cpu::lsr(uint8_t* value){
    
}

void Cpu::ror(uint8_t* value){
    
}

void Cpu::bit(uint8_t* value){
    
}

void Cpu::cpy(uint8_t* value){
    
}

void Cpu::cpx(uint8_t* value){
    
}

void Cpu::cmp(uint8_t* value){
    if (cpuRegisters.Accumulator == *value){
        setStatusFlag(ProcessorStatusFlags.Zero);
    }
    if (cpuRegisters.Accumulator < *value){
        setStatusFlag(ProcessorStatusFlags.Negative);
    }
    if (cpuRegisters.Accumulator >= *value){
        setStatusFlag(ProcessorStatusFlags.Carry);
    }
}

void Cpu::and_(uint8_t immediate){
    cpuRegisters.Accumulator = immediate & cpuRegisters.Accumulator;
}

void Cpu::eor_(uint8_t immediate){
    cpuRegisters.Accumulator = immediate ^ cpuRegisters.Accumulator;
    if (cpuRegisters.Accumulator){
        unSetStatusFlag(ProcessorStatusFlags.Zero);
    }else{
        setStatusFlag(ProcessorStatusFlags.Zero);
    }

    if(cpuRegisters.Accumulator>>7){
        setStatusFlag(ProcessorStatusFlags.Negative);
    }else{
        unSetStatusFlag(ProcessorStatusFlags.Negative);
    }
}

void Cpu::lda(uint8_t immediate){
    cpuRegisters.Accumulator = immediate;
}
void Cpu::ldx(uint8_t immediate){
    cpuRegisters.XIndex = immediate;
}
void Cpu::ldy(uint8_t immediate){
    cpuRegisters.YIndex = immediate;
}

void Cpu::sta(uint16_t address){
    systemRam.writeMem(address, cpuRegisters.Accumulator);
}

void Cpu::stx(uint16_t address){
    systemRam.writeMem(address, cpuRegisters.XIndex);
}
void Cpu::sty(uint16_t address){
    systemRam.writeMem(address, cpuRegisters.YIndex);
}

void Cpu::bne(int8_t relAddress){
    if (cpuRegisters.Accumulator != 0){
        Opcode_Length++;
        jmp(relAddress);
    }else{
        cpuRegisters.ProgramCounter++;
    }
}

void Cpu::bcc(int8_t relAddress){
    if (cpuRegisters.ProcessorStatus.test(ProcessorStatusFlags.Carry) != 0){
        Opcode_Length++;
        jmp(relAddress);
    }else{
        cpuRegisters.ProgramCounter++;
    }
}

void Cpu::beq(int8_t relAddress){
    if (cpuRegisters.ProcessorStatus.test(ProcessorStatusFlags.Zero)){
        Opcode_Length++;
        jmp(relAddress);
    }else{
        cpuRegisters.ProgramCounter++;
    }
}

void Cpu::bpl(int8_t relAddress){
    if (!cpuRegisters.ProcessorStatus.test(ProcessorStatusFlags.Negative)){
        Opcode_Length++;
        jmp(relAddress);
    }else{
        cpuRegisters.ProgramCounter++;
    }
}

void Cpu::bmi(int8_t relAddress){
    if (cpuRegisters.ProcessorStatus.test(ProcessorStatusFlags.Negative)){
        Opcode_Length++;
        jmp(relAddress);
    }else{
        cpuRegisters.ProgramCounter++;
    }
}

void Cpu::jmp(int8_t relAddress){
    cpuRegisters.ProgramCounter = relAddress+cpuRegisters.ProgramCounter+1;
}
void Cpu::jmp(uint16_t address){
    cpuRegisters.ProgramCounter = address-1;
}

void Cpu::dec(uint8_t* PValue){
    (*PValue)--;
}

void Cpu::dey(){
    cpuRegisters.YIndex--;
    if (!cpuRegisters.YIndex){
        setStatusFlag(ProcessorStatusFlags.Zero);
    }else{
        unSetStatusFlag(ProcessorStatusFlags.Zero);
    }
    if (cpuRegisters.YIndex>>7){
        setStatusFlag(ProcessorStatusFlags.Negative);
    }else{
        unSetStatusFlag(ProcessorStatusFlags.Negative);
    }
}

void Cpu::iny(){
    cpuRegisters.YIndex++;
}

void Cpu::inc(uint8_t* pValue){
    pValue++;
}


void Cpu::jsr(uint16_t address){
    cpuRegisters.ProgramCounter += 3;

    uint8_t lower_byte = (uint8_t) cpuRegisters.ProgramCounter;
    uint8_t upper_byte = (uint8_t) (cpuRegisters.ProgramCounter  >> 8);

    uint16_t stackAddress = 0x0100+cpuRegisters.StackPointer;
    systemRam.writeMem(stackAddress, upper_byte);
    cpuRegisters.StackPointer--;

    stackAddress = 0x0100+cpuRegisters.StackPointer;
    systemRam.writeMem(stackAddress, lower_byte);
    cpuRegisters.StackPointer--;

    /*
    std::cout<< "jumping from: " <<std::hex<< cpuRegisters.ProgramCounter<<std::endl;
    std::cout<< "jumping to: " <<std::hex<< address<<std::endl;
    */
    jmp(address);
}

void Cpu::rts(){

    cpuRegisters.StackPointer++;
    uint16_t stackAddress = 0x0100+cpuRegisters.StackPointer;
    //std::cout<< "StackAddress: " <<std::setfill('0')<<std::setw(4)<<std::hex<< std::bitset<16>(stackAddress).to_ulong()<<std::endl;
    uint8_t lower_byte = *systemRam.GetMemoryLocation(stackAddress);
    cpuRegisters.StackPointer++;

    stackAddress = 0x0100+cpuRegisters.StackPointer;
    //std::cout<< "StackAddress: " <<std::setfill('0')<<std::setw(4)<<std::hex<< std::bitset<16>(stackAddress).to_ulong()<<std::endl;
    uint8_t upper_byte = *systemRam.GetMemoryLocation(stackAddress);
    uint16_t returnAddress = (((uint16_t)upper_byte) << 8)+lower_byte;
    //std::cout<< "jumping to: " <<std::setfill('0')<<std::setw(4)<<std::hex<<std::bitset<16>(returnAddress).to_ulong()<<std::endl;
    jmp(returnAddress);
}

void Cpu::clc(){
    if (cpuRegisters.ProcessorStatus.test(0))
    {
        cpuRegisters.ProcessorStatus[0].flip();
    }
}
void Cpu::cld(){
    if (cpuRegisters.ProcessorStatus.test(3))
    {
        cpuRegisters.ProcessorStatus[3].flip();
    }
}
void Cpu::cli(){
    if (cpuRegisters.ProcessorStatus.test(2))
    {
        cpuRegisters.ProcessorStatus[2].flip();
    }
}
void Cpu::clv(){
    if (cpuRegisters.ProcessorStatus.test(6))
    {
        cpuRegisters.ProcessorStatus[6].flip();
    }
}

void Cpu::pha(){
    uint16_t stackAddress = 0x0100+cpuRegisters.StackPointer;
    systemRam.writeMem(stackAddress, cpuRegisters.Accumulator);
    cpuRegisters.StackPointer--;
}

void Cpu::pla(){
    cpuRegisters.StackPointer++;
    uint16_t stackAddress = 0x0100+cpuRegisters.StackPointer;
    //std::cout<< "StackAddress: " <<std::setfill('0')<<std::setw(4)<<std::hex<< std::bitset<16>(stackAddress).to_ulong()<<std::endl;
    cpuRegisters.Accumulator = *systemRam.GetMemoryLocation(stackAddress);
}

void Cpu::tax(){
    cpuRegisters.StackPointer++;
    cpuRegisters.XIndex = cpuRegisters.Accumulator;
}

void Cpu::asl(uint8_t* pValue){
    cpuRegisters.StackPointer++;

    uint8_t carry = ((*pValue>>7)&1);

    if (carry){
        setStatusFlag(ProcessorStatusFlags.Carry);
    }else{
        unSetStatusFlag(ProcessorStatusFlags.Carry);
    }

    uint8_t shifted = (uint8_t) (*pValue  << 1);
    if (shifted){
        unSetStatusFlag(ProcessorStatusFlags.Zero);
    }else{
        setStatusFlag(ProcessorStatusFlags.Zero);
    }

    if(shifted>>7){
        setStatusFlag(ProcessorStatusFlags.Negative);
    }else{
        unSetStatusFlag(ProcessorStatusFlags.Negative);
    }
    *pValue = shifted;

}