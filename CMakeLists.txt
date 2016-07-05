cmake_minimum_required (VERSION 2.6)

# If the user specifies -DCMAKE_BUILD_TYPE on the command line, take their definition
# and dump it in the cache along with proper documentation, otherwise set CMAKE_BUILD_TYPE
# to Release prior to calling PROJECT()
#
IF(DEFINED CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
ELSE()
   SET(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
ENDIF()

project (msi-gt72s-keyboard CXX)

# Add custom search modules.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#####################################################################
#           C++11 support
#####################################################################

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
if(COMPILER_SUPPORTS_CXX14)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
else()
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
endif()

#####################################################################
#           Compiler-specific flags
#####################################################################

# Warnings for gcc.
if(CMAKE_COMPILER_IS_GNUCXX)
	SET(WARNINGS "${WARNINGS} -Wextra -Wall -Wconversion -pedantic -Wmain -Weffc++ -Wswitch-default -Wswitch-enum -Wmissing-include-dirs -Wmissing-declarations -Wfloat-equal -Wundef -Wcast-align -Wredundant-decls -Winit-self -Wshadow")
endif(CMAKE_COMPILER_IS_GNUCXX)

#####################################################################
#           			Required libs
#####################################################################

find_package(HIDAPI REQUIRED)
include_directories(SYSTEM ${HIDAPI_INCLUDE_DIRS})

#####################################################################
#           			Source files
#####################################################################

FILE( GLOB SRCS
	src/*.cpp
)

#####################################################################
#           The main executable
#####################################################################

add_executable(msi_GT72S_keyboard ${SRCS})
TARGET_LINK_LIBRARIES(msi_GT72S_keyboard ${HIDAPI_LIBRARIES})

#####################################################################
#           Installation.
#####################################################################

set(INSTALL_BIN_DIR "/usr/bin" CACHE PATH "Installation directory for executables.")
set(INSTALL_UDEV_DIR "/etc/udev/rules.d" CACHE PATH "Installation directory for the udev rule.")
option(INSTALL_UDEV_RULE "Specifies whether to install the udev rule that allows running this without root access." ON)

# installation
install(TARGETS msi_GT72S_keyboard
  EXPORT MsiTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
)

if(INSTALL_UDEV_RULE)
	install(FILES
	  "${PROJECT_SOURCE_DIR}/99-msi-gt72s.rules"
	  DESTINATION "${INSTALL_UDEV_DIR}"
	)
endif()
