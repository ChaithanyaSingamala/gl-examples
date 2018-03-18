
message("building for windows x64 with ")
message("	-EGL")

add_definitions(-DENABLE_EGL)


if(WIN32)
    source_group("egl" REGULAR_EXPRESSION "platform/egl/*")
endif(WIN32)

file(GLOB_RECURSE PLATFORM_CPP_FILES 
							platform/egl/*.cpp
							platform/egl/*.h
							)


LINK_LIBRARIES( 
							assimp
							libEGL 
							libGLESv2
						)	
						
include_directories(platform/egl/)
		
INSTALL( DIRECTORY ${PATH_TARGET_DIR}/${TARGET_NAME}/${CMAKE_BUILD_TYPE}/bin/ DESTINATION ../bin/${TARGET_NAME} )	

INSTALL( DIRECTORY ${PATH_RESOURCE_DIR}/ DESTINATION ../ )	


