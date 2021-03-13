project (RenderEngine LANGUAGES C CXX)
set(TARGET_NAME RenderEngine)

include(${CMAKE_SOURCE_DIR}/Utility.cmake)


list(APPEND CONAN_INSTALL_LIBS signals)

INSTALL_CONAN_LIBS(${CONAN_INSTALL_LIBS})
conan_cmake_run(CONANFILE ${CMAKE_CURRENT_SOURCE_DIR}/conanfile.txt
                 BUILD missing BASIC_SETUP CMAKE_TARGETS)

set(SHADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}}/Shaders)

set(HEADERS RenderEngine.h
            Utility/Shader.h)
set(SOURCES RenderEngine.cpp
            Utility/Shader.cpp)
set(SHADERS)

add_library(${TARGET_NAME} SHARED ${HEADERS} ${SOURCES} ${SHADERS})

target_link_libraries(${TARGET_NAME} PRIVATE ${CONAN_LIBS})
