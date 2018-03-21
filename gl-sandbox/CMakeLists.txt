cmake_minimum_required(VERSION 3.7.1)

SET(CMAKE_INSTALL_PREFIX "install" CACHE PATH "install prefix" FORCE) 


set(NAME "GL-Sandbox")

project(${NAME})

include_directories(../${PATH_ENTERNAL_DIR}/glm)
include_directories(../${PATH_ENTERNAL_DIR}/assimp)
include_directories(../${PATH_ENTERNAL_DIR}/stb)
include_directories(src/)
include_directories(../core/)
include_directories(../${PATH_TARGET_DIR}/${TARGET_NAME}/usr/include) 

link_directories(../${PATH_TARGET_DIR}/${TARGET_NAME}/usr/lib)
link_directories(../${PATH_TARGET_DIR}/${TARGET_NAME}/usr/lib/${CMAKE_BUILD_TYPE})


if(WIN32)
    source_group("src" REGULAR_EXPRESSION "src/*")
    source_group("core" REGULAR_EXPRESSION "../core/*")
    source_group("platform" REGULAR_EXPRESSION "../platform/*")
    source_group("resources" REGULAR_EXPRESSION "../resources/*")
	source_group("glm" REGULAR_EXPRESSION "../${PATH_ENTERNAL_DIR}/glm/glm/*")
	source_group("stb" REGULAR_EXPRESSION "../${PATH_ENTERNAL_DIR}/stb/*")
endif(WIN32)

file(GLOB_RECURSE CPP_FILES 
							src/*.cpp
							../core/*.cpp
							../${PATH_ENTERNAL_DIR}/stb/*.cpp
							)
							
file(GLOB_RECURSE HPP_FILES 
							src/*.h
							../core/*.h
							../${PATH_ENTERNAL_DIR}/glm/glm/*.hpp
							../${PATH_ENTERNAL_DIR}/glm/glm/*.inl
							../resources/res/shaders/*
							../${PATH_ENTERNAL_DIR}/stb/*.h
							)
						
							
add_executable(${NAME} ${CPP_FILES} ${HPP_FILES} ${PLATFORM_CPP_FILES})




# Define project properties
set_property(TARGET ${NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY 					../bin/${TARGET_NAME})
set_property(TARGET ${NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY_DEBUG 			../bin/${TARGET_NAME})
set_property(TARGET ${NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELEASE 			../bin/${TARGET_NAME})
set_property(TARGET ${NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL 		../bin/${TARGET_NAME})
set_property(TARGET ${NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO 	../bin/${TARGET_NAME})

# Define C++ version to be used for building the project
set_property(TARGET ${NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

# Define C version to be used for building the project
set_property(TARGET ${NAME} PROPERTY C_STANDARD 99)
set_property(TARGET ${NAME} PROPERTY C_STANDARD_REQUIRED ON)

