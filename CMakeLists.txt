cmake_minimum_required (VERSION 2.6)
project (wrk)


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

#list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

target_include_directories(wrk PRIVATE src)

target_link_libraries (wrk ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(wrk m)
find_package(OpenSSL REQUIRED)
target_link_libraries(wrk OpenSSL::SSL)

#find_package(Lua53 REQUIRED)
#target_link_libraries(wrk ${LUA53_LIBRARIES})

include_directories(${CMAKE_CURRENT_LIST_DIR}/deps/luajit/src)
target_link_libraries(wrk ${LUA_LIBRARIES})

