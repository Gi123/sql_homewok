cmake_minimum_required(VERSION 3.5)
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(server_db VERSION ${PROJECT_VESRION})

find_package(Threads)
find_package(Boost COMPONENTS system)

message(${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB server_db_file_cpp
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
add_executable(server_db ${server_db_file_cpp})
target_include_directories(server_db
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${Boost_INCLUDE_DIR} 
)

set_target_properties(server_db PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

target_link_libraries(server_db
        ${CMAKE_THREAD_LIBS_INIT}
        dl
        ${Boost_LIBRARIES}
        )

install(TARGETS server_db RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

include(CPack)
