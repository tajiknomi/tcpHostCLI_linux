cmake_minimum_required(VERSION 3.20.5)

project(tcphost)

# Set default architecture if not specified
if(NOT DEFINED TARGET_ARCH)
    set(TARGET_ARCH "x86")
endif()

# Set architecture-specific flags
if(${TARGET_ARCH} STREQUAL "x86")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32")
elseif(${TARGET_ARCH} STREQUAL "x64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m64")
else()
    message(FATAL_ERROR "Unsupported architecture: ${TARGET_ARCH}")
endif()

# Set the build type to Release
set(CMAKE_BUILD_TYPE "Release")

# Set source and header file directories
set(SOURCE_DIR src)
set(HEADER_DIR include)

# Add your source files
set(SOURCES 
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/ClientResponse.cpp
    ${SOURCE_DIR}/ServerQueries.cpp
    ${SOURCE_DIR}/clientManager.cpp
    ${SOURCE_DIR}/tcpNetworkManager.cpp
    ${SOURCE_DIR}/UsageHelper.cpp
    ${SOURCE_DIR}/signalManager.cpp
)

# Optionally, add headers for IDEs or reference
set(HEADERS
    ${HEADER_DIR}/ClientResponse.h
    ${HEADER_DIR}/ServerQueries.h
    ${HEADER_DIR}/clientManager.h
    ${HEADER_DIR}/tcpNetworkManager.h
    ${HEADER_DIR}/UsageHelper.h
    ${HEADER_DIR}/signalManager.h
    
)

# Create the executable (using only source files)
add_executable(tcphost ${SOURCES})

# Set the C++17 standard
target_compile_features(tcphost PRIVATE cxx_std_17)

# Include the header directory
target_include_directories(tcphost PRIVATE ${HEADER_DIR})

# Link the pthread library
target_link_libraries(tcphost PRIVATE pthread)

# Set linker flags to disable symbol generation
set_target_properties(tcphost PROPERTIES LINK_FLAGS_RELEASE "-s")