find_package(EthRPC REQUIRED)


include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/CopyHeaders.cmake)

include_directories(${ETHRPC_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB_RECURSE SOURCES "src/*.cpp")


CopyHeaders()
add_library(bitprofile STATIC ${SOURCES})


install(DIRECTORY ${PROJECT_BINARY_DIR}/include/bitprofile DESTINATION include)
install (TARGETS bitprofile ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin)


