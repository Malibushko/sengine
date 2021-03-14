#include "Common.h"

#include <GLFW/glfw3.h>

namespace Common {
double GetTime()
{
    return glfwGetTime();
}
} // namespace Common
