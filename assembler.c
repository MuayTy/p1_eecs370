/**
 * Project 1 
 * Assembler code fragment for LC-2K 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINELENGTH 1000
#define MAXLINES 65536

struct Label_Map {
    char *word[7];
    int ad;
};

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
   
    struct Label_Map arr[MAXLINES];
    int amountOfLabels = 0;
    int currentAd = 0;
    //first pass: find labels and store address
    while (readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2)) {

        if (label[0] != '\0') {
            //check size
            if ((label[0] > 'A') || (label[0] < 'a' && label[0] > 'Z') || (label[0] > 'z')) {
                printf("label does not start with a letter. : %c\n",label[0]);
                exit(1);
            }
            //check if label starts with a letter
            if (strlen(label) > 6) {
                printf("label: %s is too long.\n", label);
                exit(1);
            }
            //check for duplicates
            for (int i = 0; i < amountOfLabels; ++i) {
                if (!strcmp(*arr[i].word,label)){
                    printf("label: %s already exists.\n",label);
                    exit(1);
                }
            }

            printf("label = %s\n",label); 
            //fill struct with data
    
            strcpy(*arr[amountOfLabels].word,label);   
            arr[amountOfLabels].ad = currentAd;
            //printf("copy = %s at address %i\n",*arr[amountOfLabels].word,*arr[amountOfLabels].ad);
            ++amountOfLabels;
        }
        ++currentAd;
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
                int address = -1;
                    for (int i = 0; i < MAXLINES; ++i){
                        if (strcmp(*arr[i].word,label)) {
                            printf("found label at element: %i", i);
                            address = arr[i].ad;
                        }
                    }
                    if (address > -1) {
                        result = address;
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
                int address = -1;
                    for (int i = 0; i < MAXLINES; ++i){
                        if (strcmp(*arr[i].word,label)) {
                            printf("found label at element: %i", i);
                            address = arr[i].ad;
                        }
                    }
                    if (address > -1) {
                        result = address;
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
                int address = -1;
                    for (int i = 0; i < MAXLINES; ++i){
                        if (strcmp(*arr[i].word,label)) {
                            printf("found label at element: %i", i);
                            address = arr[i].ad;
                        }
                    }
                    if (address > -1) {
                        result = address;
                        printf("result = %i", result);
                    }
            } 
            else {
                //2's complement
                //1111 1111 1111 1111 1000 0000 0000 0001
                if (arg2[0] < 0) {
                    //shift left to remove first (31-16 bits)
                    int neg = (atoi(arg2) << 16);
                    //shift back right to create all 0's, 
                    neg = neg >> 16;
                    result = result | neg;
                    printf("result = %i", result);
                }
                else {
                    result = result << 16 | atoi(arg2);
                    printf("result = %i", result);
                }
                
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
            if (arg0[0] != '\0') {
                //label
                if (arg0[0] > '9') {
                    int address = -1;
                    for (int i = 0; i < MAXLINES; ++i){
                        if (strcmp(*arr[i].word,label)) {
                            printf("found label at element: %i", i);
                            address = arr[i].ad;
                        }
                    }
                    if (address > -1) {
                        result = address;
                        printf("result = %i", result);
                    }
                }
                else {
                    result = atoi(arg0);
                }
            }
        
        }

        fprintf(outFilePtr,"%i\n",result);
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
