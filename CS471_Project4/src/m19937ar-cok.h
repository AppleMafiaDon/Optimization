//
// Created by TappleDon on 4/4/2019.
//

#ifndef TESTINGSUITE_M19937AR_COK_H
#define TESTINGSUITE_M19937AR_COK_H

void init_genrand(unsigned long s);
void init_by_array(unsigned long init_key[], int key_length);
static void next_state(void);
unsigned long genrand_int32(void);
long genrand_int31(void);
double genrand_real1(void);
double genrand_real2(void);
double genrand_real3(void);
double genrand_res53(void);


#endif //TESTINGSUITE_M19937AR_COK_H
