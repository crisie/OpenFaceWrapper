cmake_minimum_required(VERSION 3.9)

project(OpenFaceWrapper VERSION 0.5 DESCRIPTION "OpenFace wrapper")

add_library(OpenFaceWrapper SHARED
	OpenFaceDLL.cpp
	OpenFaceWrapper.cpp
	Utils.cpp)

#set_target_properties(OpenFaceWrapper PROPERTIES PUBLIC_HEADER OpenFaceDLL.h)

# CHANGE TO OPENFACE DIRECTORY
#set(CMAKE_OPENFACE_PATH ${CMAKE_OPENFACE_PATH} "C:/Users/Crisi/Documents/OpenFace/OpenFaceRoger")
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/build/")
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_OPENFACE_PATH}/cmake/modules/")

#set(CMAKE_CONFIG_DIR etc/OpenFaceWrapper)
#set(CONFIG_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_CONFIG_DIR}")
#add_definitions(-DCONFIG_DIR="${CONFIG_DIR}")

#set(OpenCV_DIR "D:/opencv/build") # NOTE: change in case opencv is already in path
#MESSAGE(" Opencv dir: ${OpenCV_DIR}")# NOTE: change in case opencv is already in path
find_package( OpenCV REQUIRED COMPONENTS core imgproc calib3d highgui objdetect)
if(${OpenCV_FOUND})
	MESSAGE("OpenCV information:") 
	MESSAGE("  OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}") 
	MESSAGE("  OpenCV_LIBRARIES: ${OpenCV_LIBRARIES}") 
	MESSAGE("  OpenCV_LIBRARY_DIRS: ${OpenCV_LINK_DIRECTORIES}") 
else()
    MESSAGE(FATAL_ERROR "OpenCV not found in the system.")
		MESSAGE("OpenCV information:") 
	MESSAGE("  OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}") 
	MESSAGE("  OpenCV_LIBRARIES: ${OpenCV_LIBRARIES}") 
	MESSAGE("  OpenCV_LIBRARY_DIRS: ${OpenCV_LINK_DIRECTORIES}") 
endif()

# make sure we'll use OpenBLAS only: there's a header file naming difference between different
# implementations; so OpenFace wants OpenBLAS;
find_package(OpenBLAS REQUIRED)
if ( ${OpenBLAS_FOUND} )
    MESSAGE("OpenBLAS information:")
    MESSAGE("  OpenBLAS_LIBRARIES: ${OpenBLAS_LIB}")
else()
    MESSAGE(FATAL_ERROR "OpenBLAS not found in the system.")
endif()

if ( ${OpenBLAS_INCLUDE_FOUND} )
    MESSAGE("  OpenBLAS_INCLUDE: ${OpenBLAS_INCLUDE_DIR}")
else()
    MESSAGE(WARNING "OpenBLAS include not found in the system. Using the one vended with OpenFace.")
    MESSAGE("  OpenBLAS_INCLUDE: ${OpenBLAS_INCLUDE_DIR}")
endif()

find_package( Boost 1.5.9 REQUIRED COMPONENTS filesystem system)
if(${Boost_FOUND})
	MESSAGE("Boost information:") 
	MESSAGE("  Boost_VERSION: ${Boost_VERSION}")
	MESSAGE("  Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}") 
	MESSAGE("  Boost_LIBRARIES: ${Boost_LIBRARIES}") 
	MESSAGE("  Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}") 
else()
    MESSAGE(FATAL_ERROR "Boost not found in the system.")
endif()
