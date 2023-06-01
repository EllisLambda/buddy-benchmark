# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/sym/buddy-benchmark/build/vendor/benchmark/src/project_googlebenchmark"
  "/home/sym/buddy-benchmark/build/vendor/benchmark/src/project_googlebenchmark-build"
  "/home/sym/buddy-benchmark/build/vendor/benchmark"
  "/home/sym/buddy-benchmark/build/vendor/benchmark/tmp"
  "/home/sym/buddy-benchmark/build/vendor/benchmark/src/project_googlebenchmark-stamp"
  "/home/sym/buddy-benchmark/build/vendor/benchmark/src"
  "/home/sym/buddy-benchmark/build/vendor/benchmark/src/project_googlebenchmark-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/sym/buddy-benchmark/build/vendor/benchmark/src/project_googlebenchmark-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/sym/buddy-benchmark/build/vendor/benchmark/src/project_googlebenchmark-stamp${cfgdir}") # cfgdir has leading slash
endif()
