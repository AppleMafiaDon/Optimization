//
// Created by Taylor Apple on 5/2/2019.
//
/*! \file UtilP.c
 * \brief contains the implementations for the methods declared in src/Utilities.h which produce random numbers using a mutex in POSIX format.
 *
 */

#include "../src/Utilities.h"
#include "../src/m19937ar-cok.h"
#include <pthread.h>

int genRandIntP(int modulo){
    int result = 0;/*!< Initialize the result*/
    pthread_mutex_lock(&mutex);///accessing the random number generator
    result = genrand_int32() % modulo; ///generate a random 32-bit integer number with the method defined in ../src/m19937ar-cok.h
    pthread_mutex_unlock(&mutex);///done accessing the random number generator
    return result;///return the result
}

double genRandRealP(){
    double result = 0;/*!< Initialize the result*/
    pthread_mutex_lock(&mutex);///accessing the random number generator
    result = genrand_real1(); ///generate a random real number with the method defined in ../src/m19937ar-cok.h
    pthread_mutex_unlock(&mutex);///done accessing the random number generator
    return result;///return the result
}