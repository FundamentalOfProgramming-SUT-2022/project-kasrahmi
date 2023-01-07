#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>



void help();
void cat(char *);
int checking_validation(char *);

int main() {    
    printf("Enter your command :\n");
    printf("(If you need help type the word HELP)\n");
    while(1){
        printf("-");
        mkdir("/ali", 0700);

        char cmd[4];
        char val[8];
        char address[1000];
        // get the command
        scanf("%4s" , cmd);
        if(strcmp(cmd , "HELP") != 0){
        scanf("%8s" , val);
        scanf("%s" , address);
        }

        // use strcmp function to check if 2 strings are the same or not
        if(strcmp(cmd , "HELP") == 0) {
            help();
        }
        else if(strcmp(cmd , "CAT") == 0){
            if(checking_validation(val) == 1){
                continue;
            }
            printf("%d" , checking_validation(val));
            char file_name[1000];
            strcpy(file_name , address);
            cat(file_name);
        }
    }   
 
    return 0;
}

int checking_validation(char * val){
    if(strcmp(val , " --file ") == 0){
        return 0;
    }
    else{
        printf("NOT VALID");
        printf("\n--------------------\n");
        return 1;
    }
}

void help(){
    printf("Here is a list of commands you can use : \n");
    printf("-CAT = print what is in a file\n");
    printf("-CAF = create a file\n");
    printf("-INF = insert a file\n");
    printf("-PLF = print list of files\n");
    printf("--------------------\n");
    // exit(-1);
}

void cat(char *file_name){
    FILE * fPtr;

    fPtr = fopen(file_name , "r");
    char data[1000];
    if(fPtr != NULL){
        while (fgets(data , 1000 , fPtr)){
            printf("%s" , data);
        }
    }
    else{
        printf("Does not exist");
    }
    fclose(fPtr);
    printf("\n--------------------\n");
}
        
