# Quick Start

This guide will help you set up a basic project structure.

## Project Structure

Your project should include at least the following files:

- `main.cpp`: The entry point of your application.
- `game.h`: Header file containing declarations for your game's callback functions.
- `game.cpp`: Implementation file for your game's logic.
- `unit-tests.cpp`: (Optional) For unit testing with Doctest.

### main.cpp

The `main.cpp` file should include the RC2D header and your game header.

::: warning IMPORTANT
Ensure the `main` function prototype is exactly `int main(int argc, char* argv[])` for SDL2_main compatibility.
:::

```cpp
#include <rc2d/RC2D.h>
#include "game.h"

int main(int argc, char* argv[])
{
#ifndef DOCTEST_CONFIG_DISABLE
    if (rc2d_tests_runAllTests(argc, argv) != 0) return -1;
#endif

    RC2D_Callbacks myGameCallbacks = {};
    myGameCallbacks.rc2d_unload = rc2d_unload;
    myGameCallbacks.rc2d_load = rc2d_load;
    myGameCallbacks.rc2d_update = rc2d_update;
    myGameCallbacks.rc2d_draw = rc2d_draw;
    // Implement other callbacks...

    rc2d_run(&myGameCallbacks);

    return 0;
}
```

### game.h

Declare your game's callback functions and any other game-specific functionality.

```cpp
#ifndef _GAME_H_
#define _GAME_H_

void rc2d_unload(void);
void rc2d_load(void);
void rc2d_update(double dt);
void rc2d_draw(void);

// Implement other callbacks...

#endif // _GAME_H_
```

### game.cpp

Implement your game's logic and callback functions.

```cpp
#include "game.h"

RC2D_Image image = {};

void rc2d_unload(void)
{
    rc2d_graphics_freeImage(image);
}

void rc2d_load(void)
{
    image = rc2d_graphics_newImage("images/test.png");
}

void rc2d_update(double dt)
{

}

void rc2d_draw(void)
{
    rc2d_graphics_draw(image, 300, 200);
}

// Implement other callbacks...
```

### unit-tests.cpp

(Optional) For projects using unit testing with Doctest.

```cpp
#include <doctest/doctest.h>

TEST_CASE("Example test case") {
    int x = 1;
    CHECK(x == 1); // Test success
    CHECK(x == 2); // Test error
}
```