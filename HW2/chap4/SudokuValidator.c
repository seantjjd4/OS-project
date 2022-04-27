#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int sudoku[9][9] = {
        {6, 2, 4, 5, 3, 9, 1, 8, 7},
        {5, 1, 9, 7, 2, 8, 6, 3, 4},
        {8, 3, 7, 6, 1, 4, 2, 9, 5},
        {1, 4, 3, 8, 6, 5, 7, 2, 9},
        {9, 5, 8, 2, 4, 7, 3, 6, 1},
        {7, 6, 2, 3, 9, 1, 4, 5, 8},
        {3, 7, 1, 9, 5, 6, 8, 4, 2},
        {4, 9, 6, 1, 8, 2, 5, 7, 3},
        {2, 8, 5, 4, 7, 3, 9, 1, 6}
};

bool verification[11];
int auxSquares = 2;

typedef struct {
    int row;
    int column;
} parameter;

pthread_t columns, row, first_square, second_square, third_square,
        fourth_square, fifth_square, sixth_square, seventh_square, eighth_square, ninth_square;


void *travelColumns(void *parameters) {

    parameter *column = (parameter *) parameters;
    int columnInit = column->column;
    int rowInit = column->row;

    for (int i = columnInit; i < 9; i++) {
        int col[9] = {0};
        for (int j = rowInit; j < 9; j++) {
            int aux = sudoku[i][j];
            if (col[aux - 1] == 0 && aux > 0) {
                col[aux - 1] = aux;
            } else if (aux <= 0) {
                verification[0] = 0;
                printf("Sorry, there is an invalid number in column [%d].\n", j + 1);
                pthread_exit(0);
            } else {
                verification[0] = 0;
                printf("Sorry, there is a repeated number in column [%d].\n", j + 1);
                pthread_exit(0);
            }
        }
    }
    verification[0] = 1;
    pthread_exit(0);
}

void *travelRows(void *parameters) {

    parameter *row = (parameter *) parameters;
    int columnInit = row->column;
    int rowInit = row->row;

    for (int i = columnInit; i < 9; i++) {
        int fil[9] = {0};
        for (int j = rowInit; j < 9; j++) {
            int aux = sudoku[i][j];
            if (fil[aux - 1] == 0 && aux > 0) {
                fil[aux - 1] = aux;
            } else if (aux <= 0) {
                verification[0] = 0;
                printf("Sorry, there is an invalid number in row [%d].\n", i + 1);
                pthread_exit(0);
            } else {
                verification[0] = 0;
                printf("Sorry, there is a repeated number in row [%d].\n", i + 1);
                pthread_exit(0);
            }
        }
    }
    verification[1] = 1;
    pthread_exit(0);
}

void *travelSquares(void *parameters) {

    parameter *squareW = (parameter *) parameters;
    int rowInit = squareW->row;
    int columnInit = squareW->column;
    int square[9] = {0};

    for (int i = rowInit; i < rowInit + 3; ++i) {
        for (int j = columnInit; j < columnInit + 3; ++j) {
            int aux = sudoku[i][j];
            if (square[aux - 1] == 0 && aux > 0) {
                square[aux - 1] = aux;
            }
            else {
                verification[auxSquares] = 0;
                auxSquares++;
                pthread_exit(0);
            }
        }
    }
    verification[auxSquares] = 1;
    auxSquares++;
    pthread_exit(0);
}

int main(int argc, char *argv[]) {

    parameter *checkrows = (parameter *) malloc(sizeof(parameter));
    checkrows->row = 0;
    checkrows->column = 0;

    parameter *checkcolumns = (parameter *) malloc(sizeof(parameter));
    checkcolumns->row = 0;
    checkcolumns->column = 0;

    parameter *square1 = (parameter *) malloc(sizeof(parameter));
    square1->row = 0;
    square1->column = 0;

    parameter *square2 = (parameter *) malloc(sizeof(parameter));
    square2->row = 0;
    square2->column = 3;

    parameter *square3 = (parameter *) malloc(sizeof(parameter));
    square3->row = 0;
    square3->column = 6;

    parameter *square4 = (parameter *) malloc(sizeof(parameter));
    square4->row = 3;
    square4->column = 0;

    parameter *square5 = (parameter *) malloc(sizeof(parameter));
    square5->row = 3;
    square5->column = 3;

    parameter *square6 = (parameter *) malloc(sizeof(parameter));
    square6->row = 3;
    square6->column = 6;

    parameter *square7 = (parameter *) malloc(sizeof(parameter));
    square7->row = 6;
    square7->column = 0;

    parameter *square8 = (parameter *) malloc(sizeof(parameter));
    square8->row = 6;
    square8->column = 3;

    parameter *square9 = (parameter *) malloc(sizeof(parameter));
    square9->row = 6;
    square9->column = 6;

    pthread_create(&columns, NULL, travelColumns, (void *) checkcolumns);
    pthread_create(&row, NULL, travelRows, (void *) checkrows);
    pthread_create(&first_square, NULL, travelSquares, (void *) square1);
    pthread_create(&second_square, NULL, travelSquares, (void *) square2);
    pthread_create(&third_square, NULL, travelSquares, (void *) square3);
    pthread_create(&fourth_square, NULL, travelSquares, (void *) square4);
    pthread_create(&fifth_square, NULL, travelSquares, (void *) square5);
    pthread_create(&sixth_square, NULL, travelSquares, (void *) square6);
    pthread_create(&seventh_square, NULL, travelSquares, (void *) square7);
    pthread_create(&eighth_square, NULL, travelSquares, (void *) square8);
    pthread_create(&ninth_square, NULL, travelSquares, (void *) square9);
    
    pthread_join(columns, NULL);
    pthread_join(row, NULL);
    pthread_join(first_square, NULL);
    pthread_join(second_square, NULL);
    pthread_join(third_square, NULL);
    pthread_join(fourth_square, NULL);
    pthread_join(fifth_square, NULL);
    pthread_join(sixth_square, NULL);
    pthread_join(seventh_square, NULL);
    pthread_join(eighth_square, NULL);
    pthread_join(ninth_square, NULL);

    for (int k = 0; k < 11; ++k) {
        if (!verification[k]) {
            printf("Oopsie... The Sudoku is wrong!\n");
            exit(0);
        }
    }
    printf("Nice! The Sudoku is perfect!\n");
    return 0;
}