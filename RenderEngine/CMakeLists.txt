project (RenderEngine LANGUAGES C CXX)

set(TARGET_NAME Core)

include(${CMAKE_SOURCE_DIR}/Utility.cmake)

list(APPEND CONAN_INSTALL_LIBS signals)

INSTALL_CONAN_LIBS(${CONAN_INSTALL_LIBS})
conan_cmake_run   (CONANFILE conanfile.txt BUILD missing BASIC_SETUP)

find_package(Threads REQUIRED)

set(SHADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}}/Shaders)

set(HEADERS RenderEngine.h
            Window.h
            Game.h
            Painter.h
            Traits/Identifiable.h
            Utility/Brush.h
            Utility/Color.h
            Utility/Singletone.h
            Utility/Shader.h
            Utility/Common.h
            Utility/Rect.h
            )
set(SOURCES RenderEngine.cpp
            Window.cpp
            Game.cpp
            Painter.cpp
            Traits/Identifiable.cpp
            Utility/Brush.cpp
            Utility/Color.cpp
            Utility/Shader.cpp
            Utility/Common.cpp
            Traits/Initable.h
            )
set(SHADERS)

add_library(${TARGET_NAME} SHARED ${HEADERS} ${SOURCES} ${SHADERS})

target_include_directories(${TARGET_NAME} PUBLIC  ${CONAN_INCLUDE_DIRS})
target_link_libraries     (${TARGET_NAME} PRIVATE ${CONAN_LIBS})
target_link_directories   (${TARGET_NAME} PRIVATE ${CONAN_LIB_DIRS})
