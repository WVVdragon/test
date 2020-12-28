#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#define TRUE 1
#define MAX_SIZE 1024

void print_prompt(){
    char cwd[MAX_SIZE];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Wei @Wei :%s ", cwd);
    }
}

int read_input(char* str){
    char buf[MAX_SIZE]; 
    fgets(buf, MAX_SIZE, stdin); 
    if (strlen(buf) != 1) { 
        strcpy(str, buf); 
        return 1; 
    } else {
        return 0; 
    }
}

int exec_command(char* user_input){
    char* inputs[MAX_SIZE];
    bzero(inputs, MAX_SIZE); // Very imortant, fuck gcc!
    char* token = strtok(user_input, " ");
    int i=0;
    while (token != NULL) {
        inputs[i] = token;
        i++;
        token = strtok(NULL, " "); 
    }
    if(strcmp(inputs[0], "exit")==0){
        printf("Bye.\n");
        return 1;
    }
    if(strcmp(inputs[0], "cd")==0){
        chdir(inputs[1]);
        return 0;
    }
    char path[100];
    bzero(path, 100);
    strcat(path, "/bin/");
    strcat(path, inputs[0]);
    if (fork() != 0){
        int *status;
        waitpid(-1, status, 0);
    } else {
        execve(path, inputs, 0);
    }
    return 0;
}

void main(){
    while(TRUE){
        char input_string[MAX_SIZE];
        print_prompt();
        if(!read_input(input_string)) continue;
        int len = strlen(input_string);
        input_string[len-1]='\0';
        if(exec_command(input_string)) break;
    }
}

