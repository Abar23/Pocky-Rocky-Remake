#pragma once

#include <string>
#include <cstdint>
#include "glad/glad.h"

#ifdef DEBUG
#define glCall(func, ...) \
	func(__VA_ARGS__); \
	checkOpenGlError(__FILE__, __LINE__);
#else
#define glCall(func, ...) func(__VA_ARGS__);
#endif

bool checkOpenGlError(const std::string & filename, const std::uint32_t line);

void APIENTRY glDebugOutput(GLenum source,
    GLenum type,
    unsigned int id,
    GLenum severity,
    GLsizei length,
    const char* message,
    const void* userParam);