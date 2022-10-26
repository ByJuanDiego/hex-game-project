cmake_minimum_required(VERSION 3.16.3)
project(CS2013_Project)

set(CMAKE_CXX_STANDARD 17)

include_directories(./include/)
file(GLOB SOURCE_FILES
        main.cpp
        src/*.cpp
        include/*.h
        )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

if (APPLE OR UNIX)

    target_link_libraries(${PROJECT_NAME}  sfml-system sfml-window sfml-graphics sfml-audio)

elseif(WIN32)

    set(SFML_ROOT "C:/SFML/SFML-2.5.1/64bit")
    set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")
    set(SFML_STATIC_LIBRARIES TRUE)

    find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)

    include_directories(C:/SFML/include)
    target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics -static sfml-audio)

endif()
