cmake_minimum_required(VERSION 3.6)

set(PATCH_VERSION 1 CACHE INTERNAL "Patch version. Default = 1")
set(PROJECT_VERSION 0.0.${PATCH_VERSION} CACHE INTERNAL "Application version" FORCE)

project(print-ip VERSION ${PROJECT_VERSION} LANGUAGES CXX)

configure_file(
    version.h.in
    ${CMAKE_BINARY_DIR}/version.h
)

if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT BUILD_TESTING)
    set(BUILD_TESTING ON)
endif()

if (${BUILD_TESTING})
    include(CTest)
    enable_testing()
endif()

add_subdirectory(libs/print_ip)

add_executable(${PROJECT_NAME}
    main.cpp
)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

target_include_directories(${PROJECT_NAME}
PRIVATE
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
  print-ip-lib
)

if (UNIX)
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

    set(CPACK_GENERATOR DEB)
    set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
    set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
    set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "My application")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "My Corporation")
    include(CPack)
endif()

# find_package(Doxygen)

# if (DOXYGEN_FOUND)
#     set(DOXYGEN_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/README.md\ ${CMAKE_CURRENT_SOURCE_DIR}/ )

#     set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs/)

#     set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen.conf.in)
#     set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)

#     configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

#     add_custom_target(docs ALL
#             COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
#             WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#             COMMENT "Generating docs"
#             VERBATIM )
# else (DOXYGEN_FOUND)
#     message("doxygen need to be installed")
# endif(DOXYGEN_FOUND)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen.conf.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf)

    set(DOXYGEN_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/README.md\ ${CMAKE_CURRENT_SOURCE_DIR}/ )

    set(DOXYGEN_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/docs/)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT})


    add_custom_target(doxygen COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        COMMENT "Generating docs"
        VERBATIM
    )
else(DOXYGEN_FOUND)
    message(STATUS "Doxygen not found - reference manual will not be created")
endif(DOXYGEN_FOUND)
