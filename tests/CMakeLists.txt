project(tests)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin/${OPERATIVE_SYSTEM}-${CMAKE_BUILD_TYPE}/${PROJECT_NAME})

enable_testing()

add_executable(${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME}
PRIVATE
    $<$<CONFIG:Debug>:NK_DEBUG>
    $<$<CONFIG:RelWithDebInfo>:NK_RELEASE_DEBUG_INFO>
    $<$<CONFIG:Release>:NK_RELEASE>
    NK_TESTING=1
)

if (WIN32)
    add_compile_definitions(NK_PLATFORM_WINDOWS)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
elseif (UNIX AND NOT APPLE)
    add_compile_definitions(NK_PLATFORM_LINUX)
endif()

add_subdirectory(vendor/googletest)

target_sources(${PROJECT_NAME}
PRIVATE
    src/main.cpp
    src/core/lexer.cpp
    ../src/core/lexer.cpp
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
    GTest::gtest_main
)

target_include_directories(${PROJECT_NAME}
PRIVATE
    ../include/
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
