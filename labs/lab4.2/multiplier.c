#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include "logger.h"

long *readMatrix(char *filename);
long *getColumn(int col, long *matrix);
long *getRow(int col, long *matrix);
int getLock();
int releaseLock(int lock);
long dotProduct(long *vec1, long *vec2);
long *multiply(long *matA, long *matB);
int saveResultMatrix(long *result);
void *thread(void *arg);

int NUM_BUFFERS;
long **buffers;
pthread_mutex_t *mutexes;
long *result;
pthread_t threads[2000];

struct Storage {
    long *matA;
    long *matB;
    size_t rowLoc;
    size_t colLoc;
    long *result;
};

int main(int argc, char **argv){
    // Place your magic here

    char usage[32] = "Usage: ./multiplier -n [NUMBER]";
    long *matA, *matB;

    if (argc != 3){
        errorf("Uncompatible number of arguments: %d, %s", argc, *usage);
        exit(EXIT_FAILURE);
    }else if (strcmp(argv[1], "-n")){
        errorf("%s", usage);
        exit(EXIT_FAILURE);
    }else {
        for (int i=0; i<strlen(argv[2]); i++){
            if (!isdigit(argv[2][i])){
                errorf("%s is not a number. %s", argv[2], *usage);
		exit(EXIT_FAILURE);
            }
        }
	    NUM_BUFFERS = strtol(argv[2], NULL, 10);
	    if (NUM_BUFFERS < 8){
		    errorf("Buffers should be of at least size 8");
		    exit(EXIT_FAILURE);
	    }
    }

    buffers = (long **)malloc(NUM_BUFFERS * sizeof(long *));
    mutexes = (pthread_mutex_t *)malloc(NUM_BUFFERS * sizeof(pthread_mutex_t));

    for (int i=0; i<NUM_BUFFERS; i++){
	    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
        mutexes[i] = mutex;
        pthread_mutex_init(&mutexes[i], NULL);
    }

    matA = readMatrix("matA.dat");
    matB = readMatrix("matB.dat");

    infof("Matrix multiplication started\n");
    warnf("This could take a while...\n");

    result = multiply(matA, matB);

    saveResultMatrix(result);

    infof("Result of oparation saved to \"result.dat\"\n");

    return 0;
}

long *readMatrix(char *filename){

    FILE *fp;
    char *line;
    long *matrix;
    size_t len = 0;

    fp = fopen(filename, "r");
    if (fp == NULL){
        errorf("file %s not found or couldn't be opened", filename);
        exit(EXIT_FAILURE);
    }

    matrix = (long *)malloc(2000*2000 * sizeof(long));
    
    for(int i = 1; getline(&line, &len, fp) != -1; i++){
        matrix[i] = strtol(line, NULL, 10);
    }

    return matrix;

}

long *getColumn(int col, long *matrix){

    size_t offset = col -1;
    long *tempCol;

    tempCol = (long *)malloc(2000*sizeof(long));

    for (int i = 0; i<2000; i++){
        tempCol[i] = matrix[offset];
        offset +=2000;
    }

    return tempCol;

}

long *getRow(int row, long *matrix){
    
    size_t offset = ((2*row)-2)*1000;
    long *tempRow;

    tempRow=(long *)malloc(2000*sizeof(long));

    for (int i=0; i<2000; i++){
        tempRow[i] = matrix[offset++];
    }
    return tempRow;
}

int getLock(){
    
    for (int i=0; i<NUM_BUFFERS; i++){
        if(pthread_mutex_trylock(&mutexes[i])==0){
            return i;
        }
    }
    return -1;
}

int releaseLock(int lock){
    if (pthread_mutex_unlock(&mutexes[lock])==0){
        return 0;
    }
    return -1;
}

long dotProduct(long *vec1, long *vec2){
    long tempResult = 0;

    for (int i=0; i<2000; i++){
        tempResult +=vec1[i] * vec2[i];
    }
    return tempResult;
}

long *multiply(long *matA, long *matB){

    result = (long *)malloc(2000*2000*sizeof(long));

    for(size_t i=0; i<2000; i++){
        for (size_t j=0; j<2000; j++){

            struct Storage *tempStorage;
            tempStorage = (struct Storage *)malloc(sizeof(struct Storage));

            tempStorage-> matA =matA;
            tempStorage-> matB =matB;
            tempStorage-> rowLoc= i+1;
            tempStorage-> colLoc= j+1;
            tempStorage-> result= result;

            pthread_create(&threads[j], NULL, thread, (void *)tempStorage);          

        }

        for(size_t j=0; j<2000; j++){
            pthread_join(threads[j], NULL);
        }
        printf("\r%ld%% Completed", (i*100)/1999);
        fflush(stdout);
    }
    printf("\n");
    return result;

}

int saveResultMatrix(long *result){

    FILE *fp2 = fopen("result.dat", "w");
    if (fp2 == NULL){
        errorf("file result.dat couldn't be created");
        exit(EXIT_FAILURE);
    }

    for(size_t i=0; i<(2000*2000); i++){
        fprintf(fp2, "%ld\n", result[i]);
    }

    fclose(fp2);
    return 0;
}

void *thread(void *arg){
    
    struct Storage *storage = (struct Storage *)arg;
    long index;
    int lockA, lockB;

    while((lockA = getLock())==-1);
    while((lockB = getLock())==-1);

    buffers[lockA] = getRow(storage->rowLoc, storage->matA);
    buffers[lockB] = getColumn(storage->colLoc, storage->matB);

    index = ((((storage->rowLoc -1)*2000)+ storage->colLoc)-1);
    storage->result[index] = dotProduct(buffers[lockA], buffers[lockB]);

    free(buffers[lockA]);
    free(buffers[lockB]);
    free(arg);

    while(releaseLock(lockA)!=0);
    while(releaseLock(lockB)!=0);

    return NULL;
}
