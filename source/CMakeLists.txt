add_library(thread_utility
        thread_guard.h thread_guard.cpp
        functions.h    functions.cpp
        profile.h
        )
target_link_libraries(thread_utility pthread)