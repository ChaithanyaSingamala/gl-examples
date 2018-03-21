
cmake_minimum_required(VERSION 3.4.1)

add_definitions( -DANDROID_BUILD)

add_definitions( -DNO_MAIN_FUNCTION)

set(CURRENT_EXAMPLE "gl-sandbox")
set(CURRENT_SOURCE_DIR "../../..")

include_directories(${CURRENT_SOURCE_DIR}/${CURRENT_EXAMPLE}/src/)
include_directories(${CURRENT_SOURCE_DIR}/core/)
include_directories(${CURRENT_SOURCE_DIR}/platform/android/)
include_directories(${CURRENT_SOURCE_DIR}/external/glm)
include_directories(${CURRENT_SOURCE_DIR}/external/stb)
include_directories(${CURRENT_SOURCE_DIR}/external/assimp)
include_directories(src/main/cpp/)

add_definitions(-DASSIMP_ENABLED)

file(GLOB_RECURSE CPP_FILES
                            src/main/cpp/*.cpp
							${CURRENT_SOURCE_DIR}/${CURRENT_EXAMPLE}/src/*.cpp
							${CURRENT_SOURCE_DIR}/core/*.cpp
							${CURRENT_SOURCE_DIR}/external/stb/*.cpp
							)

# shared lib
set(LIBS_DIR ../../../../src/main/jniLibs)
add_library(assimp SHARED IMPORTED)
set_target_properties(assimp PROPERTIES IMPORTED_LOCATION ${LIBS_DIR}/${ANDROID_ABI}/libassimp.so)



add_library(
             native-lib


             SHARED

             ${CPP_FILES}

             )

find_library(
              log-lib

              log )

target_link_libraries(
                        native-lib
                        GLESv2
                        GLESv3
                        android
                        assimp
                       ${log-lib} )