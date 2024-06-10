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

char *count[10000];

void help();
void cat(char * , char *);
int checking_validation(char *);
void create_file(char * , char *);
void cd(char *);
int count_char_word(char * , char *);
void filename(char *,char *);
void seperator(char *);
void insert(char *,char *);

int main() {    
    mkdir("root" , 0700);
    chdir("root");
    // rmdir("1234");
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
        // if(strcmp(cmd , "HELP") != 0){
        //     scanf("%s" , val);
        //     scanf(" %[^\n]%*c" , address );
        // }
        // printf("%s" , val);

        // use strcmp function to check if 2 strings are the same or not
        if(strcmp(cmd , "HELP") == 0) {
            help();
        }
        else if(strcmp(cmd , "CAT") == 0){
            scanf("%s" , val);
            scanf(" %[^\n]%*c" , address);
            if(checking_validation(val) == 1){
                continue;
            }
            // printf("%d" , checking_validation(val));
            char *file_name = (char*) calloc(2000 , sizeof(char));
            char *file_name2 = (char*) calloc(2000 , sizeof(char));
            int slash = '/';
            file_name = strrchr(address, slash);
            file_name2 = strtok(file_name, "/");
            filename(address , file_name2);
            // if(address[0] == '\"'){
            //     int z ;
            //     for(z = 1 ; file_name2[strlen(file_name2) - z] != '\"' ; ){
            //         file_name2[strlen(file_name2) - z] = '\0';
            //     }
            //     file_name2[strlen(file_name2) - (z)] = '\0';
            // }
            cat(file_name2 , address);
        }
        else if(strcmp(cmd , "CRF") == 0){
            scanf("%s" , val);
            scanf(" %[^\n]%*c" , address);
            if(checking_validation(val) == 1){
                continue;
            }
            char *file_name;
            char *file_name2;
            int slash = '/';
            file_name = strrchr(address, slash);
            file_name2 = strtok(file_name, "/");
            filename(address , file_name2);
            // if(address[0] == '\"'){
            //     int z ;
            //     for(z = 1 ; file_name2[strlen(file_name2) - z] != '\"' ; ){
            //         file_name2[strlen(file_name2) - z] = '\0';
            //     }
            //     file_name2[strlen(file_name2) - (z)] = '\0';
            // }
            create_file(address , file_name2);
            printf("File created successfully.\n");
            printf("\n--------------------\n");
        }
        else if(strcmp(cmd,"INF") == 0){
            scanf("%s" , val);
            scanf(" %[^\n]%*c" , address);
            char *backup_address = (char*) calloc(2000 , sizeof(char));
            strcpy(backup_address , address);
            if(checking_validation(val) == 1){
                continue;
            }
            seperator(address);
            int x;
            for(int i = 0 ; i < 100 ; i++){
                printf("%s\n" , count[i]);
                if(strcmp("--str" , count[i]) == 0){
                    printf("Ax\n");
                    x = i;
                    char *file_name = (char*) calloc(2000 , sizeof(char));
                    char *file_name2 = (char*) calloc(2000 , sizeof(char));
                    int slash = '/';
                    printf("address is : %s\n" , backup_address);
                    file_name = strrchr(backup_address, slash);
                    file_name2 = strtok(file_name, "/");
                    printf("file name is : %s\n" , file_name2);
                    filename(backup_address , file_name2);
                    printf("file name is : %s\n" , file_name2);
                    insert(file_name2 , backup_address);
                    printf("\nAx\n");
                    break;
                }
            }
            if(strcmp("--str" , count[x])){
                printf("invalid command");
                printf("\n--------------------\n");
            }
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

void cat(char *file_name , char *address){
    char buff[FILENAME_MAX];
    GetCurrentDir( buff, FILENAME_MAX );
    char* token1 = strtok(buff, " / ");
    while(token1 != NULL) {
        token1 = strtok(NULL, " / ");
        if(strcmp(token1 , "root") == 0){
            while(token1 != NULL) {
                chdir("..");
                token1 = strtok(NULL, "/");
            }
        }
    }
    const char *temp;
    char *temp2;
    int counter_address = 0;
    char backup_address[10000];
    strcpy(backup_address , address);
    // printf("%s\n",backup_address);
    char *temp3 = strtok(backup_address, "/");
    while(temp3 != NULL){
        counter_address++;
        temp3 = strtok(NULL, "/");
    }
    // printf("%d\n" , counter_address);
    char *token2 = strtok(address, "/");
    // printf("%s\n" , token2);
    while(token2 != NULL){
        if(strcmp(token2 , "\"") == 0){ // strcmp("/"token2"\"" , "\"") == 0
            temp = token2;
            token2 = strtok(NULL, "/");
            // printf("\"\"%s\n" , token2);
            // n++;
        }
        else{
            const int a = chdir(token2);
            // printf("$$$%s\n" , token2);
            // printf("%d\n" , a);
            // printf("%s\n" , file_name);
            if(strcmp(token2 , file_name) == 0){
                FILE * fPtr; 

                fPtr = fopen(file_name , "r");
                // printf("%d\n" , fPtr);
                char data[100000];
                if(fPtr != NULL){
                    while (fgets(data , 100000 , fPtr)){
                        printf("%s" , data);
                    }
                }
                else{
                    printf("File does not exist");
                }
                fclose(fPtr);
                printf("\n--------------------\n");
                break;
            }
            else if(a == 0){
                // printf("%s\n" , token2);
                chdir(token2);
                token2 = strtok(NULL, "/");
            }
            else{
                // printf("%s\n",token2);
                printf("There is not such a directory or file\n");
                break;
            }
        }
    }
    
}

void create_file(char *address , char *file_name){
    char buff[FILENAME_MAX];
    GetCurrentDir( buff, FILENAME_MAX );
    // printf("$$$$$%s\n" , buff);
    char* token1 = strtok(buff, " / ");
    // printf("%s\n" , address);
    while(token1 != NULL) {
        token1 = strtok(NULL, " / ");
        if(strcmp(token1 , "root") == 0){
            while(token1 != NULL) {
                // printf("%s\n" , token1);
                chdir("..");
                token1 = strtok(NULL, "/");
            }
        }
    }
    GetCurrentDir( buff, FILENAME_MAX );
    // printf("%s\n" , buff);
    // printf("%s\n" , address);
    const char *temp;
    char *temp2;
    char *temp3;
    char *token2 = strtok(address, "/");
    // printf("%s\n" , token2);
    if(strcmp(token2 , "\"") == 0){
        // printf("ASD");
        while (token2 != NULL) {
            if(strcmp(token2 , "\"") == 0){
                temp = token2;
                token2 = strtok(NULL, "/");
                // printf("\"\"%s\n" , token2);
            }
            else if(strcmp(token2 , file_name) == 0){
                FILE * a;
                a = fopen(file_name , "w");
                fclose(a);
                return;
            }
            else{
                cd(token2);
                temp = token2;
                token2 = strtok(NULL, "/");
                // printf("%s\n" , token2);
            }
        }
        // chdir("..");
        // rmdir(temp);
        // // for(int j = 0 ; j < 9 ; j++){
        // //     printf("%c\n" , temp[j]);
        // // }
        // // for(int j = 0 ; j < 8  ; j++){
        // //     temp2[j] = temp[j];
        // //     temp2[j+1]='\0';
        // //     printf("%c\n" , temp2[j]);
        // // }
        // int i = 0;
        // while(temp[i] != '\"'){
        //     temp2[i] = temp[i];
        //     temp2[i+1]='\0';
        //     // printf("%c\n" , temp2[i]);
        //     i++;
        // }
        // // printf("%s\n" , temp);
        // // printf("%s\n" , temp2);
        // // printf("%s\n" , temp3);
        // FILE * a;
        // a = fopen(temp2 , "w");
        // fclose(a);
    }
    else {
    // const char *temp;
    // char *token2 = strtok(address, " / ");
    while (strcmp(token2 , file_name)) {
        cd(token2);
        temp = token2;
        token2 = strtok(NULL, " / ");
    }
    FILE * a;
    a = fopen(file_name , "w");
    fclose(a);
    }
}

void cd(char *folder){
    mkdir(folder , 0700);
    chdir(folder);
}

int count_char_word(char *address , char *file_name){
    FILE* fp;

    char filename[FILENAME_MAX];

    char c ;
    char q;
    char counter_new_LINE = 0;
  

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Could not open file %s",
               filename);
        return 0;
    }
    for (q = getc(fp); q != EOF; q = getc(fp)){
        if(q == '\n'){
           counter_new_LINE = counter_new_LINE + 1;
        }
    }
    counter_new_LINE++;
    int count[counter_new_LINE ][3] ;

    for(int x = 0 ; x < counter_new_LINE ; x++){
        for(int q = 0 ; q < 2 ; q++){
            count[x][q] = 0;
        }
    }
    for(int x = 0 ; x < counter_new_LINE ; x++){
        for(int q = 2 ; q < 3 ; q++){
            count[x][q] = 1;
        }
    }
    fclose(fp);
    fp = fopen(file_name, "r");
    int i = 0 , j =0;
    while(c != EOF){
        for (c = getc(fp); c != '\n' && c != EOF; c = getc(fp)){
            count[i][1]++;
        }
        count[i][0] = i + 1;
        i++;
    }
    fclose(fp);
    fp = fopen(file_name, "r");
    char ch;
    i = 0;
    while ((ch = fgetc(fp)) != EOF)
    {


        if (ch == '\n' || ch == '\0')
            i++;


        if (ch == ' ' || ch == '\t')
            count[i][2]++;
    }

    fclose(fp);
  
    for(int x = 0 ; x < counter_new_LINE ; x++){
        for(int q = 0 ; q < 3 ; q++){
            printf("%d ",count[x][q]);
        }
        printf("\n");
    }
    return 0;
}

void filename(char *address ,char *file_name2){
    if(address[0] == '\"'){
        int z ;
            // printf("%lu\n",strlen(file_name2) - z);
        for(z = 1 ; file_name2[strlen(file_name2) - z] != '\"' ; ){
            file_name2[strlen(file_name2) - z] = '\0';
        }
        file_name2[strlen(file_name2) - (z)] = '\0';
    }
}

void seperator(char* address){
    char* backup_address = (char*) calloc(1000 , sizeof(char));
    strcpy(backup_address , address);
    char space = ' ';
    char* hold = strtok(address, &space);
    int q = 0;
    while (hold != NULL)
    {
        count[q] = hold;
        hold = strtok(NULL,&space);
        q++;
    }
}

void insert(char *file_name , char *address ){
    printf("%s" , address);
    return;
}

void handle_doubleCout(char *address){
    if(address[0] == "\""){

    }
}