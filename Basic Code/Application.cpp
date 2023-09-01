#include"Shader.h"
#include<GLFW\glfw3.h>
#include"Texture.h"

//two texture mix value
float mixValue = 0.5f;

//camrea move speed
float camreaSpeed = 0.1f;

//moust postion
bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

//camrea vector
glm::vec3 camreaPos(1.0f, 0.0f, 3.0f);
glm::vec3 camreaTar(0.0f, 0.0f, -1.0f);
glm::vec3 camreaUp(0.0f, 1.0f, 0.0f);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void EscWindow(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void ProcessInput(GLFWwindow* window);

int main()
{
    glfwInit();
    

    GLFWwindow* window = glfwCreateWindow(800, 600, "window", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //set GLFW mode
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);


    //position array
    float positions[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };


    //vertex array object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //vertex buffer object
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    //index buffer object
    unsigned int indexbuffer;
    glGenBuffers(1, &indexbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    
    //set mode in position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    
    //set mode in texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * (sizeof(float)), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);




    // shader
    Shader shader("res\\shaders\\Basic.shader");
    //get the vertex shader and fragment shader
   
    shader.ParseShader();
    shader.CompileShader();
    shader.UseProgram();


    Texture texture1("res\\texture\\img\\wall.png");
    Texture texture2("res\\texture\\img\\awesomeface.png");

    glUniform1i(shader.GetUniformLoaction("texture1"), 0);
    glUniform1i(shader.GetUniformLoaction("texture2"), 1);

    shader.UseProgram();

    
    
    
    float delta_time = 0.0f;
    float last_time = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        //input code
        EscWindow(window);

        double current_time = glfwGetTime();
        delta_time = current_time - last_time;
        last_time = current_time;
        //rendering code
        glm::vec3 light(1.0f, 1.0f, 1.0f);
        glClearColor(light.x, light.y, light.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glm::vec3 obj_color(0.5f, 0.5f, 0.3f);
        obj_color = obj_color * light;
        int color_location = shader.GetUniformLoaction("color");
        glUniform3f(color_location, obj_color.x, obj_color.y, obj_color.z);

        shader.UseProgram();

        //binding texture
        shader.BindTexture(GL_TEXTURE_2D, texture1.GetTextureID());
        shader.BindTexture(GL_TEXTURE_2D, texture2.GetTextureID());
        shader.UseProgram();
 

        //model matrix : control object


        //view matrix : control the camera view 
        camreaSpeed = 2.5f * delta_time;
        

        glm::mat4 view(1.0f);
        view = glm::lookAt(
            camreaPos,
            camreaPos + camreaTar,
            camreaUp);
        
        ProcessInput(window);

        //projection matrix :
        glm::mat4 projection(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (800.0f / 600.0f), 0.1f, 100.0f);

        //set matrix
        shader.SetMat4f("view", view);
        shader.SetMat4f("projection", projection);
        

        texture1.Bind(0);
        texture2.Bind(1);
        glBindVertexArray(VAO);

        for (int i = 0; i < 10; i++) {
            glm::mat4 model(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 25.0f * i;
            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            shader.SetMat4f("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //check the event and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &buffer);
    glDeleteBuffers(1, &indexbuffer);

    glfwTerminate();
    return 0;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

void EscWindow(GLFWwindow* window) {
    //press down the esc key on keyboard
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        //set mode to esc window
        glfwSetWindowShouldClose(window, true);
    }
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    camreaTar = glm::normalize(front);
}

void ProcessInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        //Press W
        camreaPos += camreaTar * camreaSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        //Press S
        camreaPos -= camreaTar * camreaSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        //Press A
        camreaPos -= glm::normalize(glm::cross(camreaTar, camreaUp)) * camreaSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        //Press D
        camreaPos += glm::normalize(glm::cross(camreaTar, camreaUp)) * camreaSpeed;
    }
}
