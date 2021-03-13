project (RenderEngine LANGUAGES C CXX)

set(TARGET_NAME RenderEngine)

list(APPEND CONAN_INSTALL_LIBS signals)

foreach(Lib IN LISTS ${CONAN_INSTALL_LIBS})
    message("Appending '${Lib}' to the path of libs")
    conan_cmake_install(PATH_OR_REFERENCE ${ENGINE_CONAN_DIR}/${Lib}/conanfile.py)
endforeach()

conan_cmake_run(CONANFILE conanfile.txt BUILD MISSING BASIC_SETUP)
set(SHADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}}/Shaders)

set(HEADERS RenderEngine.h
            Utility/Shader.h)
set(SOURCES RenderEngine.cpp
            Utility/Shader.cpp)
set(SHADERS)

add_library(${TARGET_NAME} SHARED ${HEADERS} ${SOURCES} ${SHADERS})
target_link_libraries(${TARGET_NAME} ${CONAN_LIBS})