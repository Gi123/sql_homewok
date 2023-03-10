cmake_minimum_required(VERSION 3.5)
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(join_server VERSION ${PROJECT_VESRION})

find_package(Threads)
find_package(Boost COMPONENTS system)

message(${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB server_db_file_cpp
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
add_executable(join_server ${server_db_file_cpp})
target_include_directories(join_server
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${Boost_INCLUDE_DIR} 
)

set_target_properties(join_server PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

target_link_libraries(join_server
        ${CMAKE_THREAD_LIBS_INIT}
        dl
        ${Boost_LIBRARIES}
        )

install(TARGETS join_server RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

include(CPack)
