cmake_minimum_required(VERSION 3.21)
project(CS2013_Project)

set(CMAKE_CXX_STANDARD 17)

include_directories(./include/)
file(GLOB SOURCE_FILES
        main.cpp
        src/*.cpp
        include/*.h
        include/Menu.h
        src/Menu.cpp
        )

add_executable(${PROJECT_NAME} ${SOURCE_FILES} include/hexagon.h src/hexagon.cpp include/HexagonFactory.h include/Render.h src/Word.cpp include/Word.h src/figure.cpp include/figure.h src/rectangle.cpp include/rectangle.h src/Options.cpp include/Options.h include/RectangleFactory.h)

if (APPLE OR UNIX)

    find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)

    if(SFML_FOUND)
        message("SFML FOUND")
        include_directories(${SFML_INCLUDE_DIR})
        target_link_libraries(${PROJECT_NAME}  sfml-system sfml-window sfml-graphics sfml-audio)
    endif()

elseif(WIN32)

    set(SFML_STATIC_LIBRARIES TRUE)
    set(SFML_DIR C:/SFML/lib/cmake/SFML)

    find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)

    include_directories(C:/SFML/include)
    target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics -static sfml-audio)

endif()
