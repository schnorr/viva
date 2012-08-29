#
# Find the PAJENG library
#

# PAJENG_INCLUDE_PATH  - Directories to include to use PAJENG
# PAJENG_LIBRARY_PATH    - Files to link against to use PAJENG
# PAJENG_FOUND        - When false, don't try to use PAJENG
#
# PAJENG_PATH can be used to make it simpler to find the various include
# directories and compiled libraries when PAJENG was not installed in the
# usual/well-known directories (e.g. because you made an in tree-source
# compilation or because you installed it in an "unusual" directory).
# Just set PAJENG_PATH it to your specific installation directory
#
FIND_LIBRARY(PAJENG_LIBRARY
  NAMES paje
  PATHS /usr/lib /usr/local/lib ${PAJENG_PATH}/lib)

IF(PAJENG_LIBRARY)
  MESSAGE ( STATUS "Found PAJENG library: ${PAJENG_LIBRARY}" )
  GET_FILENAME_COMPONENT(PAJENG_LIBRARY_tmp "${PAJENG_LIBRARY}" PATH)
  SET (PAJENG_LIBRARY_PATH ${PAJENG_LIBRARY_tmp} CACHE PATH "")
ENDIF(PAJENG_LIBRARY)

FIND_PATH( PAJENG_INCLUDE_tmp PajeSimulator.h
  PATHS
  ${PAJENG_GUESSED_INCLUDE_PATH}
  ${PAJENG_PATH}/include/
  /usr/include/
  /usr/local/include/
)

IF(PAJENG_INCLUDE_tmp)
  SET (PAJENG_INCLUDE_PATH "${PAJENG_INCLUDE_tmp}" CACHE PATH "")
ENDIF(PAJENG_INCLUDE_tmp)

IF( PAJENG_INCLUDE_PATH )
  IF( PAJENG_LIBRARY_PATH )
    SET( PAJENG_FOUND TRUE )
  ENDIF ( PAJENG_LIBRARY_PATH )
ENDIF( PAJENG_INCLUDE_PATH )

IF( NOT PAJENG_FOUND )
  MESSAGE(STATUS "PAJENG installation was not found. Please provide PAJENG_PATH:")
  MESSAGE(STATUS "  - through the GUI when working with ccmake, ")
  MESSAGE(STATUS "  - as a command line argument when working with cmake e.g.")
  MESSAGE(STATUS "    cmake .. -DPAJENG_PATH:PATH=/usr/local/pajeng/ ")
  SET(PAJENG_PATH "" CACHE PATH "Root of PAJENG install tree." )
ENDIF( NOT PAJENG_FOUND )

