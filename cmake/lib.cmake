find_package(EthRPC REQUIRED)
find_package(JsonCPP REQUIRED)
find_package(CryptoPP REQUIRED)
find_package(Boost REQUIRED)

add_definitions(-D__ABI_ENABLED__)
add_definitions(-DBOOST_PP_VARIADICS)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/CopyHeaders.cmake)

include_directories(${Boost_INCLUDE_DIRS} ${JSONCPP_INCLUDE_DIR} ${CRYPTOPP_INCLUDE_DIR} ${ETHRPC_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB_RECURSE SOURCES "src/*.cpp")


CopyHeaders()
add_library(bitprofile STATIC ${SOURCES})


install(DIRECTORY ${PROJECT_BINARY_DIR}/include/bitprofile DESTINATION include)
install (TARGETS bitprofile ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin)


