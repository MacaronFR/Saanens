cmake_minimum_required(VERSION 3.17)
project(Saanens C)

set(CMAKE_C_STANDARD 11)

add_executable(Saanens src/main.c src/interpret.c src/variable.c src/function.c src/operation.c src/regfunc.c src/parse.c src/processop.c src/cast.c src/s_func.c src/condboucle.c)

#find_package(PkgConfig REQUIRED)
#pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories("./includes")

#include_directories(${GTK3_INCLUDE_DIRS})
#link_directories(${GTK3_LIBRARY_DIRS})

#add_definitions(${GTK3_CFLAGS_OTHER})

#target_link_libraries(Saanens ${GTK3_LIBRARIES})
target_link_libraries(Saanens -lregex)
target_link_libraries(Saanens -lreadline)
target_link_libraries(Saanens -lpcre2-8)