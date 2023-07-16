cmake_minimum_required(VERSION 3.17)
project(m04_textures)



link_libraries(cs4722  glfw3 opengl32 glu32)

set(CMAKE_CXX_STANDARD 20)

include_directories(C:/cs4722fa22lib/include lib64/include)
link_directories(C:/cs4722fa22lib lib64)



add_executable(06-mixed-colors 06-mixed-colors/mixed-colors.cpp)
configure_file(06-mixed-colors/fragment_shader06.glsl .)
configure_file(06-mixed-colors/vertex_shader06.glsl .)
