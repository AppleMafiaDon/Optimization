//
// Created by AppleT on 5/15/2019.
//

/*!
 * \file HostCalls.h
 * \brief This is where all the references to the objective function call methods are stored to avoid duplication.
 *
 */

#ifndef TESTINGSUITE_HOSTCALLS_H
#define TESTINGSUITE_HOSTCALLS_H

#include "Equations.h"

//! An array of pointers to the equation methods to be used by threads in runEquationsAsThreads()
/*!
 * This is used as an easy way to iterate through the equation methods when creating the
 * threads to start processing each dimension to be tested for each equation in different threads.
 */
const void* equationHostCalls[] ={
        &schwefelHost, /*!< Reference to the schwefelHost method defined in src/Equations.h*/
        &deJongHost,/*!< Reference to the deJongHost method defined in src/Equations.h*/
        &rosenbrockHost, /*!< Reference to the rosenbrockHost method defined in src/Equations.h*/
        &rastgrinHost, /*!< Reference to the rastgrinHost method defined in src/Equations.h*/
        &griewangkHost, /*!< Reference to the griewangkHost method defined in src/Equations.h*/
        &sineEnvSineWaveHost, /*!< Reference to the sineEnvSineWaveHost method defined in src/Equations.h*/
        &stretchVSineWaveHost, /*!< Reference to the stretchVSineWaveHost method defined in src/Equations.h*/
        &ackleyOneHost, /*!< Reference to the ackleyOneHost method defined in src/Equations.h*/
        &ackleyTwoHost, /*!< Reference to the ackleyTwoHost method defined in src/Equations.h*/
        &eggHolderHost, /*!< Reference to the eggHolderHost method defined in src/Equations.h*/
        &ranaHost, /*!< Reference to the ranaHost method defined in src/Equations.h*/
        &pathologicalHost, /*!< Reference to the pathologicalHost method defined in src/Equations.h*/
        &michalewiczHost, /*!< Reference to the michalewiczHost method defined in src/Equations.h*/
        &mastersCosineWaveHost, /*!< Reference to the mastersCosineWaveHost method defined in src/Equations.h*/
        &quarticHost, /*!< Reference to the quarticHost method defined in src/Equations.h*/
        &levyHost, /*!< Reference to the levyHost method defined in src/Equations.h*/
        &stepHost, /*!< Reference to the stepHost method defined in src/Equations.h*/
        &alpineHost /*!< Reference to the alpineHost method defined in src/Equations.h*/
};

#endif //TESTINGSUITE_HOSTCALLS_H
