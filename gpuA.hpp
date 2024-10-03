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


  
//Link HIP
#include "hip/hip_runtime.h"
#include "hip/hip_runtime_api.h"


/*
#include "hipblas.h"
#include "hipsolver.h"
#include "hipblas-export.h"
*/
   
/*
#include <roctx.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/functional.h>
#include <thrust/execution_policy.h>
#include <thrust/random.h>
#include <thrust/host_vector.h>
#include <thrust/sort.h>
#include <thrust/count.h>
*/


__global__ void kernel(float* x,float* y,int n){
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) y[idx] += 1;
}



void Test()
{ 
    int count, device;   
    hipSetDevice(1); 
    hipGetDeviceCount(&count);
    hipGetDevice(&device);
    printf("[INFO]: Je suis gpuA\n");
    printf("        Test device %d %d \n", device, count);

}





