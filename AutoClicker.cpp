#include <iostream>
#include <windows.h>

int main()
{
    bool F9Running = false;
    bool F10Running = false;

    // State tracking for F9 and F10
    bool wasF9Pressed = false;
    bool wasF10Pressed = false;

    // Initialize an INPUT structure for mouse events
    INPUT inputs[2] = {0};
    inputs[0].type = INPUT_MOUSE;                // Specify that this input is for the mouse
    inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN; // Mouse button down event

    inputs[1].type = INPUT_MOUSE;              // Specify that this input is for the mouse
    inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP; // Mouse button up event

    while (true)
    {
        // Check if F9 is currently pressed
        bool isF9Pressed = GetKeyState(VK_F9) & 0x8000;

        // Check if F10 is currently pressed
        bool isF10Pressed = GetKeyState(VK_F10) & 0x8000;

        // Detect the transition from not pressed to pressed for F9
        if (isF9Pressed)
        {
            if (!F9Running)
            {
                std::cout << "F9 pressed" << std::endl;
                F9Running = true;
                SendInput(1, &inputs[0], sizeof(INPUT)); // Mouse down
                inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
            }
            else
            {
                std::cout << "F9 pressed again" << std::endl;
                F9Running = false;
                break;
            }
        }

        // Detect the transition from not pressed to pressed for F10
        if (isF10Pressed)
        {
            if (!F10Running)
            {
                std::cout << "F10 started" << std::endl;
                std::cout << isF10Pressed << std::endl;
                F10Running = true;
                // Loop until F10 is pressed again
                while (F10Running)
                {
                    // Simulate mouse button down
                    inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
                    SendInput(1, &inputs[0], sizeof(INPUT));

                    // Hold for 5 seconds
                    Sleep(2500);

                    // Simulate mouse button up
                    inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
                    SendInput(1, &inputs[0], sizeof(INPUT));

                    // Small delay before the next cycle
                    Sleep(50);

                    if (isF10Pressed)
                    {
                        std::cout << "F10 pressed again" << std::endl;
                        F10Running = false;
                        // break;
                    }
                }
            }
        }
    }

    return 0;
}
