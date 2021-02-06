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
    char sourceChar, destinationChar;
    FILE *sourceFile, *destinationFile;
    int getChar;
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
                    //printf("%s contents:\n",destinationName);

                    while(getChar != EOF){
                        // checks if the character needs to be replaced
                        // and replaces that character
                        if(getChar == sourceChar){
                            getChar = (int)destinationChar;
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
                    if(getChar == sourceChar){
                        getChar = (int)destinationChar;
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
            sourceChar = argv[i][1];
            printf("sourceChar: %c\n", sourceChar); // for debugging

        }

        // checks what the '+' (argument to be replace with) is
        // and assigns it to a variable
        else if(strncmp(argv[i], "+", 1) == 0){
            destinationChar = argv[i][1];
            printf("destinationChar: %c\n", destinationChar); // for debugging
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
                        if(getChar == sourceChar){
                            getChar = (int)destinationChar;
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
                // tell user to enter ! to execute the program
                printf("Type( ! )to write to stdout\n");
                while((getChar=getc(stdin)) != EOF){
                    // 33 is ASCII for !
                    if(getChar == 33){
                        break;
                    }
                    // replaces '-' with '+'
                    if(getChar == sourceChar){
                        getChar = (int)destinationChar;
                    }
                    // writes string with replacements do destination file
                    putc(getChar, stdout);
                }
            }
    }




    return 0;
    }
