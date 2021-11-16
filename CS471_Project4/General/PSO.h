//
// Created by AppleT on 5/9/2019.
//

/*!
 * \file PSO.h
 * \brief This is where all methods pertaining to the Particle Swarm Optimization Algorithm implementation are defined.
 *
 *  Genetic Algorithm is the process of taking parent vectors from the population, crossing over values between the two vectors,
 *  potentially mutating some or all of the dimensions of these vectors to create new populations. The new populations are then
 *  evaluated and the best results from each population are maintained for the next generation. The methods defined herein
 *  provide the functionality for this process.
 */

#ifndef CS471_PROJECT4_PSO_H
#define CS471_PROJECT4_PSO_H

#include "Utilities.h"

/// \fn void* particleSwarmAlg(void* data)
/// \brief Responsible for initializing the algorithm and all data related to the algorithm and calling related functions to start and record results fo the algorithm
///
/// \param data - void pointer to be converted to an EquationInfo struct
/// \return Nothing as it is a threaded function
void* particleSwarmAlg(void* data);
/// \fn void particleLoop(Particle* particles, int numParticles, int dimensions, double c1, double c2, double k, double* range, int equation)
/// \brief executes the loop which iterates through the population, calculates new velocities for each dimension, creates the new particle and evaluates it
///
/// \param particles - The struct to be processed
/// \param numParticles - The number of particles in the population
/// \param dimensions - the number of dimensions per particle
/// \param c1 - the personalBest modification factor
/// \param c2 - the globalBest modification factor
/// \param k - the velocity dampening factor
/// \param range - the range of accepted values
/// \param equation - the equation number for the objective function call
void particleLoop(Particle* particles, int numParticles, int dimensions, double c1, double c2, double k, double* range, int equation);
/// \fn double calcPBestModifier(Particle* particles, double c1, int vecPos, int dimPos)
/// \brief calculates the personal best term when determining a new velocity
///
/// \param particles - the struct being processed
/// \param c1  - the personalBest modification factor
/// \param vecPos - the position of the particle in the population
/// \param dimPos - the position of the dimension whose new velocity is being calculated
/// \return returns a double value representing the velocity towards the personal best dimension
double calcPBestModifier(Particle* particles, double c1, int vecPos, int dimPos);
/// \fn double calcGBestModifier(Particle* particles, double c2, int vecPos, int dimPos)
/// \brief calculates the global best term when determining the new velocity
///
/// \param particles - the struct being processed
/// \param c2  - the globalBest modification factor
/// \param vecPos - the position of the particle in the population
/// \param dimPos - the position of the dimension whose new velocity is being calculated
/// \return returns a double value representing the velocity towards the global best dimension
double calcGBestModifier(Particle* particles, double c2, int vecPos, int dimPos);
/// \fn void calcNewVelocity(Particle* particles, int dimensions, int position, double c1, double c2, double k)
/// \brief Calculates the velocity of the current dimension utilizing the old velocity and a term derived from the personal best particle and a term derived from the global best particle.
///
/// \param particles - the struct being processed
/// \param dimensions - the number of dimensions per particle in the population
/// \param position - the current particle position
/// \param c1 - the personalBest modification factor
/// \param c2 - the globalBest modification factor
/// \param k - the velocity dampening factor
void calcNewVelocity(Particle* particles, int dimensions, int position, double c1, double c2, double k);
/// \fn void calcNewVector(Particle* particles, int dimensions, int position, const double* range)
/// \brief calculates a new vector using the current dimensional value and the velocity calculated in a prior step.
///
/// \param particles - the struct being processed
/// \param dimensions - the number of dimensions per particle in the population
/// \param position - the current particle position
/// \param range - the range of acceptable values for the search space
void calcNewVector(Particle* particles, int dimensions, int position, const double* range);


#endif //CS471_PROJECT4_PSO_H
