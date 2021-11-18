//
// Created by AppleT on 5/9/2019.
//
/*!
 * \file FA.h
 * \brief This is where all methods pertaining to the Firefly Algorithm implementation are defined.
 *
 *  Firefly algorithm is the process of taking each firefly/vector and comparing it to every other firefly in the population.
 *  If the fitness of the compared vector is better than the current vector then a new vector is created moving dimensions
 *  in the direction of the better vector and then evaluating this newly developed vector. This new vector replaces the worst
 *  vector and the process continues.
 */
#ifndef CS471_PROJECT4_FA_H
#define CS471_PROJECT4_FA_H

#include "Utilities.h"

/// \fn void* fireflyAlg(void* data)
/// \brief Responsible for initializing the algorithm and all data related to the algorithm and calling related functions to start and record results fo the algorithm
///
/// \param data - void pointer to be converted to an EquationInfo struct
/// \return Nothing as it is a threaded function
void* fireflyAlg(void* data);
/// \fn double lightIntensity(const double* fitness, int iPos, double gamma, double distance)
/// \brief Calculates the light intensity of the firefly using a given distance and light absorption rate gamma and the current fitness
///
/// \param fitness - array of fitness values
/// \param iPos - fitness position of the light intensity being calculated
/// \param gamma - light absorption rate
/// \param distance - distance between fireflies
/// \return The value of the light intensity inverse squarely proportional to the distance
double lightIntensity(const double* fitness, int iPos, double gamma, double distance);
/// \fn void fireflyLoop(FireflySwarm* fireflies, double** temp, int popSize, double beta, double gamma, double alpha, int equation, double* range)
/// \brief Loops through the population calling the move firefly loop function
///
/// \param fireflies - struct being processed in the iteration
/// \param temp - the temporary population which will not be updated
/// \param popSize - the size of the population
/// \param beta - the attractiveness factor
/// \param gamma - the light absorption rate
/// \param alpha - the scaling factor on the range
/// \param equation - equation number for the objective function call
/// \param range - range of values acceptable for the population
void fireflyLoop(FireflySwarm* fireflies, double** temp, int popSize, double beta, double gamma, double alpha, int equation, double* range);
/// \fn double calcDistanceSquared(const double* fireflyI, const double* fireflyJ, int dimensions)
/// \brief Squares the difference of each dimension between the two vectors and sums them. No square root is needed as it is the distance squared
///
/// \param fireflyI - first firefly to be iterated
/// \param fireflyJ - second firefly to be iterated
/// \param dimensions - number of dimensions in the firefly
/// \return A double value representing the distance squared between the two fireflies
double calcDistanceSquared(const double* fireflyI, const double* fireflyJ, int dimensions);
/// \fn double calcAttractiveness(double** temp, int iPos, int jPos, int currDim, double beta, double gamma, double distance)
/// \brief Calculates the term representing the attractiveness and how far the new firefly will move toward the compared firefly
///
/// \param temp - the temporary population being considered in the loop
/// \param iPos - the position of the current firefly in the population
/// \param jPos - the position of the compared firefly in the population
/// \param currDim - current dimension being processed
/// \param beta - attractiveness factor
/// \param gamma - light absorption rate
/// \param distance - distance between fireflies
/// \return A double value representing the attractiveness of the firefly inverse square proportional to the distance
double calcAttractiveness(double** temp, int iPos, int jPos, int currDim, double beta, double gamma, double distance);
/// \fn double* calcAttractedVector(double** temp, int iPos, int jPos, int dimensions, double beta, double alpha, double gamma, const double* range, double distance)
/// \brief Calculates a new vector based on the current value added to the attractiveness, added to some random movement in the range.
///
/// \param temp - the temporary population being considered in the loop
/// \param iPos - the position of the current firefly in the population
/// \param jPos - the position of the compared firefly in the population
/// \param dimensions - the number of dimensions in the firefly
/// \param beta - attractiveness factor
/// \param alpha - the randomness factor for the final term
/// \param gamma - light absorption rate
/// \param range - the range of acceptable values for the equation
/// \param distance - distance between fireflies
/// \return returns a newly developed firefly
double* calcAttractedVector(double** temp, int iPos, int jPos, int dimensions, double beta, double alpha, double gamma, const double* range, double distance);
/// \fn void moveFirefliesLoop(FireflySwarm* fireflies, double** temp, int iPos, double beta, double gamma, double alpha, int equation, int popSize, double* range)
/// \brief loops through the entire population and compares the light intensity of each firefly to see if a newly attracted firefly is to be created.
///
/// \param fireflies - the struct being processed
/// \param temp - the temporary population being considered in the loop
/// \param iPos - the position of the current firefly in the population
/// \param beta - attractiveness factor
/// \param gamma - light absorption rate
/// \param alpha - the randomness factor for the final term
/// \param equation - equation number for the objective function call
/// \param popSize - the population size of fireflies
/// \param range - the range of acceptable values for the equation
void moveFirefliesLoop(FireflySwarm* fireflies, double** temp, int iPos, double beta, double gamma, double alpha, int equation, int popSize, double* range);
/// \fn void newBest(FireflySwarm* pop, double* newVector, double newResult, int popSize)
/// \brief updates the metadata regarding the best firefly in the population
///
/// \param pop - the struct being processed
/// \param newVector - the newly created firefly
/// \param newResult - the fitness of the newly created firefly
/// \param popSize- the size of the firefly population
void newBest(FireflySwarm* pop, double* newVector, double newResult, int popSize);
/// \fn void addVector(FireflySwarm* pop, double* newVector, double newResult, int popSize)
/// \brief updates the metadata regarding the worst firefly in the population
///
/// \param pop - the struct being processed
/// \param newVector - the newly created firefly
/// \param newResult - the fitness of the newly created firefly
/// \param popSize- the size of the firefly population
void addVector(FireflySwarm* pop, double* newVector, double newResult, int popSize);

#endif //CS471_PROJECT4_FA_H
