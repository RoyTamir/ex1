project(Ex1)
set(C_STANDARD C99)
add_compile_options(-Wall -Wextra -pedantic -Werror)

add_library(matrix SHARED Matrix.c ErrorCode.c )
