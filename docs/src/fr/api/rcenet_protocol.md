
# RCENet Protocol API Documentation

Welcome to the RCENet Protocol API documentation. This section provides detailed information on the protocol command size function within the RCENet library, essential for managing network communications and data packet structures.

## Overview

The RCENet library offers a comprehensive approach to network communication, encapsulating low-level networking details into a high-level API. The `enet_protocol_command_size` function is a critical component, used to determine the size of various protocol commands.

<br /><br />


## Functions

### `enet_protocol_command_size`

_Determines the size of a given protocol command._

```c
extern size_t enet_protocol_command_size(enet_uint8 command);
```

- **Parameters:**
  - `command`: The command for which the size is to be determined. This should be one of the values defined in `ENetProtocolCommand`.
- **Returns:**
  - The size of the protocol command in bytes.

- **Usage Example:**

  This function is typically used in scenarios where the size of a command needs to be dynamically determined, such as when parsing or constructing network packets.

  ```c
  enet_uint8 command = ENET_PROTOCOL_COMMAND_SEND_RELIABLE;
  size_t commandSize = enet_protocol_command_size(command);

  printf("Size of SEND_RELIABLE command: %zu bytes\n", commandSize);
  ```

- **Remarks:**
  - It is crucial to use this function for accurately sizing protocol commands, as incorrect sizes can lead to malformed packets and communication errors.
  - The `ENetProtocolCommand` enumeration contains all the supported commands, each potentially having a different size.