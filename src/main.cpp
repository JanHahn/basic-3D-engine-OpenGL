#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>

#include "cube.h"
#include "inputControl.h"
#include "CubeGenerator.h"

struct ProgramShaderSource {
    std::string VertexSource;
    std::string FragmentSource;
};

static ProgramShaderSource ParseShader(const std::string &filepath)
{

    enum ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::ifstream stream(filepath);
    if (!stream){
        std::cout << "FAILED TO OPEN A FILE" << std::endl;
    }

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE; 

    while(getline(stream, line)){
        if (line.find("#shader") != std::string::npos){
            if (line.find("vertex") != std::string::npos){
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos){
                type = ShaderType::FRAGMENT;
            }
        }
        else{
            ss[(int)type] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Faild to compile" << (type == GL_VERTEX_SHADER ? "vertex": "fragment") << "Shader!!!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
 
    return id;
}   

static unsigned CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);    

    glDeleteShader(fs);
    glDeleteShader(vs);

    return program;
}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    int width, height; // <-- TU 2
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    if (glewInit() != GLEW_OK){
        std::cout << "CHUJ" << std::endl;
    } else {
        std::cout << "JEST OK" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    float absoluteCubeCoords[3] = {0, 0, 80};
    Cube myFirstCube(absoluteCubeCoords);
    std::vector<Cube> cubeStorage = {myFirstCube};
    CubeGenerator cubeGenerator(cubeStorage);
    cubeGenerator.AddCube();

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    float* vertices = cubeGenerator.GenerateVertexes();
    glBufferData(GL_ARRAY_BUFFER, cubeGenerator.getCubeNum() * 144 * sizeof(float), vertices, GL_STATIC_DRAW);
    delete[] vertices;
    
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    unsigned int* indices = cubeGenerator.GenerateIndices();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeGenerator.getCubeNum() * 36 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    delete[] indices;

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));

    ProgramShaderSource source = ParseShader("..\\res\\shaders\\basic.shader");
    std::cout << "Vertex" << std::endl;
    std::cout << source.VertexSource << std::endl;
    std::cout << "Fragment" << std::endl;
    std::cout << source.FragmentSource << std::endl;

    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);     
    glUseProgram(shader);

    int location_u_cubeYAngleRotation = glGetUniformLocation(shader, "u_cubeYAngleRotation");
    if (location_u_cubeYAngleRotation == -1) {
        std::cout << "Ostrzeżenie: Uniform 'location_u_cubeYAngleRotation' nie został znaleziony!" << std::endl;
    }

    int location_u_cubeXAngleRotation = glGetUniformLocation(shader, "u_cubeXAngleRotation");
    if (location_u_cubeXAngleRotation == -1) {
        std::cout << "Ostrzeżenie: Uniform 'location_u_cubeXAngleRotation' nie został znaleziony!" << std::endl;
    }

    int location_u_cubeAbsolutePosition = glGetUniformLocation(shader, "u_cubeAbsolutePosition");
    if (location_u_cubeAbsolutePosition == -1) {
        std::cout << "Ostrzeżenie: Uniform 'location_u_cubeAbsolutePosition' nie został znaleziony!" << std::endl;
    }

    int location_u_Xshift = glGetUniformLocation(shader, "u_Xshift");
    if (location_u_Xshift == -1) {
        std::cout << "Ostrzeżenie: Uniform 'location_u_Xshift' nie został znaleziony!" << std::endl;
    }

    int location_u_Zshift = glGetUniformLocation(shader, "u_Zshift");
    if (location_u_Zshift == -1) {
        std::cout << "Ostrzeżenie: Uniform 'location_u_Zshift' nie został znaleziony!" << std::endl;
    } 

    int location_u_viewXangle = glGetUniformLocation(shader, "u_viewXangle");
    if (location_u_viewXangle == -1) {
        std::cout << "Ostrzeżenie: Uniform 'location_u_viewXangle' nie został znaleziony!" << std::endl;
    } 

    int location_u_viewYangle = glGetUniformLocation(shader, "u_viewYangle");
    if (location_u_viewYangle == -1) {
        std::cout << "Ostrzeżenie: Uniform 'location_u_viewYangle' nie został znaleziony!" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);

    glfwRawMouseMotionSupported();
    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetKeyCallback(window, key_callback);

    glUniform3fv(location_u_cubeAbsolutePosition, 1, myFirstCube.getAbsoluteCoordinates());

    float XshiftValue = 0;
    float ZshiftValue = 0;

    float movementSpeed = 0.1;

    float cubeSpeedRotation = 0.001;
    float cubeRotationAngleX = 0;
    float cubeRotationAngleY = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float yaw = mouseState.Xpos / 200.0f;

        float forwardX = sin(yaw);
        float forwardZ = cos(yaw);

        float rightX = cos(yaw);
        float rightZ = -sin(yaw);

        if (keyState.leftKeyPressed == false && keyState.rightKeyPressed == true){
            XshiftValue -= rightX * movementSpeed;
            ZshiftValue -= rightZ * movementSpeed;
            std::cout << XshiftValue << std::endl;
        }
        else if (keyState.leftKeyPressed == true && keyState.rightKeyPressed == false){
            XshiftValue += rightX * movementSpeed;
            ZshiftValue += rightZ * movementSpeed;
            std::cout << XshiftValue << std::endl;
        }

        if (keyState.upKeyPressed == true && keyState.downKeyPressed == false){
            XshiftValue += forwardX * movementSpeed;
            ZshiftValue += forwardZ * movementSpeed;
            std::cout << ZshiftValue << std::endl;
        }
        else if (keyState.upKeyPressed == false && keyState.downKeyPressed == true){
            XshiftValue -= forwardX * movementSpeed;
            ZshiftValue -= forwardZ * movementSpeed;
            std::cout << ZshiftValue << std::endl;
        }


        glUniform1f(location_u_cubeXAngleRotation, cubeRotationAngleX);
        glUniform1f(location_u_cubeYAngleRotation, cubeRotationAngleY);

        glUniform1f(location_u_Xshift, XshiftValue);
        glUniform1f(location_u_Zshift, ZshiftValue);

        glUniform1f(location_u_viewXangle, mouseState.Ypos / 200);
        glUniform1f(location_u_viewYangle, mouseState.Xpos / 200);
        
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //glLineWidth(3.0f);
        for (size_t cube = 0; cube < cubeGenerator.getCubeNum(); cube++){ 
            glUniform3fv(location_u_cubeAbsolutePosition, 1, cubeGenerator.GetCube(cube).getAbsoluteCoordinates());
            void* offset = (void*)(cube * 36 * sizeof(unsigned int));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, offset);
        }  

        if (CubeAdded == true){
            cubeGenerator.AddCube();

            float* vertices = cubeGenerator.GenerateVertexes();
            glBufferData(GL_ARRAY_BUFFER, cubeGenerator.getCubeNum() * 144 * sizeof(float), vertices, GL_STATIC_DRAW);
            delete[] vertices;

            unsigned int* indices = cubeGenerator.GenerateIndices();
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeGenerator.getCubeNum() * 36 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
            delete[] indices;

            CubeAdded = false;
        }

        if (RotationActivatedTogle == true){
            cubeRotationAngleX += cubeSpeedRotation;
            cubeRotationAngleY += cubeSpeedRotation;
        }
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}

