#----------------------------------------------------------------------------
# Setup the project
#----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.16...3.21)
project(SimOp)

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
    src/SimOpPhysics.cc
    src/Geometry.cc
    src/SimOpEventAction.cc
    src/SimOpVisManager.cc
    src/SimOpGeometryMessenger.cc
    src/SimOpGeometryConstruction.cc
    src/SimOpPrimaryGeneratorAction.cc
    src/SimOpRunAction.cc
    src/SimOpSteppingAction.cc
    src/SimOpActionInitialization.cc
    src/SimOpMaterials.cc
)

set(PROJECT_HEADER
    include/SimOpPhysics.hh
    include/Geometry.hh
    include/SimOpEventAction.hh
    include/SimOpVisManager.hh
    include/SimOpGeometryMessenger.hh
    include/SimOpGeometryConstruction.hh
    include/SimOpPrimaryGeneratorAction.hh
    include/SimOpRunAction.hh
    include/SimOpSteppingAction.hh
    include/SimOpActionInitialization.hh
    include/SimOpMaterials.hh
)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(SimOp SimOp.cc ${PROJECT_HEADER} ${PROJECT_SRC})
#
target_link_libraries(SimOp ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} )

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/bin)
install(TARGETS SimOp DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
message("Directory :" ${CMAKE_CURRENT_SOURCE_DIR}/bin)