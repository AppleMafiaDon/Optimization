//
// Created by AppleT on 5/9/2019.
//
/*!
 * \file FA.c
 * \brief This is where all methods defined in src/FA.h are implemented.
 *
 */

#include "FA.h"
#include "Utilities.h"
#include "MersenneMatrix.h"



void* fireflyAlg(void* data){
    EquationInfo info = *(EquationInfo*)data;
    int iterations = info.iterations;
    struct timespec start, /*!< Declare the timespec struct storing the start time of the iterations*/
            end; /*!< Declare the timespec struct storing the end time of the iterations*/
    double totTMillSec; /*!< Declare the double storing the total runtime of all iterations in milliseconds*/
    double** temp = allocateEmptyMatrix(info.numVectors, info.dimToTest);
    FireflySwarm* fireflies = calloc(1, sizeof(FireflySwarm));
    fireflies->population = createMatrix(info);
    fireflies->fitness = calloc(info.numVectors, sizeof(double));
    fireflies->dimensions = info.dimToTest;
    evaluatePop(fireflies->population, fireflies->fitness, info.numVectors, info.dimToTest, info.equationNum, &fireflies->bestPos, &fireflies->worstPos, &fireflies->bestFit, &fireflies->worstFit);
    for(int i = 0; i < iterations; i++){
        clock_gettime(CLOCK_MONOTONIC, &start); /*!< Set the start time using a monotonic clock, meaning it will ignore if the system clock changes*/
        copyMatrix(fireflies->population, temp, info.numVectors, info.dimToTest);
        fireflyLoop(fireflies, temp, info.numVectors, info.beta, info.gamma, info.alpha, info.equationNum, info.range);
        clock_gettime(CLOCK_MONOTONIC, &end);/*!< Store the end time*/
        totTMillSec = (double)((end.tv_sec - start.tv_sec) * MS_PER_SEC) +  ((end.tv_nsec - start.tv_nsec) / (double) NS_PER_MS); /*!< Calculate the total runtime by subtracting end time's seconds from the start time's seconds and converting to milliseconds and adding the end time's nanoseconds minus the start time's nanoseconds and converting to milliseconds*/
        ///write the best and worst to a file
        writeResultToFile(fireflies->bestFit, fireflies->worstFit, "FA", i, totTMillSec, info);
        if(info.currExperiment == info.printExperiment) {
            ///write the new population to a log file
            writePopulationLogToFile(fireflies->population, "FA", i, info);
        }
    }
    freeMatrix(temp, info.numVectors);
    freeFireflySwarm(fireflies, info.numVectors);
}



double lightIntensity(const double* fitness, int iPos, double gamma, double distance){
    return fitness[iPos] * exp(-1 * gamma * distance);
}

void fireflyLoop(FireflySwarm* fireflies, double** temp, int popSize, double beta, double gamma, double alpha, int equation, double* range){
    for(int i = 0; i < popSize; i++){
        moveFirefliesLoop(fireflies, temp, i, beta, gamma, alpha, equation, popSize, range);
    }
}

double calcDistanceSquared(const double* fireflyI, const double* fireflyJ, int dimensions){
    double distance = 0,
    disTerm = 0;
    for(int i = 0; i < dimensions; i++){
        disTerm = (fireflyI[i] - fireflyJ[i]);
        distance += disTerm * disTerm;
    }
    return distance;
}

double calcAttractiveness(double** temp, int iPos, int jPos, int currDim, double beta, double gamma, double distance){
    return beta * exp(-1 * gamma * distance) * (temp[jPos][currDim] - temp[iPos][currDim]);
}

double* calcAttractedVector(double** temp, int iPos, int jPos, int dimensions, double beta, double alpha, double gamma, const double* range, double distance){
    double* newVector = calloc(dimensions, sizeof(double));
    double firefly = 0;
    for(int i = 0; i < dimensions; i++){
        firefly = temp[iPos][i] + calcAttractiveness(temp, iPos, jPos, i, beta, gamma, distance) + (alpha * (genDblInRange(0, 1) - 0.5) * (range[RANGE_MAX_POS] - range[RANGE_MIN_POS]));
        if(firefly < range[RANGE_MIN_POS]){
            firefly = range[RANGE_MIN_POS];
            newVector[i] = firefly;
        }
        else if(firefly > range[RANGE_MAX_POS]){
            firefly = range[RANGE_MAX_POS];
            newVector[i] = firefly;
        }
        else{
            newVector[i] = firefly;
        }
    }
    return newVector;
}

void moveFirefliesLoop(FireflySwarm* fireflies, double** temp, int iPos, double beta, double gamma, double alpha, int equation, int popSize, double* range){
    double lightIntensityI = 0,
    distance = 0,
    newFitness = 0;
    double* newVector;
    int dimensions = fireflies->dimensions;
    for(int j = 0; j < popSize; j++){
        distance = calcDistanceSquared(temp[iPos], temp[j], dimensions);
        lightIntensityI = lightIntensity(fireflies->fitness, iPos, gamma, distance);
        if(lightIntensity(fireflies->fitness, j, gamma, distance) < lightIntensityI){
            newVector = calcAttractedVector(temp, iPos, j, dimensions, beta, alpha, gamma, range, distance);
            newFitness = evaluateFitness(newVector, dimensions, equation);
            if(newFitness < fireflies->bestFit){
                newBest(fireflies, newVector, newFitness, popSize);
            }
            else if(newFitness < fireflies->worstFit){
                addVector(fireflies, newVector, newFitness, popSize);
            }
            free(newVector);
        }
    }
}

void newBest(FireflySwarm* pop, double* newVector, double newResult, int popSize){
    pop->bestFit = newResult;
    pop->bestPos = pop->worstPos;
    addVector(pop, newVector, newResult, popSize);
}

void addVector(FireflySwarm* pop, double* newVector, double newResult, int popSize){
    pop->fitness[pop->worstPos] = newResult;
    copyArray(newVector, pop->population[pop->worstPos], pop->dimensions);
    evalNewWorst(pop->fitness, popSize, newResult, &pop->worstPos, &pop->worstFit);
}