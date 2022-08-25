# test_task

task1 - the problems are described only.

task2 - refactoring for CodeGenerator is presented. For expand the number of supported languages, just add the new language class and specific language code generator. How to build: after git pull, mkdir build -> cd build -> cmake .. -> cmake --build . -> launch the binary (small test application). 

task3 - refactoring is presented. The problems were: 1) combination of C and C++, so the C++ functions and types aliases are used for uniformity; 2) the main problem is all-in-one class, which is hardly debuggable and hardly expendable, so the functional was divided via separate classes.