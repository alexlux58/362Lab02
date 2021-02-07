#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
 * name: Alex Lux
 * Lab: Lab02
 * Date: 2/6/2021
 */

int main(int argc, char** argv) {

    char *sourceName, *destinationName;
    char sourceChar1, sourceChar2, sourceChar3, destinationChar1, destinationChar2, destinationChar3;
    FILE *sourceFile, *destinationFile;
    int getChar;
    int sourceLength, destinationLength;
    bool iFlag = false, oFlag = false;

    // loop through the number of arguments to find the source flag
    for (int i = 1; i < argc; i++){
        // check if the -i argument flag is raised
        if(strcmp(argv[i],"i") == 0){
            // sets 'i' to true
            iFlag = true;
            // increment the argument array to get the name of the input file
            sourceName = argv[++i];
            // open the src file name to read and store the contents
            sourceFile = fopen(sourceName, "r+");

            // checks if the file exists
            if(sourceFile == NULL){
                perror("sourceFile");
                exit(EXIT_FAILURE);
            }

            // nested loop to find the destination flag -o
            for(int j = 1; j < argc; j++){
                if(strcmp(argv[j], "o") == 0){
                    oFlag = true;
                    // increments the argument array to get the dest file name for writing
                    destinationName = argv[++j];
                    // opens the destination file for writing
                    destinationFile = freopen(destinationName, "w+", stdout);

                    // gets the contents of the source file
                    // and prints it to dest.txt
                    getChar = getc(sourceFile);

                    // for debugging
                    // printf("%s contents:\n",destinationName);

                    while(getChar != EOF){
                        // checks if the character needs to be replaced
                        // and replaces that character
                        if(getChar == sourceChar1){
                            getChar = (int)destinationChar1;
                        }
                        putc(getChar,destinationFile);
                        getChar = getc(sourceFile);
                    }
                }
            }

            // checks if the 'o' flag was raised
            if(!oFlag){

                // for debugging
                // printf("%s contents:\n",sourceName);

                // goes through the src.txt file and replaces all '-' with '+'
                while((getChar = getc(sourceFile)) != EOF){
                    if(getChar == sourceChar1){
                        getChar = (int)destinationChar1;
                    }
                    fflush(stdout); // to clear the stdout buffer
                    fputc(getChar, stdout);
                }

            }

            // close files
            fclose(sourceFile);
            fclose(destinationFile);
        }

        // checks what the '-' (argument to be replaced) is
        // and assigns it to a variable
        if(strncmp(argv[i], "-", 1) == 0){

            sourceLength = (int)strlen(argv[i]) - 1;

            // printf("sourceLegth: %d\n", sourceLength); // for debugging

            sourceChar1 = argv[i][1];
            sourceChar2 = argv[i][2];
            sourceChar3 = argv[i][3];

            /*
            printf("sourceChar: %c\n", sourceChar1); // for debugging
            printf("sourceChar: %c\n", sourceChar2); // for debugging
            printf("sourceChar: %c\n", sourceChar3); // for debugging
            */

        }

        // checks what the '+' (argument to be replace with) is
        // and assigns it to a variable
        else if(strncmp(argv[i], "+", 1) == 0){

            destinationLength = (int)strlen(argv[i]) - 1;

            // printf("destinationLegth: %d\n", destinationLength); // for debugging

            destinationChar1 = argv[i][1];
            destinationChar2 = argv[i][2];
            destinationChar3 = argv[i][3];

            /*
            printf("destinationChar: %c\n", destinationChar1); // for debugging
            printf("destinationChar: %c\n", destinationChar2); // for debugging
            printf("destinationChar: %c\n", destinationChar3); // for debugging
            */

            }
        }

    // checks if there is no 'i' flag argument for src.txt
    if(!iFlag){
            // nested loop to find the destination flag -o
            for(int k = 1; k < argc; k++){
                if(strcmp(argv[k], "o") == 0){
                    oFlag = true;
                    // increments the argument array to get the dest file name for writing
                    destinationName = argv[++k];

                    // for debugging
                    printf("%s contents:\n",destinationName);

                    // tell user to enter ! to execute the program
                    printf("Type( ! )to write to file\n");

                    // opens the destination file for writing
                    destinationFile = freopen(destinationName, "w", stdout);

                    // gets the user input one character at a time
                    while((getChar=getc(stdin)) != EOF){
                        // 33 is ASCII for !
                        if(getChar == 33){
                            break;
                        }
                        // replaces '-' with '+'
                        if(getChar == sourceChar1){
                            getChar = (int)destinationChar1;
                        }
                        // writes string with replacements do destination file
                        putc(getChar, destinationFile);
                    }
                    // closes file
                    fclose(destinationFile);
                }
            }

            // checks if there is no 'o' flag argument for dest.txt
            if (!oFlag){

                if(sourceLength < destinationLength){
                    printf("WARNING - extraneous replacement character\n");
                }
                else if(sourceLength > destinationLength){
                    printf("ERROR - missing replacement character\n...EXITING");
                    exit(EXIT_FAILURE);
                }

                // tell user to enter ! to execute the program
                printf("Type( ! )to write to stdout\n");
                while((getChar=getc(stdin)) != EOF){
                    // 33 is ASCII for !
                    if(getChar == 33){
                        break;
                    }

                    // replaces '-' with '+'
                    if(getChar == sourceChar1){
                        getChar = (int)destinationChar1;
                    }
                    else if(getChar == sourceChar2){
                        getChar = (int)destinationChar2;
                    }
                    else if(getChar == sourceChar3){
                        getChar = (int)destinationChar3;
                    }
                    // writes string with replacements do destination file
                    putc(getChar, stdout);
                }
            }
    }




    return 0;
    }
