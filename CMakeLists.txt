cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

set(FLAPPY_SOURCE main.c game.c sdlutils.c background.c bird.c walls.c startscreen.c readyscreen.c endgamescreen.c)
if (UNIX)
  set(ADDITIONAL_LIBRARIES m)
else (UNIX)
  set(ADDITIONAL_LIBRARIES )
endif (UNIX)

#include SDL
find_package(SDL REQUIRED)
if(NOT SDL_FOUND)
	message(SEND_ERROR "Failed to find SDL")
	return()
else()
	include_directories(${SDL_INCLUDE_DIR})
endif()

#include SDL_image
find_package(SDL_image REQUIRED)
if(NOT SDLIMAGE_FOUND)
	message(SEND_ERROR "Failed to find SDL_image")
	return()
else()
	include_directories(${SDLIMAGE_INCLUDE_DIR})
endif()

#include SDL_gfx
find_package(SDL_gfx REQUIRED)
if(NOT SDLGFX_FOUND)
	message(SEND_ERROR "Failed to find SDL_gfx")
	return()
else()
	include_directories(${SDLGFX_INCLUDE_DIR})
endif()

#create flappy executable
add_executable(cflappy ${FLAPPY_SOURCE})
target_link_libraries(cflappy
                              ${SDL_LIBRARY}
                              ${SDLIMAGE_LIBRARY}
                              ${SDLGFX_LIBRARY}
                              ${ADDITIONAL_LIBRARIES})

#copy image files
add_custom_command(TARGET cflappy POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${PROJECT_SOURCE_DIR}/images"
		$<TARGET_FILE_DIR:cflappy>/images)
