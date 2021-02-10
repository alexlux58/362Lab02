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
    int sourceLength = 0, destinationLength = 0;
    bool iFlag = false, oFlag = false, argcFlag = false;

    if(argc == 1){
        argcFlag = true;
    }

    for(int d = 1; d < argc; d++){
        // checks what the '-' (argument to be replaced) is
        // and assigns it to a variable
        if(strncmp(argv[d], "--", 2) == 0){

            sourceLength = (int)strlen(argv[d]) - 1;

            // printf("sourceLegth: %d\n", sourceLength); // for debugging

            sourceChar1 = argv[d][2];
            sourceChar2 = argv[d][3];
            sourceChar3 = argv[d][4];

            /*
            printf("sourceChar: %c\n", sourceChar1); // for debugging
            printf("sourceChar: %c\n", sourceChar2); // for debugging
            printf("sourceChar: %c\n", sourceChar3); // for debugging
            */

        }

        // checks what the '+' (argument to be replace with) is
        // and assigns it to a variable
        if(strncmp(argv[d], "-+", 2) == 0){

            destinationLength = (int)strlen(argv[d]) - 1;

            // printf("destinationLegth: %d\n", destinationLength); // for debugging

            destinationChar1 = argv[d][2];
            destinationChar2 = argv[d][3];
            destinationChar3 = argv[d][4];

            /*
            printf("destinationChar: %c\n", destinationChar1); // for debugging
            printf("destinationChar: %c\n", destinationChar2); // for debugging
            printf("destinationChar: %c\n", destinationChar3); // for debugging
            */

        }
    }

    // loop through the number of arguments to find the source flag
    for (int i = 1; i < argc; i++){

        // check if the -i argument flag is raised
        if(strncmp(argv[i],"-i", 2) == 0){
            // sets 'i' to true
            iFlag = true;
            // increment the argument array to get the name of the input file
            sourceName = argv[++i];

            // open the src file name to read and store the contents
            sourceFile = fopen(sourceName, "r");

            // checks if the file exists
            if(sourceFile == NULL){
                perror("sourceFile");
                exit(EXIT_FAILURE);
            }

            // nested loop to find the destination flag -o
            for(int j = 1; j < argc; j++){
                if(strncmp(argv[j], "-o", 2) == 0){
                    oFlag = true;
                    // increments the argument array to get the dest file name for writing
                    destinationName = argv[++j];
                    // opens the destination file for writing
                    destinationFile = fopen(destinationName, "w+");

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

                printf("\n");

            }

            // close files
            fclose(sourceFile);

            if(oFlag){
                fclose(destinationFile);
            }

        }

        else if(strcmp(argv[i], "-h") == 0){
            printf("USAGE:\n"
                   "   sub [ -h | --fromChars -+toChars [-i inputFile] [-o outputFile] ]\n"
                   "\n"
                   "DESCRIPTION:\n"
                   "   This utility copies text from an input stream to an output stream replacing every \n"
                   "   instance of a specific character in fromChars with a corresponding (position-wise) \n"
                   "   character from toChars. Any characters in fromChars and in toChars that do not \n"
                   "   have corresponding counterparts in the other one are ignored. If an input file is \n"
                   "   provided, the content is read from that file; otherwise, the standard input is used. \n"
                   "   If an output file is provided, then the modified content is written to that file; \n"
                   "   otherwise, the standard output is used.\n"
                   "\n"
                   "OPTIONS:\n"
                   "   --(followed by a string without separating space)\n"
                   "     indicates all characters that will be replaced in the processed text\n"
                   "   -+(followed by a string without separating space) \n"
                   "     indicates the characters that will be used to replace corresponding \n"
                   "     (position-wise) characters from fromChars in the processed text\n"
                   "   -i (followed by input file name) \n"
                   "     use the provided file as an input stream instead of standard input \n"
                   "   -o (followed by output file name) \n"
                   "     use the provided file as an output stream instead of standard output \n"
                   "   -h prints this help message; it is also a default if no command line\n"
                   "     arguments are provided\n");
        }


        }

    // checks if there is no 'i' flag argument for src.txt
    if(!iFlag){
            // nested loop to find the destination flag -o
            for(int k = 1; k < argc; k++){
                if(strcmp(argv[k], "-o") == 0){
                    oFlag = true;
                    // increments the argument array to get the dest file name for writing
                    destinationName = argv[++k];

                    // for debugging
                    // printf("%s contents:\n",destinationName);

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
                    // tell user to enter ! to execute the program
                    printf("Type( ! )to write to stdout\n");
                    while ((getChar = getc(stdin)) != EOF) {
                        // 33 is ASCII for !
                        if (getChar == 33) {
                            break;
                        }

                        // replaces '-' with '+'
                        if (getChar == sourceChar1) {
                            getChar = (int) destinationChar1;
                        } else if (getChar == sourceChar2) {
                            getChar = (int) destinationChar2;
                        } else if (getChar == sourceChar3) {
                            getChar = (int) destinationChar3;
                        }
                        // writes string with replacements do destination file
                        putc(getChar, stdout);
                    }
                    printf("\n");
                }
                else if(sourceLength > destinationLength){
                    printf("ERROR - missing replacement character\n...EXITING\n");
                    exit(EXIT_FAILURE);
                }
                else if(argcFlag){
                    printf("USAGE:\n"
                           "   sub [ -h | --fromChars -+toChars [-i inputFile] [-o outputFile] ]\n"
                           "\n"
                           "DESCRIPTION:\n"
                           "   This utility copies text from an input stream to an output stream replacing every \n"
                           "   instance of a specific character in fromChars with a corresponding (position-wise) \n"
                           "   character from toChars. Any characters in fromChars and in toChars that do not \n"
                           "   have corresponding counterparts in the other one are ignored. If an input file is \n"
                           "   provided, the content is read from that file; otherwise, the standard input is used. \n"
                           "   If an output file is provided, then the modified content is written to that file; \n"
                           "   otherwise, the standard output is used.\n"
                           "\n"
                           "OPTIONS:\n"
                           "   --(followed by a string without separating space)\n"
                           "     indicates all characters that will be replaced in the processed text\n"
                           "   -+(followed by a string without separating space) \n"
                           "     indicates the characters that will be used to replace corresponding \n"
                           "     (position-wise) characters from fromChars in the processed text\n"
                           "   -i (followed by input file name) \n"
                           "     use the provided file as an input stream instead of standard input \n"
                           "   -o (followed by output file name) \n"
                           "     use the provided file as an output stream instead of standard output \n"
                           "   -h prints this help message; it is also a default if no command line\n"
                           "     arguments are provided\n");
                }
                else if(destinationLength != 0 && sourceLength != 0) {
                    // tell user to enter ! to execute the program
                    printf("Type( ! )to write to stdout\n");
                    while ((getChar = getc(stdin)) != EOF) {
                        // 33 is ASCII for !
                        if (getChar == 33) {
                            break;
                        }

                        // replaces '-' with '+'
                        if (getChar == sourceChar1) {
                            getChar = (int) destinationChar1;
                        } else if (getChar == sourceChar2) {
                            getChar = (int) destinationChar2;
                        } else if (getChar == sourceChar3) {
                            getChar = (int) destinationChar3;
                        }
                        // writes string with replacements do destination file
                        putc(getChar, stdout);
                    }
                    printf("\n");
                }
            }
    }




    return 0;
    }
