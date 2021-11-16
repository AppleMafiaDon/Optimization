//
// Created by AppleT on 5/13/2019.
//

/*!
 * \file Harmonic.c
 * \brief This is where all methods defined in General/Harmonic.h are implemented.
 *
 */

#include "Harmonic.h"
#include "MersenneMatrix.h"
#include "Utilities.h"
#include "Equations.h"


void* harmonicTest(void* data){
    EquationInfo info = *(EquationInfo*)data;
    HPop* hpop = calloc(1, sizeof(HPop));
    hpop->population = createMatrix(info);
    allocateHPop(hpop, info.numVectors);
    int iterations = info.iterations;
    double newResult = 0;
    struct timespec start, /*!< Declare the timespec struct storing the start time of the iterations*/
            end; /*!< Declare the timespec struct storing the end time of the iterations*/
    double totTMillSec; /*!< Declare the double storing the total runtime of all iterations in milliseconds*/
    double** temp = allocateEmptyMatrix(info.numVectors, info.dimToTest);
    evaluatePop(hpop->population, hpop->fitness, info.numVectors, info.dimToTest, info.equationNum, &hpop->bestPos, &hpop->worstPos, &hpop->bestFit, &hpop->worstFit);
    for(int i = 0; i < iterations; i++){
        clock_gettime(CLOCK_MONOTONIC, &start); /*!< Set the start time using a monotonic clock, meaning it will ignore if the system clock changes*/
        harmonicIteration(hpop, info.dimToTest, info.numVectors, info.HMCR, info.PAR, info.bandwidth, info.range);
        newResult = evaluateFitness(hpop->newHarmonic, info.dimToTest, info.equationNum);
        if(newResult < hpop->bestFit){
            updateBest(hpop, newResult, info);
        }else if(newResult <= hpop->worstFit){
            newVector(hpop, newResult, info);
        }
        free(hpop->newHarmonic);
        clock_gettime(CLOCK_MONOTONIC, &end);/*!< Store the end time*/
        totTMillSec = (double)((end.tv_sec - start.tv_sec) * MS_PER_SEC) +  ((end.tv_nsec - start.tv_nsec) / (double) NS_PER_MS); /*!< Calculate the total runtime by subtracting end time's seconds from the start time's seconds and converting to milliseconds and adding the end time's nanoseconds minus the start time's nanoseconds and converting to milliseconds*/
        ///write the best and worst to a file
        writeResultToFile(hpop->bestFit, hpop->worstFit, "H", i, totTMillSec, info);
        if(info.currExperiment == info.printExperiment) {
            ///write the new population to a log file
            writePopulationLogToFile(hpop->population, "H", i, info);
        }
    }
    freeHPop(hpop, info.numVectors);
}

void updateBest(HPop* pop, double newResult, EquationInfo info){
    pop->bestFit = newResult;
    pop->bestPos = pop->worstPos;
    newVector(pop, newResult, info);
}

void newVector(HPop* pop, double newResult, EquationInfo info){
    pop->fitness[pop->worstPos] = newResult;
    copyArray(pop->newHarmonic, pop->population[pop->worstPos], info.dimToTest);
    evalNewWorst(pop->fitness, info.numVectors, newResult, &pop->worstPos, &pop->worstFit);
}

void pitchAdjustment(double* harmonic,int position, double bandwidth, const double* range){
    double rand = genDblInRange(-1,1);
    double temp = harmonic[position];

    temp += rand * bandwidth;
    if(temp < range[RANGE_MIN_POS]){
        temp = range[RANGE_MIN_POS];
        harmonic[position] = temp;
    }
    else if(temp > range[RANGE_MAX_POS]){
        temp = range[RANGE_MAX_POS];
        harmonic[position] = temp;
    }
    else{
        harmonic[position] = temp;
    }
}

void harmonicIteration(HPop* hpop, int NI, int HMS, double HMCR, double PAR, double bandwidth, const double* range){
    double* newHarmonic = calloc(NI, sizeof(double));

    for(int i = 0; i < NI; i++){
        if(genDblInRange(0, 1) < HMCR){
            newHarmonic[i] = hpop->population[genNonNegInt(HMS)][i];
            if(genDblInRange(0, 1) < PAR){
                pitchAdjustment(newHarmonic, i, bandwidth, range);
            }
        }else{
            newHarmonic[i] = genDblInRange(range[RANGE_MIN_POS],range[RANGE_MAX_POS]);
        }
    }
    hpop->newHarmonic = newHarmonic;
}