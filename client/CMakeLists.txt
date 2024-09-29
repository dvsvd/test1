cmake_minimum_required (VERSION 3.14)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (client "${SOURCE_DIR}/client.cpp" "${INCLUDE_DIR}/client.h"
	"${COMMON_INCLUDE_DIR}/CommonFunctions.h" "${COMMON_SOURCE_DIR}/CommonFunctions.cpp"
	"${COMMON_INCLUDE_DIR}/Logger.h" "${COMMON_SOURCE_DIR}/Logger.cpp"
	"${COMMON_INCLUDE_DIR}/CommonIncludes.h")

target_include_directories(client PRIVATE ${BOOST_INCLUDE_DIR} ${INCLUDE_DIR})
target_link_directories(client PRIVATE ${BOOST_LIB_DIR})

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(client PRIVATE nlohmann_json::nlohmann_json)
