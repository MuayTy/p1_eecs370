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
    char word[7];
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
   
    struct Label_Map maps[MAXLINES];
    int amountOfLabels = 0;
    int currentAd = 0;      //never change the 0 address? so start at 1
    //first pass: find labels and store address
    while (readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2)) {

        if (label[0] != '\0') {
            //check size
            if (label[0] < 'A') {
                printf("0 label does not start with a letter. : %c\n",label[0]);
                exit(1);
            }
            if ((label[0] < 'a') && (label[0] > 'Z')) {
                printf("1 label does not start with a letter. : %c\n",label[0]);
                exit(1);
            }
            if (label[0] > 'z') {
                printf("2 label does not start with a letter. : %c\n",label[0]);
                exit(1);
            }
            //check if label starts with a letter
            if (strlen(label) > 6) {
                printf("label: %s is too long.\n", label);
                exit(1);
            }
            //check for duplicates
            for (int i = 0; i < amountOfLabels; ++i) {
                if (!strcmp(maps[i].word,label)){
                    printf("label: %s already exists.\n",label);
                    exit(1);
                }
            }

            printf("label = %s\n",label); 
            //fill struct with data
            struct Label_Map m;
             m.ad = currentAd;
             strcpy(m.word,label);
            printf("m- label: %s, address: %i\n", m.word,m.ad); 
            maps[amountOfLabels] = m;
            printf("store in maps\n");
            //printf("copy = %s at address %i\n",*maps[amountOfLabels].word,*maps[amountOfLabels].ad);
            ++amountOfLabels;
        }
        ++currentAd;
    }

    /* this is how to rewind the file ptr so that you start reading from the
        beginning of the file */
    rewind(inFilePtr);
    int pc = 0;
    //second pass - output ISA as decimal
    while (readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2)) {
        //the first 8 bits are always zeros
        int result;
        

        //label
        //instruction
        if (!strcmp(opcode, "add")) {
            result = 0b000;


            printf("add: %i\n",result);

            //reg A - bits 21-19
            result = (result << 3) | atoi(arg0);
            printf("current result: %i\n", result);
        
            //reg B - bits 18-16
            result = (result << 3) | atoi(arg1);
            printf("current result: %i\n", result);

            //bits 15-3 are unused
            result = result << 13;

            //dest - bits 2-0
            result = (result << 3) | atoi(arg2);
            printf("current result: %i\n", result);

        }
        else if (!strcmp(opcode, "nor")) {
            result = 0b001;
            printf("nor: %i\n",result);

             //reg A - bits 21-19
            result = (result << 3) | atoi(arg0);
            printf("current result: %i\n", result);
        
            //reg B - bits 18-16
            result = (result << 3) | atoi(arg0);
            printf("current result: %i\n", result);

            //bits 15-3 are unused
            result = result << 13;

            //dest - bits 2-0
            result = (result << 3) | atoi(arg0);
            printf("current result: %i\n", result);
        }
        else if (!strcmp(opcode, "lw")) {
            result = 0b010;
            printf("lw: %i\n",result);

             //reg A - bits 21-19
            result = (result << 3) | atoi(arg0);
            printf("reg A- result: %i\n", result);
        
            //reg B - bits 18-16
            result = (result << 3) | atoi(arg1);
            printf("reg B- result: %i\n", result);

            //check for label
            if (arg2[0] > '9') {
                int address = -1;
                    for (int i = 0; i < MAXLINES; ++i){
                        printf("map {%s , %i}\n",maps[i].word,maps[i].ad);
                        if (!strcmp(maps[i].word,arg2)) {
                            printf("found label: %s at address: %i\n",arg2, maps[i].ad);
                            address = maps[i].ad;
                            break;
                        }
                    }
                    if (address > -1) {
                        result = (result << 16) | address;
                        printf("result from lw no label = %i\n", result);
                    }
            }
            else {
                //deals with negatives
               if (atoi(arg2) < 0) {
                    unsigned int temp = atoi(arg2);
                    temp = temp << 16; 
                    printf("offset = %i\n",temp);
                    temp = temp >> 16; 
                    printf("offset = %i\n",temp);
                    result = (result << 16) | temp;
                    printf("result = %i\n", result);
                }
                else {
                    result = (result << 16) | atoi(arg2);
                    printf("result = %i\n", result);
                }
            }         
        }
        else if (!strcmp(opcode, "sw")) {
            result = 0b011;
            printf("sw: %i\n",result);

            //reg A - bits 21-19
            result = (result << 3) | atoi(arg0);
            printf("current result: %i\n", result);
        
            //reg B - bits 18-16
            result = (result << 3) | atoi(arg0);
            printf("current result: %i\n", result);

            result = result << 16;

            //check for label
            if (arg2[0] > '9') {
                int address = -1;
                    for (int i = 0; i < MAXLINES; ++i){
                        if (!strcmp(maps[i].word,label)) {
                            printf("found label: %s at element: %i\n",label, i);
                            address = maps[i].ad;
                            break;
                        }
                    }
                    if (address > -1) {
                        result = (result << 16) | address;
                        printf("result = %i\n", result);
                    }
            } 
            else {
                //deal with negatives
                if (atoi(arg2) < 0) {
                    unsigned int temp = atoi(arg2);
                    temp = temp << 16; 
                    printf("offset = %i\n",temp);
                    temp = temp >> 16; 
                    printf("offset = %i\n",temp);
                    result = (result << 16) | temp;
                    printf("result = %i\n", result);
                }
                else {
                    result = (result << 16) | atoi(arg2);
                    printf("result = %i\n", result);
                }
                
            }
        }
        else if (!strcmp(opcode, "beq")) {
            result = 0b100;
            printf("beq: %i\n",result);

            //reg A - bits 21-19
            result = (result << 3) | atoi(arg0);
            printf("current result: %i\n", result);
        
            //reg B - bits 18-16
            result = (result << 3) | atoi(arg1);
            printf("current result: %i\n", result);

            //reg a and reg b are the same
            if (atoi(arg1) == atoi(arg2)) {
                //check for label
                if (arg2[0] > '9') {
                    int address = -1;
                    for (int i = 0; i < MAXLINES; ++i){
                        printf("map {%s , %i}\n",maps[i].word,maps[i].ad);
                        if (!strcmp(maps[i].word,arg2)) {
                            printf("found label: %s at address: %i\n",arg2, maps[i].ad);
                            address = maps[i].ad;
                            break;
                        }
                    }
                    if (address > -1) {
                        printf("pc = %i\n",pc);
                        int offset = address - pc - 1;
                        printf("offset = %i\n",offset);

                        //fix two's complement
                        if (offset < 0) {
                            unsigned int temp = address - pc - 1;
                            temp = temp << 16; 
                            printf("offset = %i\n",temp);
                            temp = temp >> 16; 
                            printf("offset = %i\n",temp);
                            result = (result << 16) | temp;
                            printf("result = %i\n", result);
                        }
                        else {
                            result = (result << 16) | offset;
                            printf("result = %i\n", result);
                        }

                        
                        
                    }
                }
                else {
                    //2's complement
                    //1111 1111 1111 1111 1000 0000 0000 0001
                        int neg = atoi(arg2);
                        int offset = neg - pc - 1;
                    if (offset < 0) {
                        unsigned int temp = neg - pc - 1;
                            temp = temp << 16; 
                            printf("offset = %i\n",temp);
                            temp = temp >> 16; 
                            printf("offset = %i\n",temp);
                            result = (result << 16) | temp;
                            printf("result = %i\n", result);
                    }
                    else {
                            result = (result << 16) | offset;
                            printf("result = %i\n", result);
                    }
                                   
                }
            }
            else {
                    //check for label
                if (arg2[0] > '9') {
                    int address = -1;
                        for (int i = 0; i < MAXLINES; ++i){
                            printf("map {%s , %i}\n",maps[i].word,maps[i].ad);
                            if (!strcmp(maps[i].word,arg2)) {
                                printf("found label: %s at address: %i\n",arg2, maps[i].ad);
                                address = maps[i].ad;
                                break;
                            }
                        }
                        if (address > -1) {
                            result = (result << 16) | address;
                            printf("result = %i\n", result);
                        }
                } 
                else {
                    //2's complement
                    //1111 1111 1111 1111 1000 0000 0000 0001
                    if (atoi(arg2) < 0) {
                        //shift left to remove first (31-16 bits)
                        int neg = (atoi(arg2) << 16);
                        //shift back right to create all 0's, 
                        neg = neg >> 16;
                        result = (result << 16) | neg;
                        printf("result = %i\n", result);
                    }               
                    else {
                        result = (result << 16) | atoi(arg2);
                        printf("result = %i\n", result);
                    }                   
                }
            }    
        }
        else if (!strcmp(opcode, "jair")) {
            result = 0b101;
            printf("jair: %i\n",result);

            //reg A - bits 21-19
            result = (result << 3) | atoi(arg0);
            printf("current result: %i\n", result);
        
            //reg B - bits 18-16
            result = (result << 3) | atoi(arg0);
            printf("current result: %i\n", result);

            //bits 15-0 are unused
            result = result << 16;
        }
        else if (!strcmp(opcode, "halt")) {
            result = 0b110;
            printf("halt: %i\n",result);

            //bits 21-0 are unused
            result = result << 22;
        }
        else if (!strcmp(opcode, "noop")) {
            result = 0b111;
            printf("noop: %i\n",result);

            //bits 21-0 are unused
            result = result << 22;
        }
        else {
            if (arg0[0] != '\0') {
                //label
                if (arg0[0] > '9') {
                    int address = -1;
                    for (int i = 0; i < MAXLINES; ++i){
                        if (!strcmp(maps[i].word,arg0)) {
                            printf("found label: %s at element: %i\n",arg0, i);
                            address = maps[i].ad;
                            break;
                        }
                    }
                    if (address > -1) {
                        result = address;
                        printf("result = %i\n", result);
                    }
                }
                else {
                    result = atoi(arg0);
                }
            }
        
        }

        fprintf(outFilePtr,"%i\n",result);
        ++pc;
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
