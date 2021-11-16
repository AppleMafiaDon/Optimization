//
// Created by TappleDon on 4/2/2019.
//

/*!
 * \file Equations.h
 * \brief This is where the methods for the calls in General/TestTypes.c are defined.
 *
 *  Here we define and describe the methods which are referenced in General/TestTypes.c and implemented in General/Equations.c.
 *  Based on the equation we process a randomized vector stored in a TestInfo struct matrix, perform different calculations returning
 *  the result for the vector.
 */
#ifndef TESTINGSUITE_EQUATIONS_H
#define TESTINGSUITE_EQUATIONS_H

/// \fn double schwefelHost(double* vector, int numDim)
/// \brief This is the method which  performs calculations for each vector in the matrix utilizing the Schwefel function
///
/// \param vector - The vector of values to use in this function calculation
/// \param numDim - the number of dimensions in the vector for the function calculation
/// \return The resulting value from the calculation
double schwefelHost(const double*, int);
/// \fn double deJongHost(double* vector, int numDim)
/// \brief This is the method which performs calculations for each vector in the matrix utilizing the DeJong Sphere function
///
/// \param vector - The vector of values to use in this function calculation
/// \param numDim - the number of dimensions in the vector for the function calculation
/// \return The resulting value from the calculation
double deJongHost(const double*, int);
/// \fn double rosenbrockHost(double* vector, int numDim)
/// \brief This is the method which performs calculations for each vector in the matrix utilizing the Rosenbrock function
///
/// \param vector - The vector of values to use in this function calculation
/// \param numDim - the number of dimensions in the vector for the function calculation
/// \return The resulting value from the calculation
double rosenbrockHost(const double*, int);
/// \fn double rastgrinHost(double* vector, int numDim)
/// \brief This is the method which performs calculations for each vector in the matrix utilizing the Rastgrin function
///
/// \param vector - The vector of values to use in this function calculation
/// \param numDim - the number of dimensions in the vector for the function calculation
/// \return The resulting value from the calculation
double rastgrinHost(const double*, int);
/// \fn double griewangkHost(double* vector, int numDim)
/// \brief This is the method which performs calculations for each vector in the matrix utilizing the Griewangk function
///
/// \param vector - The vector of values to use in this function calculation
/// \param numDim - the number of dimensions in the vector for the function calculation
/// \return The resulting value from the calculation
double griewangkHost(const double*, int);
/// \fn double sineEnvSineWaveHost(double* vector, int numDim)
/// \brief This is the method which performs calculations for each vector in the matrix utilizing the Sine Envelope function
///
/// \param vector - The vector of values to use in this function calculation
/// \param numDim - the number of dimensions in the vector for the function calculation
/// \return The resulting value from the calculation
double sineEnvSineWaveHost(const double*, int);
/// \fn double stretchVSineWaveHost(double* vector, int numDim)
/// \brief This is the method which performs calculations for each vector in the matrix utilizing the Stretch V Sine Wave function
///
/// \param vector - The vector of values to use in this function calculation
/// \param numDim - the number of dimensions in the vector for the function calculation
/// \return The resulting value from the calculation
double stretchVSineWaveHost(const double*, int);
/// \fn double ackleyOneHost(double* vector, int numDim)
/// \brief This is the method which performs calculations for each vector in the matrix utilizing the Ackley One function
///
/// \param vector - The vector of values to use in this function calculation
/// \param numDim - the number of dimensions in the vector for the function calculation
/// \return The resulting value from the calculation
double ackleyOneHost(const double*, int);
/// \fn double ackleyTwoHost(double* vector, int numDim)
/// \brief This is the method which performs calculations for each vector in the matrix utilizing the Ackley Two function
///
/// \param vector - The vector of values to use in this function calculation
/// \param numDim - the number of dimensions in the vector for the function calculation
/// \return The resulting value from the calculation
double ackleyTwoHost(const double*, int);
/// \fn double eggHolderHost(double* vector, int numDim)
/// \brief This is the method which performs calculations for each vector in the matrix utilizing the Egg Holder function
///
/// \param vector - The vector of values to use in this function calculation
/// \param numDim - the number of dimensions in the vector for the function calculation
/// \return The resulting value from the calculation
double eggHolderHost(const double*, int);
/// \fn double ranaHost(double* vector, int numDim)
/// \brief This is the method which performs calculations for each vector in the matrix utilizing the Rana function
///
/// \param vector - The vector of values to use in this function calculation
/// \param numDim - the number of dimensions in the vector for the function calculation
/// \return The resulting value from the calculation
double ranaHost(const double*, int);
/// \fn double pathologicalHost(double* vector, int numDim)
/// \brief This is the method which performs calculations for each vector in the matrix utilizing the provided Pathological function
///
/// \param vector - The vector of values to use in this function calculation
/// \param numDim - the number of dimensions in the vector for the function calculation
/// \return The resulting value from the calculation
double pathologicalHost(const double*, int);
/// \fn double michalewiczHost(double* vector, int numDim)
/// \brief This is the method which performs calculations for each vector in the matrix utilizing the Michalewicz function
///
/// \param vector - The vector of values to use in this function calculation
/// \param numDim - the number of dimensions in the vector for the function calculation
/// \return The resulting value from the calculation
double michalewiczHost(const double*, int);
/// \fn double mastersCosineWaveHost(double* vector, int numDim)
/// \brief This is the method which performs calculations for each vector in the matrix utilizing the Master's Cosine Wave function
///
/// \param vector - The vector of values to use in this function calculation
/// \param numDim - the number of dimensions in the vector for the function calculation
/// \return The resulting value from the calculation
double mastersCosineWaveHost(const double*, int);
/// \fn double quarticHost(double* vector, int numDim)
/// \brief This is the method which performs calculations for each vector in the matrix utilizing the Quartic function
///
/// \param vector - The vector of values to use in this function calculation
/// \param numDim - the number of dimensions in the vector for the function calculation
/// \return The resulting value from the calculation
double quarticHost(const double*, int);
/// \fn double levyHost(double* vector, int numDim)
/// \brief This is the method which performs calculations for each vector in the matrix utilizing the Levy function
///
/// \param vector - The vector of values to use in this function calculation
/// \param numDim - the number of dimensions in the vector for the function calculation
/// \return The resulting value from the calculation
double levyHost(const double*, int);
/// \fn double stepHost(double* vector, int numDim)
/// \brief This is the method which performs calculations for each vector in the matrix utilizing the provided Step function
///
/// \param vector - The vector of values to use in this function calculation
/// \param numDim - the number of dimensions in the vector for the function calculation
/// \return The resulting value from the calculation
double stepHost(const double*, int);
/// \fn double alpineHost(double* vector, int numDim)
/// \brief This is the method which performs calculations for each vector in the matrix utilizing the Alpine function
///
/// \param vector - The vector of values to use in this function calculation
/// \param numDim - the number of dimensions in the vector for the function calculation
/// \return The resulting value from the calculation
double alpineHost(const double*, int);


#endif //TESTINGSUITE_EQUATIONS_H
