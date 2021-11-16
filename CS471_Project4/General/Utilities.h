//
// Created by TappleDon on 4/2/2019.
//
/*!
 * \file Utilities.h
 * \brief This is where all general purpose methods, constants, enums, and structs are declared.
 *
 */
#ifndef TESTINGSUITE_UTILITIES_H
#define TESTINGSUITE_UTILITIES_H
#include "Equations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif


#define MINIMUM_ITERATIONS 30 /*!< declare the constant for the minimum number of iterations*/
#define RANGE_SIZE 2 /*!< declare the constant for the size of a range*/
#define RANGE_MIN_POS 0 /*!< declare a constant representing the location of the minimum value in the range*/
#define RANGE_MAX_POS 1 /*!< declare a constant representing the location of the maximum value in the range*/
#define LINE_LENGTH 10000 /*!< declare a constant for reading in lines of a certain length for the input file*/
#define MAX_NUM_EQUATIONS 18 /*!< declare the constant for the maximum number of equations being evaluated*/
#define MAX_FILE_NAME_LEN 255 /*!< declare the constant for creating the filename string*/
#define DEFAULT_INIT_FILE "../General/init.txt" /*!< declare the constant representing the default input file location for the program*/
#define FILE_ARGUMENT 1 /*!< declare the constant for the */
#define NS_PER_MS 1000000 /*!< declare the constant for converting nanoseconds to milliseconds*/
#define MS_PER_SEC 1000 /*!< declare the constant to convert milliseconds to seconds*/


/*!
 * The enum which represents the position of the different functions utilized through the application.
 * Referenced in General/EquationHandlers.c, and General/EquationHandlers32.c
 */
enum EquationPosition{
    Schwefel,
    DeJong,
    Rosenbrock,
    Rastgrin,
    Griewangk,
    SineEnvelope,
    StretchedWave,
    AckleyOne,
    AckleyTwo,
    EggHolder,
    Rana,
    Pathological,
    Michalewicz,
    MastersCosineWave,
    Quartic,
    Levy,
    Step,
    Alpine
};

/*!
 * enum representing the selected test type to be run as selected by the user in General/Init.c
 */
enum TestType{
    ParticleSwarm, Firefly, Harmonic
};

/*!
 * stores all of the necessary information for the program to run for all functions and all test types
 */
typedef struct _Info{
    int numExperiments;
    int numVectors;
    int numDimensions;
    int numEquations;
    double** ranges;
    int* dimsToTest;
    int iterations;
    int testSelection;
    double bandwidth;
    double PAR;
    double HMCR;
    double beta;
    double gamma;
    double alpha;
    double c1;
    double c2;
    double k;
} Info;

/*!
 * stores all of the information required by a single equation for a single set of dimensions to be processed in the selected test type.
 * used in Win32/EquationsHandlers32.c and PThread/EquationHandlers.c
 */
typedef struct _EquationInfo{
    char* equationName;
    int currExperiment;
    int printExperiment;
    int equationNum;
    int numVectors;
    double* range;
    int dimToTest;
    int iterations;
    double bandwidth;
    double PAR;
    double HMCR;
    double beta;
    double gamma;
    double alpha;
    double c1;
    double c2;
    double k;
}EquationInfo;

/*!
 * Stores all information related to a population necessary for the Particle Swarm meta heuristics
 */
typedef struct _Particle{
    double* pBestFit;
    double gBestFit;
    double gWorstFit;
    double** velocities;
    double** personalBest;
    double** population;
    double* fitness;
    int worstPos;
    int bestPos;
}Particle;

/*!
 * Stores all information related to a population necessary for the Firefly Algorithm meta heuristics
 */
typedef struct _FireflySwarm{
    double** population;
    double* fitness;
    int dimensions;
    double bestFit;
    int bestPos;
    double worstFit;
    int worstPos;
}FireflySwarm;

/*!
 * Stores all information related to a population necessary for the Harmonic Search meta heuristics
 */
typedef struct _HarmonicPop{
    double bestFit;
    int bestPos;
    double worstFit;
    int worstPos;
    double** population;
    double* fitness;
    double* newHarmonic;
}HPop;

#ifdef WIN32
HANDLE mutex; /*!< declare the Windows 32 mutex handle to be used when generating random numbers*/
int genRandInt32(int modulo); /*!< declare the win32 method for threaded random integers*/
double genRandReal32(); /*!< declare the win32 method for threaded random real numbers*/
#else
pthread_mutex_t mutex;  /*!< declare the POSIX mutex  to be used when generating random numbers*/
int genRandIntP(int modulo); /*!< declare the POSIX method for threaded random integers*/
double genRandRealP(); /*!< declare the POSIX method for threaded random real numbers*/
#endif

/// \fn void writeResultToFile(double bestFit, double worstFit, char* algorithm, int currIter, double time, EquationInfo info)
/// \brief This is the method which writes the results of the current Iteration to the designated result file
///
/// \param bestFit - The best fitness of the current iteration
/// \param worstFit - the worst fitness of the current iteration
/// \param algorithm - the algorithm name being run, used for file name
/// \param currIter - the current iteration being written to the file
/// \param time - the time the iteration took to run
/// \param info - The EquationInfo struct which houses the information for setting up the process
/// \return No return as it simply prints to a file
void writeResultToFile(double bestFit, double worstFit, char* algorithm, int currIter, double time, EquationInfo info);
/// \fn void writePopulationLogToFile(double** population, char* algorithm, int currIter, EquationInfo info)
/// \brief This is the method which writes the population log to a file tracking the changes in the population per iteration of an experiment
///
/// \param population - The population resulting from the current iteration
/// \param algorithm - the algorithm name being run, used for file name
/// \param currIter - the current iteration being written to the file
/// \param info - The EquationInfo struct which houses the information for setting up the process
/// \return No return as it simply prints to a file
void writePopulationLogToFile(double** population, char* algorithm, int currIter, EquationInfo info);
/// \fn void printDArray(double* list, int size)
/// \brief This is the method which prints a double array to the console for debugging
///
/// \param list - The array to be printed
/// \param size - size of the array
/// \return No return as it simply prints to console
void printDArray(double* list, int size);
/// \fn void printIArray(int* list, int size)
/// \brief This is the method which prints an integer array to the console for debugging
///
/// \param list - The array to be printed
/// \param size - size of the array
/// \return No return as it simply prints to console
void printIArray(int* list, int size);
/// \fn void printMatrix(double** matrix, int numRows, int numCols)
/// \brief This is the method which prints a 2 dimensional array of doubles to the console for debugging
///
/// \param matrix - The 2 dimensional array to be printed
/// \param numRows - the number of rows in matrix
/// \param numCols - the number of columns per row in matrix
/// \return No return as it simply prints to console
void printMatrix(double** matrix, int numRows, int numCols);
/// \fn double** allocateEmptyMatrix(int popSize, int dimensions)
/// \brief This is the method which allocates the space for an empty population of a certain size with a certain number of dimensions
///
/// \param popSize - The number of rows to be allocated
/// \param dimensions - The number of columns to be allocated per row
/// \return returns an empty matrix
double** allocateEmptyMatrix(int, int);
/// \fn void allocateHPop(HPop* pop, int popSize)
/// \brief This is the method which allocates the fitness array for the HPop struct
///
/// \param pop - The HPop struct being initialized
/// \param popSize - The size of the population being initialized
/// \return No return as it modifies the struct directly
void allocateHPop(HPop* pop, int popSize);
/// \fn void createParticles(Particle* particles, int numVectors, int dimensions, EquationInfo info)
/// \brief Initializes a Particle struct for the algorithm implemented in General/PSO.c
///
/// \param particles - the struct to be initialized
/// \param numVectors  - the number of particles to be stored in the population
/// \param dimensions  - the dimensions of the particles in the population
/// \param info - the EquationInfo struct housing equation specific info
void createParticles(Particle* particles, int numVectors, int dimensions, EquationInfo info);
/// \fn void copyArray(double* in, double* out, int size)
/// \brief This method is used to copy the values from one array into another so the original can be freed
///
/// \param in - the array to be copied
/// \param out - the array to story the values being copied
/// \param size - number of values in the array being copied
/// \return No return as it modifies the pointer directly
void copyArray(const double*, double*, int);
/// \fn void copyMatrix(double** in, double** out, int height, int width)
/// \brief This method is used to copy the values from one matrix into another so the original can be freed
///
/// \param in - the matrix to be copied
/// \param out - the matrix to story the values being copied
/// \param height - number of rows in the matrix being copied
/// \param width - numbver of columns in the matrix being copied
/// \return No return as it modifies the pointer directly
void copyMatrix(double**, double**, int, int);
/// \fn double evaluateFitness(double* firefly, int dimensions, int equation)
/// \brief This method is responsible for executing the appropriate objective function on the given vector.
///
/// \param firefly - The given vector to be sent to the objective function
/// \param dimensions - the number of dimensions in the vector
/// \param equation - the objective function number to be run against
/// \return the fitness of the vector with regards to the objective function
double evaluateFitness(double* firefly, int dimensions, int equation);
/// \fn void evaluatePop(double** pop, double* fitness, int popSize, int dimensions, int equation, int* objBestPos, int* objWorstPos, double* objBestFit, double* objWorstFit)
/// \brief Takes an entire population, evaluates the fitness of the entire population and stores the best and worst fitness, and the positions in the population
/// of these fitnesses for aiding the algorithm processing.
///
/// \param pop - the population matrix for the struct being processed
/// \param fitness - pointer to the fitness array of the processed population
/// \param popSize - The number of rows to be evaluated
/// \param dimensions - The number of columns in the row to be evaluated
/// \param equation - the objective function number to be run against
/// \param objBestPos - pointer to the structs best position
/// \param objWorstPos - pointer to the structs worst position
/// \param objBestFit - pointer to the structs best fitness
/// \param objWorstFit - pointer to the structs worst fitness
void evaluatePop(double** pop, double* fitness, int popSize, int dimensions, int equation, int* objBestPos, int* objWorstPos, double* objBestFit, double* objWorstFit);
/// \fn void evalNewWorst(const double* fitness, int popSize, double newResult, int* objWorstPos, double* objWorstFit)
/// \brief Evaluates the population to determine the fitness and position of the worst vector in the population.
///
/// \param fitness - the array of fitness values for the population
/// \param popSize - the size of the population to be checked
/// \param newResult - the fitness of the newly developed vector
/// \param objWorstPos - pointer to the structs worst position
/// \param objWorstFit - pointer to the structs worst fitness
void evalNewWorst(const double* fitness, int popSize, double newResult, int* objWorstPos, double* objWorstFit);

/// \fn void freeEquationInfo(EquationInfo* info)
/// \brief frees the EquationInfo struct and related information when a process thread is done
///
/// \param info - The EquationInfo struct which houses the information for setting up the individual process threads
/// \return No return as it only frees memory
void freeEquationInfo(EquationInfo*);
/// \fn void freeInfo(Info* info)
/// \brief This frees the Info struct when the program has finished
///
/// \param info - The Info struct which houses the information for the whole program
/// \return No return as it only frees memory
void freeInfo(Info*);
/// \fn void freeMatrix(double** matrix, int height)
/// \brief frees a matrix of the given size
///
/// \param matrix - 2 dimensional array to be freed
/// \param height - number of rows in the matrix
/// \return No return as it only frees memory
void freeMatrix(double**, int);
/// \fn void freeHPop(HPop* pop, int popSize)
/// \brief frees the HPop struct
///
/// \param pop - the struct to be freed
/// \param popSize - the size of the population which is being freed
void freeHPop(HPop* pop, int popSize);
/// \fn void freeFireflySwarm(FireflySwarm* pop, int popSize)
/// \brief frees the FireflySwarm struct
///
/// \param pop - the struct to be freed
/// \param popSize - the size of the population which is being freed
void freeFireflySwarm(FireflySwarm* pop, int popSize);
/// \fn void freeParticles(Particle* particles, int popSize)
/// \brief frees the Particle struct passed in
///
/// \param particles - the struct to be freed
/// \param popSize - the size of the population which is being freed
void freeParticles(Particle* particles, int popSize);

#endif //TESTINGSUITE_UTILITIES_H
