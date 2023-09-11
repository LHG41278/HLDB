# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/lhg/code_repository/HLDB/thirdparty/iuring"
  "/home/lhg/code_repository/HLDB/build/_deps/iuring-build"
  "/home/lhg/code_repository/HLDB/build/_deps/iuring-subbuild/iuring-populate-prefix"
  "/home/lhg/code_repository/HLDB/build/_deps/iuring-subbuild/iuring-populate-prefix/tmp"
  "/home/lhg/code_repository/HLDB/build/_deps/iuring-subbuild/iuring-populate-prefix/src/iuring-populate-stamp"
  "/home/lhg/code_repository/HLDB/build/_deps/iuring-subbuild/iuring-populate-prefix/src"
  "/home/lhg/code_repository/HLDB/build/_deps/iuring-subbuild/iuring-populate-prefix/src/iuring-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/lhg/code_repository/HLDB/build/_deps/iuring-subbuild/iuring-populate-prefix/src/iuring-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/lhg/code_repository/HLDB/build/_deps/iuring-subbuild/iuring-populate-prefix/src/iuring-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
