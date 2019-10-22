#ifndef PROCESSOR_PROCESSOR_H
#define PROCESSOR_PROCESSOR_H

#include <cassert>
#include <cmath>
#include "Stack.h"



const char Input_File[] = "/Users/albatraozrus/Desktop/Output_File.txt";

#define PC_MOVE(Mode) {\
if (Mode == 'i')\
PC += 2 * sizeof(char) + sizeof(int);\
if (Mode == 'c')\
PC += 3 * sizeof(char);}

struct MYCPU {
    MyStack_t stk;

    int CR[4] = {};
};

enum Register {
    RAX = 'a',
    RBX = 'b',
    RCX = 'c',
    RDX = 'd'
};
enum Specs{
    NUMBER   = 1,
    REGISTER = 2,
    NOTHING  = 3,
};

void CPU_Reader (char *bytecode, MyStack_t *stk, MYCPU *CPU);
char * Reading(size_t *amount);
size_t CounterOfLines(char *buffer, long size);
size_t CounterOfSymbols(FILE * readfile);

#endif //PROCESSOR_PROCESSOR_H
