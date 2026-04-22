#ifndef INPUT
#define INPUT

#include <GLFW/glfw3.h>

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

struct MouseState {
    double Xpos;
    double Ypos;
};

struct KeyState {
    bool leftKeyPressed;
    bool rightKeyPressed;
    bool upKeyPressed;
    bool downKeyPressed;
};

extern bool CubeAdded;
extern bool RotationActivatedTogle;
extern MouseState mouseState;
extern KeyState keyState;

#endif