cmake_minimum_required(VERSION 2.6)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}/CMake" p)
list(APPEND CMAKE_MODULE_PATH "${p}") #For old Imagine++
list(APPEND CMAKE_SYSTEM_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?
find_package(Imagine REQUIRED)

project(MehrioKurt)
set(CMAKE_CXX_STANDARD 11)

add_executable(MehrioKurt test.cpp main.cpp asset.cpp asset.h map.cpp map.h physics.cpp physics.h kart.cpp kart.h mesh_3D.cpp mesh_3D.h)
ImagineUseModules(MehrioKurt Graphics)
ImagineUseModules(MehrioKurt Images)
