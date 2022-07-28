#pragma once

#include <iostream>

#ifdef DEBUG
#define ASSERT(condition, message) \
    if (! (condition)) { \
		std::cerr << "***ERROR*** (" << __FILE__ << ": " << __LINE__ << ")\n"; \
        std::cerr << "Assertion `" #condition "` failed! Error message: " << message << std::endl; \
        std::terminate(); \
    }
#else
#define ASSERT(condition, message)
#endif
