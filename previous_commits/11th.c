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
int len = 0; 

void help();
void cat(char * , char *);
int checking_validation(char *);
void create_file(char * , char *);
void cd(char *);
int count_char_word(char * , char * ,char * , char *);
void filename(char *,char *);
void seperator(char *);
void insert(char *,char * , char *, char *);
void position(char * , char * , char * );
void handle_doubleCout(char *);

int main() {    
    mkdir("root" , 0700);
    chdir("root");
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

        char cmd[4];
        char val[7];
        char address[1000];
        scanf("%4s" , cmd);
        if(strcmp(cmd , "HELP") == 0) {
            help();
        }
        else if(strcmp(cmd , "CAT") == 0){
            scanf("%s" , val);
            scanf(" %[^\n]%*c" , address);
            handle_doubleCout(address);
            printf("NEW add is : %s\n" , address);
            if(checking_validation(val) == 1){
                continue;
            }
            char *file_name = (char*) calloc(2000 , sizeof(char));
            char *file_name2 = (char*) calloc(2000 , sizeof(char));
            int slash = '/';
            file_name = strrchr(address, slash);
            file_name2 = strtok(file_name, "/");
            filename(address , file_name2);
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
            create_file(address , file_name2);
            printf("File created successfully.\n");
            printf("\n--------------------\n");
        }
        else if(strcmp(cmd,"INF") == 0){
            char pos_line = 0;
            char pos_char = 0;
            scanf("%s" , val);
            scanf(" %[^\n]%*c" , address);
            char *backup_address = (char*) calloc(2000 , sizeof(char));
            char *backup_address2 = (char*) calloc(2000 , sizeof(char));
            strcpy(backup_address , address);
            strcpy(backup_address2 , address);
            if(checking_validation(val) == 1){
                continue;
            }
            seperator(address);
            int x;
            for(int i = 0 ; i < 100 ; i++){
                printf("%s\n" , count[i]);
                if(strcmp("--str" , count[i]) == 0){
                    x = i;
                    char *file_name = (char*) calloc(2000 , sizeof(char));
                    char *file_name2 = (char*) calloc(2000 , sizeof(char));
                    int slash = '/';
                    file_name = strrchr(backup_address, slash);
                    file_name2 = strtok(file_name, "/");
                    filename(backup_address , file_name2);
                    position(backup_address2 , pos_line , pos_char);
                    insert(file_name2 , backup_address2 , pos_line , pos_char);
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
    char *temp3 = strtok(backup_address, "/");
    while(temp3 != NULL){
        counter_address++;
        temp3 = strtok(NULL, "/");
    }
    char *token2 = strtok(address, "/");
    while(token2 != NULL){
        if(strcmp(token2 , "\"") == 0){ 
            temp = token2;
            token2 = strtok(NULL, "/");
        }
        else{
            const int a = chdir(token2);
            if(strcmp(token2 , file_name) == 0){
                FILE * fPtr; 

                fPtr = fopen(file_name , "r");
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
                chdir(token2);
                token2 = strtok(NULL, "/");
            }
            else{
                printf("There is not such a directory or file\n");
                break;
            }
        }
    }
    
}

void create_file(char *address , char *file_name){
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
    GetCurrentDir( buff, FILENAME_MAX );
    const char *temp;
    char *temp2;
    char *temp3;
    char *token2 = strtok(address, "/");
    if(strcmp(token2 , "\"") == 0){
        while (token2 != NULL) {
            if(strcmp(token2 , "\"") == 0){
                temp = token2;
                token2 = strtok(NULL, "/");
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
            }
        }
        
    }
    else {
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

int count_char_word(char *address , char *file_name , char *pos1 , char *pos2){
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
    if(*pos1 > counter_new_LINE) return -1;
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
    if(*pos2 > count[*pos1][1]) return -1;

    return 1;
}

void filename(char *address ,char *file_name2){
    if(address[0] == '\"'){
        int z ;
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

void insert(char *file_name , char *address , char *pos1 , char *pos2){
    printf("%s\n" , address);
    char *backup_address2 = (char*) calloc(2000 , sizeof(char));
    strcpy(backup_address2 , address);
    char *add = strtok(backup_address2 , "--str");
    printf("%s\n" , add);
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
    char *temp3 = strtok(backup_address, "/");
    while(temp3 != NULL){
        counter_address++;
        temp3 = strtok(NULL, "/");
    }
    char *token2 = strtok(address, "/");
    while(token2 != NULL){
        if(strcmp(token2 , "\"") == 0){ 
            temp = token2;
            token2 = strtok(NULL, "/");
        }
        else{
            const int a = chdir(token2);
            if(strcmp(token2 , file_name) == 0){
                if(count_char_word(address , file_name , pos1 , pos2)){
                    printf("kar dare\n");
                }
                else if(count_char_word(address , file_name , pos1 , pos2) == -1){
                    printf("The position does not exist\n");
                    break;
                }
            }
            else if(a == 0){
                chdir(token2);
                token2 = strtok(NULL, "/");
            }
            else{
                printf("There is not such a directory\n");
                break;
            }
        }
    }
    
    return;
}

void handle_doubleCout(char *address){
    int k = 0 ; 
    if(address[0] == '\"') k ++ ; 

    for(int i = 0 ; i < strlen(address)  ; i++ ){
    address[i] = address[i+k] ; 
    }
    for(int i = strlen(address) - 1 ; i >= 0 ; i--){
        if(address[i] == '\"'){
            address[i] = '\0';
            break;
        }
    }
}

void position(char *address , char *pos1 , char *pos2){
    char *backup_address = (char*) calloc(2000 , sizeof(char));
    char *backup_address2 = (char*) calloc(2000 , sizeof(char));
    strcpy(backup_address , address);
    strcpy(backup_address2 , address);
    char *possition_second = strtok(backup_address2 , "--pos");
    printf("%s\n" , possition_second);
    char *temp;
    while(possition_second != NULL){
        temp = possition_second;
        possition_second = strtok(NULL , "--pos");
    }
    pos1 = temp[1];
    pos2 = temp[3];
}

void directory(char *dir1 , char **dir2){
    int i = 0 , Have_Space = 0 , len = 0;
    char c;
    while(1){
        scanf("%c" , &c);
        if(c != '\"' && i == 0) Have_Space = 1;
        if(c != '\"' && c != '\n' && c != '-'){ dir1[i] = c ; i++ ; }
        if(Have_Space == 1 && c == ' '){dir1[i - 1] = '\0' ; break;}
        if(c == '-'){if(dir1[i - 1] == 0){dir1 = '\0';} break;}
        if(c == '\n') break;
    }
    char *token = strtok(dir1 , "/");
    int x = 0;
    while(token != NULL){
        dir2[x] = token;
        x++;
        token = strtok(NULL , "/");
        len++;
    }
}