find_package(EthRPC REQUIRED)
find_package(EthCrypto REQUIRED)
find_package(JsonCPP REQUIRED)
#find_package(Boost REQUIRED)
find_package(Boost COMPONENTS system thread filesystem date_time chrono regex REQUIRED)


set(CMAKE_THREAD_PREFER_PTHREAD ON)
find_package(Threads REQUIRED)
