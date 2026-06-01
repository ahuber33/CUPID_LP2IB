#----------------------------------------------------------------------------
# Setup the project
#----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.16...3.21)
project(SCOPSim)

#----------------------------------------------------------------------------
# Options
#----------------------------------------------------------------------------
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
option(GEANT4_USE_QT ON)
option(BUILD_TESTS "Build unit tests" ON)

#----------------------------------------------------------------------------
# Find Geant4 package
#----------------------------------------------------------------------------
if(WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED gdml ui_all vis_all)
else()
    find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# ROOT
#----------------------------------------------------------------------------
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIRS})

#----------------------------------------------------------------------------
# Include directories
#----------------------------------------------------------------------------
include(${Geant4_USE_FILE})
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${Geant4_INCLUDE_DIR}
    ${ROOT_INCLUDE_DIRS}
)

#----------------------------------------------------------------------------
# Project sources and headers
#----------------------------------------------------------------------------
set(PROJECT_SRC
    src/SCOPSimPhysics.cc
    src/Geometry.cc
    src/SCOPSimEventAction.cc
    src/SCOPSimVisManager.cc
    src/SCOPSimGeometryMessenger.cc
    src/SCOPSimGeometryConstruction.cc
    src/SCOPSimPrimaryGeneratorAction.cc
    src/SCOPSimRunAction.cc
    src/SCOPSimSteppingAction.cc
    src/SCOPSimActionInitialization.cc
    src/SCOPSimMaterials.cc
    src/SCOPSimTrackingAction.cc
)

set(PROJECT_HEADER
    include/SCOPSimPhysics.hh
    include/Geometry.hh
    include/SCOPSimEventAction.hh
    include/SCOPSimVisManager.hh
    include/SCOPSimGeometryMessenger.hh
    include/SCOPSimGeometryConstruction.hh
    include/SCOPSimPrimaryGeneratorAction.hh
    include/SCOPSimRunAction.hh
    include/SCOPSimSteppingAction.hh
    include/SCOPSimActionInitialization.hh
    include/SCOPSimMaterials.hh
    include/SCOPSimTrackingAction.hh
    include/TrackDecayInfo.hh
)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(SCOPSim SCOPSim.cc ${PROJECT_HEADER} ${PROJECT_SRC})
#
target_link_libraries(SCOPSim ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} )

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/bin)
install(TARGETS SCOPSim DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
message("Directory :" ${CMAKE_CURRENT_SOURCE_DIR}/bin)
