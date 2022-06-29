#pragma once

#include <iostream>

#ifdef DEBUG
#   define ASSERT(condition, message) \
    if (! (condition)) { \
        std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                    << " line " << __LINE__ << ": " << message << std::endl; \
        std::terminate(); \
    }
#else
#   define ASSERT(condition, message) 0
#endif