##
# Header
##

########################################################################
# Project setup
########################################################################
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
project(libMATio)
add_library(libMATio INTERFACE)
target_sources(libMATio INTERFACE MATio.hpp)

########################################################################
# Install all files from the local include dir to proper system dir
########################################################################
install (DIRECTORY include/MATio DESTINATION include)

