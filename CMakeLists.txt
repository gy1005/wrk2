cmake_minimum_required (VERSION 2.6)
project (wrk)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")


if (UNIX)
    set(
        SOURCES
        src/ae.cc
        src/ae_epoll.cc
        src/aprintf.cc
        src/hdr_histogram.cc
        src/http_parser.cc
        src/net.cc
        src/script.cc
        src/ssl.cc
        src/stats.cc
        src/tinymt64.cc
        src/units.cc
        src/wrk.cc
        src/zmalloc.cc
    )
endif(UNIX)

add_executable(
    wrk
    ${SOURCES}
)

target_include_directories(wrk PRIVATE src)

target_link_libraries (wrk ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(wrk m)
find_package(OpenSSL REQUIRED)
target_link_libraries(wrk OpenSSL::SSL)

find_package(Lua51 REQUIRED)
include_directories(/usr/local/include ${LUA_INCLUDE_DIR})
target_link_libraries(wrk ${LUA_LIBRARIES})

find_package(OpenTracing)
target_link_libraries(wrk OpenTracing::opentracing)

