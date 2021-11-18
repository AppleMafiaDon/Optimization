//
// Created by Taylor Apple on 4/2/2019.
//

/*!
 * \file MersenneMatrix.h
 * \brief Defines the method which creates the randomized matrix for use in all tests, for all equations in the program and generating a random double in the range.
 */

#ifndef TESTINGSUITE_MERSENNEMATRIX_H
#define TESTINGSUITE_MERSENNEMATRIX_H

#include "Utilities.h"

/// \fn double** createMatrix(struct EquationInfo info)
/// \brief Using the Mersenne Twister algorithm to develop a set of unique randomized values.
///
/// \param info - EquationInfo struct
/// \return A matrix (2D-Array) of randomized double values
double** createMatrix(EquationInfo);
/// \fn double** createVelocities(EquationInfo info)
/// \brief Using the Mersenne Twister algorithm to develop a set of unique randomized velocities.
///
/// \param info  - EquationInfo struct
/// \return A random matrix of initial velocities for use in src/PSO.c
double** createVelocities(EquationInfo info);
/// \fn double genDblInRange(double min, double max)
/// \brief Using the Mersenne Twister algorithm to develop a scalar between 0 and 1, a unique randomized value between
/// min and max is produced.
///
/// \param min - double representing the minimum value in the range
/// \param max - double representing the maximum value in the range
/// \return A random double between min and max
double genDblInRange(double, double);
/// \fn int genNonNegInt(int max)
/// \brief Using the Mersenne Twister algorithm to develop a non-negative integer between 0 and max non-inclusive.
///
/// \param max - int representing the maximum value in the range
/// \return A random int between 0 and max
int genNonNegInt(int);

#endif //TESTINGSUITE_MERSENNEMATRIX_H
