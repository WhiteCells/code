option(USE_TEST1 "Use test1" OFF)

set(SRC test2.cpp)
if(USE_TEST1)
    set(SRC test1.cpp ${SRC})
endif()

add_library(libtest ${SRC})

if(USE_TEST1)
    target_compile_definitions(libtest PUBLIC "USE_TEST1")
endif()