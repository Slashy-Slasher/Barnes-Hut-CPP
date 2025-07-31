# CMakeList.txt : CMake project for Barnes-Hut, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Barnes-Hut "Barnes-Hut.cpp" "Barnes-Hut.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Barnes-Hut PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
