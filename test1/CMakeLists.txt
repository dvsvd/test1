# CMakeList.txt: проект CMake для test1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.14)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (test1 "${SOURCE_DIR}/test1.cpp" "${INCLUDE_DIR}/test1.h"
	"${SOURCE_DIR}/Functions.cpp" "${INCLUDE_DIR}/Functions.h"
	"${COMMON_INCLUDE_DIR}/CommonFunctions.h" "${COMMON_SOURCE_DIR}/CommonFunctions.cpp"
	"${COMMON_INCLUDE_DIR}/Logger.h" "${COMMON_SOURCE_DIR}/Logger.cpp"
	"${COMMON_INCLUDE_DIR}/CommonIncludes.h"
	"${INCLUDE_DIR}/Storage.h" "${SOURCE_DIR}/Storage.cpp"
	"${INCLUDE_DIR}/ClientHandler.h" "${SOURCE_DIR}/ClientHandler.cpp"
	"${INCLUDE_DIR}/TcpServer.h" "${SOURCE_DIR}/TcpServer.cpp"   "include/JsonValidator.h" "src/JsonValidator.cpp" )
target_include_directories(test1 PRIVATE ${Boost_INCLUDE_DIRS} ${INCLUDE_DIR})

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(test1 PRIVATE nlohmann_json::nlohmann_json)