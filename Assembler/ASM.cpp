#include "ASM.h"

int Assembler (char *bytecode, size_t *amount)
{
    struct Line *ptrstruct = Reading(amount);
    DeleteComments(ptrstruct, *amount);

    auto *Command = (char*) calloc(4, sizeof(char));
    char Command_Number = -2;
    int PC = 0;
    int Param = Poison;
    struct Marks Labels;
    Labels.NameLabel = (char*) calloc(15, sizeof(char));


    for (int NumberOfLine = 0; Command_Number != -1 && NumberOfLine <*amount ; NumberOfLine++){

        LocateLabels(ptrstruct, NumberOfLine, &Labels);

        if (Labels.NameLabel != nullptr)
            Labels.Address = PC;
        PC++;

        ScanCommand(Command, ptrstruct, NumberOfLine);

        if (PassTrash(Command))
            continue;

        FullBytecode(&PC, bytecode, &Command_Number, Command, NumberOfLine, ptrstruct, &Param);
    }

    free(Command);
    return PC;
}

char WhichCommand (char *Command)
{
    assert(Command!= nullptr);

  #define CMD_COMPARE(name, num, processor) \
    { if (strcasecmp(Command, #name) == 0)\
    return num;\
    }
#include "Commands.h"

#undef COMMANDS
#undef CMD_COMPARE

    return ErrorWhichCommand;
}


void DeleteComments (struct Line *ptrstruct, size_t amount)
{
    char *temp = nullptr;

    for (int NumberOfLine = 0; NumberOfLine < amount; NumberOfLine++) {
        if ((temp = strchr(ptrstruct[NumberOfLine].ptrbuffer, ';')) != nullptr)
            *temp = '\0';
    }
}

bool PassTrash(char *Command)
{
    return strlen(Command) == 0;
}

bool ScanCommand (char *Command, struct Line *ptrstruct, int NumberOfLine)
{
    *Command = 0;
    sscanf(ptrstruct[NumberOfLine].ptrbuffer, "%s", Command);

    return true;
}

int WhichSpec (struct Line *ptrstruct, int NumberOfLine)
{
    int Letter = 0;
    while (isalpha(ptrstruct[NumberOfLine].ptrbuffer[Letter]))
        Letter++;
    if (isnumber(ptrstruct[NumberOfLine].ptrbuffer[Letter + 1]))
        return 1;
    if (isalpha(ptrstruct[NumberOfLine].ptrbuffer[Letter + 1]) &&
                ptrstruct[NumberOfLine].ptrbuffer[Letter] == ' ')
        return 2;
    return 3;
}

void ScanParam (int Spec, struct Line *ptrstruct, int NumberOfLine, int *Param, int *PC, char *bytecode)
{
    switch (Spec){
        case 1: {sscanf(ptrstruct[NumberOfLine].ptrbuffer, "%*s %d",        Param);
                *(int*)(bytecode + *PC) = *Param; printf("%d ", bytecode[*PC]);*PC += sizeof(int);  break;}
        case 2: {sscanf(ptrstruct[NumberOfLine].ptrbuffer, "%*s %c", (char*)Param);
                *(bytecode + *PC) = *(char*)Param;       printf("%d ", bytecode[*PC]);*PC += sizeof(char); break;}
        case 3: {                                 *PC += sizeof(char); break;}

        default: break;
    }
}

void FullBytecode (int *PC, char *bytecode, char *Command_Number, char *Command,
                   int NumberOfLine, struct Line *ptrstruct, int *Param)
{
    *Command_Number = WhichCommand(Command);
    bytecode[*PC] = *Command_Number;
    printf("%d ", bytecode[*PC]);
    *PC += sizeof(char);
    bytecode[*PC] =  (char) WhichSpec(ptrstruct, NumberOfLine);
    printf("%d ", bytecode[*PC]);
    //printf("SPEC IS %d\n", bytecode[*PC]);
    *PC += sizeof(char);
    *Param = Poison;
    ScanParam (bytecode[*PC - 1],ptrstruct, NumberOfLine, Param, PC, bytecode);
    //printf("PARAM IS %d\n", bytecode[*PC]);
}

void LocateLabels(struct Line *ptrstruct, int NumberOfLine, struct Marks *Labels)
{
    if (strchr(ptrstruct[NumberOfLine].ptrbuffer, ':') == nullptr)
        return;

    int Letter = 0;
    while (isalpha(ptrstruct[NumberOfLine].ptrbuffer[Letter]))
        Letter++;
    strncpy(ptrstruct[NumberOfLine].ptrbuffer, Labels->NameLabel, (size_t) Letter);

}
