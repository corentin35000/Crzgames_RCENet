# RCENet Socket API Documentation

Welcome to the RCENet Socket API documentation. This section offers an in-depth guide on socket management within RCENet, highlighting key functions and structures for creating, managing, and utilizing sockets for network communication.

## Overview

The RCENet library abstracts the complexities involved in socket programming, providing a simplified interface for network communication. This document delves into the `ENetSocket`, a fundamental aspect of network communication, covering their creation, options, and usage within the RCENet library.

<br /><br />


## Enumerations

### `ENetSocketType`

Defines the behavior and characteristics of sockets used in network communications.

- **Types:**
  - `ENET_SOCKET_TYPE_STREAM`: Stream socket (TCP), providing reliable, sequenced, and connection-oriented transmissions.
  - `ENET_SOCKET_TYPE_DATAGRAM`: Datagram socket (UDP), used for connectionless transmissions.

```c
typedef enum _ENetSocketType
{
   ENET_SOCKET_TYPE_STREAM   = 1,
   ENET_SOCKET_TYPE_DATAGRAM = 2
} ENetSocketType;
```

<br />

### `ENetSocketWait`

Specifies conditions a socket should wait for during selection operations.

- **Conditions:**
  - `ENET_SOCKET_WAIT_NONE`: No waiting condition.
  - `ENET_SOCKET_WAIT_SEND`: Wait for the socket to be ready to send data.
  - `ENET_SOCKET_WAIT_RECEIVE`: Wait for the socket to be ready to receive data.
  - `ENET_SOCKET_WAIT_INTERRUPT`: Wait for an interrupt.

```c
typedef enum _ENetSocketWait
{
   ENET_SOCKET_WAIT_NONE      = 0,
   ENET_SOCKET_WAIT_SEND      = (1 << 0),
   ENET_SOCKET_WAIT_RECEIVE   = (1 << 1),
   ENET_SOCKET_WAIT_INTERRUPT = (1 << 2)
} ENetSocketWait;
```

<br />

### `ENetSocketOption`

Options for configuring socket behavior at the OS level.

- **Options:**
  - `ENET_SOCKOPT_NONBLOCK`: Enable non-blocking mode for the socket.
  - `ENET_SOCKOPT_BROADCAST`: Enable the sending of broadcast packets.
  - `ENET_SOCKOPT_RCVBUF`: Size of the receive buffer.
  - `ENET_SOCKOPT_SNDBUF`: Size of the send buffer.
  - `ENET_SOCKOPT_REUSEADDR`: Allow reuse of local addresses.
  - `ENET_SOCKOPT_RCVTIMEO`: Timeout for receiving.
  - `ENET_SOCKOPT_SNDTIMEO`: Timeout for sending.
  - `ENET_SOCKOPT_ERROR`: Get pending error on the socket.
  - `ENET_SOCKOPT_NODELAY`: Disable Nagle's algorithm (for TCP sockets).
  - `ENET_SOCKOPT_TTL`: Set the TTL for IP packets.
  - `ENET_SOCKOPT_IPV6ONLY`: IPv6-only socket, without support for IPv4-mapped addresses.

```c
typedef enum _ENetSocketOption
{
   ENET_SOCKOPT_NONBLOCK  = 1,
   ENET_SOCKOPT_BROADCAST = 2,
   ENET_SOCKOPT_RCVBUF    = 3,
   ENET_SOCKOPT_SNDBUF    = 4,
   ENET_SOCKOPT_REUSEADDR = 5,
   ENET_SOCKOPT_RCVTIMEO  = 6,
   ENET_SOCKOPT_SNDTIMEO  = 7,
   ENET_SOCKOPT_ERROR     = 8,
   ENET_SOCKOPT_NODELAY   = 9,
   ENET_SOCKOPT_TTL       = 10,
   ENET_SOCKOPT_IPV6ONLY  = 11
} ENetSocketOption;
```

<br />

### `ENetSocketShutdown`

Modes for socket shutdown operations.

- **Modes:**
  - `ENET_SOCKET_SHUTDOWN_READ`: Close the receive side of the socket.
  - `ENET_SOCKET_SHUTDOWN_WRITE`: Close the send side of the socket.
  - `ENET_SOCKET_SHUTDOWN_READ_WRITE`: Close both send and receive sides.

```c
typedef enum _ENetSocketShutdown
{
    ENET_SOCKET_SHUTDOWN_READ       = 0,
    ENET_SOCKET_SHUTDOWN_WRITE      = 1,
    ENET_SOCKET_SHUTDOWN_READ_WRITE = 2
} ENetSocketShutdown;
```

<br /><br />


## Functions

This section provides a detailed overview of the socket-related functions in the RCENet library, allowing for the creation, management, and utilization of network sockets for UDP and TCP communications.

### `enet_socket_create`

Creates a socket of the specified type.

- **Prototype**:
  ```c
  ENET_API ENetSocket enet_socket_create(ENetAddressType addressType, ENetSocketType socketType);
  ```
- **Parameters**:
  - `addressType`: The type of address (IPv4, IPv6) the socket will use.
  - `socketType`: The type of socket to create (STREAM for TCP, DATAGRAM for UDP).
- **Returns**: A handle to the newly created socket, or `ENET_SOCKET_NULL` on failure.

<br />

### `enet_socket_bind`

Binds a socket to a local address.

- **Prototype**:
  ```c
  ENET_API int enet_socket_bind(ENetSocket socket, const ENetAddress *address);
  ```
- **Parameters**:
  - `socket`: The socket to bind.
  - `address`: The local address to bind the socket to.
- **Returns**: `0` on success, `< 0` on failure.

<br />

### `enet_socket_listen`

Listens for incoming connections on a socket.

- **Prototype**:
  ```c
  ENET_API int enet_socket_listen(ENetSocket socket, int backlog);
  ```
- **Parameters**:
  - `socket`: The socket to listen on.
  - `backlog`: The maximum length for the queue of pending connections.
- **Returns**: `0` on success, `< 0` on failure.

<br /><br />

### Data Transmission

### `enet_socket_send`

Sends data to a specified destination.

- **Prototype**:
  ```c
  ENET_API int enet_socket_send(ENetSocket socket, const ENetAddress *destination, const ENetBuffer *buffers, size_t bufferCount);
  ```
- **Parameters**:
  - `socket`: The socket from which data is sent.
  - `destination`: The address of the recipient.
  - `buffers`: An array of data buffers to send.
  - `bufferCount`: The number of data buffers.
- **Returns**: The total number of bytes sent, or `< 0` on failure.

<br /><br />

### `enet_socket_receive`

Receives data from a socket.

- **Prototype**:
  ```c
  ENET_API int enet_socket_receive(ENetSocket socket, ENetAddress *sender, ENetBuffer *buffers, size_t bufferCount);
  ```
- **Parameters**:
  - `socket`: The socket on which data is received.
  - `sender`: The address of the sender.
  - `buffers`: An array of buffers to store the received data.
  - `bufferCount`: The number of data buffers.
- **Returns**: The total number of bytes received, or `< 0` on failure.

<br /><br />

### Socket Configuration

### `enet_socket_set_option`

Sets an option on a socket.

- **Prototype**:
  ```c
  ENET_API int enet_socket_set_option(ENetSocket socket, ENetSocketOption option, int value);
  ```
- **Parameters**:
  - `socket`: The socket to configure.
  - `option`: The specific option to set.
  - `value`: The value to set for the option.
- **Returns**: `0` on success, `< 0` on failure.

<br /><br />


### Socket Shutdown and Destruction

### `enet_socket_shutdown`

Shuts down part of a full-duplex connection.

- **Prototype**:
  ```c
  ENET_API int enet_socket_shutdown(ENetSocket socket, ENetSocketShutdown how);
  ```
- **Parameters**:
  - `socket`: The socket to shut down.
  - `how`: The method of shutdown (read, write, or both).
- **Returns**: `0` on success, `< 0` on failure.

<br /><br />

### `enet_socket_destroy`

Closes and destroys a socket.

- **Prototype**:
  ```c
  ENET_API void enet_socket_destroy(ENetSocket socket);
  ```
- **Parameters**:
  - `socket`: The socket to destroy.

<br /><br />


## Conclusion

The RCENet Socket API simplifies network programming by providing a high-level interface to socket operations, enabling developers to focus on the core logic of their networked applications. For further information or assistance, please consult the official RCENet documentation or the ENet programming guide.