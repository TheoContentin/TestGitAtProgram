cmake_minimum_required(VERSION 2.6)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}/CMake" p)
list(APPEND CMAKE_MODULE_PATH "${p}") #For old Imagine++
list(APPEND CMAKE_SYSTEM_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?
find_package(Imagine REQUIRED)

project(FastMarching)

add_executable(test_priorite
               pointDist.h
               priorite.h priorite.cpp
               test_priorite.cpp)

add_executable(distancePoint
               distancePoint.cpp
               fastMarching.h fastMarching.cpp
               pointDist.h
               priorite.h priorite.cpp)
ImagineUseModules(distancePoint Images)

add_executable(geodesique
               geodesique.cpp
               fastMarching.h fastMarching.cpp
               pointDist.h
               priorite.h priorite.cpp)
ImagineUseModules(geodesique Images)

add_executable(ombres
               ombres.cpp
               fastMarching.h fastMarching.cpp
               pointDist.h
               priorite.h priorite.cpp)
ImagineUseModules(ombres Images)
