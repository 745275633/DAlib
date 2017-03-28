cmake_minimum_required(VERSION 3.5)
project(DA-lubrary)
# 版本号
set (major_version 0)
set (minor_version 1)
set (revision_version 1)
file(STRINGS build-times build_version)
configure_file (
  "${PROJECT_SOURCE_DIR}/version.hpp.in"
  "${PROJECT_SOURCE_DIR}/include/version.hpp"
)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include/DA)
#install(DIRECTORY ${PROJECT_SOURCE_DIR}/lib/ DESTINATION lib)
