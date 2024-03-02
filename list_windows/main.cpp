#include <iostream>
#include <string>
#include <sstream>
#include <ostream>
#include <optional>
#include <X11/Xlib.h>

std::optional<std::string> GetWindowName(Display *display, const Window &window);

int main()
{
    Display *display;
    Window root;
    Window *children;
    unsigned int num_children;
    unsigned int i;

    // Open the display
    display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        fprintf(stderr, "Cannot open display\n");
        return 1;
    }

    // Get the root window
    root = DefaultRootWindow(display);

    // Query for all children of the root window
    if (XQueryTree(display, root, &root, &root, &children, &num_children))
    {
        // Iterate over all children
        for (i = 0; i < num_children; i++)
        {
            // Get the window attributes
            XWindowAttributes attrs;
            XGetWindowAttributes(display, children[i], &attrs);

            // Check if the window is visible
            if (attrs.map_state == IsViewable)
            {
                if (auto str = GetWindowName(display, children[i]))
                {
                    std::cout << "ID: " << children[i]
                              << " Name: " << *str << std::endl;
                }
                else
                {
                    std::cout << "ID: " << children[i] << std::endl;
                }
            }
        }

        // Free the children array
        XFree(children);
    }

    // Close the display
    XCloseDisplay(display);

    return 0;
}

std::optional<std::string> GetWindowName(Display *display, const Window &window)
{
    Atom netWmName = XInternAtom(display, "_NET_WM_NAME", False);
    Atom actualType;
    int actualFormat;
    unsigned long nItems, bytesAfter;
    unsigned char *prop = NULL;

    Window windowID = window;
    std::optional<std::string> finalName = {};

    if (XGetWindowProperty(display, windowID, netWmName, 0L, (~0L), False, AnyPropertyType,
                           &actualType, &actualFormat, &nItems, &bytesAfter, &prop) == Success)
    {
        std::ostringstream stringStream;
        stringStream << prop;
        finalName = stringStream.str();
    }
    else
    {
        finalName = {};
    }
    XFree(prop);

    return finalName;
}