/*! \file main.c
 *  \brief The entry point for Unix/Linux machines when executing this program
 *
 *  Here, the arguments passed to the program are processed to determine the init file name,
 *  the init file is processed to determine the parameters for the program to utilize,
 */
#include "../General/Utilities.h"
#include "../General/Init.h"
#include "../General/EquationHandlers.h"
#include "../General/m19937ar-cok.h"
#include <pthread.h>


//! An array of pointers to the equation handler methods to be used by threads in main()
/*!
 * This is used as an easy way to iterate through the equation handlers when creating the
 * threads to start processing each equation in different threads.
 */
const void* equationHandlers[] = {
        &schwefelHandler, /*!< Reference to the schwefelHandler method defined in General/EquationHandlers.h*/
        &deJongHandler, /*!< Reference to the deJongHandler method defined in General/EquationHandlers.h*/
        &rosenbrockHandler, /*!< Reference to the rosenbrockHandler method defined in General/EquationHandlers.h*/
        &rastgrinHandler, /*!< Reference to the rastgrinHandler method defined in General/EquationHandlers.h*/
        &griewangkHandler, /*!< Reference to the griewangkHandler method defined in General/EquationHandlers.h*/
        &sineEnvSineWaveHandler, /*!< Reference to the sineEnvSineWaveHandler method defined in General/EquationHandlers.h*/
        &stretchVSineWaveHandler, /*!< Reference to the stretchVSineWaveHandler method defined in General/EquationHandlers.h*/
        &ackleyOneHandler, /*!< Reference to the ackleyOneHandler method defined in General/EquationHandlers.h*/
        &ackleyTwoHandler, /*!< Reference to the ackleyTwoHandler method defined in General/EquationHandlers.h*/
        &eggHolderHandler, /*!< Reference to the eggHolderHandler method defined in General/EquationHandlers.h*/
        &ranaHandler, /*!< Reference to the ranaHandler method defined in General/EquationHandlers.h*/
        &pathologicalHandler, /*!< Reference to the pathologicalHandler method defined in General/EquationHandlers.h*/
        &michalewiczHandler, /*!< Reference to the michalewiczHandler method defined in General/EquationHandlers.h*/
        &mastersCosineWaveHandler, /*!< Reference to the mastersCosineWaveHandler method defined in General/EquationHandlers.h*/
        &quarticHandler, /*!< Reference to the quarticHandler method defined in General/EquationHandlers.h*/
        &levyHandler, /*!< Reference to the levyHandler method defined in General/EquationHandlers.h*/
        &stepHandler, /*!< Reference to the stepHandler method defined in General/EquationHandlers.h*/
        &alpineHandler /*!< Reference to the alpineHandler method defined in General/EquationHandlers.h*/
};

/// \fn int main(int argc, char*argv[])
/// \brief Entry point for the program on Unix/Linux machines. Failures: Too many arguments, reading the init file failed, creating threads failed, and error returned from the threads.
/// \param argc - This represents the number of arguments provided to the program.
/// \param argv - This is the array of arguments provided to the program. argv[0] = program name, argv[1] = init filepath
/// \return 0 on success, -1 on failures.
int main(int argc, char*argv[]) {
    char* filename; /*!< Filepath for the init file required for this program*/
    Info progInfo= *(Info*)calloc(1, sizeof(Info)); /*!< Info struct that houses the data read in from the init file. Struct defined in General/Utilities.h*/
    /*!
     * Check the arguments passed to the program to determine what init file to use.
     * If no arguments were provided, argc = 1 and use the DEFAULT_INIT_FILE constant.
     * Else if one argument was provided, treat the argument at FILE_ARGUMENT as the filename which, if incorrect, will be handled later.
     * Otherwise too many arguments were provided and the program will print an error message and return failure.
     */
    if(argc == 1){
        filename = DEFAULT_INIT_FILE; /*!< DEFAULT_INIT_FILE is defined in General/Utilities.h*/
    }
    else if (argc == 2){
        filename = argv[FILE_ARGUMENT]; /*!< FILE_ARGUMENT is defined in General/Utilities.h*/
    }
    else{
        printf("Too many arguments were provided. Usage: <Program Name> <Init filename (Optional)>. Please try executing the code again.\n");
        return -1;
    }
    /*!
     * Create the mutex to be used when generating random numberss and writing to files
     */
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("There was an issue trying to initialize the mutex:");
        return -2;
    }
    unsigned long seed = clock(); /*! < generating a value to seed the Mersenne Twister algorithm*/
    /*!
     * Seed the Mersenne Twister algorithm defined in General/m19937ar-cok.h
     */
    init_genrand(seed);
    /*!
     * Once the filename is set, process the init file, passing in the Info struct and the file name
     * to the init function of General/Init.h. The init method will print the subsequent errors and
     * if failed return a value less than 0. Free progInfo and return failure.
     */
    if(init(filename, &progInfo) < 0) {
        freeInfo(&progInfo);
        return -1;
    }

    int numExp = progInfo.numExperiments,
    numEq = progInfo.numEquations; /*! < creating a local variable for the number of equations to avoid accessing the struct multiple times*/
    /*!
     * Provide user output to verify that init file info was properly read in.
     * Print the list of ranges, dimensions which will be tested, and the optimum values.
     */
    printMatrix(progInfo.ranges, numEq, RANGE_SIZE);
    printIArray(progInfo.dimsToTest, progInfo.numDimensions);

    /*!
     * Create an array of pthread_t which is how threads are referenced in POSIX threads.
     * Iterate from 0 to (numExp - 1) and set the current experiment number to our iteration.
     * Iterate from 0 to (numEq - 1) and start a thread for each equation handler from
     * the constant defined above. Each thread will be passed a reference to the progInfo
     * struct. If it fails, print the error message, free progInfo and threads, and return failure.
     */
    pthread_t *threads = calloc(numEq, sizeof(pthread_t));

    for (int i = 0; i < numEq; i++) {
        if (pthread_create(&threads[i], NULL, equationHandlers[i], &progInfo) < 0) {
            fprintf(stderr, "There was an error creating the equation thread at position: %d", i);
            freeInfo(&progInfo);
            free(threads);
            return -1;
        }
    }
    /*!
     * Iterate through the threads array and join all of the threads waiting for them to finish
     * before finalising the program. If it fails, print the error message, free progInfo and threads,
     * and return failure.
     */
    for (int i = 0; i < numEq; i++) {
        if (pthread_join(threads[i], NULL) < 0) {
            fprintf(stderr, "There was an error joining the equation thread at position: %d", i);
            freeInfo(&progInfo);
            free(threads);
            return -1;
        }
    }
    /*!
     * The program has finished. Free progInfo and threads, then destroy the mutex then return success.
     */
    freeInfo(&progInfo);
    free(threads);
    pthread_mutex_destroy(&mutex);
    return 0;
}