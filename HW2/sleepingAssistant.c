#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define STUDENT_AMOUNT 5

void *studentWork(void *arg);
void *taWork();
int sleepRandomTime();

sem_t taWakeUp;
sem_t taTeaching;
pthread_mutex_t check_available = PTHREAD_MUTEX_INITIALIZER;
int chair_count = 0;
int finish_teaching_count = 0;

int main() {
    srand(time(NULL));
    pthread_t ta;
    pthread_t students[STUDENT_AMOUNT];
    int studentsId[] = {0, 1, 2, 3, 4};
    sem_init(&taWakeUp, 0, 0);
    sem_init(&taTeaching, 0, 0);
    pthread_create(&ta, NULL, taWork, NULL);
    for (int i = 0; i < STUDENT_AMOUNT; i++) {
        pthread_create(&students[i], NULL, studentWork, studentsId[i]);
    }
    pthread_join(ta, NULL);
    for (int i = 0; i < STUDENT_AMOUNT; i++) {
        pthread_join(students[i], NULL);
    }
}

void *studentWork(void *arg) {
    int *studentId = (int *)arg;
    while (1) {
        printf("student %d need help\n", *studentId);
        pthread_mutex_lock(&check_available);

        if (chair_count < 3) {
            chair_count++;
            printf("student %d waiting on seat %d\n", *studentId, chair_count);
            pthread_mutex_unlock(&check_available);
            if (chair_count == 0) {
                sem_post(&taWakeUp);
            }
            sem_wait(&taTeaching);
            printf("Student %d Leaving\n", studentId);
            pthread_exit(0);
        } else {
            pthread_mutex_unlock(&check_available);
            printf("Student %d coming back later\n");
            sleepRandomTime();
        }
    }
}

void *taWork() {
    while (1) {
        printf("ta is sleeping\n");
        sem_wait(&taWakeUp);
        printf("ta is waked up\n");
        while (chair_count != 0) {
            pthread_mutex_lock(&check_available);
            printf("helping student\n");
            chair_count--;
            pthread_mutex_unlock(&check_available);
            sleepRandomTime();
            printf("finish teaching this student\n");
            finish_teaching_count++;
            sem_post(&taTeaching);

            if (finish_teaching_count == 5) {
                printf("all %d students been help\n", STUDENT_AMOUNT);
                pthread_exit(0);
            }
        }
    }
}

int sleepRandomTime() {
    sleep(rand()%10 + 1);
}