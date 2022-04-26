#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LENGTH 80

char history[10][MAX_LENGTH];

int getInput(char *str) {
    char c;
    int i = 0;
    while ((c = getchar()) != '\n' && i < MAX_LENGTH) {
        str[i] = c;
        i++;
    }
    if (i >= 80) {
        printf("command too long!!!");
        return 0;
    } else {
        return i;
    }
}

void displayHistory(int history_front, int history_rear) {
    int index = 0;
    if (history_front != history_rear) {
        for (int i = history_front; i < (history_rear + 10) % 10; i++) {
            printf("[%d]\t%s", index, history[i]);
            index++;
        }
    } else {
        printf("no command!!!");
    }
}

void addHistory(char *str, int *history_front, int *history_rear) {
    strcpy(history[*history_rear], str);
    *history_rear = (*history_rear + 1) % 10;
    if (*history_front == *history_rear) {
        *history_front = (*history_front + 1) % 10;
    }
}

int changeIntoArgs(char *str, char *args[]) {
    int i = 0;
    char *temp = strtok(str, " ");
    while (temp != NULL && i < MAX_LENGTH/2) {  // 不用 "+1" 因為原本的需在 "-1"
        strcpy(args[i], temp);
        temp = strtok(NULL, " ");
        i++;
    }
    return i;
}

int main(void) {
    int str_length = 0;
    char str[MAX_LENGTH];
    char *args[MAX_LENGTH/2 + 1];
    int history_front = 0;
    int history_rear = 0;
    int args_length = 0;
    int process_status;

    while (1) {
        printf("osh>");     // start
        fflush(stdout);

        str_length = getInput(str);
        if (str_length == 0) continue;

        if (strcmp(str, "exit") == 0) {     // check command
            return 0;
        } else if (strcmp(str, "!!") == 0) {
            if (history_front != history_rear) {
                strcpy(str, history[(history_rear - 1) % 10]);
                str_length = strlen(str);
            } else {
                printf("no command!!!");
            }
        } else if (strcmp(str, "history") == 0) {
            displayHistory(history_front, history_rear);
        } else {
            addHistory(str, &history_front, &history_rear);
        }

        args_length = changeIntoArgs(str, args);    // change into args for child process

        pid_t pid = fork();
        if (pid < 0) {
            printf("fork failed");
            return 1;
        } else if (pid == 0) {
            execvp(args[0], args);
        } else {
            wait(&process_status);
            if (process_status == -1) {
                printf("command fail");
            }
        }
    }
    return 0;
}