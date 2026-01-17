#include<iostream>
#include<stdlib.h>



using Byte=unsigned char;
using Word =unsigned short; 
using u32=unsigned int;

struct Mem
{
    static constexpr u32 MAX_MEM=1024*64;
    Byte Data[MAX_MEM];     //Memory size is 64kb

    void initilize(){ 
        for(u32 i=0;i<MAX_MEM;i++){
            Data[i]=0;
        }
    }


    // Read the 1 byte
    Byte operator [] (u32 Address) const {
        return Data[Address];
    }

    void WriteWord(u32 &Cycles,Word Value,u32 Address){
        Data[Address]=Value & 0xFF;
        Data[Address +1]=(Value>>8);
        Cycles -=2;
    }

};

struct CPU
{

    Word PC; //Program counter = 16 bit 
    Word SP;

    Byte A,X,Y; //8 bit Register


    //flags
    Byte C : 1;  // Carry
    Byte Z : 1;  // Zero
    Byte I : 1;  // Interrupt Disable
    Byte D : 1;  // Decimal
    Byte B : 1;  // Break
    Byte V : 1;  // Overflow
    Byte N : 1;  // Negative
    
    Word FetchWord(u32 & Cycles, Mem& memory){
    Word Data = memory[PC];
    PC++;
    Cycles--;

    Data |= (memory[PC] << 8);
    PC++;
    Cycles--;

    return Data;
    }



    //Instruction up code 
    static constexpr Byte INS_LDA_IM=0xA9,INS_LDA_ZP=0xA5,INS_LDA_ZPX=0xB5,INS_JSR=0x20;

    void Reset(Mem & memory){ 
        PC=0xFFFC;
        SP=0x0100;
        D=0;
        A=X=Y=0;
        C=Z=I=D=B=V=N=0;
        memory.initilize();
    }


    void LDASetStatus(){
        Z=(A==0);
        N=(A & 0b10000000)>0;
    }

    Byte FetchByte(u32 & Cycles, Mem & memory){
        Byte Data=memory[PC];
        PC ++;
        Cycles --;
        return Data;
    }
    
    Byte ReadByte(u32 & Cycles,Byte& Address, Mem & memory){
        Byte Data=memory[Address];
        Cycles --;
        return Data;
    }

    void Excute(u32 Cycles,Mem & memory){
         while(Cycles > 0){
            Byte Ins=FetchByte(Cycles,memory);

            switch(Ins){
                case INS_LDA_IM:
                {
                    Byte value=FetchByte(Cycles,memory);
                    A=value;
                    LDASetStatus();
                    break;
                }
                case INS_LDA_ZP:
                {
                    Byte ZeroPageAddress=FetchByte(Cycles,memory);
                    A= ReadByte(Cycles,ZeroPageAddress,memory);
                    LDASetStatus();
                    break;
                }
                case INS_LDA_ZPX:
                {
                    Byte ZeroPageAddress=FetchByte(Cycles,memory);
                    ZeroPageAddress +=X;
                    Cycles--;
                    Byte A= ReadByte(Cycles,ZeroPageAddress,memory);
                    LDASetStatus();
                    break;
                }
                case INS_JSR:
                {
                   Word SubAddr= FetchWord(Cycles,memory);
                    memory.WriteWord(Cycles,PC-1,SP);
                    PC=SubAddr;
                   Cycles --;
                   break;
                }
                default:
                    std::cout<<"There is problem on excuting the instruction"<<" "<<Ins;
                    break;
            }
         }
    }

};



int main() {
    CPU cpu;
    Mem mem;

    cpu.Reset(mem);

    mem.Data[0xFFFC] = 0x00;
    mem.Data[0xFFFD] = 0x80;

    u32 i = 0x8000;

    mem.Data[i++] = CPU::INS_LDA_IM;
    mem.Data[i++] = 0x05;

    mem.Data[i++] = CPU::INS_JSR;
    mem.Data[i++] = 0x06;
    mem.Data[i++] = 0x80;

    mem.Data[0x8006] = CPU::INS_LDA_IM;
    mem.Data[0x8007] = 0x0A;

    cpu.PC = mem[0xFFFC] | (mem[0xFFFD] << 8);

    cpu.Excute(10, mem);

    std::cout << "A = " << (int)cpu.A << std::endl;
    std::cout << "PC = 0x" << std::hex << cpu.PC << std::endl;

    return 0;
}
