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
int findAddress(char *,char *);

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
   
    char *addy[MAXLINELENGTH];
    int i = 0;
    //first pass: find labels and store address
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
        int result;

        //label
        //instruction
        if (!strcmp(opcode, "add")) {
            result = 0b000;


            printf("add: %i",result);

            //reg A - bits 21-19
            result = (result << 3) | atoi(arg0);
            printf("current result: %i", result);
        
            //reg B - bits 18-16
            result = (result << 3) | atoi(arg0);
            printf("current result: %i", result);

            //bits 15-3 are unused
            result = result << 13;

            //dest - bits 2-0
            result = (result << 3) | atoi(arg0);
            printf("current result: %i", result);

        }
        else if (!strcmp(opcode, "nor")) {
            result = 0b001;
            printf("nor: %i",result);

             //reg A - bits 21-19
            result = (result << 3) | atoi(arg0);
            printf("current result: %i", result);
        
            //reg B - bits 18-16
            result = (result << 3) | atoi(arg0);
            printf("current result: %i", result);

            //bits 15-3 are unused
            result = result << 13;

            //dest - bits 2-0
            result = (result << 3) | atoi(arg0);
            printf("current result: %i", result);
        }
        else if (!strcmp(opcode, "lw")) {
            result = 0b010;
            printf("lw: %i",result);

             //reg A - bits 21-19
            result = (result << 3) | atoi(arg0);
            printf("current result: %i", result);
        
            //reg B - bits 18-16
            result = (result << 3) | atoi(arg0);
            printf("current result: %i", result);

            result = result << 16;

            //check for label
            if (arg2[0] > '9') {
                int address = findAddress(addy,arg2);
                if (address > -1) {
                    result = result | address;
                    printf("result = %i", result);
                }
            }
            else {
                result = result | atoi(arg2);
                printf("result = %i", result);
            }

        }
        else if (!strcmp(opcode, "sw")) {
            result = 0b011;
            printf("sw: %i",result);

            //reg A - bits 21-19
            result = (result << 3) | atoi(arg0);
            printf("current result: %i", result);
        
            //reg B - bits 18-16
            result = (result << 3) | atoi(arg0);
            printf("current result: %i", result);

            result = result << 16;

            //check for label
            if (arg2[0] > '9') {
                int address = findAddress(addy,arg2);
                if (address > -1) {
                    result = result | address;
                    printf("result = %i", result);
                }
            }
            else {
                result = result | atoi(arg2);
                printf("result = %i", result);
            }
        }
        else if (!strcmp(opcode, "beq")) {
            result = 0b100;
            printf("beq: %i",result);

            //reg A - bits 21-19
            result = (result << 3) | atoi(arg0);
            printf("current result: %i", result);
        
            //reg B - bits 18-16
            result = (result << 3) | atoi(arg0);
            printf("current result: %i", result);

            result = result << 16;

            //check for label
            if (arg2[0] > '9') {
                int address = findAddress(addy,arg2);
                if (address > -1) {
                    result = result | address;
                    printf("result = %i", result);
                }
            }
            else {
                result = result | atoi(arg2);
                printf("result = %i", result);
            }
        }
        else if (!strcmp(opcode, "jair")) {
            result = 0b101;
            printf("jair: %i",result);

            //reg A - bits 21-19
            result = (result << 3) | atoi(arg0);
            printf("current result: %i", result);
        
            //reg B - bits 18-16
            result = (result << 3) | atoi(arg0);
            printf("current result: %i", result);

            //bits 15-0 are unused
            result = result << 16;
        }
        else if (!strcmp(opcode, "halt")) {
            result = 0b110;
            printf("halt: %i",result);

            //bits 21-0 are unused
            result = result << 22;
        }
        else if (!strcmp(opcode, "noop")) {
            result = 0b111;
            printf("noop: %i",result);

            //bits 21-0 are unused
            result = result << 22;
        }
        else {
            printf("opcode not found");
        }

      
        
        //field1
        //field2

    }

    return(0);
}

//searches an array of strings for the location of given label.
//if the array contains the label, returns the location of the label.
//if not returns -1;
int findAddress(char *arrOfStr, char *label) {
    for (int i = 0; i < MAXLINELENGTH; ++i){
        if (strcmp(arrOfStr[i],label) {
            //return location of label
            printf("found label at element: %i", i);
            return i;
        }
    }
    printf("label: %s not found",label);
    return -1;
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
