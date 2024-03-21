# RCENet Address API Documentation

Welcome to the RCENet Address API documentation. This section provides a comprehensive guide to managing network addresses with RCENet, covering essential functions and structures for IP address manipulation and interaction within the RCENet library.

## Overview

The RCENet library simplifies network programming by abstracting complex networking operations, including address management. This document focuses on the `ENetAddress` structure and associated functions, which play a critical role in network communication by representing network endpoints.

<br /><br />


## Structure

### `ENetAddress`

Represents a network endpoint with an IP address and a port number.

- **Fields:**
  - `ENetAddressType type`: The type of address (IPv4, IPv6).
  - `enet_uint16 port`: The port number in host byte order.
  - `union host`: IP address in network byte order. Use `v4` for IPv4 or `v6` for IPv6.

```c
typedef struct _ENetAddress {
   ENetAddressType type;
   enet_uint16 port;
   union {
       enet_uint8 v4[4];
       enet_uint16 v6[8];
   } host;
} ENetAddress;
```

<br /><br />


## Functions

### Comparison and Validation Functions
<br />

#### `enet_address_equal_host`
Compares the host part of two addresses to determine if they are equal.

- **Prototype**:
  ```c
  ENET_API int enet_address_equal_host(const ENetAddress * firstAddress, const ENetAddress * secondAddress);
  ```

- **Parameters**:
  - `firstAddress`: Pointer to the first address to compare.
  - `secondAddress`: Pointer to the second address to compare.

- **Returns**: `1` if the host parts are equal, `0` otherwise.

<br /><br />

#### `enet_address_equal`
Compares two addresses, including their ports, to determine if they are equal.

- **Prototype**:
  ```c
  ENET_API int enet_address_equal(const ENetAddress * firstAddress, const ENetAddress * secondAddress);
  ```

- **Parameters**:
  - `firstAddress`: Pointer to the first address to compare.
  - `secondAddress`: Pointer to the second address to compare.

- **Returns**: `1` if both the host parts and the ports are equal, `0` otherwise.

<br /><br />

#### `enet_address_is_any`
Checks if an address is the special "any" address, which listens on all interfaces.

- **Prototype**:
  ```c
  ENET_API int enet_address_is_any(const ENetAddress * address);
  ```

- **Parameters**:
  - `address`: Pointer to the address to check.

- **Returns**: `1` if the address is the "any" address, `0` otherwise.

<br /><br />

#### `enet_address_is_broadcast`
Determines if an address is a broadcast address.

- **Prototype**:
  ```c
  ENET_API int enet_address_is_broadcast(const ENetAddress * address);
  ```

- **Parameters**:
  - `address`: Pointer to the address to check.

- **Returns**: `1` if the address is a broadcast address, `0` otherwise.

<br /><br />

#### `enet_address_is_loopback`
Checks if an address is a loopback address.

- **Prototype**:
  ```c
  ENET_API int enet_address_is_loopback(const ENetAddress * address);
  ```

- **Parameters**:
  - `address`: Pointer to the address to check.

- **Returns**: `1` if the address is a loopback address, `0` otherwise.

<br /><br />

### Resolution and Conversion Functions
<br />

#### `enet_address_set_host_ip`
Parses a string IP address and sets the address object.

- **Prototype**:
  ```c
  ENET_API int enet_address_set_host_ip(ENetAddress * address, const char * hostName);
  ```

- **Parameters**:
  - `address`: Pointer to the address object to be set.
  - `hostName`: IP address in string format.

- **Returns**: `0` on success, `<0` on failure.

<br /><br />


#### `enet_address_set_host`
Resolves a hostname to an IP address and stores it in an address object.

- **Prototype**:
  ```c
  ENET_API int enet_address_set_host(ENetAddress * address, ENetAddressType type, const char * hostName);
  ```

- **Parameters**:
  - `address`: Pointer to the address object to be set.
  - `type`: Type of the address (IPv4 or IPv6).
  - `hostName`: Hostname to resolve.

- **Returns**: `0` on success, `<0` on failure.

<br /><br />


#### `enet_address_get_host_ip`
Retrieves the printable IP address from an address object.

- **Prototype**:
  ```c
  ENET_API int enet_address_get_host_ip(const ENetAddress * address, char * hostName, size_t nameLength);
  ```

- **Parameters**:
  - `address`: Pointer to the address object.
  - `hostName`: Buffer to store the printable IP address.
  - `nameLength`: Length of the buffer.

- **Returns**: `0` on success, `<0` on failure.

<br /><br />


#### `enet_address_get_host`
Performs a reverse lookup of the IP address to find the hostname.

- **Prototype**:
  ```c
  ENET_API int enet_address_get_host(const ENetAddress * address, char * hostName, size_t nameLength);
  ```

- **Parameters**:
  - `address`: Pointer to the address object.
  - `hostName`: Buffer to store the hostname.
  - `nameLength`: Length of the buffer.

- **Returns**: `0` on success, `<0` on failure.

<br /><br />


## Conclusion

This documentation aims to elucidate the foundational concepts related to address management in RCENet. For further information or assistance, please consult the official RCENet documentation or the ENet programming guide.