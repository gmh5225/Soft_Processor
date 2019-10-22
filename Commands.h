
CMD_COMPARE (Push, 16,
    {
    if (bytecode[PC + 1] == NUMBER) // arg is immediate constant
        {
        StackPush (&CPU->stk, bytecode[PC + 2]);
        PC_MOVE ('i');
        break;
        }

    if (bytecode[PC + 1] == REGISTER) // arg is register
        {
        Dump (&CPU->stk);
        CPU->CR[bytecode[PC + 2] - 'a'] = StackPop(&CPU->stk);
        Dump (&CPU->stk);

        PC_MOVE ('c');
        }

    break;
    })

CMD_COMPARE (Pop, 17,
    {
    if (bytecode [PC + 1] == NOTHING){
        StackPop(&CPU->stk);
        PC_MOVE('c');
        break;
    }
    if (bytecode [PC + 1] == REGISTER)
       StackPush(&CPU->stk, CPU->CR[bytecode[PC + 2] - 'a']);
       PC_MOVE('c');
       break;
    })

CMD_COMPARE(Add, 18,
{
    StackPush(&CPU->stk, StackPop(&CPU->stk) + StackPop(&CPU->stk));
    PC_MOVE('c');
    break;
})

CMD_COMPARE(Sub, 19,
    {
    StackPush(&CPU->stk, -StackPop(&CPU->stk) + StackPop(&CPU->stk));
    PC_MOVE('c');
    break;
    })

CMD_COMPARE(Mul, 20,
    {
    StackPush(&CPU->stk, StackPop(&CPU->stk) * StackPop(&CPU->stk));
    PC_MOVE('c');
    break;
    })

CMD_COMPARE(Div, 21,
    {int temp1 = StackPop(&CPU->stk);
    int temp2 = StackPop(&CPU->stk);
    StackPush(&CPU->stk, temp2 / temp1);
    PC_MOVE('c');
    break;
    })

CMD_COMPARE(Sqrt, 22,
    {
    StackPush(&CPU->stk, sqrt(StackPop(&CPU->stk)));
    PC_MOVE('c');
    break;
    })

CMD_COMPARE(Sin, 23,
    {
    StackPush(&CPU->stk, sin(StackPop(&CPU->stk)));
    PC_MOVE('i');
    break;
    })
CMD_COMPARE(Cos, 24,
    {
    StackPush(&CPU->stk, cos(StackPop(&CPU->stk)));
    PC_MOVE('i');
    break;
    })
CMD_COMPARE(Out, 25,
    {
    printf("The answer is \"%d\"\n", StackPop(&CPU->stk));
    PC_MOVE('c');
    break;
    })


CMD_COMPARE(End, -1,
    {
    return;
    })




