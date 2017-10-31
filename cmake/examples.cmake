
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/examples)

file(GLOB EXAMPLES 
    "examples/*.cpp"
)

include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR}/include ${ETHCRYPTO_INCLUDE_DIRS})

foreach(EXAMPLE ${EXAMPLES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE} NAME_WE)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE})
    target_link_libraries(${EXAMPLE_NAME} 
        bitprofile
        ${ETHRPC_LIBRARY}
        ${JSONCPP_LIBRARY}
        ${Boost_DATE_TIME_LIBRARY}
        ${Boost_CHRONO_LIBRARY}
        ${Boost_REGEX_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_THREAD_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${ETHCRYPTO_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
    )
    if(WIN32)
        target_link_libraries(${EXAMPLE_NAME} ws2_32)
    endif()
    add_dependencies(${EXAMPLE_NAME} bitprofile)
endforeach(EXAMPLE)
