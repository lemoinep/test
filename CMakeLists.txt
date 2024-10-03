
project(main LANGUAGES CXX HIP)

cmake_minimum_required(VERSION 3.22)


set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)


message(CURRENT DIR= [${CMAKE_CURRENT_SOURCE_DIR}])
message(CURRENT DIR PREFIX_PATH= [${MAKE_PREFIX_PATH}])

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

MESSAGE("{COMPILE_WITH_HIP}")
if (TRUE)
    include_directories(/opt/rocm-5.7.2/hip/include)
    include_directories(/opt/rocm-5.7.2/hipblas/include)
    include_directories(/opt/rocm-5.7.2/hipblas/lib)
    include_directories(/opt/rocm-5.7.2/roctracer/include)
    list(APPEND CMAKE_PREFIX_PATH /opt/rocm-5.7.2)
endif()

# Trouver le package HIP
find_package(hip REQUIRED)

set(GPU_RUNTIME "HIP" CACHE STRING "Switches between HIP and CUDA")
set(GPU_RUNTIMES "HIP" "CUDA")
set_property(CACHE GPU_RUNTIME PROPERTY STRINGS ${GPU_RUNTIMES})

if(NOT "${GPU_RUNTIME}" IN_LIST GPU_RUNTIMES)
    set(ERROR_MESSAGE "GPU_RUNTIME is set to \"${GPU_RUNTIME}\".\nGPU_RUNTIME must be either HIP or CUDA.")
    message(FATAL_ERROR ${ERROR_MESSAGE})
endif()

enable_language(${GPU_RUNTIME})

set(CMAKE_${GPU_RUNTIME}_STANDARD 17)
set(CMAKE_${GPU_RUNTIME}_EXTENSIONS OFF)
set(CMAKE_${GPU_RUNTIME}_STANDARD_REQUIRED ON)
set(ROCM_ROOT "/opt/rocm-5.7.2" CACHE PATH "Root directory of the ROCm installation")
list(APPEND CMAKE_PREFIX_PATH "${ROCM_ROOT}")

add_compile_definitions( __HIP_PLATFORM_AMD__)

# Options de compilation HIP
set(HIP_HIPCC_FLAGS "${HIP_HIPCC_FLAGS} -fPIC -O3")

# Fonction pour configurer la cible GPU
function(configure_hip_target target)
    set_target_properties(${target} PROPERTIES
        LANGUAGE HIP
        LINKER_LANGUAGE HIP
    )
    target_link_libraries(${target} PRIVATE hip::device hip::host)
endfunction()

# Définition des fichiers sources pour le noyau HIP
set(KERNEL_SOURCES
    gpuA.hpp
)

# Propriétés de compilation séparable à tous les fichiers kernel
set_source_files_properties(${KERNEL_SOURCES}
    PROPERTIES
    HIP_SOURCE_PROPERTY_FORMAT 1
    HIP_SEPARABLE_COMPILATION ON
)

# Bibliothèque statique pour les noyaux HIP
add_library(hip_kernels STATIC ${KERNEL_SOURCES})
configure_hip_target(hip_kernels)

# Ajouter des fichiers sources pour l'application principale
set(MAIN_SOURCES
    main.cpp
    cpuA.hpp
)

add_executable(main ${MAIN_SOURCES} ${KERNEL_SOURCES})

set_source_files_properties(main.cpp PROPERTIES LANGUAGE ${GPU_RUNTIME})
#set_target_properties(main PROPERTIES HIP_ARCHITECTURES "gfx90a" )


