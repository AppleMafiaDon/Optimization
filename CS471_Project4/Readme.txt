--------------------------------------------------------------------------------------------------
* Created by Taylor Apple
* Student ID: 40936734
* last edited: 5/20/2019
*
--------------------------------------------------------------------------------------------------
This program utilizes an input file to determine the set of equations
to be tested, including the number of vectors per tested equation, 
the number of different dimensions to test, and the number of dimensions
in each different test, the number of equations, and the range for values for each equation. Then it spawns a thread for each equation. Each equation will then be processed for each
different dimension with a randomly generated matrix seeding the population for further testing and refinement.



Each of these matrices will be used to calculate an array of results
which is then processed to calculate the following metrics: 
best solution, average, standard deviation, range, median, and 
time in milliseconds.
----------------------------------------------------------------------------------------------------

INPUT FILE FORMAT (Must follow this format)
<> = data type of value
... = more values to be given
------------------------------------------------------------------------------------------------------
# of Experiments=<int> (Note: must be a positive integer)
Population=<int> (Note: must be a positive integer)
# of Dimensions=<int> (Note:Must come before "Test Dimensions" line)
Test Dimensions=<int>,<int>,<int>,... (Note:Cannot have more values than declared in previous line and must come after "# of Dimensions" line)
# of Equations=<int> 
Ranges=<double>,<double>,<double>,... (Note:Cannot have more values than declared in equations line and must come after equations line)
Iterations=<int> (Note: Has to be 30 or more)
Gamma=<double>
Alpha=<double> (Note: must be between [0, 1])
Beta=<double>
Dampener=<double> (Note: Suggested values between [0.8, 1.2])
C1=<double> (Note: must be between (0,2])
C2=<double> (Note: must be between (0,2])
PAR=<double> (Note: Suggested values between [0.1, 0.5] must be between [0,1])
HMCR=<double> (Note: Suggested values between [0.7,0.9] must be between [0,1])
Bandwidth=<double>
-----------------------------------------------------------------------------------------------------

For compiling the code, this will depend on the Operating System you have.
For any OS you must first have gcc version 8.2.0-3 installed. This can be looked up online.
Once installed, in command line (preferably PowerShell for Windows), navigate to the build directory of the source 
code provided. (e.g. cd C:\Users\TappleDon\OneDrive\CS471\Project2\build).
The build directory should be in the same parent directory as the source directories, General,
PThread, and Win32, as well as the directory Results. 
Then run the following commands:
	
	For Unix and Linux:
gcc ../General/Utilities.c ../General/Utilities.h ../General/HostCalls.h ../PThread/UtilP.c ../PThread/main.c ../PThread/EquationHandlers.c ../General/EquationHandlers.h ../General/Init.c ../General/Init.h ../General/Equations.c ../General/Equations.h ../General/m19937ar-cok.c ../General/m19937ar-cok.h ../General/MersenneMatrix.c ../General/MersenneMatrix.h ../General/PSO.c ../General/PSO.h ../General/FA.c ../General/FA.h ../General/Harmonic.c ../General/Harmonic.h -o testing -lm -lpthread
	For Windows:
gcc ../General/Utilities.c ../General/Utilities.h ../General/HostCalls.h ../Win32/Util32.c ../Win32/main32.c ../Win32/EquationHandlers32.c ../General/EquationHandlers.h ../General/Init.c ../General/Init.h ../General/Equations.c ../General/Equations.h ../General/m19937ar-cok.c ../General/m19937ar-cok.h ../General/MersenneMatrix.c ../General/MersenneMatrix.h ../General/PSO.c ../General/PSO.h ../General/FA.c ../General/FA.h ../General/Harmonic.c ../General/Harmonic.h -o testing -lm

This will create a file testing (or testing.exe in Windows) in the build folder.
To run the program type ./testing (or ./testing.exe in Windows) while in the build folder.
If one would like to specify a file path for an init file, please enter the file path as the
first and only accepted argument to the program call (e.g. ./testing.exe C:\Users\TappleDon\OneDrive\CS471\Project2\build)

When the program runs it will print out the init file provided for review of the read in data,
and then ask the user what type of test they would like to run. Either 'Particle' for Particle Swarm,
or 'Firefly' for the Firefly Algorithm, or 'Harmonic' for Harmonic Search. 
Particle Swarm will update the results in
Results/<Number of Dimensions>_Dimensions_results_PSO.csv
and
Results/<EquationName>_<Number of Dimensions>_Dimensions_log_PSO.csv
Firefly Algorithm will update the results in
Results/<Number of Dimensions>_Dimensions_results_FA.csv
and
Results/<EquationName>_<Number of Dimensions>_Dimensions_log_FA.csv
Harmonic Search will update the results in
Results/<Number of Dimensions>_Dimensions_results_H.csv
and
Results/<EquationName>_<Number of Dimensions>_Dimensions_log_H.csv

Recent Improvements
-------------------------------------------------------------------------------------------------------------------
-Made auxilary functions for random number generation, mutex locking, and population/vector fitness evaluation.
-Added a single header file to store the references to objective function calls to avoid duplication.
-Structured my algorithms to be more concise and compact focusing on limited and specific tasks and adding modularity.
-Condensed the way results were written so there are fewer files and results should be easier to process for the report.
-Moved seeding for the Mersenne Twister algorithm into main so it is only performed once at the start rather than each time a population is created.
-

Current known issues
----------------------------------------------------------------------------------------------------------
Was unable to perform all of the tuning I wanted to perform as I kept running up on an issue which kept setting my timeline back. Because I was using a OneDrive location to store my files and results occasionally the OneDrive process would interrupt and take hold of the file causing my program to crash unable to access the file it needed to write to. I changed the location of the files to be written but I was already running out of time and needed to get tests run utilizing all of my CPU.
