# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8)
project (AdaptationEngine)

#---- Enable C++14 ---- ////////////////
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Boost 1.54 REQUIRED)
include_directories(${Boost_INCLUDE_DIR} include)
include_directories(
  adaptation
  listener
  model
  include
  include/3rdparty
  include/queries
  include/client   
  include/rapidjson   
  $ENV{ROQME_ROOT}/roqmeDDS/include
  $ENV{ROQME_ROOT}/roqmeDDS/cpp/idl
  $ENV{OSPL_HOME}/include/dcps/C++/isocpp2
  $ENV{OSPL_HOME}/include/sys
  $ENV{OSPL_HOME}/include
  $ENV{OSPL_HOME}/include/dcps/C++/SACPP
)

link_directories($ENV{OSPL_HOME}/lib)
link_directories($ENV{ROQME_ROOT}/roqmeDDS/lib)

#file(GLOB_RECURSE SRC_${PROJECT_NAME} src/*.cpp)

add_executable(${PROJECT_NAME}_engine Adaptation-Engine.cpp)
target_link_libraries(${PROJECT_NAME}_engine -lzmq -pthread -ldcpsgapi -ldcpsgapi -lddsdatabase -lddsos -lddskernel -ldcpsisocpp2 -lroqmedds )

