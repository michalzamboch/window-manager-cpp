
#include "WindowInfo.h"

namespace WindowManager
{
    bool Visible(HWND hwnd)
    {
        return IsWindowVisible(hwnd);
    }
}