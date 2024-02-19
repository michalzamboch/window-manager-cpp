#include <stdio.h>
#include <X11/Xlib.h>

int main() {
    Display *display;
    Window root;
    Window *children;
    unsigned int num_children;
    unsigned int i;

    // Open the display
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        return  1;
    }

    // Get the root window
    root = DefaultRootWindow(display);

    // Query for all children of the root window
    if (XQueryTree(display, root, &root, &root, &children, &num_children)) {
        // Iterate over all children
        for (i =  0; i < num_children; i++) {
            // Get the window attributes
            XWindowAttributes attrs;
            XGetWindowAttributes(display, children[i], &attrs);

            // Check if the window is visible
            if (attrs.map_state == IsViewable) {
                // Print the window ID
                printf("Window ID: %lu\n", children[i]);
            }
        }

        // Free the children array
        XFree(children);
    }

    // Close the display
    XCloseDisplay(display);

    return  0;
}

