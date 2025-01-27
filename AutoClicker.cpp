#include <iostream>
#include <windows.h>

enum class clickerType
{
    AUTO,
    HOLD,
    HOLDBREAK
};

int enumIndex;

clickerType currentType = clickerType::AUTO;

INPUT inputs[2] = {0};

void autoClicker(int delay)
{
    while (true)
    {
        std::cout << "Click" << std::endl;
        Sleep(delay);

        if (GetAsyncKeyState(VK_F10) & 0x01)
        {
            std::cout << "broke out" << std::endl;
            break;
        }
    }
}

void holdClicker()
{
    while (true)
    {
        std::cout << "Click" << std::endl;

        if (GetAsyncKeyState(VK_F10) & 0x01)
        {
            std::cout << "broke out" << std::endl;
            break;
        }
    }
}

void cycleStates()
{
    if (GetAsyncKeyState(VK_F8) & 0x01)
    {
        enumIndex = (int)(currentType);

        // Increment and wrap around
        if (enumIndex < 2)
        {
            enumIndex++;
        }
        else
        {
            enumIndex = 0; // Reset to the first type
        }

        currentType = static_cast<clickerType>(enumIndex); // Update the currentType
        std::cout << enumIndex << " type" << std::endl;
    }
}

int main()
{
    // Initialize an INPUT structure for mouse events
    inputs[0].type = INPUT_MOUSE;
    inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    inputs[1].type = INPUT_MOUSE;
    inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    while (true)
    {
        if (GetAsyncKeyState(VK_F9) & 0x01)
        {
            autoClicker(1000);
        }

        cycleStates();
    }

    return 0;
}