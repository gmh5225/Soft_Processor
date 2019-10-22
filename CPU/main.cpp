#include "Processor.h"

int main() {

    printf("Welcome to the CPU\n");
    printf("Processing...\n");
    char *buffer = nullptr;
    size_t amount = 0;
    buffer = Reading(&amount);

    MYCPU CPU = {};

    StackConstruct(&CPU.stk);

    CPU_Reader(buffer, &CPU.stk, &CPU);
    printf("Program finished successfully!\n");

    StackDestruct(&CPU.stk);

    return 0;
}
