//
// Created by TappleDon on 4/2/2019.
//
/*!
 * \file Utilities.c
 * \brief This is where all general purpose methods are implemented. All methods are defined in General/Utilities.h
 *
 */
#include "Utilities.h"
#include "MersenneMatrix.h"
#include "HostCalls.h"
#include <fcntl.h>

void lock(){
#ifdef WIN32
    WaitForSingleObject(mutex, INFINITE );///lock for writing to file WIN32
#else
    pthread_mutex_lock(&mutex);///lock for writing to file POSIX
#endif
}

void unlock(){
#ifdef WIN32
    ReleaseMutex(mutex);///done writing to file WIN32
#else
    pthread_mutex_unlock(&mutex);///done writing to file POSIX
#endif
}

void writeResultToFile(double bestFit, double worstFit, char* algorithm, int currIter, double time, EquationInfo info){
    char filename [MAX_FILE_NAME_LEN], /*!< Declare the filename as a static char array of MAX_FILE_NAME_LENGTH defined in General/Utilities.h*/
            value[LINE_LENGTH];/*!< Declare the static char array of LINE_LENGTH size defined in General/Utilities.h which will store the values to be printed to the file*/
    lock();
    sprintf(filename, "../Results/%d_Dimensions_results_%s.csv",info.dimToTest, algorithm); ///set the file name to our expected file
    FILE* output = fopen(filename, "a+"); ///open the file in append mode
    if(!output){ ///if there is an error opening the file tell the user and exit failure
        fprintf(stderr, "There was an issue opening or creating %s. Make sure you have access to write to the directory.\n", filename);
        exit(EXIT_FAILURE);
    }
    int numIter = info.iterations; ///store the number of iterations locally
    sprintf(value, "%d,%d,%d,%d,%s,%lf,%lf,%lf\n", info.currExperiment, currIter, info.dimToTest, info.equationNum, info.equationName, bestFit, worstFit, time);///store the current test information to value to be written
    fwrite(value, 1, strlen(value),output); ///write this to the file
    unlock();
    fclose(output); ///close the file
}

void writePopulationLogToFile(double** population, char* algorithm, int currIter, EquationInfo info){
    char filename [MAX_FILE_NAME_LEN], /*!< Declare the filename as a static char array of MAX_FILE_NAME_LENGTH defined in General/Utilities.h*/
            value[LINE_LENGTH];/*!< Declare the static char array of LINE_LENGTH size defined in General/Utilities.h which will store the values to be printed to the file*/
    sprintf(filename, "../Results/%s_%d_Dimensions_log_%s.csv", info.equationName, info.dimToTest, algorithm); ///set the file name to our expected file
    FILE* output = fopen(filename, "a+"); ///open the file in append mode
    if(!output){ ///if there is an error opening the file tell the user and exit failure
        fprintf(stderr, "There was an issue opening or creating %s. Make sure you have access to write to the directory.\n", filename);
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < info.numVectors; i++) {
        sprintf(value, "%d,%d,%s,%d,%d", info.currExperiment, info.equationNum, info.equationName, currIter, i);/// for every row store the current test information to value to be written
        fwrite(value, 1, strlen(value), output); ///write this to the file
        /*!
         * Iterate through the dimensions of the row and write the value of the current dimension to the file.
         */
        for(int j = 0; j < info.dimToTest; j++){
            sprintf(value, ",%lf", population[i][j]);
            fwrite(value, 1, strlen(value),output);
        }
        sprintf(value, "\n");
        fwrite(value, 1, strlen(value),output);
    }
    fclose(output); ///close the file
}

void printDArray(double* list, int size) {
    printf("[ ");///add a character indicating the start of an array to the buffer
    /*!
     * iterate through the array and add to the buffer the current value separated by commas
     */
    for (int i = 0; i < size; i++) {
        if(i != 0){
            printf(", ");
        }
        printf("%0.9f", list[i]);
    }
    /*!
     * finally add a character to signify the end of the array to the buffer and flush the buffer to the console
     */
    printf("] \n"); fflush(stdout);
}

void printIArray(int* list, int size) {
    printf("[ ");///add a character indicating the start of an array to the buffer
    /*!
     * iterate through the array and add to the buffer the current value separated by commas
     */
    for (int i = 0; i < size; i++) {
        if(i != 0){
            printf(", ");
        }
        printf("%d", list[i]);
    }
    /*!
     * finally add a character to signify the end of the array to the buffer and flush the buffer to the console
     */
    printf("] \n"); fflush(stdout);
}

void printMatrix(double** matrix, int numRows, int numCols) {
    /*!
     * iterate through each row of the matrix
     */
    for (int i = 0; i < numRows; i++) {
        printf("[");///add a character indicating the start of a row to the buffer
        /*!
         * iterate through the array and add to the buffer the current value separated by commas
         */
        for (int j = 0; j < numCols; j ++) {
            if(j != 0){
                printf(", ");
            }
            printf("%0.3f", matrix[i][j]);
        }
        /*!
         * finally add a character to signify the end of the row to the buffer and flush the buffer to the console, then moving to the next row
         */
        printf("]\n"); fflush(stdout);
    }
}

double** allocateEmptyMatrix(int popSize, int dimensions){
    double** pop = calloc(popSize, sizeof(double*));///allocate space for population size number of pointers
    /*!
     * iterate for the population size and allocate space initializing the values to 0 for each pointer
     */
    for (int i = 0; i<popSize; i++){
        pop[i] = calloc(dimensions, sizeof(double));
    }
    return pop;///return the pointer for your population
}

void copyArray(const double* in, double* out, int size){
    /*!
     * iterate through the array being copied, and store the value at the current position to that position in the new array
     */
    for (int i = 0; i < size;i++){
        out[i] = in[i];
    }
}

void copyMatrix(double** in, double** out, int height, int width){
    /*!
     * iterate through the array being copied, and store the value at the current position to that position in the new array
     */
     for(int j = 0; j < height; j++) {
         for (int i = 0; i < width; i++) {
             out[j][i] = in[j][i];
         }
     }
}

void allocateHPop(HPop* pop, int popSize){
    ///the fitness array storing fitness values for the population is allocated
    pop->fitness = calloc(popSize, sizeof(double));
}

void createParticles(Particle* particles, int numVectors, int dimensions, EquationInfo info){
    particles->population = createMatrix(info); ///Create a random population matrix
    particles->velocities = createVelocities(info); ///create random initial velocities for the population
    particles->personalBest = allocateEmptyMatrix(numVectors, dimensions); ///allocate an empty matrix to store the personal best particles
    copyMatrix(particles->population, particles->personalBest,numVectors, dimensions); ///copy the initial matrix into the personal best matrix
    particles->fitness = calloc(numVectors, sizeof(double)); ///allocate the fitness array
    particles->pBestFit = calloc(numVectors, sizeof(double)); ///allocate the array storing personal best fitness
}

double evaluateFitness(double* firefly, int dimensions, int equation){
    double(*eqFunction)(); /*!< Declare a function pointer of type double to represent the current equation to be used*/
    eqFunction = equationHostCalls[equation]; /*!< Set the function to the appropriate function reference defined above*/
    return eqFunction(firefly, dimensions); ///return the result of the calculation on the vector
}

void evaluatePop(double** pop, double* fitness, int popSize, int dimensions, int equation, int* objBestPos, int* objWorstPos, double* objBestFit, double* objWorstFit){
    double bestFit = 0, /*!< Initialize the best fitness to 0*/
            worstFit = 0, /*!< Initialize the worst fitness to 0*/
            currFit = 0; /*!< Initialize the current fitness to 0*/
    int bestPos = 0, /*!< Initialize the position of the best fitness to 0*/
            worstPos = 0; /*!< Initialize the position of the worst fitness to 0*/
    /*!
     * Iterate through the population, evaluate the fitness of the current vector, store that fitness, and if its the first iteration
     * store this as the best and worst fitness to be compared against. Otherwise for other iterations if it is less than the best fitness
     * save this value and position as the best otherwise if it is greater than the worst fitness store this value and
     * position as the worst.
     */
    for (int i = 0; i < popSize; i++){
        currFit = evaluateFitness(pop[i], dimensions, equation);
        fitness[i] = currFit;
        if(i == 0){
            bestFit = currFit;
            worstFit = currFit;
        }else {
            if(currFit < bestFit){
                bestFit = currFit;
                bestPos = i;
            }else if(currFit > worstFit){
                worstFit = currFit;
                worstPos = i;
            }
        }
    }
    *objBestFit = bestFit; ///store the best fitness to the address provided
    *objBestPos = bestPos; ///store the position of the best fitness to the address provided
    *objWorstFit = worstFit; ///store the worst fitness to the address provided
    *objWorstPos = worstPos; ///store the position of the worst fitness to the address provided
}

void evalNewWorst(const double* fitness, int popSize, double newResult, int* objWorstPos, double* objWorstFit){
    double worstFit = newResult, /*!< Initialize the worst fitness to the newResult*/
            currFit = 0; /*!< Initialize the current fitness to 0*/
    int worstPos = 0; /*!< Initialize the position of the worst fitness to 0*/
    /*!
     * Iterate through the population and for each fitness value if it is greater than the worst fitness then set
     * the worst fitness to this value and the position to the current iteration.
     */
    for (int i = 0; i < popSize; i++){
        currFit = fitness[i];
        if(currFit > worstFit){
            worstPos = i;
            worstFit = currFit;
        }
    }
    *objWorstFit = worstFit; ///store the worst fitness to the address provided
    *objWorstPos = worstPos; ///store the position of the worst fitness to the address provided
}


void freeEquationInfo(EquationInfo* info){
    free(info->range);///free the pointer storing the range for values to be used in the equation
}

void freeMatrix(double** matrix, int height){
    /*!
     * iterate through the rows of the matrix and free the pointers for each row
     */
    for (int i = 0; i < height; i++) {
        free(matrix[i]);
    }
}

void freeInfo(Info* info){
    free(info->dimsToTest); ///free the pointer storing the dimensions which will be tested as part of the program
    if(info->ranges != NULL) {///if ranges exists free the matrix of ranges
        freeMatrix(info->ranges, info->numEquations);
        free(info->ranges);
    }
}

void freeHPop(HPop* pop, int popSize){
    freeMatrix(pop->population, popSize); ///free the population matrix
    free(pop->fitness); ///free the fitness array
}

void freeFireflySwarm(FireflySwarm* pop, int popSize){
    freeMatrix(pop->population, popSize); ///free the population matrix
    free(pop->fitness); ///free the fitness array
}

void freeParticles(Particle* particles, int popSize){
    free(particles->pBestFit); ///free the array of personal best fitness values
    free(particles->fitness); ///free the array of fitness values
    freeMatrix(particles->population, popSize); ///free the population matrix
    freeMatrix(particles->personalBest, popSize); ///free the personal best population matrix
    freeMatrix(particles->velocities, popSize); ///free the velocities matrix
}