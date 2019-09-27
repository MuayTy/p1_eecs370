/**
 * Project 1
 * EECS 370 LC-2K Instruction-level simulator
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUMMEMORY 65536 /* maximum number of words in memory */
#define NUMREGS 8 /* number of machine registers */
#define MAXLINELENGTH 1000

//opcodes
#define ADD     0b000
#define NOR     0b001
#define LW      0b010
#define SW      0b011
#define BEQ     0b100
#define JALR    0b101
#define HALT    0b110
#define NOOP    0b111

typedef struct stateStruct {
    int pc;
    int mem[NUMMEMORY];
    int reg[NUMREGS];
    int numMemory;
} stateType;

void printState(stateType *);
int convertNum(int);

int
main(int argc, char *argv[])
{
    char line[MAXLINELENGTH];
    stateType state;
    FILE *filePtr;

    if (argc != 2) {
        printf("error: usage: %s <machine-code file>\n", argv[0]);
        exit(1);
    }

    filePtr = fopen(argv[1], "r");
    if (filePtr == NULL) {
        printf("error: can't open file %s", argv[1]);
        perror("fopen");
        exit(1);
    }

    

    /* read the entire machine-code file into memory */
    for (state.numMemory = 0; fgets(line, MAXLINELENGTH, filePtr) != NULL;
            state.numMemory++) {

        if (sscanf(line, "%d", state.mem+state.numMemory) != 1) {
            printf("error in reading address %d\n", state.numMemory);
            exit(1);
        }
        printf("memory[%d]=%d\n", state.numMemory, state.mem[state.numMemory]);
    }

        //init variables
    state.pc = 0;
    state.reg = {0,0,0,0,0,0,0,0};

        //perform instructions
    while (state.pc < state.numMemory) {
        printState(state);

        int opcode = state.mem[state.pc] >> 21;

        printf("opcode = %i",opcode);

        //check opcode
        if (opcode == ADD) {
            printf("performing add\n");
            int regA = (state.mem[state.pc] << 10) >> 29;
            int regB = (state.mem[state.pc] << 13) >> 29;
            int dest = (state.mem[state.pc] << 29) >> 29;

            //add contents of regA with contents of regB and store result in dest
            state.reg[dest] = state.reg[regA] + state.reg[regB];
        }
        else if (opcode == NOR) {
            printf("performing nor\n");
        }
        else if (opcode == LW) {
            printf("performing lw\n");
        }
        else if (opcode == SW) {
            printf("performing sw\n");
        }
        else if (opcode == BEQ) {
            printf("performing beq\n");
        }
        else if (opcode == JALR) {
            printf("performing jalr\n");
        }
        else if (opcode == HALT) {
            printf("performing halt\n");
        }
        else if (opcode == NOOP) {
            printf("performing noop\n");
        }
        else {
            printf("invalid opcode\n");
            exit(1);
        }
        ++state.pc;
    }
    

    return(0);
}

void
printState(stateType *statePtr)
{
    int i;
    printf("\n@@@\nstate:\n");
    printf("\tpc %d\n", statePtr->pc);
    printf("\tmemory:\n");
    for (i=0; i<statePtr->numMemory; i++) {
              printf("\t\tmem[ %d ] %d\n", i, statePtr->mem[i]);
    }
    printf("\tregisters:\n");
    for (i=0; i<NUMREGS; i++) {
              printf("\t\treg[ %d ] %d\n", i, statePtr->reg[i]);
    }
    printf("end state\n");
}

int
convertNum(int num)
{
    /* convert a 16-bit number into a 32-bit Linux integer */
    if (num & (1<<15) ) {
        num -= (1<<16);
    }
    return(num);
}

