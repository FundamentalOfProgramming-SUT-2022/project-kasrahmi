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
int len = 0 , pos_line , pos_char , Have_Space = 0 , counter_new_LINE , size ;
char bORf; 

void help();
void cat(char * , char *);
int checking_validation(char *);
void create_file(char * , char *);
void cd(char *);
int count_char_word(char * ,int , int);
void filename(char *,char *);
void insert();
void position(char * , char * , char * );
void directory(char * , char **);
void go_to_directory(char **);
void go_to_root();
void remove_file();

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
            scanf("%s" , val);
            if(checking_validation(val) == 1){
                continue;
            }
            insert();
        }
        else if(strcmp(cmd , "RMV") == 0){
            scanf("%s" , val);
            if(checking_validation(val) == 1){
                continue;
            }
            remove_file();
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

int count_char_word(char *file_name , int pos1 , int pos2){
    FILE* fp;

    char filename[FILENAME_MAX];

    char c ;
    char q;
    counter_new_LINE = 0;
  

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
    if(pos1 > counter_new_LINE || pos1 < 1) {
        return -1;
    }
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
    if(pos2 > count[pos1 - 1][1] || pos2 < 0) return -1;

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

void insert(){
    char dir1[1000];
    char *dir2[100];
    char valstr[20] = "12345678";
    char matn[10000];
    char temp;
    getchar();
    directory(dir1 , dir2);
    go_to_root();
    go_to_directory(dir2);
    if(Have_Space == 0){
        valstr[0] = '-';
        int i;
        for(i = 1 ; ; i++){
            valstr[i] = getchar();
            if(valstr[i] == ' ') break;
        }
        valstr[i] = '\0';
    }
    else{
        scanf("%s" , valstr);
    }
    getchar();
    if(strcmp(valstr , "--str") == 0){
        temp = getchar();
        if(temp != '\"'){
            Have_Space = 1;
            matn[0] = temp;
            temp = getchar();
            int x = 1;
            while(temp != ' '){
                matn[x] = temp;
                temp = getchar();
                x++;
            }
        }
        else{
            Have_Space = 0;
            int x = 0;
            while(1){
                scanf("%c" , &matn[x]);
                if(matn[x] == '-'){
                    if(matn[x-1] == ' '){
                        if(matn[x-2] == '\"'){
                            matn[x-2] = '\0';
                            break;
                        }
                    }
                }
                x++;
            }           
        }
        printf("your text is : %s\n" , matn);
        char posstr[20] ="1234567890";
        if(Have_Space == 0){
            posstr[0] = '-';
            int i;
            for(i = 1 ; ; i++){
                posstr[i] = getchar();
                if(posstr[i] == ' ') break;
            }
            posstr[i] = '\0';
        }
        else{
            scanf("%s" , posstr);
        }
        if(strcmp(posstr , "--pos") == 0) {
            scanf("%d:%d" , &pos_line , &pos_char);
        }
        else{ printf("Invalid command!\n"); return;}
        FILE * fPtr; 
        fPtr = fopen(dir2[len - 1] , "r");
        if(fPtr == NULL){
            printf("File does not exist\n");
            return;
        }
        else{
            int a = count_char_word(dir2[len - 1] , pos_line , pos_char);
            if(a == -1){
                printf("position does not exist\n");
                return;
            }
            else if(a == 1){
                FILE * newFile;
                newFile = fopen("nemidoonam" , "w");
                int row = 0 , character = 0;
                int fileChar;
                // printf("pos line is : %d\ncounter new line is : %d\n" , pos_line , counter_new_LINE);
                while (row < pos_line - 1){
                    fileChar = fgetc(fPtr);
                    // printf("filechar is : %c\n" , fileChar);
                    fputc(fileChar , newFile);
                    if(fileChar == '\n') row++;
                }

                while (character < pos_char ){
                    fileChar = fgetc(fPtr);
                    // printf("filechar is : %c\n" , fileChar);
                    fputc(fileChar , newFile);
                    character++;
                }
                for(int a = 0 ; matn[a] != '\0' ; a++){
                    int x = matn[a];
                    if(matn[a] == '\\'){ 
                        if(matn[a+1] == '\\'){ 
                            if(matn[a+2] == 'n') {
                                fprintf(newFile , "\\n"); 
                                a = a + 2;
                            }
                        }
                        else if(matn[a] == '\\') {
                            if(matn[a+1] == 'n') {
                                int y = '\n';
                                fputc(y , newFile);
                                a = a + 1;
                            }
                        }
                    }
                    else {
                        fputc(x , newFile);
                    }
                }
                while(fileChar != EOF){
                    fileChar = fgetc(fPtr);
                    if(fileChar == EOF) break;
                    fputc(fileChar , newFile);
                }
                fclose(newFile);
                fclose(fPtr);
                fPtr = fopen(dir2[len - 1] , "w");
                newFile = fopen("nemidoonam" , "r");
                fileChar = fgetc(newFile);
                // printf("filechar is : %c\n" , fileChar);
                while (fileChar != EOF)
                {
                    // printf("filechar is : %c\n" , fileChar);
                    fputc(fileChar,fPtr);
                    fileChar = fgetc(newFile);
                }
                fclose(newFile);
                fclose(fPtr);
                remove("nemidoonam");
            }
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
    int i = 0  , flag = 0; 
    len = 0 ;
    Have_Space = 0;
    char c;
    scanf("%c" , &c);
    if(c != '\"' ) {
        Have_Space = 1;
    }
    while(flag == 0){
        scanf("%c" , &c);
        if(c != '\"' && c != '\n' && c != '-'){
            dir1[i] = c; 
            dir1[i + 1] = '\0';
            i++ ; 
        }
        if(Have_Space == 1 && c == ' '){
            dir1[i] = '\0' ; 
            flag = 1;
        }
        if(c == '-'){
            if(dir1[i - 1] == 0){
                dir1[i - 1] = '\0';
            } 
            flag = 1;
        }
        if(c == '\n') {
            flag=1;
        }
    }
    char *token = strtok(dir1 , "/");
    int x = 0;
    while(token != NULL){
        dir2[x] = token;
        x++;
        len++;
        token = strtok(NULL , "/");
    }
}

void go_to_root(){
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
}

void go_to_directory(char **dir){
    for(int i = 0 ; i < len - 1 ; i++){
        const int a = chdir(dir[i]);
        if(a == 0){
            chdir(dir[i]);
        }
        else{
            printf("There is not such a directory or file\n");
            break;
        }
    }
}

void remove_file(){
    char dir1[1000];
    char *dir2[100];
    char posstr[20] = "12345678";
    char matn[10000];
    char temp;
    getchar();
    directory(dir1 , dir2);
    go_to_root();
    go_to_directory(dir2);
    if(Have_Space == 0){
        posstr[0] = '-';
        int i;
        for(i = 1 ; ; i++){
            posstr[i] = getchar();
            if(posstr[i] == ' ') break;
        }
        posstr[i] = '\0';
    }
    else{
        scanf("%s" , posstr);
    }
    if(strcmp(posstr , "--pos") == 0){
        scanf("%d:%d" , &pos_line , &pos_char);
        char sizestr[20];
        scanf("%s" , sizestr);
        if(strcmp(sizestr , "--size") == 0){
            scanf("%d" , &size);
            getchar();
            scanf("%c" , &bORf);
            if(size < 1 || (bORf != 'b' && bORf != 'f')){
                printf("Invalid command\n");
                return;
            }

        }
    }
}