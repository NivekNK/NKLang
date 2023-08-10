cmake_minimum_required(VERSION 3.24)

project(nklang)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(UNIX AND NOT APPLE)
    set(OPERATIVE_SYSTEM "Linux")
elseif(WIN32)
    set(OPERATIVE_SYSTEM "Win32")
else()
    message(FATAL_ERROR "Unsupported operative system!")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin/${OPERATIVE_SYSTEM}-${CMAKE_BUILD_TYPE})

add_executable(${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME}
PRIVATE
    $<$<CONFIG:Debug>:NK_DEBUG>
    $<$<CONFIG:RelWithDebInfo>:NK_RELEASE_DEBUG_INFO>
    $<$<CONFIG:Release>:NK_RELEASE>
)

if (WIN32)
    add_compile_definitions(NK_PLATFORM_WINDOWS)
elseif (UNIX AND NOT APPLE)
    add_compile_definitions(NK_PLATFORM_LINUX)
endif()

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(vendor/json)

target_precompile_headers(${PROJECT_NAME} PUBLIC include/nkpch.h)

target_sources(${PROJECT_NAME}
PRIVATE
    src/main.cpp
    src/core/lexer.cpp
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
    nlohmann_json::nlohmann_json
)

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/json/include
)
