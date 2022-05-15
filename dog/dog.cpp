#include <iostream>
#include <windows.h>
#include <thread>
#include <stdlib.h>
#include <time.h>

using namespace std;

long width;
long height;

void go() {
    // 0 = Left click at location
    // 1 = Double left click at location
    // 2 = Left down at locaiton, left up at location
    // 3 = Right click at location

    while (true) {
        switch (rand() % 4) {
            case 0: {
                INPUT inputs[2] = {};
                inputs[0].type = INPUT_MOUSE;
                inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
                inputs[1].type = INPUT_MOUSE;
                inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
                UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
                break;
            }
            case 1: {
                INPUT inputs[4] = {};
                inputs[0].type = INPUT_MOUSE;
                inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
                inputs[1].type = INPUT_MOUSE;
                inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
                inputs[2].type = INPUT_MOUSE;
                inputs[2].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
                inputs[3].type = INPUT_MOUSE;
                inputs[3].mi.dwFlags = MOUSEEVENTF_LEFTUP;
                UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
                break;
            }
            case 2: {
                INPUT inputs[2] = {};
                inputs[0].type = INPUT_MOUSE;
                inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
                inputs[1].type = INPUT_MOUSE;
                inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
                inputs[1].mi.dx = rand() % width;
                inputs[1].mi.dy = rand() % height;
                UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
                break;
            }
            case 3: {
                INPUT inputs[2] = {};
                inputs[0].type = INPUT_MOUSE;
                inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
                inputs[1].type = INPUT_MOUSE;
                inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
                UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
                break;
            }
        }
    }
}

int main()
{
    // Get CPU count.
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    int numCPU = sysinfo.dwNumberOfProcessors - 1;

    // Get monitor resolution.
    SetProcessDPIAware();
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    width = desktop.right + 1;
    height = desktop.bottom + 1;

    srand(time(NULL));

    for (int i = 0; i < numCPU; ++i) {
        thread(go);
    }

    go();
}