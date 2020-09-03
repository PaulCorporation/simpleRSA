cmake_minimum_required(VERSION 3.10)
find_library(LIBGMP_LIBRARY NAMES gmp libgmp)
if(${LIBGMP_LIBRARY} STREQUAL "LIBGMP_LIBRARY-NOTFOUND")
	message(FATAL_ERROR "Try sudo apt-get install libgmp to install gmp library")
endif()
find_library(LIBGMPXX_LIBRARY NAMES gmpxx libgmpxx)
set (SRCS
	${CMAKE_BINARY_DIR}/../sources/rsa.cpp
	)
set (HEADERS
	${CMAKE_BINARY_DIR}/../sources/rsa.h
	)
add_library(simpleRSA ${SRCS} ${HEADERS})
target_link_libraries(simpleRSA ${LIBGMP_LIBRARY})
target_link_libraries(simpleRSA ${LIBGMPXX_LIBRARY})
find_path(LIBGMP_INCLUDE_LIBRARY NAMES gmpxx.h)
set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
target_include_directories(simpleRSA PUBLIC ${LIBGMP_INCLUDE_LIBRARY})
set_target_properties(simpleRSA
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin/"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin/"
)
