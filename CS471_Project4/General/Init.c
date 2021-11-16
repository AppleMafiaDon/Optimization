//
// Created by TappleDon on 4/2/2019.
//

/*! \file Init.c
* \brief Handles processing the input file for use throughout this testing.
*
* Processes all required lines as designated in the readme file and stores the value to an Info struct pointer
* and asks for the users input on which test type to run. This info is then used in PThread/main.c or Win32/main32.c
 * and throughout the tests.
 */
#include "Utilities.h"
#include "Init.h"

/*!
 * Enum used for the state of the flags for lines which are being read
 */
enum inputFlag{
    NotRead, /*!< Signifies that the current line has not been read*/
    Reading, /*!< Signifies that the current line is being read and values need to be processed*/
    Read /*!< Signifies that the information for that current line has been processed and stored*/
};

int checkTestType(){
    int testFlag = Reading; /*!< Signify we are reading the test type input*/
    char testInput[50]; /*!< declare an array for the user input*/
    /*!
     * Infinitely loop until we get a correct input from the user of 'Random', 'Local', or 'Iterative'
     */
    while(testFlag == Reading){
        /*!
         * prompt the user for input then listen for input.  if the user inputs 'Particle' return the value for PSO
         * defined in the TestType enum within General/Utilities.h, otherwise if the user inputs 'Firefly' return Firefly
         * from this same enum, or if the user inputs 'Harmonic' return Harmonic from this same enum. Otherwise tell the
         * user it is an incorrect response and prompt the user for input again.
         */
        printf("What type of test would you like to run? ('Particle' = Particle Swarm Optimization/'Firefly' = Firefly Algorithm/'Harmonic' = Harmonic Search): \n");fflush(stdout);
        scanf("%s", testInput);
        if(strcmp(testInput, "Particle") == 0){
            return ParticleSwarm;
        }
        else if(strcmp(testInput, "Firefly") == 0){
            return Firefly;
        }
        else if(strcmp(testInput, "Harmonic") == 0){
            return Harmonic;
        }
        else{
            printf("Incorrect Response. Please input 'Particle' or 'Firefly' or 'Harmonic'. \n"); fflush(stdout);
        }
    }
}

int processVectors(char* arg, Info* progInfo){
    /*!
     * Attempt to convert the value in the given string arg to an integer and if it is not a positive integer tell the user
     * and return failure. Otherwise return success.
     */
    if((progInfo->numVectors = atoi(arg)) <= 0){
        printf("Please provide a positive integer for the number of vectors in the population to be tested. Check the input file and try again.\n");
        return -1;
    }
    return 0;
}

int processExperiments(char* arg, Info* progInfo){
    /*!
     * Attempt to convert the value in the given string arg to an integer and if it is not a positive integer tell the user
     * and return failure. Otherwise return success.
     */
    if((progInfo->numExperiments = atoi(arg)) <= 0){
        printf("Please provide a positive integer for the number of experiments to be run. Check the input file and try again.\n");
        return -1;
    }
    return 0;
}

int processDimensions(char* arg, Info* progInfo){
    /*!
     * Attempt to convert the value in the given string arg to an integer and if it is not a positive integer tell the user
     * and return failure. Otherwise allocate space for the array of different dimensions and return success.
     */
    if((progInfo->numDimensions = atoi(arg)) <= 0) {
        printf("Please provide a positive integer for the number of dimensions to be tested. Check the input file and try again.\n");
        return -1;
    }
    progInfo->dimsToTest = calloc(progInfo->numDimensions, sizeof(int));
    return 0;
}

int processDimList(char* arg, Info* progInfo){
    /*!
     * Tokenize the current string arg on ',' and initialize variables for processing the line. dim will be the current
     * dimension being processed in the tokenized string, dimCounter counts the number of dimensions which have been
     * processed, not to exceed numDim which is the number of dimensions declared in the input file. NumDimensions is
     * required to be defined before this method is called.
     */
    char* dimsTok = strtok(arg, ",");
    int dim = 0, dimCounter = 0, numDim = progInfo->numDimensions;
    /*!
     * While there are dimensions to process, check that it hasn't exceeded the number of expected dimensions, otherwise
     * tell the user and return failure. Attempt to parse the string to an integer and if it is not a positive integer
     * tell the user and return failure. If successfully parsed set the processed dimension to the corresponding position
     * in the array, increase the counter, and get the next token. Lastly, after all values have been parsed, make sure
     * we have parsed the right number of values, if not, tell the user and return failure, otherwise return success.
     */
    while(dimsTok){
        if(dimCounter == numDim){
            printf("Too many dimensions to test were entered. Please check the input file and try again.\n");
            return -1;
        }
        if((dim = atoi(dimsTok)) <= 0){
            dimCounter++;
            printf("Please enter a positive integer for the number of dimensions to be tested. Value entered: %d as the %d th value\n", dim, dimCounter);
            return -1;
        }
        progInfo->dimsToTest[dimCounter] = dim;
        dimCounter++;
        dimsTok = strtok(NULL, ",");
    }
    /*!
     * If not enough dimensions were provided tell the user and return failure otherwise return success.
     */
    if(dimCounter < numDim){
        printf("Not enough dimensions were provided for the test. Expected: %d, Received: %d. Please check the input file and try again.\n", numDim, dimCounter);
        return -1;
    }
    return 0;
}

int processEquations(char* arg, Info* progInfo){
    /*!
     * Attempt to convert the value in the given string arg to an integer and if it is not a positive integer tell the user
     * and return failure.
     */
    if((progInfo->numEquations = atoi(arg)) <= 0){
        printf("Please provide a positive integer for the number of equations to be tested. Check the input file and try again.\n");
        return -1;
    }
    int numEq = progInfo->numEquations;/*!< Store the number of equations locally*/
    /*!
     * if the number of equations defined is larger than the MAX_NUM_EQUATIONS defined in General/Utilities.h tell
     * the user and return failure. Otherwise allocate the arrays to stor optimum values and ranges for each equation
     * and return success.
     */
    if(numEq > MAX_NUM_EQUATIONS){
        printf("Requested too many equations. Please make sure the value is between 1 and %d.\n", MAX_NUM_EQUATIONS);
        return -1;
    }
    progInfo->ranges = calloc(numEq, sizeof(double*));
    for(int i = 0; i < numEq; i++){
        progInfo->ranges[i] = calloc(RANGE_SIZE, sizeof(double));
    }
    return 0;
}

int processRanges(char* arg, Info* progInfo){
    char* end; /*!< This is used to house the terminating character of the decimal parsing*/
    double rangeVal = 0; /*!< Initialize the variable to store the range value*/
    int rangeCounter = 0, /*!< Initialize the variable to store the range counter of current position*/
    numEq = progInfo->numEquations; /*!< Store the number of equations locally*/
    char** temp = calloc(numEq, sizeof(char*)); /*!< Allocate an array to temporarily store the unparsed ranges for each equation*/
    char* rangeTok = strtok(arg, ","); ///Tokenize the string on ','
    while(rangeTok){ ///While there are tokens
        /*!
         * If our counter equals the number of equations we know we have received too many values, tell the user and return failure.
         * Otherwise, store the unparsed string to the temp array increase the counter and get the next token.
         */
        if(rangeCounter == numEq){
            printf("Too many ranges were entered. Please check the input file and try again.\n");
            return -1;
        }
        temp[rangeCounter] = rangeTok;
        rangeCounter++;
        rangeTok = strtok(NULL, ",");
    }
    /*!
     * If the counter is less than our number of equations it did not receive enough range values, tell the user and
     * return failure.
     */
    if(rangeCounter < numEq){
        printf("Not enough ranges were provided for the test. Expected: %d, Received: %d. Please check the input file and try again.\n", numEq, rangeCounter);
        return -1;
    }
    /*!
     * Iterate through the temp array from 0 - (numEq - 1), resetting the range counter to 0, and tokenizing each
     * unparsed string on ';'.
     */
    for(int i = 0; i < numEq; i++) {
        rangeCounter = 0;
        rangeTok = strtok(temp[i], ";");
        while(rangeTok){ ///While there are tokens
            /*!
             * If our counter equals the number of range values in a range we know we have received too many values, tell the user and return failure.
             */
            if(rangeCounter == RANGE_SIZE){
                printf("Too many range values were provided. Please check the input file and try again.\n");
                return -1;
            }
            /*!
             * As the range value can be 0 in some cases, it will print a warning if it equals 0 after parsing the string to a double
             * and let the user determine if there was some improper output. Then store the value to the corresponding
             * location, increase the counter, and get the next token.
             */
            if((rangeVal = strtod(rangeTok, &end)) == 0.0){
                printf("Warning: Please make sure the intended value was 0 and wasn't mistakenly a string. Value entered: %s as the %d th value of equation %d\n", rangeTok, rangeCounter + 1, i + 1);
            }
            progInfo->ranges[i][rangeCounter] = rangeVal;
            rangeCounter++;
            rangeTok = strtok(NULL, ";");
        }
        /*!
         * If the counter is less than the number of range values it did not receive enough range values, tell the user and
         * return failure. Otherwise continue in the loop.
         */
        if(rangeCounter < RANGE_SIZE){
            printf("Not enough range values were provided for the test. Expected: %d, Received: %d. Please check the input file and try again.\n", RANGE_SIZE, rangeCounter);
            return -1;
        }
    }
    /*!
     * temp is no longer needed as the program parsed all of its values successfully so free temp and return success.
     */
    free(temp);
    return 0;
}

int processIterations(char* arg, Info* progInfo){
    /*!
     * Attempt to convert the value in the given string arg to an integer and if it is not a positive integer
     * greater than or equal to MINIMUM_ITERATIONS defined in General/Utilities.h tell the user
     * and return failure. Otherwise return success.
     */
    if((progInfo->iterations = atoi(arg)) < MINIMUM_ITERATIONS){
        printf("Need to declare a number of iterations greater than or equal to %d for statistical significance. Please check the input file and try again.\n", MINIMUM_ITERATIONS);
        return -1;
    }
    return 0;
}

int processBeta(char *arg, Info *progInfo){
    char* end; /*!< This is used to house the terminating character of the decimal parsing*/
    /*!
     * Attempt to convert the value in the given string arg to a double and if it is not a positive double tell the user
     * and return failure. Otherwise return success.
     */
    if((progInfo->beta = strtod(arg, &end)) <= 0){
        printf("Need to have a positive real number for the beta value. Please check the input file and try again.\n");
        return -1;
    }
    return 0;
}

int processGamma(char *arg, Info *progInfo){
    char* end; /*!< This is used to house the terminating character of the decimal parsing*/
    /*!
     * Attempt to convert the value in the given string arg to a double and if it is not a positive double tell the user
     * and return failure. Otherwise return success.
     */
    if((progInfo->gamma = strtod(arg, &end)) <= 0){
        printf("Need to have a positive real number for the gamma value. Please check the input file and try again.\n");
        return -1;
    }
    return 0;
}

int processAlpha(char *arg, Info *progInfo){
    char* end; /*!< This is used to house the terminating character of the decimal parsing*/
    /*!
     * Attempt to convert the value in the given string arg to a double and if it is not a positive double tell the user
     * and return failure. Otherwise return success.
     */
    if((progInfo->alpha = strtod(arg, &end)) <= 0){
        printf("Need to have a positive real number suggested between (0, 1] for the alpha value. Please check the input file and try again.\n");
        return -1;
    }
    return 0;
}

int processDampener(char *arg, Info *progInfo){
    char* end; /*!< This is used to house the terminating character of the decimal parsing*/
    /*!
     * Attempt to convert the value in the given string arg to a double and if it is not a positive double tell the user
     * and return failure. Otherwise return success.
     */
    if((progInfo->k = strtod(arg, &end)) <= 0){
        printf("Need to have a positive real number suggested between [0.8, 1.2] for the particle dampener value. Please check the input file and try again.\n");
        return -1;
    }
    return 0;
}

int processC1(char *arg, Info *progInfo){
    char* end; /*!< This is used to house the terminating character of the decimal parsing*/
    /*!
     * Attempt to convert the value in the given string arg to a double and if it is not a positive double tell the user
     * and return failure. Otherwise return success.
     */
    if((progInfo->c1 = strtod(arg, &end)) <= 0 && progInfo->c1 > 2){
        printf("Need to have a positive real number between (0, 2] for the c1 value. Please check the input file and try again.\n");
        return -1;
    }
    return 0;
}

int processC2(char *arg, Info *progInfo){
    char* end; /*!< This is used to house the terminating character of the decimal parsing*/
    /*!
     * Attempt to convert the value in the given string arg to a double and if it is not a positive double tell the user
     * and return failure. Otherwise return success.
     */
    if((progInfo->c2 = strtod(arg, &end)) <= 0 && progInfo->c2 > 2){
        printf("Need to have a positive real number between (0, 2] for the c2 value. Please check the input file and try again.\n");
        return -1;
    }
    return 0;
}

int processHMCR(char *arg, Info *progInfo){
    char* end; /*!< This is used to house the terminating character of the decimal parsing*/
    /*!
     * Attempt to convert the value in the given string arg to a double and if it is not a positive double tell the user
     * and return failure. Otherwise return success.
     */
    if((progInfo->HMCR = strtod(arg, &end)) < 0 && progInfo->HMCR > 1){
        printf("Need to have a positive real number between [0, 1] for the Harmonic Memory Consideration Rate value. Please check the input file and try again.\n");
        return -1;
    }
    return 0;
}

int processPAR(char *arg, Info *progInfo){
    char* end; /*!< This is used to house the terminating character of the decimal parsing*/
    /*!
     * Attempt to convert the value in the given string arg to a double and if it is not a positive double tell the user
     * and return failure. Otherwise return success.
     */
    if((progInfo->PAR = strtod(arg, &end)) < 0 && progInfo->PAR > 1){
        printf("Need to have a positive real number between [0, 1] for the pitch adjustment rate value. Please check the input file and try again.\n");
        return -1;
    }
    return 0;
}

int processBandwidth(char *arg, Info *progInfo){
    char* end; /*!< This is used to house the terminating character of the decimal parsing*/
    /*!
     * Attempt to convert the value in the given string arg to a double and if it is not a positive double tell the user
     * and return failure. Otherwise return success.
     */
    if((progInfo->bandwidth = strtod(arg, &end)) <= 0){
        printf("Need to have a positive real number for the bandwidth value. Please check the input file and try again.\n");
        return -1;
    }
    return 0;
}

int init(char* filename, Info* progInfo){
    FILE *inputFile = fopen(filename, "r");
    if(!inputFile){
        fprintf(stderr, "There was an issue opening the input file. Make sure the file exists and is in this directory or the proper directory is specified in the input argument.\n");
        return -1;
    }
    char line[LINE_LENGTH]; /*!< Declare a char array of LINE_LENGTH defined in General/Utilities.h to store the current line being processed*/
    int kFlag = NotRead, /*!< Initialize the flag representing the dampener line having been read to NotRead*/
    c1Flag = NotRead, /*!< Initialize the flag representing the C1 line having been read to NotRead*/
    c2Flag = NotRead, /*!< Initialize the flag representing the C2 (Roulette or Tournament) line having been read to NotRead*/
    betaFlag = NotRead, /*!< Initialize the flag representing the beta/attractiveness factor line having been read to NotRead*/
    experimentFlag = NotRead, /*!< Initialize the flag representing the number of experiments line having been read to NotRead*/
    vectorFlag = NotRead, /*!< Initialize the flag representing the number of vectors line having been read to NotRead*/
    dimensionFlag = NotRead, /*!< Initialize the flag representing the number of dimensions line having been read to NotRead*/
    dimListFlag = NotRead, /*!< Initialize the flag representing the different dimensions line having been read to NotRead*/
    equationFlag = NotRead, /*!< Initialize the flag representing the number of equations line having been read to NotRead*/
    alphaFlag = NotRead, /*!< Initialize the flag representing the alpha line having been read to NotRead*/
    rangeFlag = NotRead, /*!< Initialize the flag representing the ranges line having been read to NotRead*/
    iterationFlag = NotRead, /*!< Initialize the flag representing the number of iterations line having been read to NotRead*/
    gammaFlag = NotRead, /*!< Initialize the flag representing the gamma line having been read to NotRead*/
    PARFlag = NotRead, /*!< Initialize the flag representing the pitch adjustment line having been read to NotRead*/
    HMCRFlag = NotRead, /*!< Initialize the flag representing the HMCR line having been read to NotRead*/
    bandwidthFlag = NotRead, /*!< Initialize the flag representing the bandwidth line having been read to NotRead*/
    testDimStr = 0, /*!< Initialize a variable tracking the result of comparing to the expected dimensions line flag*/
    rangeStr = 0; /*!< Initialize a variable tracking the result of comparing to the expected ranges line flag*/
    char* arg; /*!< Stores the tokenized string from the line read in*/
    while (line[0] != EOF && fgets(line, sizeof(line), inputFile)) { ///while we still have lines to read
        printf("line: %s\n", line); fflush(stdout); ///print the line being read
        arg = strtok(line, "=");///split the line on '='
        while (arg) { ///while there are more tokens splitting on '='
            /*!
             * If we are reading the number of vectors line, processVectors and if it failed close the file and return -1.
             * Otherwise set the flag to Read and break the loop effectively moving to the next line being read.
             */
            if(vectorFlag == Reading){
                if(processVectors(arg, progInfo) < 0) {
                    fclose(inputFile);
                    return -1;
                }
                vectorFlag = Read;
                break;
            }
            /*!
             * If we are reading the number of dimensions line, processDimensions and if it failed close the file and return -1.
             * Otherwise set the flag to Read and break the loop effectively moving to the next line being read.
             */
            if(dimensionFlag == Reading){
                if(processDimensions(arg, progInfo) < 0) {
                    fclose(inputFile);
                    return -1;
                }
                dimensionFlag = Read;
                break;
            }
            /*!
             * If we are reading the different dimensions line, processDimList and if it failed close the file and return -1.
             * Otherwise set the flag to Read and break the loop effectively moving to the next line being read.
             */
            if(dimListFlag == Reading){
                if(processDimList(arg, progInfo) < 0){
                    fclose(inputFile);
                    return -1;
                }
                dimListFlag = Read;
                break;
            }
            /*!
             * If we are reading the number of equations line, processEquations and if it failed close the file and return -1.
             * Otherwise set the flag to Read and break the loop effectively moving to the next line being read.
             */
            if(equationFlag == Reading){
                if(processEquations(arg, progInfo) < 0) {
                    fclose(inputFile);
                    return -1;
                }
                equationFlag = Read;
                break;
            }
            /*!
             * If we are reading the ranges line, processRanges and if it failed close the file and return -1.
             * Otherwise set the flag to Read and break the loop effectively moving to the next line being read.
             */
            if(rangeFlag == Reading){
                if(processRanges(arg, progInfo) < 0) {
                    fclose(inputFile);
                    return -1;
                }
                rangeFlag = Read;
                break;
            }
            /*!
             * If we are reading the number of iterations line, processIterations and if it failed close the file and return -1.
             * Otherwise set the flag to Read and break the loop effectively moving to the next line being read.
             */
            if(iterationFlag == Reading){
                if(processIterations(arg, progInfo) < 0) {
                    fclose(inputFile);
                    return -1;
                }
                iterationFlag = Read;
                break;
            }
            /*!
             * If we are reading the gamma line, processGamma and if it failed close the file and return -1.
             * Otherwise set the flag to Read and break the loop effectively moving to the next line being read.
             */
            if(gammaFlag == Reading){
                if(processGamma(arg, progInfo) < 0) {
                    fclose(inputFile);
                    return -1;
                }
                gammaFlag = Read;
                break;
            }
            /*!
             * If we are reading the pitch adjustment line, processPAR and if it failed close the file and return -1.
             * Otherwise set the flag to Read and break the loop effectively moving to the next line being read.
             */
            if(PARFlag == Reading){
                if(processPAR(arg, progInfo) < 0) {
                    fclose(inputFile);
                    return -1;
                }
                PARFlag = Read;
                break;
            }
            /*!
             * If we are reading the number of experiments line, processExperiments and if it failed close the file and return -1.
             * Otherwise set the flag to Read and break the loop effectively moving to the next line being read.
             */
            if(experimentFlag == Reading){
                if(processExperiments(arg, progInfo) < 0) {
                    fclose(inputFile);
                    return -1;
                }
                experimentFlag = Read;
                break;
            }
            /*!
             * If we are reading the alpha line, processAlpha and if it failed close the file and return -1.
             * Otherwise set the flag to Read and break the loop effectively moving to the next line being read.
             */
            if(alphaFlag == Reading){
                if(processAlpha(arg, progInfo) < 0) {
                    fclose(inputFile);
                    return -1;
                }
                alphaFlag = Read;
                break;
            }
            /*!
             * If we are reading the dampener line, processDampener and if it failed close the file and return -1.
             * Otherwise set the flag to Read and break the loop effectively moving to the next line being read.
             */
            if(kFlag == Reading){
                if(processDampener(arg, progInfo) < 0) {
                    fclose(inputFile);
                    return -1;
                }
                kFlag = Read;
                break;
            }
            /*!
             * If we are reading the C1 line, processC1 and if it failed close the file and return -1.
             * Otherwise set the flag to Read and break the loop effectively moving to the next line being read.
             */
            if(c1Flag == Reading){
                if(processC1(arg, progInfo) < 0) {
                    fclose(inputFile);
                    return -1;
                }
                c1Flag = Read;
                break;
            }
            /*!
             * If we are reading the C2 line, processC2 and if it failed close the file and return -1.
             * Otherwise set the flag to Read and break the loop effectively moving to the next line being read.
             */
            if(c2Flag == Reading){
                if(processC2(arg, progInfo) < 0) {
                    fclose(inputFile);
                    return -1;
                }
                c2Flag = Read;
                break;
            }
            /*!
             * If we are reading the beta line, processBeta and if it failed close the file and return -1.
             * Otherwise set the flag to Read and break the loop effectively moving to the next line being read.
             */
            if(betaFlag == Reading){
                if(processBeta(arg, progInfo) < 0) {
                    fclose(inputFile);
                    return -1;
                }
                betaFlag = Read;
                break;
            }
            /*!
             * If we are reading the HMCR line, processHMCR and if it failed close the file and return -1.
             * Otherwise set the flag to Read and break the loop effectively moving to the next line being read.
             */
            if(HMCRFlag == Reading){
                if(processHMCR(arg, progInfo) < 0) {
                    fclose(inputFile);
                    return -1;
                }
                HMCRFlag = Read;
                break;
            }
            /*!
             * If we are reading the bandwidth line, processBandwidth and if it failed close the file and return -1.
             * Otherwise set the flag to Read and break the loop effectively moving to the next line being read.
             */
            if(bandwidthFlag == Reading){
                if(processBandwidth(arg, progInfo) < 0) {
                    fclose(inputFile);
                    return -1;
                }
                bandwidthFlag = Read;
                break;
            }
            /*!
             * This point is reached if the program is not currently reading any of the specified lines and is looking
             * to see if it is reading one of the expected lines.
             */
             /*!
              * If we haven't read the number of vectors line already and it equals the signifier for the number of
              * vectors line, set the flag to Reading, tokenize on '=' to get the value and continue the arg while loop.
              */
            if(strcmp(arg, "Population") == 0 && vectorFlag == NotRead) {
                vectorFlag = Reading;
                arg = strtok(NULL, "=");
                continue;
            }
            /*!
              * If we haven't read the number of dimensions line already and it equals the signifier for the number of
              * dimensions line, set the flag to Reading, tokenize on '=' to get the value and continue the arg while loop.
              */
            if(strcmp(arg, "# of Dimensions") == 0 && dimensionFlag == NotRead) {
                dimensionFlag = Reading;
                arg = strtok(NULL, "=");
                continue;
            }
            /*!
              * If we haven't read the different dimensions line already and it equals the signifier for the different
              * dimensions line, and we have read the number of dimensions line, set the flag to Reading, tokenize
              * on '=' to get the value and continue the arg while loop.
              */
            if((testDimStr = strcmp(arg, "Test Dimensions"))  == 0 && dimListFlag == NotRead && dimensionFlag == Read) {
                dimListFlag = Reading;
                arg = strtok(NULL, "=");
                continue;
            }
            /*!
             * Otherwise if we have come to the different dimensions line and have not read the number of dimensions in
             * tell the user, close the file and return failure.
             */
            else if(testDimStr == 0 && dimensionFlag == NotRead){
                printf("Input file is malformed. You must declare the number of dimensions before providing the dimensions to test. Please reformat the input file.\n");
                fclose(inputFile);
                return -1;
            }
            /*!
              * If we haven't read the number of Equations line already and it equals the signifier for the number of
              * Equations line, set the flag to Reading, tokenize on '=' to get the value and continue the arg while loop.
              */
            if(strcmp(arg, "# of Equations") == 0 && equationFlag == NotRead) {
                equationFlag = Reading;
                arg = strtok(NULL, "=");
                continue;
            }
            /*!
              * If we haven't read the ranges line already and it equals the signifier for the ranges line,
              * and we have read the number of equations line, set the flag to Reading, tokenize
              * on '=' to get the value and continue the arg while loop.
              */
            if((rangeStr = strcmp(arg, "Ranges")) == 0 && rangeFlag == NotRead && equationFlag == Read) {
                rangeFlag = Reading;
                arg = strtok(NULL, "=");
                continue;
            }
            /*!
             * Otherwise if we have come to the ranges line and have not read the number of equations in
             * tell the user, close the file and return failure.
             */
            else if (rangeStr == 0 && equationFlag == NotRead){
                printf("Input file is malformed. You must declare the number of equations before providing the ranges for equations. Please reformat the input file.\n");
                fclose(inputFile);
                return -1;
            }
            /*!
              * If we haven't read the number of Generations/Iterations line already and it equals the signifier for the number of
              * Generations/Iterations line, set the flag to Reading, tokenize on '=' to get the value and continue the arg while loop.
              */
            if(strcmp(arg, "Iterations") == 0 && iterationFlag == NotRead){
                iterationFlag = Reading;
                arg = strtok(NULL, "=");
                continue;
            }
            /*!
              * If we haven't read the Gamma line already and it equals the signifier for the Gamma line,
              * set the flag to Reading, tokenize on '=' to get the value and continue the arg while loop.
              */
            if(strcmp(arg, "Gamma") == 0 && gammaFlag == NotRead){
                gammaFlag = Reading;
                arg = strtok(NULL, "=");
                continue;
            }
            /*!
              * If we haven't read the pitch adjustment line already and it equals the signifier for the pitch adjustment line,
              * set the flag to Reading, tokenize on '=' to get the value and continue the arg while loop.
              */
            if(strcmp(arg, "PAR") == 0 && PARFlag == NotRead){
                PARFlag = Reading;
                arg = strtok(NULL, "=");
                continue;
            }
            /*!
              * If we haven't read the number of experiments line already and it equals the signifier for the number of experiments
              * line, set the flag to Reading, tokenize on '=' to get the value and continue the arg while loop.
              */
            if(strcmp(arg, "# of Experiments") == 0 && experimentFlag == NotRead){
                experimentFlag = Reading;
                arg = strtok(NULL, "=");
                continue;
            }
            /*!
              * If we haven't read the alpha line already and it equals the signifier for the alpha line,
              * set the flag to Reading, tokenize on '=' to get the value and continue the arg while loop.
              */
            if(strcmp(arg, "Alpha") == 0 && alphaFlag == NotRead){
                alphaFlag = Reading;
                arg = strtok(NULL, "=");
                continue;
            }
            /*!
              * If we haven't read the dampener line already and it equals the signifier for the dampener line,
              * set the flag to Reading, tokenize on '=' to get the value and continue the arg while loop.
              */
            if(strcmp(arg, "Dampener") == 0 && kFlag == NotRead){
                kFlag = Reading;
                arg = strtok(NULL, "=");
                continue;
            }
            /*!
              * If we haven't read the C1 line already and it equals the signifier for the C1 line,
              * set the flag to Reading, tokenize on '=' to get the value and continue the arg while loop.
              */
            if(strcmp(arg, "C1") == 0 && c1Flag == NotRead){
                c1Flag = Reading;
                arg = strtok(NULL, "=");
                continue;
            }
            /*!
              * If we haven't read the C2 line already and it equals the signifier for the C2 line,
              * set the flag to Reading, tokenize on '=' to get the value and continue the arg while loop.
              */
            if(strcmp(arg, "C2") == 0 && c2Flag == NotRead){
                c2Flag = Reading;
                arg = strtok(NULL, "=\n");
                continue;
            }
            /*!
              * If we haven't read the beta line already and it equals the signifier for the beta line,
              * set the flag to Reading, tokenize on '=' to get the value and continue the arg while loop.
              */
            if(strcmp(arg, "Beta") == 0 && betaFlag == NotRead){
                betaFlag = Reading;
                arg = strtok(NULL, "=");
                continue;
            }
            /*!
              * If we haven't read the HMCR line already and it equals the signifier for the HMCR line,
              * set the flag to Reading, tokenize on '=' to get the value and continue the arg while loop.
              */
            if(strcmp(arg, "HMCR") == 0 && HMCRFlag == NotRead){
                HMCRFlag = Reading;
                arg = strtok(NULL, "=");
                continue;
            }
            /*!
              * If we haven't read the bandwidth line already and it equals the signifier for the bandwidth line,
              * set the flag to Reading, tokenize on '=' to get the value and continue the arg while loop.
              */
            if(strcmp(arg, "Bandwidth") == 0 && bandwidthFlag == NotRead){
                bandwidthFlag = Reading;
                arg = strtok(NULL, "=");
                continue;
            }
            /*!
             * This point is reached if none of the proper tags were found, exiting the arg while loop and
             * effectively moving to the next line.
             */
            break;
        }
    }
    /*!
     * If one of the expected/required lines was not Read tell the user and close the file then return failure. Otherwise
     * close the file ask the user for the test type and then return success.
     */
    if(kFlag != Read || c1Flag != Read || c2Flag != Read || betaFlag != Read || experimentFlag != Read ||
            vectorFlag != Read || dimensionFlag != Read || dimListFlag != Read || equationFlag != Read ||
            alphaFlag != Read || rangeFlag != Read || iterationFlag != Read || gammaFlag != Read || PARFlag != Read ||
            HMCRFlag != Read || bandwidthFlag != Read){
        printf("Not all required lines were provided. Please check the readme file, fix the input file and try again.\n");
        fclose(inputFile);
        return -1;
    }
    fclose(inputFile);
    progInfo->testSelection = checkTestType();
    return 0;
}