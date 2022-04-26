#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HISTORY_SIZE 100
static char *history[HISTORY_SIZE];
int historyCount = 0;

void getHostName(){
    char name[128];
    gethostname(name, sizeof(name)-1);
    printf("%s:", name);
}

void getLogName(){
    struct passwd* pass;
    pass = getpwuid(getuid());
    printf("%s@", pass->pw_name);
}

void getDir(){
    char pwd[128];
    getcwd(pwd, sizeof(pwd)-1);
    int len = strlen(pwd);
    char* p = pwd+len-1;
    while(*p != '/'){
        p--;
    }
    p++;
    printf(" %s$ ", p);
}


int main(){
    while(1){
        // getLogName();
        // getHostName();
        // getDir(); 
        //Linuxstyle

        printf("osh> ");
        fflush(stdout);

        char cmd[128];
        ssize_t _s = read(0, cmd, sizeof(cmd)-1);
        if(_s > 0){
            cmd[_s-1]='\0';
        }
        else{
            perror("readline fail");
            return 0;
        }

        if(strcmp(cmd, "exit") == 0){
            break;
        }
        else if(strcmp(cmd, "history") == 0){
            for(int i = 0; i < historyCount; i++) {
		        printf("%i %s\n", i+1, history[i]);
	        }
        }
        
        history[historyCount] = strdup(cmd);
        historyCount++;

        if(strcmp(cmd, "!!") == 0){
			if(*history == 0){
			    printf("empty history\n");
			}
            else{
                strcpy(cmd, history[historyCount-2]);
            }
		}

        char* _argv[32];
        _argv[0] = cmd;
        char* start = cmd;
        int i =1;
        while(*start){
            if(isspace(*start)){
                *start ='\0';
                start++;
                _argv[i] = start;
                i++;
                continue;
            }
            start++;
        }
        _argv[i] = NULL;


        pid_t pid;

        pid = fork();

        if(pid < 0){
            perror("Fork Fail\n");
            return 1;
        }
        else if(pid == 0){
            execvp(_argv[0], _argv);
            exit(1);
        }
        else{
            int status = 0;
            pid_t ret = waitpid(pid,&status,0);
        }
    }
    return 0;
}