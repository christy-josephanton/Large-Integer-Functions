# Large-Integer-Functions
Allows for simple arithmetic operations on integers larger than what C++ natively allows

C++ is limited to intgers up to -2^31 to 2^31-1. Although this is a very large range, some usecases may require intgeters larger than what can natively be done in the programming language. 

In this set of functions, a string of any interger can be inputted, and is then stored in a std::vector. This was chosen due its abiltiy to qucikly add/removed elements from the front of the data structure without added complexity. 

Although addition and subtraction are stright forward, and can be done in a reasonable amount of time, traditional multiplication methods taught in school can take up to n^2 in time comeplexity. Due to this, the Karatsuba multiplation method was used.

The cpp file above includes constructers to create the large interger from a string, and functions for addition, subtraction, multiplation, comparaison. It also includes a function that can be used to test the runtime of each funtion with slight modication.

The suite of functions were tested against the Boost C libraries. It also includes functions to perform operations on large integers. 
