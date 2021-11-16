//
// Created by TappleDon on 4/2/2019.
//
/*!
 * \file EquationHandlers.h
 * \brief This is where the methods for the threaded calls in PThread/main.c or Win32/main32.c are defined.
 *
 *  Here we define and describe the methods which are referenced in PThread/main.c or Win32/main32.c
 *  and implemented in either PThread/EquationHandlers.c or Win32/EquationHandlers32.c depending on
 *  whether you are using a Win32 or Unix/Linux machine. Based on the equation we pass certain information
 *  to the runEquationsAsThreads method which then runs each equation threaded by the dimensions required
 *  for each test. E.g. if there are 3 dimensions to test 3 threads will be created to run the functions,
 *  one for each dimension.
 */
#ifndef TESTINGSUITE_EQUATIONHANDLERS_H
#define TESTINGSUITE_EQUATIONHANDLERS_H

#include "Utilities.h"

/// \fn int runEquationsAsThreads(int equationPos, char* eqName, Info* data)
/// \brief Creates EquationInfo structs from the Info struct passed in and then creates threads for each of the dimensional tests.
///
/// This method takes in some basic information from the handler methods, equationPos and eqName, and then utilizes
/// the Info struct passed to each equation's thread to create a specific EquationInfo struct for each dimensional
/// test. Then it passes these structs to individual threads for each dimensional test.
///
/// \param equationPos - indicates the position within the various arrays of the Info struct for this equation's info
/// \param eqName - Name of the equation being run used for file naming
/// \param data - the Info struct which will be referenced to create the appropriate EquationInfo structs
/// \return 0 on success, -1 on failures
int runEquationsAsThreads(int, char*, Info*);
/// \fn void* schwefelHandler(void* info)
/// \brief This is the method which sets up some basic information before passing that info to runEquationsAsThreads()
///
/// \param info - The reference to the Info struct for this series of tests
/// \return Threaded function so no return.
void* schwefelHandler(void* info);
/// \fn void* deJongHandler(void* info)
/// \brief This is the method which sets up some basic information before passing that info to runEquationsAsThreads()
///
/// \param info - The reference to the Info struct for this series of tests
/// \return Threaded function so no return.
void* deJongHandler(void* info);
/// \fn void* rosenbrockHandler(void* info)
/// \brief This is the method which sets up some basic information before passing that info to runEquationsAsThreads()
///
/// \param info - The reference to the Info struct for this series of tests
/// \return Threaded function so no return.
void* rosenbrockHandler(void* info);
/// \fn void* rastgrinHandler(void* info)
/// \brief This is the method which sets up some basic information before passing that info to runEquationsAsThreads()
///
/// \param info - The reference to the Info struct for this series of tests
/// \return Threaded function so no return.
void* rastgrinHandler(void* info);
/// \fn void* griewangkHandler(void* info)
/// \brief This is the method which sets up some basic information before passing that info to runEquationsAsThreads()
///
/// \param info - The reference to the Info struct for this series of tests
/// \return Threaded function so no return.
void* griewangkHandler(void* info);
/// \fn void* sineEnvSineWaveHandler(void* info)
/// \brief This is the method which sets up some basic information before passing that info to runEquationsAsThreads()
///
/// \param info - The reference to the Info struct for this series of tests
/// \return Threaded function so no return.
void* sineEnvSineWaveHandler(void* info);
/// \fn void* stretchVSineWaveHandler(void* info)
/// \brief This is the method which sets up some basic information before passing that info to runEquationsAsThreads()
///
/// \param info - The reference to the Info struct for this series of tests
/// \return Threaded function so no return.
void* stretchVSineWaveHandler(void* info);
/// \fn void* ackleyOneHandler(void* info)
/// \brief This is the method which sets up some basic information before passing that info to runEquationsAsThreads()
///
/// \param info - The reference to the Info struct for this series of tests
/// \return Threaded function so no return.
void* ackleyOneHandler(void* info);
/// \fn void* ackleyTwoHandler(void* info)
/// \brief This is the method which sets up some basic information before passing that info to runEquationsAsThreads()
///
/// \param info - The reference to the Info struct for this series of tests
/// \return Threaded function so no return.
void* ackleyTwoHandler(void* info);
/// \fn void* eggHolderHandler(void* info)
/// \brief This is the method which sets up some basic information before passing that info to runEquationsAsThreads()
///
/// \param info - The reference to the Info struct for this series of tests
/// \return Threaded function so no return.
void* eggHolderHandler(void* info);
/// \fn void* ranaHandler(void* info)
/// \brief This is the method which sets up some basic information before passing that info to runEquationsAsThreads()
///
/// \param info - The reference to the Info struct for this series of tests
/// \return Threaded function so no return.
void* ranaHandler(void* info);
/// \fn void* pathologicalHandler(void* info)
/// \brief This is the method which sets up some basic information before passing that info to runEquationsAsThreads()
///
/// \param info - The reference to the Info struct for this series of tests
/// \return Threaded function so no return.
void* pathologicalHandler(void* info);
/// \fn void* michalewiczHandler(void* info)
/// \brief This is the method which sets up some basic information before passing that info to runEquationsAsThreads()
///
/// \param info - The reference to the Info struct for this series of tests
/// \return Threaded function so no return.
void* michalewiczHandler(void* info);
/// \fn void* mastersCosineWaveHandler(void* info)
/// \brief This is the method which sets up some basic information before passing that info to runEquationsAsThreads()
///
/// \param info - The reference to the Info struct for this series of tests
/// \return Threaded function so no return.
void* mastersCosineWaveHandler(void* info);
/// \fn void* quarticHandler(void* info)
/// \brief This is the method which sets up some basic information before passing that info to runEquationsAsThreads()
///
/// \param info - The reference to the Info struct for this series of tests
/// \return Threaded function so no return.
void* quarticHandler(void* info);
/// \fn void* levyHandler(void* info)
/// \brief This is the method which sets up some basic information before passing that info to runEquationsAsThreads()
///
/// \param info - The reference to the Info struct for this series of tests
/// \return Threaded function so no return.
void* levyHandler(void* info);
/// \fn void* stepHandler(void* info)
/// \brief This is the method which sets up some basic information before passing that info to runEquationsAsThreads()
///
/// \param info - The reference to the Info struct for this series of tests
/// \return Threaded function so no return.
void* stepHandler(void* info);
/// \fn void* alpineHandler(void* info)
/// \brief This is the method which sets up some basic information before passing that info to runEquationsAsThreads()
///
/// \param info - The reference to the Info struct for this series of tests
/// \return Threaded function so no return.
void* alpineHandler(void* info);

#endif //TESTINGSUITE_EQUATIONHANDLERS_H
