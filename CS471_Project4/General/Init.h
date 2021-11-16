//
// Created by TappleDon on 4/2/2019.
//
/*!
 * \file Init.h
 * \brief This is where the methods for the building the program info from the init file are defined. Referenced in PThread/main.c or Win32/main32.c.
 *
 *  Here we define and describe the methods which are called in PThread/main.c or Win32/main32.c
 *  and implemented in General/Init.c. Based on the input from the init file, we read in all the lines and process the
 *  information validating against expected input. All lines for both tests are expected to be present then the user selects
 *  which test they would like to run.
 */
#ifndef TESTINGSUITE_INIT_H
#define TESTINGSUITE_INIT_H

#include "Utilities.h"

/// \fn int init(char* filename, Info* progInfo)
/// \brief This is the method which reads in the init file, and processes the information contained within into the progInfo Info struct
///         using helper methods based on the flags which are set during processing.
///
/// This iterates through the lines of the init file tokenizing the lines on '=' and then sets flags based on what line was just read in.
/// It checks that all of the lines which require an order are processed in the right order and returns -1 on a failure.
/// Failures: Not enough argument lines, Arguments are out of order, couldn't convert a value properly, incorrect number of matching arguments
/// e.g. 3 dimensions expected only 2 provided in the dimension list.
///
/// \param progInfo - The reference to the Info struct for this series of tests defined in General/Utilities.h
/// \return 0 for success, -1 on failure;
int init(char*, Info*);
/// \fn int processVectors(char* arg, Info* progInfo)
/// \brief This is the method which processes the number of vectors from the line containing this information.
///
/// Failure: can't convert to a positive number
/// \param arg - The portion of the line containing the value to store
/// \param progInfo - The reference to the Info struct for this series of tests defined in General/Utilities.h
/// \return 0 for success, -1 on failure;
int processVectors(char*, Info*);
/// \fn int processDimensions(char* arg, Info* progInfo)
/// \brief This is the method which processes the number of different dimensions from the line containing this information.
///
/// Failure: can't convert to a positive number
/// \param arg - The portion of the line containing the value to store
/// \param progInfo - The reference to the Info struct for this series of tests defined in General/Utilities.h
/// \return 0 for success, -1 on failure;
int processDimensions(char*, Info*);
/// \fn int processDimList(char* arg, Info* progInfo)
/// \brief This is the method which processes the array of dimensions to test from the line containing this information.
///
/// Failure: can't convert to a positive number, not enough or too many dimensions provided
/// \param arg - The portion of the line containing the values to store
/// \param progInfo - The reference to the Info struct for this series of tests defined in General/Utilities.h
/// \return 0 for success, -1 on failure;
int processDimList(char*, Info*);
/// \fn int processEquations(char* arg, Info* progInfo)
/// \brief This is the method which processes the number of equations to test from the line containing this information.
///
/// Failure: can't convert to a positive number or is beyond the maximum number of equations in this testing suite.
/// \param arg - The portion of the line containing the value to store
/// \param progInfo - The reference to the Info struct for this series of tests defined in General/Utilities.h
/// \return 0 for success, -1 on failure;
int processEquations(char*, Info*);

/// \fn int processRanges(char* arg, Info* progInfo)
/// \brief This is the method which processes the range values for each equation from the line containing this information.
///
/// Failure: not enough or too many range values provided beyond the number of expected equations
/// \param arg - The portion of the line containing the values to store
/// \param progInfo - The reference to the Info struct for this series of tests defined in General/Utilities.h
/// \return 0 for success, -1 on failure;
int processRanges(char*, Info*);
/// \fn int processIterations(char* arg, Info* progInfo)
/// \brief This is the method which processes the number of iterations/generations for Genetic Algorithm and Differential Evolution from the line containing this information.
///
/// Failure: A value which does not convert to an interger greater than or equal to MINIMUM_ITERATIONS defined in General/Utilities.h
/// \param arg - The portion of the line containing the values to store
/// \param progInfo - The reference to the Info struct for this series of tests defined in General/Utilities.h
/// \return 0 for success, -1 on failure;
int processIterations(char*, Info*);
/// \fn int processBeta(char* arg, Info* progInfo)
/// \brief This is the method which processes the beta/attractiveness factor from the line containing this information.
///
/// Failure: A value which does not convert to a positive real number
/// \param arg - The portion of the line containing the values to store
/// \param progInfo - The reference to the Info struct for this series of tests defined in General/Utilities.h
/// \return 0 for success, -1 on failure;
int processBeta(char *arg, Info *progInfo);
/// \fn int processGamma(char* arg, Info* progInfo)
/// \brief This is the method which processes the gamma/light absorption rate from the line containing this information.
///
/// Failure: A value which does not convert to a positive real number
/// \param arg - The portion of the line containing the values to store
/// \param progInfo - The reference to the Info struct for this series of tests defined in General/Utilities.h
/// \return 0 for success, -1 on failure;
int processGamma(char *arg, Info *progInfo);
/// \fn int processAlpha(char* arg, Info* progInfo)
/// \brief This is the method which processes the alpha/random scaling factor from the line containing this information.
///
/// Failure: A value which does not convert to a positive real number
/// \param arg - The portion of the line containing the values to store
/// \param progInfo - The reference to the Info struct for this series of tests defined in General/Utilities.h
/// \return 0 for success, -1 on failure;
int processAlpha(char *arg, Info *progInfo);
/// \fn int processDampener(char* arg, Info* progInfo)
/// \brief This is the method which processes the velocity dampener value applied in General/PSO.c from the line containing this information.
///
/// Failure: A value which does not convert to a positive real number
/// \param arg - The portion of the line containing the values to store
/// \param progInfo - The reference to the Info struct for this series of tests defined in General/Utilities.h
/// \return 0 for success, -1 on failure;
int processDampener(char *arg, Info *progInfo);
/// \fn int processC1(char* arg, Info* progInfo)
/// \brief This is the method which processes the personal best modification factor applied in General/PSO.c from the line containing this information.
///
/// Failure: A value which does not convert to a positive real number between (0, 2]
/// \param arg - The portion of the line containing the values to store
/// \param progInfo - The reference to the Info struct for this series of tests defined in General/Utilities.h
/// \return 0 for success, -1 on failure;
int processC1(char *arg, Info *progInfo);
/// \fn int processC2(char* arg, Info* progInfo)
/// \brief This is the method which processes the global best modification factor applied in General/PSO.c from the line containing this information.
///
/// Failure: A value which does not convert to a positive real number between (0, 2]
/// \param arg - The portion of the line containing the values to store
/// \param progInfo - The reference to the Info struct for this series of tests defined in General/Utilities.h
/// \return 0 for success, -1 on failure;
int processC2(char *arg, Info *progInfo);
/// \fn int processHMCR(char* arg, Info* progInfo)
/// \brief This is the method which processes the Harmonic Memory Consideration Rate from the line containing this information.
///
/// Failure: A value which does not convert to a positive real number between [0, 1]
/// \param arg - The portion of the line containing the values to store
/// \param progInfo - The reference to the Info struct for this series of tests defined in General/Utilities.h
/// \return 0 for success, -1 on failure;
int processHMCR(char *arg, Info *progInfo);
/// \fn int processPAR(char* arg, Info* progInfo)
/// \brief This is the method which processes the pitch adjustment rate from the line containing this information.
///
/// Failure: A value which does not convert to a positive real number between [0, 1]
/// \param arg - The portion of the line containing the values to store
/// \param progInfo - The reference to the Info struct for this series of tests defined in General/Utilities.h
/// \return 0 for success, -1 on failure;
int processPAR(char *arg, Info *progInfo);
/// \fn int processBandwidth(char* arg, Info* progInfo)
/// \brief This is the method which processes the bandwidth from the line containing this information.
///
/// Failure: A value which does not convert to a positive real number
/// \param arg - The portion of the line containing the values to store
/// \param progInfo - The reference to the Info struct for this series of tests defined in General/Utilities.h
/// \return 0 for success, -1 on failure;
int processBandwidth(char *arg, Info *progInfo);

/// \fn int checkTestType()
/// \brief This is the method which takes user input to define the type of tests to run; either Genetic Algorithm or Differential Evolution.
///
/// \return 0 for Differential Evolution, 1 for Genetic Algoriothm;
int checkTestType();


#endif //TESTINGSUITE_INIT_H
