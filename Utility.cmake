function (ENABLE_CONAN)
    find_program(conan conan)
    if(NOT EXISTS ${conan})
    if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
        message(FATAL_ERROR "Conan is required.\
                            Please run this command to install and setup conan:
                            py -3 ${CMAKE_SOURCE_DIR}\tools\cmake_builder\tools\install_conan.py")
    else()
        message(FATAL_ERROR "Conan is required.\
                             Please run this command to install and setup conan:
                             python3 ${CMAKE_SOURCE_DIR}/tools/cmake_builder/tools/install_conan.py")
        endif()
        return()
    else()
        message("Conan found at ${conan}")
    endif()
endfunction()

set(ENGINE_CONAN_DIR ${CMAKE_SOURCE_DIR}/conan)

function (INSTALL_CONAN_LIBS LIBS)
    ENABLE_CONAN()
    foreach(LIB IN LISTS LIBS)
        message("Installing '${LIB}' library")
        execute_process(COMMAND ${conan} create ${ENGINE_CONAN_DIR}/${LIB}/conanfile.py
                    RESULT_VARIABLE install_result)
        message("Install result: ${install_result}")
    endforeach()
endfunction()