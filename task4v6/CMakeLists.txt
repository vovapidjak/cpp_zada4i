cmake_minimum_required(VERSION 3.10)

# Название проекта
project(GraphMSTApp)

# Стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Убедитесь, что wxWidgets установлен
find_package(wxWidgets REQUIRED COMPONENTS core base)

# Включить библиотеки wxWidgets
include(${wxWidgets_USE_FILE})

# Добавить исходные файлы
set(SOURCES
    main.cpp
    graph.cpp
)

# Добавить заголовочные файлы
set(HEADERS
    graph.h
)

# Создать исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Связать wxWidgets с исполняемым файлом
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
