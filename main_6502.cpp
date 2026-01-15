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

    void Reset(Mem & memory){ 
        PC=0xFFFC;
        SP=0x0100;
        D=0;
        A=X=Y=0;
        C=Z=I=D=B=V=N=0;
        memory.initilize();
    }


    Byte FetchByte(u32 & Cycles, Mem & memory){
        Byte Data=memory[PC];
        PC ++;
        Cycles --;
        return Data;
    }

    static constexpr Byte INS_LDA_IM=0xA9;

    void Excute(u32 Cycles,Mem & memory){
         while(Cycles > 0){
            Byte Ins=FetchByte(Cycles,memory);

            switch(Ins){
                case INS_LDA_IM:
                {
                    Byte value=FetchByte(Cycles,memory);
                    A=value;
                    Z=(A==0);
                    N=(A & 0b10000000)>0;
                    break;
                }
                default:
                    std::cout<<"There is problem on excuting the ilnstruction"<<" "<<Ins;
                    break;

            }
         }
    }

};


int main() {
   CPU cpu;
   Mem mem;
   cpu.Reset(mem);
   cpu.Excute(2,mem);
    return 0;
}