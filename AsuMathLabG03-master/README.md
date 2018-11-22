# MathLab

C++ project for calculating some mathematical operations similar to Matlab or Octave .



## Environment

Development under linux , coded with C++ and compiled with g++ using Makefile

##   Setup
      git clone git@github.com:ahmedibrahim6/AsuMathLabG03.git
      cd AsuMathLabG03/
      make
      ./matrix example.m
      ./matrix bigexample.m


##   Project phases

- [x] Phase 1 : Build a Matrix class , support basic mathematical operations and process input file ,show each step result on terminal 
* Phase 2 : support advanced operations and tuning 
    * support mathematical functions ( trigonometric - logarithmic - roots - power )
        * ex : A = (12 * sin(0.4))^3 + log(sqrt(32))
    * support mathematical expressions like element addition , subtration .. 
        * ex : A = (A./3).+(A.^4)
    * support flexible matrix parser ( accept matrix in matrix , expressions and variables )
        * ex : A = [[A [ 5.6 ; 6.8 ; 8.9 ]] ;[ 5 5 7 9]]
    * support error handling 
   




------------------------------------------------------------------------------------------------------------------------------------------
