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
        &schwefelHost, /*!< Reference to the schwefelHost method defined in General/Equations.h*/
        &deJongHost,/*!< Reference to the deJongHost method defined in General/Equations.h*/
        &rosenbrockHost, /*!< Reference to the rosenbrockHost method defined in General/Equations.h*/
        &rastgrinHost, /*!< Reference to the rastgrinHost method defined in General/Equations.h*/
        &griewangkHost, /*!< Reference to the griewangkHost method defined in General/Equations.h*/
        &sineEnvSineWaveHost, /*!< Reference to the sineEnvSineWaveHost method defined in General/Equations.h*/
        &stretchVSineWaveHost, /*!< Reference to the stretchVSineWaveHost method defined in General/Equations.h*/
        &ackleyOneHost, /*!< Reference to the ackleyOneHost method defined in General/Equations.h*/
        &ackleyTwoHost, /*!< Reference to the ackleyTwoHost method defined in General/Equations.h*/
        &eggHolderHost, /*!< Reference to the eggHolderHost method defined in General/Equations.h*/
        &ranaHost, /*!< Reference to the ranaHost method defined in General/Equations.h*/
        &pathologicalHost, /*!< Reference to the pathologicalHost method defined in General/Equations.h*/
        &michalewiczHost, /*!< Reference to the michalewiczHost method defined in General/Equations.h*/
        &mastersCosineWaveHost, /*!< Reference to the mastersCosineWaveHost method defined in General/Equations.h*/
        &quarticHost, /*!< Reference to the quarticHost method defined in General/Equations.h*/
        &levyHost, /*!< Reference to the levyHost method defined in General/Equations.h*/
        &stepHost, /*!< Reference to the stepHost method defined in General/Equations.h*/
        &alpineHost /*!< Reference to the alpineHost method defined in General/Equations.h*/
};

#endif //TESTINGSUITE_HOSTCALLS_H
