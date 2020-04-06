
set(MYLIB_ROOT “$ENV{MYLIBDIR}”
	CACHE PATH “_parallel root directory.”)
	
find_path(MYLIB_INCLUDE_DIRS
		  NAMES dynamic.h
          HINTS $ENV{MYLIBDIR}
          PATHS ${MYLIB_ROOT}
          PATH_SUFFIXES include)
		  
find_library(MYLIB_LIB
			 NAMES _parallel
             HINTS $ENV{MYLIBDIR}
             PATHS ${MYLIB_ROOT}
             PATH_SUFFIXES lib
             NO_DEFAULT_PATH)
			 
include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(
                                  MYLIB DEFAULT_MSG
                                  MYLIB_LIB MYLIB_INCLUDE_DIRS)