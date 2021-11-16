//
// Created by AppleT on 5/9/2019.
//

/*!
 * \file PSO.c
 * \brief This is where all methods defined in General/PSO.h are implemented.
 *
 */

#include "PSO.h"
#include "Utilities.h"
#include "MersenneMatrix.h"

void* particleSwarmAlg(void* data){
    EquationInfo info = *(EquationInfo*)data;
    int iterations = info.iterations,
    numVec = info.numVectors,
    numDim = info.dimToTest;
    struct timespec start, /*!< Declare the timespec struct storing the start time of the iterations*/
            end; /*!< Declare the timespec struct storing the end time of the iterations*/
    double totTMillSec; /*!< Declare the double storing the total runtime of all iterations in milliseconds*/
    Particle* particles = calloc(1, sizeof(Particle));
    createParticles(particles, numVec, numDim, info);
    evaluatePop(particles->population, particles->fitness, numVec, numDim, info.equationNum, &particles->bestPos, &particles->worstPos, &particles->gBestFit, &particles->gWorstFit);
    copyArray(particles->fitness, particles->pBestFit, numVec);
    for(int i =0; i < iterations; i++){
        clock_gettime(CLOCK_MONOTONIC, &start); /*!< Set the start time using a monotonic clock, meaning it will ignore if the system clock changes*/
        particleLoop(particles, numVec, numDim, info.c1, info.c2, info.k, info.range, info.equationNum); ///run the particle swarm loop for this iteration
        clock_gettime(CLOCK_MONOTONIC, &end);/*!< Store the end time*/
        totTMillSec = (double)((end.tv_sec - start.tv_sec) * MS_PER_SEC) +  ((end.tv_nsec - start.tv_nsec) / (double) NS_PER_MS); /*!< Calculate the total runtime by subtracting end time's seconds from the start time's seconds and converting to milliseconds and adding the end time's nanoseconds minus the start time's nanoseconds and converting to milliseconds*/
        ///write the best and worst to a file
        writeResultToFile(particles->gBestFit, particles->gWorstFit, "PSO", i, totTMillSec, info);
        if(info.currExperiment == info.printExperiment) {
            ///write the new population to a log file
            writePopulationLogToFile(particles->population, "PSO", i, info);
        }
    }
    ///free PSO
    freeParticles(particles, info.numVectors);
}

double calcPBestModifier(Particle* particles, double c1, int vecPos, int dimPos){
    return c1 * genDblInRange(0, 1) * (particles->personalBest[vecPos][dimPos] - particles->population[vecPos][dimPos]);
}

double calcGBestModifier(Particle* particles, double c2, int vecPos, int dimPos){
    return c2 * genDblInRange(0, 1) * (particles->personalBest[particles->bestPos][dimPos] -  particles->population[vecPos][dimPos]);
}

void calcNewVelocity(Particle* particles, int dimensions, int position, double c1, double c2, double k){
    for(int i = 0; i < dimensions; i++){
        particles->velocities[position][i] = k * (particles->velocities[position][i] + calcPBestModifier(particles, c1, position, i) + calcGBestModifier(particles, c2, position, i));
    }
}

void calcNewVector(Particle* particles, int dimensions, int position, const double* range){
    double temp = 0;
    for(int i = 0; i < dimensions; i++){
        temp = particles->population[position][i] + particles->velocities[position][i];
        if(temp < range[RANGE_MIN_POS]){
            temp = range[RANGE_MIN_POS];
            particles->population[position][i] = temp;
        }
        else if(temp > range[RANGE_MAX_POS]){
            temp = range[RANGE_MAX_POS];
            particles->population[position][i] = temp;
        }
        else{
            particles->population[position][i] = temp;
        }
    }
}

void particleLoop(Particle* particles, int numParticles, int dimensions, double c1, double c2, double k, double* range, int equation){
    double newFitness = 0;
    for(int i = 0; i < numParticles; i++){
        calcNewVelocity(particles, dimensions, i, c1, c2, k);
        calcNewVector(particles, dimensions, i, range);
        newFitness = evaluateFitness(particles->population[i], dimensions, equation);
        particles->fitness[i] = newFitness;
        if(newFitness < particles->pBestFit[i]){
            particles->pBestFit[i] = newFitness;
            copyArray(particles->population[i], particles->personalBest[i], dimensions);
        }
        if(newFitness < particles->gBestFit){
            particles->gBestFit = newFitness;
            particles->bestPos = i;
        }
    }
}