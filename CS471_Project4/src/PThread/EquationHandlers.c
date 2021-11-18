//
// Created by Taylor Apple on 4/2/2019.
//
/*!
 * \file EquationHandlers.c
 * \brief Handles the individual equation threads created in PThread/main.c and provides implementation for functions defined in src/EquationHandlers.h.
 *
 * Contains the implementations for the functions defined in src/EquationHandlers.h. Processes the Info struct provided by the threads in main.c
 * and creates EquationInfo structs defined in src/Utilities.h to pass to the actual testType methods defined in src/TestTypes.h. Will create
 * a number of threads for each dimension to be tested.
 */
#include "../src/Utilities.h"
#include "../src/FA.h"
#include "../src/Harmonic.h"
#include "../src/PSO.h"
#include "../src/EquationHandlers.h"
#include <pthread.h>


//! An array of pointers to the TestType methods to be used by threads in runEquationsAsThreadss()
/*!
 * This is used as an easy way to select the correct test type from the user input when creating the
 * threads to start processing each equation by dimension in different threads.
 */
const void* testTypeCalls[] = {
        &particleSwarmAlg, /*!< Reference to the Particle Swarm Optimization Algorithm method defined in src/PSO.h*/
        &fireflyAlg, /*!< Reference to the Firefly Algorithm method defined in src/FA.h*/
        &harmonicTest /*!< Reference to the Harmonic Search Algorithm method defined in src/Harmonic.h*/
};

int runEquationsAsThreads(int equationPos, char* eqName, Info* data){
    int numDim = data->numDimensions; /*!< Store the number of different dimensions to be tested locally*/
    EquationInfo* eqInfo = calloc(numDim, sizeof(EquationInfo)); /*!< Create an array of EquationInfo structs defined in src/Utilities.h*/
    /*!
     * Iterate through the number of different dimensions to be tested, create an EquationInfo struct to be passed to the equation function
     * for each dimension, and fill it with relevant info for the dimension to be tested. Finally, store it to the array of structs.
     */
    for(int i = 0; i < numDim; i++){
        EquationInfo temp; /*!< Create a temporary struct to be added to the array defined above*/
        temp.equationName = eqName; /*!< Set the equationName to the value passed form the handler*/
        temp.equationNum = equationPos; /*!< Set the equationNum to one greater than the position in a 0 based array*/
        temp.numVectors = data->numVectors; /*!< Set the number of vectors for the test*/
        temp.dimToTest = data->dimsToTest[i]; /*!< Set the specific dimensions for this test*/
        temp.iterations = data->iterations; /*!< Set the number of iterations for this test*/
        temp.bandwidth = data->bandwidth; /*!< Set the bandwidth for the harmonic test*/
        temp.PAR = data->PAR; /*!< Set the pitch adjustment rate for the harmonic test*/
        temp.HMCR = data->HMCR ; /*!< Set the Harmony Memory Considering Rate for the harmonic test*/
        temp.beta = data->beta ;/*!< Set the beta value for attractiveness in the firefly algorithm test*/
        temp.gamma = data->gamma ;/*!< Set the absorption rate value for the firefly algorithm test*/
        temp.alpha  = data->alpha;/*!< Set the alpha value for the firefly algorithm test*/
        temp.c1  = data->c1;/*!< Set the personalBest term modifier c1 for PSO test*/
        temp.c2  = data->c2;/*!< Set the globalBest term modifier c2 for PSO test*/
        temp.k  = data->k;/*!< Set the dampening factor for PSO test*/
        temp.range = calloc(RANGE_SIZE, sizeof(double)); /*!< Allocate space for the range of this equation*/
        temp.range = calloc(RANGE_SIZE, sizeof(double)); /*!< Allocate space for the range of this equation*/
        temp.printExperiment = genRandIntP(data->numExperiments);
        /*!
         * Loop through the range for this equation and copy the values over.
         */
        for(int j = 0; j <= RANGE_MAX_POS; j++)
            temp.range[j] = data->ranges[equationPos][j]; /*!< Copy the value from the data Info struct to the range array*/
        eqInfo[i] = temp; /*!< Store the temp struct to the array*/
    }
    printf("EquationInfo created successfully: %s\n", eqInfo[0].equationName); fflush(stdout);
    /*!
     * Create an array of pthread_t which is how threads are referenced in POSIX threads.
     * Iterate for the number of experiments to be completed and within each iteration
     * Iterate from 0 to (numDim - 1) and start a thread for each equation dimension from
     * the constant defined above. Each thread will be passed a reference to the EquationInfo
     * struct for each dimension. If it fails, print the error message, free the struct, and return failure.
     */
    pthread_t *threads = calloc(numDim, sizeof(pthread_t));
    int numExp = data->numExperiments;
    for(int e = 0; e < numExp; e++) {
        for (int i = 0; i < numDim; i++) {
            eqInfo[i].currExperiment = e; /*!< Set the currentExperiment number for this test*/
            if (pthread_create(&threads[i], NULL, testTypeCalls[data->testSelection], &eqInfo[i]) < 0) {
                fprintf(stderr,
                        "There was an error creating the equation dimension thread for equation: %s and test dimension: %d",
                        eqName, i);
                for (int j = 0; j < numDim; j++) {
                    freeEquationInfo(&eqInfo[j]);
                }
                free(threads);
                return -1;
            }
        }
        /*!
         * Wait for all the threads to finish, and if there was an error, print the last error and return failure.
         */
        for (int i = 0; i < numDim; i++) {
            if (pthread_join(threads[i], NULL) < 0) {
                fprintf(stderr,
                        "There was an error joining the equation dimension thread for equation: %s and test dimension: %d",
                        eqName, i);
                for (int j = 0; j < numDim; j++) {
                    freeEquationInfo(&eqInfo[j]);
                }
                free(threads);
                return -1;
            }
        }
        printf("EquationInfo completed successfully: %s\n", eqInfo[0].equationName);
        fflush(stdout);
    }
    /*!
     * This equation has finished for all dimensions and experiments, free the threads array, free the array of EquationInfo structs and return success.
     */
    free(threads);
    for(int j = 0; j < numDim; j++) {
        freeEquationInfo(&eqInfo[j]);
    }
    return 0;
}

void* schwefelHandler(void* info){
    int equationPos = Schwefel; /*!< Set the position where the equation specific information can be found in the Info struct. References Enum EquationsPosition defined in src/Utilities.h*/
    Info* data = ((Info*)info); /*!< Cast the passed in struct back to an Info struct for processing*/
    char* eqName = "Schwefel"; /*!< Set the name of the equation to be run for file output in writeResultsToFile defined in src/Utilities.h*/
    /// pass in the variables defined above to the runEquationsAsThreads method and if it returns less than 0 it failed and exit failure
    if(runEquationsAsThreads(equationPos, eqName, data) < 0)
        exit(EXIT_FAILURE);
}
void* deJongHandler(void* info){
    int equationPos = DeJong; /*!< Set the position where the equation specific information can be found in the Info struct. References Enum EquationsPosition defined in src/Utilities.h*/
    Info* data = ((Info*)info); /*!< Cast the passed in struct back to an Info struct for processing*/
    char* eqName = "DeJong's 1st"; /*!< Set the name of the equation to be run for file output in writeResultsToFile defined in src/Utilities.h*/
    /// pass in the variables defined above to the runEquationsAsThreads method and if it returns less than 0 it failed and exit failure
    if(runEquationsAsThreads(equationPos, eqName, data) < 0)
        exit(EXIT_FAILURE);
}
void* rosenbrockHandler(void* info){
    int equationPos = Rosenbrock; /*!< Set the position where the equation specific information can be found in the Info struct. References Enum EquationsPosition defined in src/Utilities.h*/
    Info* data = ((Info*)info); /*!< Cast the passed in struct back to an Info struct for processing*/
    char* eqName = "Rosenbrock's Saddle"; /*!< Set the name of the equation to be run for file output in writeResultsToFile defined in src/Utilities.h*/
    /// pass in the variables defined above to the runEquationsAsThreads method and if it returns less than 0 it failed and exit failure
    if(runEquationsAsThreads(equationPos, eqName, data) < 0)
        exit(EXIT_FAILURE);
}
void* rastgrinHandler(void* info){
    int equationPos = Rastgrin; /*!< Set the position where the equation specific information can be found in the Info struct. References Enum EquationsPosition defined in src/Utilities.h*/
    Info* data = ((Info*)info); /*!< Cast the passed in struct back to an Info struct for processing*/
    char* eqName = "Rastgrin"; /*!< Set the name of the equation to be run for file output in writeResultsToFile defined in src/Utilities.h*/
    /// pass in the variables defined above to the runEquationsAsThreads method and if it returns less than 0 it failed and exit failure
    if(runEquationsAsThreads(equationPos, eqName, data) < 0)
        exit(EXIT_FAILURE);
}
void* griewangkHandler(void* info){
    int equationPos = Griewangk; /*!< Set the position where the equation specific information can be found in the Info struct. References Enum EquationsPosition defined in src/Utilities.h*/
    Info* data = ((Info*)info); /*!< Cast the passed in struct back to an Info struct for processing*/
    char* eqName = "Griewangk"; /*!< Set the name of the equation to be run for file output in writeResultsToFile defined in src/Utilities.h*/
    /// pass in the variables defined above to the runEquationsAsThreads method and if it returns less than 0 it failed and exit failure
    if(runEquationsAsThreads(equationPos, eqName, data) < 0)
        exit(EXIT_FAILURE);
}
void* sineEnvSineWaveHandler(void* info){
    int equationPos = SineEnvelope; /*!< Set the position where the equation specific information can be found in the Info struct. References Enum EquationsPosition defined in src/Utilities.h*/
    Info* data = ((Info*)info); /*!< Cast the passed in struct back to an Info struct for processing*/
    char* eqName = "Sine Envelope Sine Wave"; /*!< Set the name of the equation to be run for file output in writeResultsToFile defined in src/Utilities.h*/
    /// pass in the variables defined above to the runEquationsAsThreads method and if it returns less than 0 it failed and exit failure
    if(runEquationsAsThreads(equationPos, eqName, data) < 0)
        exit(EXIT_FAILURE);
}
void* stretchVSineWaveHandler(void* info){
    int equationPos = StretchedWave; /*!< Set the position where the equation specific information can be found in the Info struct. References Enum EquationsPosition defined in src/Utilities.h*/
    Info* data = ((Info*)info); /*!< Cast the passed in struct back to an Info struct for processing*/
    char* eqName = "Stetch V Sine Wave"; /*!< Set the name of the equation to be run for file output in writeResultsToFile defined in src/Utilities.h*/
    /// pass in the variables defined above to the runEquationsAsThreads method and if it returns less than 0 it failed and exit failure
    if(runEquationsAsThreads(equationPos, eqName, data) < 0)
        exit(EXIT_FAILURE);
}
void* ackleyOneHandler(void* info){
    int equationPos = AckleyOne; /*!< Set the position where the equation specific information can be found in the Info struct. References Enum EquationsPosition defined in src/Utilities.h*/
    Info* data = ((Info*)info); /*!< Cast the passed in struct back to an Info struct for processing*/
    char* eqName = "Ackley One"; /*!< Set the name of the equation to be run for file output in writeResultsToFile defined in src/Utilities.h*/
    /// pass in the variables defined above to the runEquationsAsThreads method and if it returns less than 0 it failed and exit failure
    if(runEquationsAsThreads(equationPos, eqName, data) < 0)
        exit(EXIT_FAILURE);
}
void* ackleyTwoHandler(void* info){
    int equationPos = AckleyTwo; /*!< Set the position where the equation specific information can be found in the Info struct. References Enum EquationsPosition defined in src/Utilities.h*/
    Info* data = ((Info*)info); /*!< Cast the passed in struct back to an Info struct for processing*/
    char* eqName = "Ackley Two"; /*!< Set the name of the equation to be run for file output in writeResultsToFile defined in src/Utilities.h*/
    /// pass in the variables defined above to the runEquationsAsThreads method and if it returns less than 0 it failed and exit failure
    if(runEquationsAsThreads(equationPos, eqName, data) < 0)
        exit(EXIT_FAILURE);
}
void* eggHolderHandler(void* info){
    int equationPos = EggHolder; /*!< Set the position where the equation specific information can be found in the Info struct. References Enum EquationsPosition defined in src/Utilities.h*/
    Info* data = ((Info*)info); /*!< Cast the passed in struct back to an Info struct for processing*/
    char* eqName = "Egg Holder"; /*!< Set the name of the equation to be run for file output in writeResultsToFile defined in src/Utilities.h*/
    /// pass in the variables defined above to the runEquationsAsThreads method and if it returns less than 0 it failed and exit failure
    if(runEquationsAsThreads(equationPos, eqName, data) < 0)
        exit(EXIT_FAILURE);
}
void* ranaHandler(void* info){
    int equationPos = Rana; /*!< Set the position where the equation specific information can be found in the Info struct. References Enum EquationsPosition defined in src/Utilities.h*/
    Info* data = ((Info*)info); /*!< Cast the passed in struct back to an Info struct for processing*/
    char* eqName = "Rana"; /*!< Set the name of the equation to be run for file output in writeResultsToFile defined in src/Utilities.h*/
    /// pass in the variables defined above to the runEquationsAsThreads method and if it returns less than 0 it failed and exit failure
    if(runEquationsAsThreads(equationPos, eqName, data) < 0)
        exit(EXIT_FAILURE);
}
void* pathologicalHandler(void* info){
    int equationPos = Pathological; /*!< Set the position where the equation specific information can be found in the Info struct. References Enum EquationsPosition defined in src/Utilities.h*/
    Info* data = ((Info*)info); /*!< Cast the passed in struct back to an Info struct for processing*/
    char* eqName = "Pathological"; /*!< Set the name of the equation to be run for file output in writeResultsToFile defined in src/Utilities.h*/
    /// pass in the variables defined above to the runEquationsAsThreads method and if it returns less than 0 it failed and exit failure
    if(runEquationsAsThreads(equationPos, eqName, data) < 0)
        exit(EXIT_FAILURE);
}
void* michalewiczHandler(void* info){
    int equationPos = Michalewicz; /*!< Set the position where the equation specific information can be found in the Info struct. References Enum EquationsPosition defined in src/Utilities.h*/
    Info* data = ((Info*)info); /*!< Cast the passed in struct back to an Info struct for processing*/
    char* eqName = "Michalewicz"; /*!< Set the name of the equation to be run for file output in writeResultsToFile defined in src/Utilities.h*/
    /// pass in the variables defined above to the runEquationsAsThreads method and if it returns less than 0 it failed and exit failure
    if(runEquationsAsThreads(equationPos, eqName, data) < 0)
        exit(EXIT_FAILURE);
}
void* mastersCosineWaveHandler(void* info){
    int equationPos = MastersCosineWave; /*!< Set the position where the equation specific information can be found in the Info struct. References Enum EquationsPosition defined in src/Utilities.h*/
    Info* data = ((Info*)info); /*!< Cast the passed in struct back to an Info struct for processing*/
    char* eqName = "Masters' Cosine Wave"; /*!< Set the name of the equation to be run for file output in writeResultsToFile defined in src/Utilities.h*/
    /// pass in the variables defined above to the runEquationsAsThreads method and if it returns less than 0 it failed and exit failure
    if(runEquationsAsThreads(equationPos, eqName, data) < 0)
        exit(EXIT_FAILURE);
}
void* quarticHandler(void* info){
    int equationPos = Quartic; /*!< Set the position where the equation specific information can be found in the Info struct. References Enum EquationsPosition defined in src/Utilities.h*/
    Info* data = ((Info*)info); /*!< Cast the passed in struct back to an Info struct for processing*/
    char * eqName = "Quartic"; /*!< Set the name of the equation to be run for file output in writeResultsToFile defined in src/Utilities.h*/
    /// pass in the variables defined above to the runEquationsAsThreads method and if it returns less than 0 it failed and exit failure
    if(runEquationsAsThreads(equationPos, eqName, data) < 0)
        exit(EXIT_FAILURE);
}
void* levyHandler(void* info){
    int equationPos = Levy; /*!< Set the position where the equation specific information can be found in the Info struct. References Enum EquationsPosition defined in src/Utilities.h*/
    Info* data = ((Info*)info); /*!< Cast the passed in struct back to an Info struct for processing*/
    char* eqName = "Levy"; /*!< Set the name of the equation to be run for file output in writeResultsToFile defined in src/Utilities.h*/
    /// pass in the variables defined above to the runEquationsAsThreads method and if it returns less than 0 it failed and exit failure
    if(runEquationsAsThreads(equationPos, eqName, data) < 0)
        exit(EXIT_FAILURE);
}
void* stepHandler(void* info){
    int equationPos = Step; /*!< Set the position where the equation specific information can be found in the Info struct. References Enum EquationsPosition defined in src/Utilities.h*/
    Info* data = ((Info*)info); /*!< Cast the passed in struct back to an Info struct for processing*/
    char* eqName = "Step"; /*!< Set the name of the equation to be run for file output in writeResultsToFile defined in src/Utilities.h*/
    /// pass in the variables defined above to the runEquationsAsThreads method and if it returns less than 0 it failed and exit failure
    if(runEquationsAsThreads(equationPos, eqName, data) < 0)
        exit(EXIT_FAILURE);
}
void* alpineHandler(void* info){
    int equationPos = Alpine; /*!< Set the position where the equation specific information can be found in the Info struct. References Enum EquationsPosition defined in src/Utilities.h*/
    Info* data = ((Info*)info); /*!< Cast the passed in struct back to an Info struct for processing*/
    char* eqName = "Alpine"; /*!< Set the name of the equation to be run for file output in writeResultsToFile defined in src/Utilities.h*/
    /// pass in the variables defined above to the runEquationsAsThreads method and if it returns less than 0 it failed and exit failure
    if(runEquationsAsThreads(equationPos, eqName, data) < 0)
        exit(EXIT_FAILURE);
}