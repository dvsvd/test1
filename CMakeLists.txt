cmake_minimum_required (VERSION 3.14)

project ("test1")

message("generator is set to ${CMAKE_GENERATOR}")

add_compile_definitions(_UNICODE)

set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_CXX_STANDARD_REQUIRED 17)
set(CMAKE_CXX_STANDARD 17)

set (BOOST_ROOT "C:/boost_1_79_0")
set (BOOST_INCLUDE_DIR "C:/boost_1_79_0")
set (BOOST_LIB_DIR "${BOOST_ROOT}/libs")

set(COMMON_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(COMMON_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

include_directories("${PROJECT_SOURCE_DIR}/include")

#set(CXX_LIB_DIR_ROOT "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.29.30133/lib")
#if(${CMAKE_SYSTEM_PROCESSOR} MATCHES ".*64.*")
#	set(CXX_LIB_DIR "${CXX_LIB_DIR_ROOT}/x64")
#	set(RUNTIME_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/x64")
#else()
#	set(CXX_LIB_DIR "${CXX_LIB_DIR_ROOT}/x86")
#	set(RUNTIME_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/x86")
#endif()

if(WIN32)
	set (CXX_STANDARD_LIBRARIES kernel32.lib user32.lib gdi32.lib
	winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib
	comdlg32.lib advapi32.lib vcruntime.lib)
	add_compile_definitions(_WIN32_WINNT=0x0A00) # Winddows 10
endif(WIN32)
add_subdirectory ("test1" "test1")
add_subdirectory ("client" "client")