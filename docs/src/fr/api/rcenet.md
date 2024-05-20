# RCENet General API Documentation

Welcome to the RCENet General API documentation. This section provides detailed information about the general functions available in RCENet for initializing and managing the library's global state, as well as querying version information.

## Overview

Before utilizing any of the functions or features provided by RCENet for network communication, the library must be properly initialized. This documentation covers the necessary steps to initialize and deinitialize RCENet, along with how to override default callbacks and check the library version.

<br /><br />


## Functions

### Initialization and Deinitialization
<br />

#### `enet_initialize`
_Initializes ENet globally. Must be called before using any functions in ENet._

- **Prototype**:
  ```c
  ENET_API int enet_initialize(void);
  ```

- **Parameters**: None.

- **Returns**: `0` on success, `< 0` on failure. Indicates whether ENet was initialized successfully.

<br /><br />

#### `enet_initialize_with_callbacks`
_Initializes ENet globally with user-overridden callbacks. This function should be called instead of `enet_initialize()` if custom callbacks are needed._

- **Prototype**:
  ```c
  ENET_API int enet_initialize_with_callbacks(ENetVersion version, const ENetCallbacks *inits);
  ```

- **Parameters**:
  - `version`: The constant `ENET_VERSION` should be supplied to ensure compatibility.
  - `inits`: A pointer to an `ENetCallbacks` structure that allows the user to override certain internal functions. Any `NULL` callbacks will use ENet's defaults.

- **Returns**: `0` on success, `< 0` on failure. It allows for more granular initialization based on user needs.

<br /><br />

#### `enet_deinitialize`
_Shuts down ENet globally. Should be called when a program that has initialized ENet exits._

- **Prototype**:
  ```c
  ENET_API void enet_deinitialize(void);
  ```

- **Parameters**: None.

- **Action**: Cleans up global ENet resources. It is crucial to call this function to avoid resource leaks.

<br /><br />

### Version Information
<br />

#### `enet_linked_version`
_Returns the version number of the linked ENet library._

- **Prototype**:
  ```c
  ENET_API ENetVersion enet_linked_version(void);
  ```

- **Parameters**: None.

- **Returns**: The version number of the ENet library. This can be useful for debugging or ensuring compatibility with certain library versions.

<br /><br />

## Conclusion

The RCENet General API plays a crucial role in the initialization and management of the ENet library's overall operation. Proper initialization is essential for the successful use of the library's network communication features. For further information or assistance, please refer to the official RCENet documentation or the ENet programming guide.