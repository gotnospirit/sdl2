cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "sdl2_test")

# Overwrite default configurations RelWithDebInfo-- & MinSizeRel--
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE)

project(${PROJECT_NAME})

if (MSVC)
    # 0x0501 for Windows XP
    # 0x0502 for Windows Server 2003
    # 0x0600 for Windows Vista
    # 0x0601 for Windows 7
    # 0x0602 for Windows 8
    # 0x0603 for Windows 8.1
    #
    # @see http://msdn.microsoft.com/en-us/library/6sehtctf.aspx
    add_definitions(
        -D_WIN32_WINNT=0x0602
        -DNOMINMAX
        -DWIN32_LEAN_AND_MEAN
        -D_CRT_SECURE_NO_WARNINGS
        -DNODEFAULTLIB:msvcrt
    )
else ()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
endif ()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

execute_process(COMMAND
    ${CMAKE_COMMAND} -E remove_directory ${EXECUTABLE_OUTPUT_PATH}
)

if (MSVC)
    set(SDL_LIBRARIES
        "${CMAKE_SOURCE_DIR}/vendor/SDL2-2.0.4/lib/x86/SDL2.lib"
        "${CMAKE_SOURCE_DIR}/vendor/SDL2-2.0.4/lib/x86/SDL2main.lib"
        "${CMAKE_SOURCE_DIR}/vendor/SDL2_image-2.0.0/lib/x86/SDL2_image.lib"
        "${CMAKE_SOURCE_DIR}/vendor/SDL2_ttf-2.0.13/lib/x86/SDL2_ttf.lib"
    )

    set(COPY_DLL
        "vendor/SDL2-2.0.4/lib/x86/SDL2.dll"
        "vendor/SDL2_image-2.0.0/lib/x86/SDL2_image.dll"
        "vendor/SDL2_image-2.0.0/lib/x86/zlib1.dll"
        "vendor/SDL2_image-2.0.0/lib/x86/libpng16-16.dll"
        "vendor/SDL2_ttf-2.0.13/lib/x86/SDL2_ttf.dll"
        "vendor/SDL2_ttf-2.0.13/lib/x86/libfreetype-6.dll"
    )
else ()
    include(FindPkgConfig)

    PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
    PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
    PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})

    set(SDL_LIBRARIES
        ${SDL2_LIBRARIES}
        ${SDL2IMAGE_LIBRARIES}
        ${SDL2TTF_LIBRARIES}
    )
endif ()

set(COPY_ASSETS
    "assets/foo.png"
    "assets/3dchip.png"
    "assets/carpet.normal.mobile.png"
    "assets/frame.big.mobile.png"
    "assets/Montserrat-Regular.ttf"
)

include_directories(
    include
    vendor/SDL2-2.0.4/include
    vendor/SDL2_image-2.0.0/include
    vendor/SDL2_ttf-2.0.13/include
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/utils.cpp
    src/actions.cpp
    src/message_bus.cpp
    src/system.cpp
    src/input_system.cpp
    src/render_system.cpp
    src/display_object.cpp
    src/sprite.cpp
    src/square.cpp
    src/spritesheet.cpp
    src/font.cpp
)

target_link_libraries(${PROJECT_NAME}
    ${SDL_LIBRARIES}
)

foreach(dll ${COPY_DLL})
    get_filename_component(dll_filename ${dll} NAME)

    add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/${dll}" "${EXECUTABLE_OUTPUT_PATH}/$<CONFIGURATION>/${dll_filename}"
    )
endforeach()

foreach(asset ${COPY_ASSETS})
    get_filename_component(asset_filename ${asset} NAME)

    add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/${asset}" "${EXECUTABLE_OUTPUT_PATH}/$<CONFIGURATION>/${asset_filename}"
    )
endforeach()