//
// Created by AppleT on 5/13/2019.
//
/*!
 * \file Harmonic.h
 * \brief This is where all methods pertaining to the Harmonic Search Algorithm implementation are defined.
 *
 *  Harmonic Search takes random dimensions from among the population, adjusts the value to test within the neighborhood,
 *  and then produces a single vector to be tested per iteration saving it if it is better than the worst vector and reevaluating
 *  the population for the new worst vector.
 */

#ifndef TESTINGSUITE_HARMONIC_H
#define TESTINGSUITE_HARMONIC_H

#include "Utilities.h"

/// \fn void* harmonicTest(void* data)
/// \brief Responsible for initializing the algorithm and all data related to the algorithm and calling related functions to start and record results fo the algorithm
///
/// \param data - void pointer to be converted to an EquationInfo struct
/// \return Nothing as it is a threaded function
void* harmonicTest(void* data);
/// \fn void pitchAdjustment(double* harmonic,int position, double bandwidth, const double* range)
/// \brief adjusts the pitch of the current harmonic based on a random number, the current value and the bandwidth
///
/// \param harmonic - the harmonic to be adjusted
/// \param position - the dimension within the harmonic being adjusted
/// \param bandwidth - the bandwidth for the tuning
/// \param range - the range of acceptable values in the search space
void pitchAdjustment(double* harmonic,int position, double bandwidth, const double* range);
/// \fn void updateBest(HPop* pop, double newResult, EquationInfo info)
/// \brief updates the metadata pertaining to the best fitness within the struct
///
/// \param pop - the struct being processed
/// \param newResult - the newly calculated fitness value
/// \param info - The EquationInfo struct storing equation specific information
void updateBest(HPop* pop, double newResult, EquationInfo info);
/// \fn void newVector(HPop* pop, double newResult, EquationInfo info)
/// \brief adds the vector to the population at the worst fitness position
///
/// \param pop - the struct being processed
/// \param newResult - the newly calculated fitness value
/// \param info - The EquationInfo struct storing equation specific information
void newVector(HPop* pop, double newResult, EquationInfo info);
/// \fn void harmonicIteration(HPop* hpop, int NI, int HMS, double HMCR, double PAR, double bandwidth, const double* range)
/// \brief This iterates through the number of dimensions and grabs random values from the range or population and occasionally adjusts the value at each dimension.
///
/// \param hpop - the struct being processed
/// \param NI - The number of dimensions in the Harmonics
/// \param HMS - Harmonic Size or population size
/// \param HMCR - Harmonic Conssideration Rate
/// \param PAR - Pitch Adjustment Rate
/// \param bandwidth - the bandwidth for the tuning
/// \param range - the range of acceptable values in the search space
void harmonicIteration(HPop* hpop, int NI, int HMS, double HMCR, double PAR, double bandwidth, const double* range);

#endif //TESTINGSUITE_HARMONIC_H
