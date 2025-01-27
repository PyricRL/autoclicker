#include <iostream>
#include <windows.h>

enum class clickerType
{
    AUTO,
    HOLD,
    HOLDBREAK
};

int enumIndex;
bool holdingClick = false;

clickerType currentType = clickerType::AUTO;

INPUT inputs[2] = {0};

void autoClicker(int delay)
{
    while (true)
    {
        // handle click down and up
        inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        SendInput(1, &inputs[0], sizeof(INPUT));

        inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
        SendInput(1, &inputs[0], sizeof(INPUT));

        // wait for the delay
        Sleep(delay);

        // handle exiting the auto clicker
        if (GetAsyncKeyState(VK_F10) & 0x01)
        {
            break;
        }
    }
}

void holdClicker()
{
    while (true)
    {
        // allows less sending of packets (less laggy)
        if (!holdingClick)
        {
            // hold down click
            inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
            SendInput(1, &inputs[0], sizeof(INPUT));
            holdingClick = true;
        }

        // handle exiting the hold clicker
        if (GetAsyncKeyState(VK_F10) & 0x01)
        {
            // stop holding click
            inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
            SendInput(1, &inputs[0], sizeof(INPUT));
            holdingClick = false;

            break;
        }
    }
}

void holdBreakClicker(int delay)
{
    while (true)
    {
        // Simulate mouse button down
        inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        SendInput(1, &inputs[0], sizeof(INPUT));

        // Hold for 2.5 seconds
        Sleep(delay);

        // Simulate mouse button up
        inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
        SendInput(1, &inputs[0], sizeof(INPUT));

        // Small delay before the next cycle
        Sleep(50);

        // handle exiting the hold break clicker
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
            if (currentType == clickerType::AUTO)
            {
                autoClicker(1);
            }

            if (currentType == clickerType::HOLD)
            {
                holdClicker();
            }

            if (currentType == clickerType::HOLDBREAK)
            {
                holdBreakClicker(2500);
            }
        }

        cycleStates();
    }

    return 0;
}