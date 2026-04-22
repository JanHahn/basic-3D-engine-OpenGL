#include "inputControl.h"
#include <iostream>

MouseState mouseState;
KeyState keyState;
bool CubeAdded;
bool RotationActivatedTogle;

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
    static double lastXpos;
    static double lastYpos;
    static size_t counter;
    counter++;
    std::cout << "Mouse callback event: " <<  counter << std::endl;

    double delatX = lastXpos - xpos;
    double delatY = lastYpos - ypos;

    mouseState.Xpos += delatX;
    mouseState.Ypos += delatY;

    lastXpos = xpos;
    lastYpos = ypos;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if ((key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) && action == GLFW_PRESS){
        keyState.rightKeyPressed = true;
        std::cout << "RIGHT KEY PRESSED" << std::endl;
    }
    if ((key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) && action == GLFW_RELEASE){
        keyState.rightKeyPressed = false;
        std::cout << "RIGHT KEY RELEASED" << std::endl;
    }
    if ((key == GLFW_KEY_LEFT || key == GLFW_KEY_A) && action == GLFW_PRESS){
        keyState.leftKeyPressed = true;
        std::cout << "LEFT KEY PRESSED" << std::endl;
    }
    if ((key == GLFW_KEY_LEFT || key == GLFW_KEY_A) && action == GLFW_RELEASE){
        keyState.leftKeyPressed = false;
        std::cout << "LEFT KEY RELEASED" << std::endl;
    }

    if ((key == GLFW_KEY_UP || key == GLFW_KEY_W) && action == GLFW_PRESS){
        keyState.upKeyPressed = true;
        std::cout << "RIGHT KEY PRESSED" << std::endl;
    }
    if ((key == GLFW_KEY_UP || key == GLFW_KEY_W) && action == GLFW_RELEASE){
        keyState.upKeyPressed = false;
        std::cout << "RIGHT KEY RELEASED" << std::endl;
    }
    if ((key == GLFW_KEY_DOWN || key == GLFW_KEY_S) && action == GLFW_PRESS){
        keyState.downKeyPressed = true;
        std::cout << "LEFT KEY PRESSED" << std::endl;
    }
    if ((key == GLFW_KEY_DOWN || key == GLFW_KEY_S) && action == GLFW_RELEASE){
        keyState.downKeyPressed = false;
        std::cout << "LEFT KEY RELEASED" << std::endl;
    }
    if (key == GLFW_KEY_C && action == GLFW_PRESS){
        CubeAdded = true;
        std::cout << "CubeAdded" << std::endl;
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS){
        if (RotationActivatedTogle == true){
            RotationActivatedTogle = false;
        }
        else{
            RotationActivatedTogle = true;
        }
        std::cout << "CubeAdded" << std::endl;
    }
}