
cmake_minimum_required(VERSION 3.4.1)

add_definitions( -DANDROID_BUILD)

set(CURRENT_SOURCE_DIR "../../..")

include_directories(${CURRENT_SOURCE_DIR}/external/glm)
include_directories(${CURRENT_SOURCE_DIR}/external/assimp)
include_directories(${CURRENT_SOURCE_DIR}/renderer/core)
include_directories(src/main/cpp/)

file(GLOB_RECURSE CPP_FILES
							${CURRENT_SOURCE_DIR}/renderer/core/common/*.cpp
							${CURRENT_SOURCE_DIR}/renderer/core/gl/*.cpp
							${CURRENT_SOURCE_DIR}/renderer/core/model/*.cpp
							${CURRENT_SOURCE_DIR}/renderer/test/*.cpp
							${CURRENT_SOURCE_DIR}/renderer/core/soil/*.c
							src/main/cpp/AndroidHelper.cpp
							src/main/cpp/native-lib.cpp
							)

file(GLOB_RECURSE HPP_FILES
							${CURRENT_SOURCE_DIR}/renderer/core/common/*.h
							${CURRENT_SOURCE_DIR}/renderer/core/gl/*.h
							${CURRENT_SOURCE_DIR}/renderer/core/model/*.h
							${CURRENT_SOURCE_DIR}/renderer/test/*.h
							${CURRENT_SOURCE_DIR}/renderer/core/soil/*.h
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