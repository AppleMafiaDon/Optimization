//
// Created by TappleDon on 5/2/2019.
//

/*! \file Util32.c
 * \brief contains the implementations for the methods declared in General/Utilities.h which produce random numbers using a mutex in WIN332 format.
 *
 */

#include "../General/Utilities.h"
#include "../General/m19937ar-cok.h"

int genRandInt32(int modulo){
    int result = 0; /*!< Initialize the result*/
    WaitForSingleObject(mutex, INFINITE );///accessing the random number generator
    result = genrand_int32() % modulo; ///generate a random 32-bit integer number with the method defined in ../General/m19937ar-cok.h
    ReleaseMutex(mutex);/// done accessing the random number generator
    return result;///return the result
}

double genRandReal32(){
    double result = 0; /*!< Initialize the result*/
    WaitForSingleObject(mutex, INFINITE );///accessing the random number generator
    result = genrand_real1(); ///generate a random real number with the method defined in ../General/m19937ar-cok.h
    ReleaseMutex(mutex);/// done accessing the random number generator
    return result; ///return the result
}