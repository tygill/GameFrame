# From:
# https://github.com/quantumelixir/tada/blob/master/cmake/FindCPPUNIT.cmake
#
# Find the CppUnit includes and library
#
# This module defines
# CPPUNIT_INCLUDE_DIR, where to find tiff.h, etc.
# CPPUNIT_LIBRARIES, the libraries to link against to use CppUnit.
# CPPUNIT_FOUND, If false, do not try to use CppUnit.

# also defined, but not for general use are
# CPPUNIT_LIBRARY, where to find the CppUnit library.
# CPPUNIT_DEBUG_LIBRARY, where to find the CppUnit library in debug
# mode.

FIND_PATH(CppUnit_INCLUDE_DIR cppunit/TestCase.h
    /usr/local/include
    /usr/include
)

# With Win32, important to have both
IF(WIN32)
    FIND_LIBRARY(CppUnit_LIBRARY cppunit
        ${CppUnit_INCLUDE_DIR}/../lib
        /usr/local/lib
        /usr/lib)
    FIND_LIBRARY(CppUnit_DEBUG_LIBRARY cppunitd
        ${CppUnit_INCLUDE_DIR}/../lib
        /usr/local/lib
        /usr/lib)
ELSE(WIN32)
# On unix system, debug and release have the same name
    FIND_LIBRARY(CppUnit_LIBRARY cppunit
        ${CppUnit_INCLUDE_DIR}/../lib
        /usr/local/lib
        /usr/lib)
    FIND_LIBRARY(CppUnit_DEBUG_LIBRARY cppunit
        ${CppUnit_INCLUDE_DIR}/../lib
        /usr/local/lib
        /usr/lib)
ENDIF(WIN32)

IF(CppUnit_INCLUDE_DIR)
    IF(CppUnit_LIBRARY)
        SET(CppUnit_FOUND "YES")
        SET(CppUnit_LIBRARIES ${CppUnit_LIBRARY} ${CMAKE_DL_LIBS})
        SET(CppUnit_DEBUG_LIBRARIES ${CppUnit_DEBUG_LIBRARY} ${CMAKE_DL_LIBS})
    ENDIF(CppUnit_LIBRARY)
ENDIF(CppUnit_INCLUDE_DIR)
