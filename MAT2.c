/**
* @file Q2.c
* @brief Medial axis transformation (MAT) 
*
* @author Harshit Verma
*
* @date 08/5/19
*/
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <stdbool.h> 
#include <string.h>
#include <time.h>

//! Quadtree node
struct node {
    int label;
    int bit;
    int level;
};

int N, n, **arr, **max_sq_arr, top = 0;
struct node _quadtree[6000];
double TOTAL_TIME = 0;

/**
* This method will be used to get value of input array from input.txt file
* @author diksha
* @date 08/4/2019
*/
void initialize() {
    __clock_t 	start_time, end_time;
	start_time = clock();

    FILE *fp = fopen("input.txt", "r");
    
    if(fp == NULL) {printf("No input.txt file found!\n"); return;}

    char ch; int x = 0;
    while( (ch = fgetc(fp)) != EOF) {
        if(ch == ' ' || ch == '\n') continue;
        x++;
    }

    n = sqrt(x);

    end_time = clock();
    TOTAL_TIME += (double)(end_time - start_time) / CLOCKS_PER_SEC;
}

/**
* This method will be used to read the array from input.txt file
* @author diksha
* @date 08/4/2019
*/
void read_inputfile() {
    __clock_t 	start_time, end_time;
	start_time = clock();

    FILE *fp = fopen("input.txt", "r");
    
    if(fp == NULL) {printf("No input.txt file found!\n"); return;}

    char ch; 
    int i = 1, j = 1;
    while( (ch = fgetc(fp)) != EOF) {
        if(ch == ' ' || ch == '\n') continue;
        arr[i][j] = ch - '0';
        
        j++;
        if(j == n+1) { j = 1; i++;}
    }

    end_time = clock();
    TOTAL_TIME += (double)(end_time - start_time) / CLOCKS_PER_SEC;
}

/**
* This method will be used to normalize the array size to pow of 2.
* @param n the size of input array 
* @author harshit Verma
* @date 08/5/2019
*/
void change(int n) {
    __clock_t 	start_time, end_time;
	start_time = clock();

    N = pow(2, ceil(log2(n)));

    end_time = clock();
    TOTAL_TIME += (double)(end_time - start_time) / CLOCKS_PER_SEC;
}

/**
* This method will be used to fill the maximal square array with node value
* @author diksha
* @date 08/4/2019
*/
void get_the_msa(int x1, int y1, int x2, int y2, int node) {
    __clock_t   start_time, end_time;
    start_time = clock();

    for(int i = x1; i <= x2; i++)
        for(int j = y1; j <= y2; j++)
            max_sq_arr[i][j] = node;

    end_time = clock();
    TOTAL_TIME += (double)(end_time - start_time) / CLOCKS_PER_SEC;        
}


/**
* This method will be used to check if subarray has same bits 
* @author diksha
* @date 08/4/2019
*/
bool check_same_bits(int x1, int y1, int x2, int y2) {
    __clock_t 	start_time, end_time;
	start_time = clock();

    int bit = arr[x1][y1];

    for(int i = x1; i <= x2; i++)
        for(int j = y1; j <= y2; j++) 
            if(arr[i][j] != bit) return false;

    end_time = clock();
    TOTAL_TIME += (double)(end_time - start_time) / CLOCKS_PER_SEC;

    return true;
}


/**
* This recursive method will be used to set the msa array with node values 
* @author diksha
* @date 08/4/2019
*/
int Matrix(int x1, int y1, int x2, int y2, int node, int level) {
     __clock_t 	start_time, end_time;
	start_time = clock();

    if(check_same_bits(x1, y1, x2, y2)) { 
        get_the_msa(x1, y1, x2, y2, node);
        
        _quadtree[top].label = node;
        _quadtree[top].bit = arr[x1][y1];
        _quadtree[top].level = level;
        top++;

        return ++node;
    }

    node = Matrix(x1, y1, (x1 + x2) / 2, (y1 + y2) / 2, node, level+1);
    node = Matrix(x1, (y1 + y2) / 2 + 1, (x1 + x2) / 2, y2, node, level+1);
    node = Matrix((x1 + x2) / 2 + 1, y1, x2, (y1 + y2) / 2, node, level+1);
    node = Matrix((x1 + x2) / 2 + 1, (y1 + y2) / 2 + 1, x2, y2, node, level+1);

    end_time = clock();
    TOTAL_TIME += (double)(end_time - start_time) / CLOCKS_PER_SEC;
    
    return node;
}

int main() {
    
    initialize();

    change(n);

    arr = (int **) malloc ((N+1) * sizeof(int*));
    for(int i = 0; i < N+1; i++)
        arr[i] = (int *) malloc((N+1) * sizeof(int));

    max_sq_arr = (int **) malloc ((N+1) * sizeof(int*));
    for(int i = 0; i < N+1; i++)
        max_sq_arr[i] = (int *) malloc((N+1) * sizeof(int));

    read_inputfile();

    int x = Matrix(1, 1, N, N, 1, 0);


    while(1) {
        
        printf("------- Medial axis transformation (MAT) -------\n");
        printf("1. Maximal square array\n");
        printf("2. Quadtree\n");
        printf("3. Exit\n");

        int cases;
        scanf("%d", &cases);

        switch(cases) {
            
            case 1 : {
                
                putchar('\n');
                printf("Maximal square array :");
                putchar('\n');
                putchar('\n');
                for(int i = 1; i <= N; i++) {
                    for(int j = 1; j <= N; j++)
                        printf("%d ", max_sq_arr[i][j]);
                    putchar('\n');
                }
                putchar('\n');
                break;
            }

            case 2 : {
                
                for(int i = 0; i < top; i++) {
                    printf("%d, %d, %d\n", _quadtree[i].label, _quadtree[i].bit, _quadtree[i].level);
                }

                break;
            }

            case 3 : {
                printf("CPU Time : %f\n", TOTAL_TIME);      
                printf("Program terminating..\n");
                return 0;
            }
            default : {
                printf("the opted case cannot be implemented!");
            }
        }    
    }
}