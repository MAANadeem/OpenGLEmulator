#include <iostream>
#include <GLFW/glfw3.h>
#include <string>
#include "CPU.h"

int main(int argc, char* argv[]) {

    CPU arm7 = CPU();
    std::string input;
    while (true) {
        for (int i = 0; i < 13; ++i) {
            int32_t reg = (int32_t)arm7.GetReg(i);
            std::cout << " REG " << i << ": " << reg;
        }
        std::cout << std::endl;
        std::cout << " N: " << arm7.GetFlag(CPU::cpsr_flags::N);
        std::cout << " Z: " << arm7.GetFlag(CPU::cpsr_flags::Z);
        std::cout << " C: " << arm7.GetFlag(CPU::cpsr_flags::C);
        std::cout << " V: " << arm7.GetFlag(CPU::cpsr_flags::V);
        std::cout << std::endl;

        std::getline(std::cin, input);
        if (input == "q") {
            break;
        }
        int length = input.length();
        int pow = 1;
        int total = 0;
        for (int i = 0; i < length; ++i) {
            if (input[length - i - 1] == '1') {
                total += pow;
            }
            pow *= 2;
        }
        uint16_t opcode = total;
        arm7.ExecuteThumb(opcode);
    }

    /*
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(800, 600, "GBA", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    float move = 1.0f / 600.0f;
    float x = 0.0;

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

    */
    return 0;
}