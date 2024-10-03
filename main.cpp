#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <optional>
#include <random>
#include <cfloat>





//#include "titi.hip"
#include "gpuA.hpp"
#include "cpuA.hpp"

int main(){
    Test();
    TestcpuA();
    std::cout << "[INFO]: WELL DONE :-) FINISHED !"<<"\n";
    return 0;
}







