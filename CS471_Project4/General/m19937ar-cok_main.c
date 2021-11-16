//
// Created by TappleDon on 4/18/2019.
//
/*!
 * This is the main file for testing the mersenne twister algorithm implemented in General/m19937ar-cok.c All credit
 * goes to those cited in the comments of that imported file.
 * */
#include "m19937ar-cok.h"

int main(void)
{
    int i;
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);
    *//* This is an example of initializing by an array.       *//*
            *//* You may use init_genrand(seed) with any 32bit integer *//*
                    *//* as a seed for a simpler initialization                *//*
                            printf("1000 outputs of genrand_int32()\n");
    for (i=0; i<1000; i++) {
        printf("%10lu ", genrand_int32());
        if (i%5==4) printf("\n");
    }
    printf("\n1000 outputs of genrand_real2()\n");
    for (i=0; i<1000; i++) {
        printf("%10.8f ", genrand_real2());
        if (i%5==4) printf("\n");
    }

    return 0;
}