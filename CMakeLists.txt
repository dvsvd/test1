cmake_minimum_required (VERSION 3.14)

project ("test1")

message("generator is set to ${CMAKE_GENERATOR}")

add_compile_definitions(_UNICODE)

set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_CXX_STANDARD_REQUIRED 17)
set(CMAKE_CXX_STANDARD 17)

if(NOT DEFINED BOOST_ROOT)
	message (FATAL_ERROR "Could not find BOOST_ROOT. Please add \"-D BOOST_ROOT=/path/to/boost/location\" to cmake call")
endif()

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.79.0 REQUIRED)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
endif()

set(COMMON_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(COMMON_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

include_directories("${PROJECT_SOURCE_DIR}/include")

if(WIN32)
	set (CXX_STANDARD_LIBRARIES kernel32.lib user32.lib gdi32.lib
	winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib
	comdlg32.lib advapi32.lib vcruntime.lib)
	add_compile_definitions(_WIN32_WINNT=0x0A00) # Winddows 10
endif(WIN32)
add_subdirectory ("test1" "test1")
add_subdirectory ("client" "client")