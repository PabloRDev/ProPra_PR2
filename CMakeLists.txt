cmake_minimum_required(VERSION 3.29)
project(UOC20242 C)

set(CMAKE_C_STANDARD 11)

# Headers
include_directories(UOCPlay/include test/include)

# UOCPlay -> library
add_library(UOCPlay STATIC
        UOCPlay/src/api.c
        UOCPlay/src/csv.c
        UOCPlay/src/date.c
        UOCPlay/src/film.c
        UOCPlay/src/person.c
        UOCPlay/src/show.c
        UOCPlay/src/subscription.c
        UOCPlay/src/watchstack.c
)

# Library output dir
set_target_properties(UOCPlay PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
        ARCHIVE_OUTPUT_NAME "UOCPlay"
        DEBUG_POSTFIX "d"  # Add "d" in Debug mode
)

add_executable(UOC20242
        src/main.c
        test/src/test.c
        test/src/test_pr1.c
        test/src/test_pr2.c
        test/src/test_suite.c
)

target_link_libraries(UOC20242 UOCPlay)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")
endif()