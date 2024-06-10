#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif



void help();
void cat(char *);
int checking_validation(char *);
void create_file(char *);
void cd(char *);

int main() {    
    mkdir("root" , 0700);
    chdir("root");
    rmdir("1234");
    printf("Enter your command :\n");
    printf("(If you need help type the word HELP)\n");
    while(1){
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s ", cwd);
        } 
        else {
            perror("getcwd() error");
            return 1;
        }
        // mkdir("/ali", 0700);

        char cmd[4];
        char val[7];
        char address[1000];
        // get the command
        scanf("%4s" , cmd);
        if(strcmp(cmd , "HELP") != 0){
            scanf("%s" , val);
            scanf("%s" , address);
        }
        // printf("%s" , val);

        // use strcmp function to check if 2 strings are the same or not
        if(strcmp(cmd , "HELP") == 0) {
            help();
        }
        else if(strcmp(cmd , "CAT") == 0){

            if(checking_validation(val) == 1){
                continue;
            }
            // printf("%d" , checking_validation(val));
            char file_name[1000];
            strcpy(file_name , address);
            cat(file_name);
        }
        else if(strcmp(cmd , "CRF") == 0){
            if(checking_validation(val) == 1){
                continue;
            }
            create_file(address);
        }
        else{
            printf("Command does not exist");
            printf("\n--------------------\n");
        }
    }   
 
    return 0;
}

int checking_validation(char * val){
    if(strcmp(val , "--file") == 0){
        return 0;
    }
    else{
        printf("invalid command");
        printf("\n--------------------\n");
        return 1;
    }
}

void help(){
    printf("Here is a list of commands you can use : \n");
    printf("-CAT = print what is in a file\n");
    printf("-CRF = create a file\n");
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
        printf("File does not exist");
    }
    fclose(fPtr);
    printf("\n--------------------\n");
}

void create_file(char *address){
    printf("%s\n" , address);
    char buff[FILENAME_MAX];
    GetCurrentDir( buff, FILENAME_MAX );
    char* token1 = strtok(buff, " / ");
    while(token1 != NULL) {
        token1 = strtok(NULL, " / ");
        if(strcmp(token1 , "root") == 0){
            while(token1 != NULL) {
                chdir("..");
                token1 = strtok(NULL, " / ");
            }
        }
    }
    const char *temp;
    char *token2 = strtok(address, " / ");
    while (token2 != NULL) {
        cd(token2);
        temp = token2;
        token2 = strtok(NULL, " / ");
    }
    chdir("..");
    rmdir(temp);
    FILE * a;
    a = fopen(temp , "w");
    fclose(a);
}

void cd(char *folder){
    mkdir(folder , 0700);
    chdir(folder);
}