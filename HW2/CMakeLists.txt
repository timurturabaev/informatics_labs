project(HW2)

file(GLOB SOURCES "src/*.cpp")

# Создаём исполняемый файл
add_executable(vector src/vector.cpp)
add_executable(vector_profiler src/vector_profiler.cpp)
add_executable(matrix src/matrix.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE include)