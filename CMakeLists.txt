cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(libevent-demo-cmake VERSION 1.0.0)

# -----------------------------------------
# Windows
# mkdir vs
# cd vs
# cmake .. -DCMAKE_BUILD_TYPE=Debug
# cmake .. -DCMAKE_BUILD_TYPE=Release
# -----------------------------------------

set(CMAKE_BUILD_TYPE Debug)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release
        CACHE STRING "Set build type to Debug o Release (default Release)" FORCE)
endif()

string(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_LOWER)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Limited configurations" FORCE)

message(STATUS "Build Type: " ${CMAKE_BUILD_TYPE})

if(UNIX)
    message(STATUS "Linux Plateform")
else()
    message(STATUS "Windows Plateform")
    set(libevent_INCLUDE_DIRS C:/SDKs/github.com/libevent-2.1.12-stable-bin/include)
    if ("${CMAKE_BUILD_TYPE_LOWER}" STREQUAL "debug")
        set(libevent_LIBRARY_DIRS C:/SDKs/github.com/libevent-2.1.12-stable-bin/lib/Debug)
    else()
        set(libevent_LIBRARY_DIRS C:/SDKs/github.com/libevent-2.1.12-stable-bin/lib/Release)
    endif()
endif()

include_directories(${libevent_INCLUDE_DIRS})
link_directories(${libevent_LIBRARY_DIRS})

if (UNIX)

else()
    set(LIB_PLATFORM ws2_32 shell32 advapi32 Iphlpapi)
endif()

add_executable(main main.cpp)
add_executable(main2 main2.cpp)

target_link_libraries(main event event_core event_extra event_openssl ${LIB_PLATFORM})
target_link_libraries(main2 event event_core event_extra event_openssl ${LIB_PLATFORM})



