
cmake_minimum_required(VERSION 3.4.1)

add_definitions( -DANDROID_BUILD)

set(CURRENT_EXAMPLE "gl-hellotriangle")
set(CURRENT_SOURCE_DIR "../../..")

include_directories(${CURRENT_SOURCE_DIR}/${CURRENT_EXAMPLE}/src/)
include_directories(${CURRENT_SOURCE_DIR}/common/)
include_directories(${CURRENT_SOURCE_DIR}/platform/android/)
include_directories(${CURRENT_SOURCE_DIR}/external/glm)
include_directories(src/main/cpp/)

file(GLOB_RECURSE CPP_FILES
                            src/main/cpp/*.cpp
							${CURRENT_SOURCE_DIR}/${CURRENT_EXAMPLE}/src/*.cpp
							${CURRENT_SOURCE_DIR}/common/*.cpp
							)

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
                       ${log-lib} )