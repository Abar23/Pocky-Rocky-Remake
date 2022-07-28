#include <iostream>
#include "GlErrorCheck.h"

bool checkOpenGlError(const std::string& filename, const std::uint32_t line)
{
	GLenum glErrorCode = glGetError();
	if (glErrorCode != GL_NO_ERROR)
	{
		std::cerr << "\n***ERROR*** (" << filename << ": " << line << ")\n";
		switch (glErrorCode)
		{
			case GL_INVALID_ENUM:
				std::cerr << "GL_INVALID_ENUM: an unacceptable value has been passed for an enumerated argument in an OpenGL function";
				break;

			case GL_INVALID_VALUE:
				std::cerr << "GL_INVALID_VALUE: an out of range numeric argument was passed to an OpenGL function";
				break;

			case GL_INVALID_OPERATION:
				std::cerr << "GL_INVALID_OPERATION: an OpenGL function that is not allowed in the current OpenGL state was called";
				break;

			case GL_INVALID_FRAMEBUFFER_OPERATION:
				std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION: an OpenGL framer buffer object is not complete";
				break;

			case GL_OUT_OF_MEMORY:
				std::cerr << "GL_OUT_OF_MEMORY: not enough memory is left to complete the called OpenGL function";
				break;

			case GL_STACK_UNDERFLOW:
				std::cerr << "GL_STACK_UNDERFLOW: an OpenGL pop operation was called at the bottom of the OpenGL stack";
				break;

			case GL_STACK_OVERFLOW:
				std::cerr << "GL_STACK_OVERFLOW: an OpenGL push operation has exceeded the maximum size of the OpenGl stack";
				break;
		}
		std::cerr << std::endl;
		return false;
	}
	return true;
}

void glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam)
{
	if (id == 131185 || id == 131218) return;

	std::cout << "\n***DEBUG*** ( ID: " << id << "): " << message << std::endl;
	
	std::cout << "Source: ";
	switch (source)
	{
		case GL_DEBUG_SOURCE_API:
			std::cout << "OpenGL API" << std::endl;
			break;

		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			std::cout << "Windowing System API" << std::endl;
			break;

		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			std::cout << "Shader Compiler" << std::endl;
			break;

		case GL_DEBUG_SOURCE_THIRD_PARTY:
			std::cout << "Third Party Application associated with OpenGL" << std::endl;
			break;

		case GL_DEBUG_SOURCE_APPLICATION:
			std::cout << "User of this Application" << std::endl;
			break;

		case GL_DEBUG_SOURCE_OTHER:
			std::cout << "Other" << std::endl;
			break;
	}

	std::cout << "Type: ";
	switch (type)
	{
		case GL_DEBUG_TYPE_ERROR:
			std::cout << "API Error" << std::endl;
			break;

		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			std::cout << "Deprecated Behavior Used" << std::endl;
			break;

		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			std::cout << "Undefined Behavior" << std::endl;
			break;

		case GL_DEBUG_TYPE_PORTABILITY:
			std::cout << "Non-Portable Functionality Used" << std::endl;
			break;

		case GL_DEBUG_TYPE_PERFORMANCE:
			std::cout << "Code Performance Issue" << std::endl;
			break;

		case GL_DEBUG_TYPE_MARKER:
			std::cout << "Marker" << std::endl;
			break;

		case GL_DEBUG_TYPE_PUSH_GROUP:
			std::cout << "Group Pushing" << std::endl;
			break;

		case GL_DEBUG_TYPE_POP_GROUP:
			std::cout << "Group Popping" << std::endl;
			break;

		case GL_DEBUG_TYPE_OTHER:
			std::cout << "Other" << std::endl;
			break;
	}

	std::cout << "Severity: ";
	switch (severity)
	{
		case GL_DEBUG_SEVERITY_HIGH:
			std::cout << "High" << std::endl;
			break;

		case GL_DEBUG_SEVERITY_MEDIUM:
			std::cout << "Medium" << std::endl;
			break;

		case GL_DEBUG_SEVERITY_LOW:
			std::cout << "Low" << std::endl;
			break;

		case GL_DEBUG_SEVERITY_NOTIFICATION:
			std::cout << "Notification" << std::endl;
			break;
	}

	std::cout << std::endl;
}
