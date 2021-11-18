//
// Created by Taylor Apple on 4/2/2019.
//
/*! \file MersenneMatrix.c
 *  \brief Implementation of the create matrix method defined in src/MersenneMatrix.h
 *
 *  In this file the matrix of randomized values with numVectors x dimToTest dimensions is allocated
 *  and created using the Mersenne Twister algorithm referenced in src/m19937ar-cok.h.
 */
#include "Utilities.h"
#include "MersenneMatrix.h"
#include "m19937ar-cok.h"


double** createMatrix(EquationInfo info){
    int numVec = info.numVectors, /*! < Storing the value for number of vectors to test locally*/
    dim = info.dimToTest; /*! < Storing the value for the number of dimensions in the vector locally*/

    double** matrix = calloc(numVec, sizeof(double*)); /*! < Allocate the space for the return matrix of random values*/
    double valInRange = 0.0, /*! < Declare and initialize the value which will be calculated and stored as one of the vector dimensions*/
    minVal = info.range[RANGE_MIN_POS], /*! < Store the range minimum from the read in file for this equation locally for later calculations. RANGE_MIN_POS is defined in src/Utilities.h*/
    maxVal = info.range[RANGE_MAX_POS]; /*! < Store the range maximum from the read in file for this equation locally for later calculations. RANGE_MAX_POS is defined in src/Utilities.h*/
    /*!
     * Iterate through the matrix and allocate the space for the dimensions in each vector
     */
    for(int i = 0; i < numVec; i++){
        matrix[i] = calloc(dim, sizeof(double));
    }
    /*!
     * Iterate through every matrix position of matrix[i][j] and generate a random double value in the range
     * [minVal, maxVal]. Then finally store that value in matrix[i][j] and repeat till all values are set.
     */
    for (int i = 0; i < numVec; i++){
        for(int j = 0; j < dim; j++){
            valInRange = genDblInRange(minVal, maxVal);
            matrix[i][j] = valInRange;
        }
    }

    /// Return the randomly generated matrix.
    return matrix;
}

double** createVelocities(EquationInfo info){
    int numVec = info.numVectors, /*! < Storing the value for number of vectors to test locally*/
            dim = info.dimToTest; /*! < Storing the value for the number of dimensions in the vector locally*/
    double minVal = info.range[RANGE_MIN_POS], /*! < Store the range minimum from the read in file for this equation locally for later calculations. RANGE_MIN_POS is defined in src/Utilities.h*/
    maxVal = info.range[RANGE_MAX_POS], /*! < Store the range maximum from the read in file for this equation locally for later calculations. RANGE_MAX_POS is defined in src/Utilities.h*/
    range = maxVal - minVal; /*!< calculate the range of possible values as defined in info*/
    double** matrix = calloc(numVec, sizeof(double*)); /*! < Allocate the space for the return matrix of random values*/
    /*!
     * Iterate through the matrix and allocate the space for the dimensions in each vector
     */
    for(int i = 0; i < numVec; i++){
        matrix[i] = calloc(dim, sizeof(double));
    }
    /*!
     * Iterate through every matrix position of matrix[i][j] and generate a random double value in the range
     * [0, .5 * range]. Then finally store that value in matrix[i][j] and repeat till all values are set.
     */
    for (int i = 0; i < numVec; i++){
        for(int j = 0; j < dim; j++) {
            matrix[i][j] = genDblInRange(0, 0.5 * range);
        }
    }
    /// Return the randomly generated matrix.
    return matrix;
}

double genDblInRange(double min, double max){
    double scalar = 0.0;
    #ifdef WIN32
        scalar = genRandReal32(); ///WIN32 version of mutex locking and generating random number
    #else
        scalar = genRandRealP(); ///Posix version of mutex locking and generating random number
    #endif
    return min + ((max - min) * scalar);
}

int genNonNegInt(int max){
#ifdef WIN32
    return genRandInt32(max); ///WIN32 version of mutex locking and generating random number
#else
    return genRandIntP(max); ///Posix version of mutex locking and generating random number
#endif
}