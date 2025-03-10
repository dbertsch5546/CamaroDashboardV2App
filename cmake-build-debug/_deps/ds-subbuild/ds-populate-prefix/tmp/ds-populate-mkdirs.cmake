# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/dbertsch/CLionProjects/camarodashboardv2app/cmake-build-debug/_deps/ds-src"
  "/home/dbertsch/CLionProjects/camarodashboardv2app/cmake-build-debug/_deps/ds-build"
  "/home/dbertsch/CLionProjects/camarodashboardv2app/cmake-build-debug/_deps/ds-subbuild/ds-populate-prefix"
  "/home/dbertsch/CLionProjects/camarodashboardv2app/cmake-build-debug/_deps/ds-subbuild/ds-populate-prefix/tmp"
  "/home/dbertsch/CLionProjects/camarodashboardv2app/cmake-build-debug/_deps/ds-subbuild/ds-populate-prefix/src/ds-populate-stamp"
  "/home/dbertsch/CLionProjects/camarodashboardv2app/cmake-build-debug/_deps/ds-subbuild/ds-populate-prefix/src"
  "/home/dbertsch/CLionProjects/camarodashboardv2app/cmake-build-debug/_deps/ds-subbuild/ds-populate-prefix/src/ds-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/dbertsch/CLionProjects/camarodashboardv2app/cmake-build-debug/_deps/ds-subbuild/ds-populate-prefix/src/ds-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/dbertsch/CLionProjects/camarodashboardv2app/cmake-build-debug/_deps/ds-subbuild/ds-populate-prefix/src/ds-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
