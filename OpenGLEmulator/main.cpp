#include <iostream>
#include <GLFW/glfw3.h>

int main(int argc, char* argv[]) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "GBA", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    float move = 1.0f / 600.0f;
    float x = 0.0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Set the pixel color to white
        glColor3f(1.0f, 1.0f, 1.0f);

        // Set the pixel position in normalized device coordinates
        // (0, 0) is the center of the screen in normalized coordinates
        glBegin(GL_POINTS);
        glVertex2f(x, 0.0f);
        glEnd();

        x = (x >= 1.0f) ? -1.0f : x + move;

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}