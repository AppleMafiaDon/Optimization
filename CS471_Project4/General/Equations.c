//
// Created by TappleDon on 4/2/2019.
//

/*!
 * \file Equations.c
 * \brief This is where the methods for the calls in General/TestTypes.c and defined in General/Equations.h are implemented.
 *
 *  Here we implement the functions to perform calculations on a single vector and produce a result for that vector based on
 *  a set of predetermined equations.
 */
#include "Utilities.h"
#include "Equations.h"
#include "MersenneMatrix.h"


double schwefelHost(const double* vector, int numDim){
    double calcValue = 0.0, /*!< Declare the variable to store the resulting calculation*/
    element; /*!< Declare the variable to represent the current element of the summation*/
    double schwefelConstant = (418.9829 * numDim); //!< Schwefel's constant, subtract the summation result from this number for final result
    /*!
     *  Loop through the vector for testing, multiply the current element by -1 and multiply that by sin(sqrt(|element|)).
     *  Once the total sum of all elements transformed in that manner is calculated subtract the sum from the constant defined above.
     */
    for(int j = 0; j < numDim; j++){
        element = vector[j]; /*!< Store the current element being operated on*/
        calcValue += (-1.0 * element) * sin(sqrt(fabs(element))); /*!< Calculate the sum*/
    }
    calcValue = schwefelConstant - calcValue; /*!< store to the calculated value: constant - sum*/
    ///return the final resulting value
    return calcValue;
}

double deJongHost(const double* vector, int numDim){
    double calcValue = 0.0; /*!< Initialize the variable to store the resulting calculation*/
    /*!
     * Loop through the vector for testing, for each element square it, and sum all the squares.
     */
    for(int j = 0; j < numDim; j++){
        calcValue += pow(vector[j], 2.0);
    }
    ///return the final resulting value
    return calcValue;
}

double rosenbrockHost(const double* vector, int numDim){
    double calcValue = 0.0, /*!< Implement the variable to store the resulting calculation*/
            element, /*!< Declare the variable to represent the current element of the summation*/
            nextElem; /*!< Declare the variable to represent the next element*/
    /*!
     * Loop through the vector for testing, multiply 100 by (current element squared - the next element) squared,
     * then add (1 - the current element) squared, and sum all of these transformed values.
     */
    for(int j = 0; j < numDim - 1; j++){
        element = vector[j];
        nextElem = vector[j+1];
        calcValue +=((100.0 * pow(pow(element, 2.0) - nextElem, 2.0)) + pow((1.0 - element), 2.0));
    }
    ///return the final resulting value
    return calcValue;
}
double rastgrinHost(const double* vector, int numDim){
    double calcValue= 0.0, /*!< Initialize the variable to store the resulting calculation*/
            element; /*!< Declare the variable to represent the current element of the summation*/
    double rastgrinConst = 10.0 * numDim; /*!< Set the Rastgrin constant to multiply the sum by after calculation*/
    /*!
     * Loop through the vector for testing, take the current element squared and subtract 10 times the
     * cos(2 times pi times the current element), sum all of the values transformed in this manner, and multiply
     * the total sum by the constant defined above. (10 times the number of dimensions/elements.)
     */
    for(int j = 0; j < numDim; j++){
        element = vector[j];
        calcValue += pow(element, 2.0) - (10.0 * cos(2.0 * M_PI * element));
    }
    calcValue = rastgrinConst * calcValue;
    ///return the final resulting value
    return calcValue;
}
double griewangkHost(const double* vector, int numDim){
    double addValue = 0.0, /*!< Initializing the variable to store the summation result*/
    multValue = 0.0, /*!< Initializing the variable to store the product result*/
    totalValue = 0.0, /*!< Initialize the variable to store the final result*/
    element; /*!< Declare the variable to represent the current element of the summation*/
    /*!
     * Loop through the vector for testing, for the summation result, add all terms of the current element squared divided by 4000,
     * and for the product result multiply all terms of cos(current element divided by the square root of the current index).
     * Once the summation and product are complete take 1 + the summation result - the product result.
     */
    for(int j = 0; j < numDim; j++){
        element = vector[j];
        addValue += pow(element, 2.0) / 4000.0;
        if(j == 0)
            multValue = cos(element / sqrt(j+1.0));
        else
            multValue *= cos(element / sqrt(j+1.0));
    }
    totalValue = 1.0 + addValue - multValue;
    ///return the final resulting value
    return totalValue;
}
double sineEnvSineWaveHost(const double* vector, int numDim){
    double calcValue = 0.0, /*!< Initialize the variable to store the resulting calculation*/
            element, /*!< Declare the variable to represent the current element of the summation*/
            nextElem; /*!< Declare the variable to represent the next element*/
    /*!
     * Loop through the vector for testing, adding 0.5 to sin((currElement^2 + nextElement^2 - 0.5)^2)/(1.0 + 0.001*(currElement^2 + nextElement^2)^2)
     * once the total value has been calculated multiply it by -1 for the final result.
     */
    for(int j = 0; j < numDim - 1; j++){
        element = vector[j];
        nextElem = vector[j+1];
        calcValue += 0.5 + (sin(pow( pow(element, 2.0) +  pow(nextElem, 2.0) - 0.5,2.0))/pow(1.0 + 0.001*(pow(element, 2.0) +  pow(nextElem, 2.0)), 2.0));
    }
    calcValue = -1.0 * calcValue;
    ///return the final resulting value
    return calcValue;
}
double stretchVSineWaveHost(const double* vector, int numDim){
    double calcValue =0.0, /*!< Initialize the variable to store the resulting calculation*/
            element, /*!< Declare the variable to represent the current element of the summation*/
            nextElem; /*!< Declare the variable to represent the next element*/
    /*!
     * Loop through the vector for testing, calculating the sum of the following for each element
     * (currElement^2 + nextElement^2)^0.25 * sin((50 * (currElement^2 + nextElement^2)^0.1)^2) + 1
     */
    for(int j = 0; j < numDim - 1; j++){
        element = vector[j];
        nextElem = vector[j+1];
        calcValue += pow(pow(element, 2.0) +  pow(nextElem, 2.0), 0.25) * sin(pow(50.0 * pow(pow(element, 2.0) +  pow(nextElem, 2.0), 0.1),2.0)) + 1.0;
    }
    ///return the final resulting value
    return calcValue;
}
double ackleyOneHost(const double* vector, int numDim){
    double calcValue = 0.0, /*!< Initialize the variable to store the resulting calculation*/
            element, /*!< Declare the variable to represent the current element of the summation*/
            nextElem; /*!< Declare the variable to represent the next element*/
    double ackleyConst = (1.0/exp(0.2)); /*!< Initialize the ackley constant to 1/e^0.2*/
    /*!
     * Loop through the vector for testing, calculating the sum of the following for each element
     * ackleyConst * sqrt((currElement^2 + nextElement^2)) + (3 * cos(2 * currElement)) + sin(2 * nextElement)
     */
    for(int j = 0; j < numDim - 1; j++){
        element = vector[j];
        nextElem = vector[j+1];
        calcValue += (ackleyConst*sqrt(pow(element, 2.0) +  pow(nextElem, 2.0))) +  3.0 * (cos(2.0 * element) + sin(2.0 * nextElem));
    }
    ///return the final resulting value
    return calcValue;
}
double ackleyTwoHost(const double* vector, int numDim){
    double calcValue = 0.0, /*!< Initialize the variable to store the resulting calculation*/
            element, /*!< Declare the variable to represent the current element of the summation*/
            nextElem; /*!< Declare the variable to represent the next element*/
    double ackleyConst = (1.0/exp(0.2));
    /*!
     * Loop through the vector for testing, calculating the sum of the following for each element
     * 20 + e - (20 / e^(0.2 * sqrt((currElement^2 + nextElement^2) / 2))) - e^(0.5 * (cos(2 * pi * currElement) + cos(2 * pi * nextElement)))
     */
    for(int j = 0; j < numDim - 1; j++){
        element = vector[j];
        nextElem = vector[j+1];
        calcValue += 20.0 + exp(1.0) - (20.0/exp(0.2 * sqrt((pow(element, 2.0) +  pow(nextElem, 2.0)) / 2.0))) - exp(0.5*(cos(2.0 * M_PI * element) + cos(2.0 * M_PI * nextElem)));
    }
    ///return the final resulting value
    return calcValue;
}
double eggHolderHost(const double* vector, int numDim){
    double calcValue = 0.0, /*!< Initialize the variable to store the resulting calculation*/
            element, /*!< Declare the variable to represent the current element of the summation*/
            nextElem; /*!< Declare the variable to represent the next element*/
    /*!
     * Loop through the vector for testing, calculating the sum of the following for each element
     * (-1 * currElement * sin(sqrt(absoluteVal(currElement - nextElement -47)))) - ((nextElement + 47) * sin(sqrt(absoluteVal(nextElement + 47 + (currElement / 2)))))
     */
    for(int j = 0; j < numDim - 1; j++){
        element = vector[j];
        nextElem = vector[j+1];
        calcValue += (-1.0 * element * sin(sqrt(fabs(element - nextElem - 47)))) - ((nextElem + 47) * sin(sqrt(fabs(nextElem + 47 + (element / 2.0)))));
    }
    ///return the final resulting value
    return calcValue;
}
double ranaHost(const double* vector, int numDim){
    double calcValue = 0.0, /*!< Initialize the variable to store the resulting calculation*/
            element, /*!< Declare the variable to represent the current element of the summation*/
            nextElem; /*!< Declare the variable to represent the next element*/
    /*!
     * Loop through the vector for testing, calculating the sum of the following for each element
     * (element * sin(sqrt(fabs(nextElem - element + 1.0))) * cos(sqrt(fabs(nextElem + element + 1.0))))
                + ((nextElem + 1.0) * cos(sqrt(fabs(nextElem - element + 1.0))) * sin(sqrt(fabs(nextElem + element + 1.0))))
     */
    for(int j = 0; j < numDim - 1; j++){
        element = vector[j];
        nextElem = vector[j+1];
        calcValue += (element * sin(sqrt(fabs(nextElem - element + 1.0))) * cos(sqrt(fabs(nextElem + element + 1.0))))
                + ((nextElem + 1.0) * cos(sqrt(fabs(nextElem - element + 1.0))) * sin(sqrt(fabs(nextElem + element + 1.0))));
    }
    ///return the final resulting value
    return calcValue;
}
double pathologicalHost(const double* vector, int numDim){
    double calcValue = 0.0, /*!< Initialize the variable to store the resulting calculation*/
            element, /*!< Declare the variable to represent the current element of the summation*/
            nextElem; /*!< Declare the variable to represent the next element*/
    /*!
     * Loop through the vector for testing, calculating the sum of the following for each element
     * 0.5 + ((sin(pow(sqrt((100.0 * pow(element, 2.0)) + pow(nextElem, 2.0)),2.0)) - 0.5)
                /(1.0 + (0.001 * pow(pow(element, 2.0) - (2.0 * element * nextElem) + pow(nextElem, 2.0), 2.0))))
     */
    for(int j = 0; j < numDim - 1; j++){
        element = vector[j];
        nextElem = vector[j+1];
        calcValue += 0.5 + ((sin(pow(sqrt((100.0 * pow(element, 2.0)) + pow(nextElem, 2.0)),2.0)) - 0.5)
                /(1.0 + (0.001 * pow(pow(element, 2.0) - (2.0 * element * nextElem) + pow(nextElem, 2.0), 2.0))));
    }
    ///return the final resulting value
    return calcValue;
}
double michalewiczHost(const double* vector, int numDim){
    double calcValue = 0.0, /*!< Initialize the variable to store the resulting calculation*/
            element; /*!< Declare the variable to represent the current element of the summation*/
    /*!
     * Loop through the vector for testing, calculating the sum of the following for each element
     * sin(element) * pow(sin(((j+1) * pow(element, 2.0)) / M_PI), 20.0)
     */
    for(int j = 0; j < numDim; j++){
        element = vector[j];
        calcValue += sin(element) * pow(sin(((j+1) * pow(element, 2.0)) / M_PI), 20.0);
    }
    calcValue = -1.0 * calcValue;
    ///return the final resulting value
    return calcValue;
}
double mastersCosineWaveHost(const double* vector, int numDim){
    double calcValue = 0.0, /*!< Initialize the variable to store the resulting calculation*/
            element, /*!< Declare the variable to represent the current element of the summation*/
            nextElem; /*!< Declare the variable to represent the next element*/
    /*!
     * Loop through the vector for testing, calculating the sum of the following for each element
     * exp((-1.0 / 8.0) *(pow(element, 2.0) + pow(nextElem, 2.0) + (0.5 * nextElem * element)))
                * cos(pow(pow(element, 2.0) + pow(nextElem, 2.0) + (0.5 * nextElem * element), 0.25))
     */
    for(int j = 0; j < numDim; j++){
        element = vector[j];
        nextElem = vector[j+1];
        calcValue += exp((-1.0 / 8.0) *(pow(element, 2.0) + pow(nextElem, 2.0) + (0.5 * nextElem * element)))
                * cos(pow(pow(element, 2.0) + pow(nextElem, 2.0) + (0.5 * nextElem * element), 0.25));
    }
    calcValue = -1.0 * calcValue;
    ///return the final resulting value
    return calcValue;
}
double quarticHost(const double* vector, int numDim){
    double calcValue = 0.0; /*!< Initialize the variable to store the resulting calculation*/
    /*!
     * Loop through the vector for testing, calculating the sum of the following for each element
     * (j + 1.0) * pow(vector[j], 4.0)
     */
    for(int j = 0; j < numDim; j++){
        calcValue += (j + 1.0) * pow(vector[j], 4.0);
    }
    ///return the final resulting value
    return calcValue;
}
double levyHost(const double* vector, int numDim){
    double calcValue = 0.0, /*!< Initialize the variable to store the resulting calculation*/
        levyFirstConst = 1.0 + ((vector[0] - 1.0) /4.0), /*!< Initialize the variable for storing W0 in the vector*/
        levyLastConst = 1.0 + ((vector[numDim - 1] - 1.0) /4.0), /*!< Initialize the variable for storing Wn in the vector*/
        wi; /*!< Declares the variable for declaring Wi for the current dimension in the vector*/
    /*!
     * Loop through the vector for testing, calculating the sum of the following for each element
     * first calculating  Wi = 1.0 + ((vector[j] - 1.0)/4.0)
     * (pow(wi - 1.0, 2.0) * (1.0 + 10.0 * pow(sin((M_PI * wi) + 1.0), 2.0))) + (pow(Wn - 1.0, 2.0) * (1.0 + pow(sin(2.0 * M_PI * Wn), 2.0)))
     * once this total is acquired adding pow(sin(M_PI * W0), 2.0) for the final result
     */
    for(int j = 0; j < numDim - 1; j++){
        wi = 1.0 + ((vector[j] - 1.0)/4.0);
        calcValue += (pow(wi - 1.0, 2.0) * (1.0 + 10.0 * pow(sin((M_PI * wi) + 1.0), 2.0))) + (pow(levyLastConst - 1.0, 2.0) * (1.0 + pow(sin(2.0 * M_PI * levyLastConst), 2.0)));
    }
    calcValue = pow(sin(M_PI * levyFirstConst), 2.0) + calcValue;
    ///return the final resulting value
    return calcValue;
}
double stepHost(const double* vector, int numDim){
    double calcValue = 0.0; /*!< Initialize the variable to store the resulting calculation*/
    /*!
     * Loop through the vector for testing, calculating the sum of the following for each element
     * pow(fabs(vector[j]) + 0.5, 2.0)
     */
    for(int j = 0; j < numDim; j++){
        calcValue += pow(fabs(vector[j]) + 0.5, 2.0);
    }
    ///return the final resulting value
    return calcValue;
}
double alpineHost(const double* vector, int numDim){
    double calcValue = 0.0, /*!< Initialize the variable to store the resulting calculation*/
            element; /*!< Declare the variable to represent the current element of the summation*/
    /*!
     * Loop through the vector for testing, calculating the sum of the following for each element
     * fabs((element * sin(element)) + (0.1 * element))
     */
    for(int j = 0; j < numDim; j++){
        element = vector[j];
        calcValue += fabs((element * sin(element)) + (0.1 * element));
    }
    ///return the final resulting value
    return calcValue;
}
