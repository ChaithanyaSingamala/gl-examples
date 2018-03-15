cmake_minimum_required(VERSION 3.7.1)

set(NAME "GL-Examples")

SET(TARGET_NAME "vc2015-powervrsdk-win32" CACHE STRING "should be set to correct target") 
set_property(CACHE TARGET_NAME PROPERTY STRINGS "vc2015-powervrsdk-win32;vc2015-powervrsdk-x64;target01;target02")


project(${NAME})

set(PATH_TARGET_DIR "target" CACHE STRING "should be set to correct target path")
set_property(CACHE PATH_TARGET_DIR PROPERTY STRINGS "target;../gles-target")
set(PATH_ENTERNAL_DIR "external")
set(PATH_RESOURCE_DIR "resources")


include(${PATH_TARGET_DIR}/${TARGET_NAME}/toolchain.cmake)


add_subdirectory(gl-hellotriangle)



