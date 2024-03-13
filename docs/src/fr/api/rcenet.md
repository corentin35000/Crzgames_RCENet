
# RC2D General API Documentation

Welcome to the RC2D General API documentation. This section introduces the core functionalities and the main entry point for the RC2D game engine, encompassing game loop management, event handling, and callback registration.

## Structures

### `RC2D_Callbacks`

Defines a comprehensive set of callbacks for game loop events, input handling, and other game-related events, allowing for a high degree of interaction and control within the game environment.

- **Fields:**
  - `void (*rc2d_load)(void);`: Invoked at the start of the application to load resources.
  - `void (*rc2d_unload)(void);`: Invoked when the application is closing to clean up resources.
  - `void (*rc2d_update)(double dt);`: Called every frame, with `dt` representing the time since the last update, for game logic.
  - `void (*rc2d_draw)(void);`: Called every frame to render the game.
  - `void (*rc2d_keypressed)(const char* key, bool isrepeat);`: Triggered when a keyboard key is pressed.
  - `void (*rc2d_keyreleased)(const char* key);`: Triggered when a keyboard key is released.
  - `void (*rc2d_mousemoved)(int x, int y);`: Invoked when the mouse moves.
  - `void (*rc2d_mousepressed)(int x, int y, const char* button, int presses);`: Invoked when a mouse button is pressed.
  - `void (*rc2d_mousereleased)(int x, int y, const char* button, int presses);`: Invoked when a mouse button is released.
  - `void (*rc2d_wheelmoved)(const char* scroll);`: Triggered when the mouse wheel is scrolled.
  - `void (*rc2d_gamepadpressed)(SDL_JoystickID joystick, Uint8 button);`: Invoked when a gamepad button is pressed.
  - `void (*rc2d_gamepadreleased)(SDL_JoystickID joystick, Uint8 button);`: Invoked when a gamepad button is released.
  - `void (*rc2d_joystickpressed)(SDL_JoystickID joystick, Uint8 button);`: Triggered when a joystick button is pressed.
  - `void (*rc2d_joystickreleased)(SDL_JoystickID joystick, Uint8 button);`: Triggered when a joystick button is released.
  - `void (*rc2d_joystickadded)(Sint32 joystick);`: Invoked when a joystick is connected.
  - `void (*rc2d_joystickremoved)(Sint32 joystick);`: Invoked when a joystick is disconnected.
  - `void (*rc2d_dropfile)(const char* pathFile);`: Triggered when a file is dropped onto the game window.
  - Additional callbacks for text drop, drop begin, and drop complete events.

## API Functions

### `rc2d_run`

Initializes and starts the game loop, utilizing user-defined callbacks for game events.

- **Parameters:**
  - `RC2D_Callbacks* callbacksUser`: Pointer to a structure containing user-defined callback functions.

```c
int rc2d_run(RC2D_Callbacks* callbacksUser);
```

### `rc2d_quit`

Gracefully shuts down the game engine, cleaning up resources.

```c
void rc2d_quit(void);
```

## Conclusion

This documentation provides an overview of the RC2D General API, which is at the heart of game development with the RC2D game engine. Utilize the `rc2d_run` function to kickstart your game loop and register necessary callbacks for handling game events. For more detailed information or assistance, please refer to the specific module documentation within the RC2D game engine framework or consult the RC2D support resources.
