cmake_minimum_required(VERSION 3.14)
project(FeedbackAnalyzer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/utf-8)
endif()

add_executable(feedback_analyzer
    src/cpp/main.cpp
    src/cpp/Constants.cpp
    src/cpp/Filters.cpp
    src/cpp/Logger.cpp
    src/cpp/Session.cpp
    src/cpp/TextAnalyzer.cpp
    src/cpp/UIComponents.cpp
)

target_include_directories(feedback_analyzer PRIVATE src/cpp)

# Windows: httplib mmap uses CreateFile2 / CreateFileMappingFromApp (Win8+).
# MinGW defaults to older WINVER unless raised here.
if(WIN32)
    target_compile_definitions(feedback_analyzer PRIVATE
        _WIN32_WINNT=0x0A00
        WINVER=0x0A00
    )
    target_link_libraries(feedback_analyzer PRIVATE ws2_32)
endif()

include(CTest)

if(BUILD_TESTING)
    include(FetchContent)

    find_package(GTest QUIET)

    if(NOT GTest_FOUND)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
            DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        )
        FetchContent_MakeAvailable(googletest)
    endif()

    set(APPROVAL_TESTS_BUILD_TESTING OFF CACHE BOOL "" FORCE)
    set(APPROVAL_TESTS_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(
        ApprovalTests
        GIT_REPOSITORY https://github.com/approvals/ApprovalTests.cpp.git
        GIT_TAG master
    )
    FetchContent_MakeAvailable(ApprovalTests)

    add_executable(sentiment_tests
        tests/sentiment_tests.cpp
        tests/golden_master_tests.cpp
        src/cpp/Constants.cpp
        src/cpp/TextAnalyzer.cpp
    )

    target_include_directories(sentiment_tests PRIVATE src/cpp)
    target_compile_definitions(sentiment_tests PRIVATE
        GOLDEN_MASTER_EXPECTED_PATH="${CMAKE_CURRENT_SOURCE_DIR}/tests/golden_master_expected.txt"
    )
    target_link_libraries(sentiment_tests PRIVATE GTest::gtest_main ApprovalTests::ApprovalTests)

    include(GoogleTest)
    gtest_discover_tests(sentiment_tests)
endif()
