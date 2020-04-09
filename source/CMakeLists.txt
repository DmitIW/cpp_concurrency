add_library(thread_utility
        thread_guard.h thread_guard.cpp
        )
target_link_libraries(thread_utility pthread)