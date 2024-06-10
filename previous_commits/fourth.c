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
            gets(address);
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
    char *temp2;
    char *temp3;
    char *token2 = strtok(address, "/");
    printf("%s\n" , token2);
    while (token2 != NULL) {
        if(strcmp(token2 , " \"") == 0){
            temp = token2;
            token2 = strtok(NULL, "/");
            printf("\"\"%s\n" , token2);
        }
        else{
            cd(token2);
            temp = token2;
            token2 = strtok(NULL, "/");
            printf("%s\n" , token2);
        }
    }
    chdir("..");
    rmdir(temp);
    // for(int j = 0 ; j < 9 ; j++){
    //     printf("%c\n" , temp[j]);
    // }
    // for(int j = 0 ; j < 8  ; j++){
    //     temp2[j] = temp[j];
    //     temp2[j+1]='\0';
    //     printf("%c\n" , temp2[j]);
    // }
    int i = 0;
    while(temp[i] != '\"'){
        temp2[i] = temp[i];
        temp2[i+1]='\0';
        // printf("%c\n" , temp2[i]);
        i++;
    }
    // printf("%s\n" , temp);
    // printf("%s\n" , temp2);
    // printf("%s\n" , temp3);
    FILE * a;
    a = fopen(temp2 , "w");
    fclose(a);
}

void cd(char *folder){
    mkdir(folder , 0700);
    chdir(folder);
}