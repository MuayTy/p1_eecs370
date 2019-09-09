/**
 * Project 1 
 * Assembler code fragment for LC-2K 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINELENGTH 1000

int readAndParse(FILE *, char *, char *, char *, char *, char *);
int isNumber(char *);

int
main(int argc, char *argv[])
{
    char *inFileString, *outFileString;
    FILE *inFilePtr, *outFilePtr;
    char label[MAXLINELENGTH], opcode[MAXLINELENGTH], arg0[MAXLINELENGTH],
            arg1[MAXLINELENGTH], arg2[MAXLINELENGTH];

    if (argc != 3) {
        printf("error: usage: %s <assembly-code-file> <machine-code-file>\n",
            argv[0]);
        exit(1);
    }

    inFileString = argv[1];
    outFileString = argv[2];

    inFilePtr = fopen(inFileString, "r");
    if (inFilePtr == NULL) {
        printf("error in opening %s\n", inFileString);
        exit(1);
    }
    outFilePtr = fopen(outFileString, "w");
    if (outFilePtr == NULL) {
        printf("error in opening %s\n", outFileString);
        exit(1);
    }
    //first pass: find labels and store address
    int addy[MAXLINELENGTH];
    int i = 0;

    while (readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2)) {

        if (label[0] != '\0') {
            printf("label = %s\n",label);
            strcpy(addy[i],label);
            printf("copy = %s at address %i\n",addy[i],i);
        }
        ++i;
    }

    /* this is how to rewind the file ptr so that you start reading from the
        beginning of the file */
    rewind(inFilePtr);

    //second pass - output ISA as decimal
    while (readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2)) {
        //the first 8 bits are always zeros
        char *binary[MAXLINELENGTH];

        //label
        //instruction
        if (!strcmp(opcode, "add")) {
            char *op_b[MAXLINELENGTH] = "000";

            strcat(binary,op_b);
            printf("add: %s",binary);
        }
        else if (!strcmp(opcode, "nor")) {
            char *op_b[MAXLINELENGTH] = "001";

            strcat(binary,op_b);
            printf("nor: %s",binary);
        }
        else if (!strcmp(opcode, "lw")) {
            char *op_b[MAXLINELENGTH] = "010";

            strcat(binary,op_b);
            printf("lw: %s",binary);
        }
        else if (!strcmp(opcode, "sw")) {
            char *op_b[MAXLINELENGTH] = "011";

            strcat(binary,op_b);
            printf("sw: %s",binary);
        }
        else if (!strcmp(opcode, "beq")) {
            char *op_b[MAXLINELENGTH] = "100";

            strcat(binary,op_b);
            printf("beq: %s",binary);
        }
        else if (!strcmp(opcode, "jair")) {
            char *op_b[MAXLINELENGTH] = "101";

            strcat(binary,op_b);
            printf("jair: %s",binary);
        }
        else if (!strcmp(opcode, "halt")) {
            char *op_b[MAXLINELENGTH] = "110";

            strcat(binary,op_b);
            printf("halt: %s",binary);
        }
        else if (!strcmp(opcode, "noop")) {
            char *op_b[MAXLINELENGTH] = "111";

            strcat(binary,op_b);
            printf("noop: %s",binary);
        }
        else {
            printf("opcode not found");
        }
        //field0
        //field1
        //field2

    }

    return(0);
}

/*
 * Read and parse a line of the assembly-language file.  Fields are returned
 * in label, opcode, arg0, arg1, arg2 (these strings must have memory already
 * allocated to them).
 *
 * Return values:
 *     0 if reached end of file
 *     1 if successfully read
 *
 * exit(1) if line is too long.
 */
int
readAndParse(FILE *inFilePtr, char *label, char *opcode, char *arg0,
        char *arg1, char *arg2)
{
    char line[MAXLINELENGTH];

    /* delete prior values */
    label[0] = opcode[0] = arg0[0] = arg1[0] = arg2[0] = '\0';

    /* read the line from the assembly-language file */
    if (fgets(line, MAXLINELENGTH, inFilePtr) == NULL) {
        /* reached end of file */
        return(0);
    }

    /* check for line too long (by looking for a \n) */
    if (strchr(line, '\n') == NULL) {
        /* line too long */
        printf("error: line too long\n");
        exit(1);
    }

    /* is there a label? */
    char *ptr = line;
    if (sscanf(ptr, "%[^\t\n\r ]", label)) {
        /* successfully read label; advance pointer over the label */
        ptr += strlen(label);
    }

    /*
     * Parse the rest of the line.  Would be nice to have real regular
     * expressions, but scanf will suffice.
     */
    sscanf(ptr, "%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]",
        opcode, arg0, arg1, arg2);
    return(1);
}

int
isNumber(char *string)
{
    /* return 1 if string is a number */
    int i;
    return( (sscanf(string, "%d", &i)) == 1);
}
