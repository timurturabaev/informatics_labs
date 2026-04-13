project(HW1)

file(GLOB SOURCES "src/*.cpp")

# Создаём исполняемый файл
add_executable(HW1_1 src/HW1_1.cpp)
add_executable(HW1_2 src/HW1_2.cpp)
add_executable(HW1_3 src/HW1_3.cpp)
add_executable(HW1_4 src/HW1_4.cpp)
add_executable(HW1_5 src/HW1_5.cpp)
add_executable(HW1_6 src/HW1_6.cpp)
add_executable(HW1_7 src/HW1_7.cpp)
add_executable(HW1_8 src/HW1_8.cpp)
add_executable(vector src/vector.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE include)