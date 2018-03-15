
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
							libEGL 
							libGLESv2
						)	
						
include_directories(platform/egl/)

install(FILES   ${PATH_TARGET_DIR}/${TARGET_NAME}/${CMAKE_BUILD_TYPE}/bin/libGLESv2.dll
				DESTINATION bin/${TARGET_NAME}
				COMPONENT executables  
				PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)	
				
install(FILES   ${PATH_TARGET_DIR}/${TARGET_NAME}/${CMAKE_BUILD_TYPE}/bin/libEGL.dll
				DESTINATION bin/${TARGET_NAME}
				COMPONENT executables  
				PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)	
