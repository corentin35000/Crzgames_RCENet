
# RCENet Address API Documentation

Welcome to the RCENet Address API documentation. This section provides a comprehensive guide to managing network addresses with RCENet, covering essential functions and structures for IP address manipulation and interaction within the RCENet library.

## Overview

The RCENet library simplifies network programming by abstracting complex networking operations, including address management. This document focuses on the `ENetAddress` structure and associated functions, which play a critical role in network communication by representing network endpoints.

## Structures

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

## Functions

### Address Comparison and Validation

- **`enet_address_equal_host`**  
  _Compares the host part of two addresses._
  - **Parameters:** Two `ENetAddress` pointers for comparison.
  - **Returns:** `1` if equal, `0` otherwise.

- **`enet_address_equal`**  
  _Compares two addresses including their ports._
  - **Parameters:** Two `ENetAddress` pointers for comparison.
  - **Returns:** `1` if equal, `0` otherwise.

- **`enet_address_is_any`**  
  _Checks if an address is a wildcard (ANY) address._
  - **Parameters:** `ENetAddress` pointer.
  - **Returns:** `1` if it is an ANY address, `0` otherwise.

- **`enet_address_is_broadcast`**  
  _Determines if an address is a broadcast address._
  - **Parameters:** `ENetAddress` pointer.
  - **Returns:** `1` if broadcast, `0` otherwise.

- **`enet_address_is_loopback`**  
  _Checks if an address is a loopback address._
  - **Parameters:** `ENetAddress` pointer.
  - **Returns:** `1` if loopback, `0` otherwise.

### Address Resolution and Conversion

- **`enet_address_set_host_ip`**  
  _Parses a string IP address into an `ENetAddress` structure._
  - **Parameters:** `ENetAddress` pointer and a string containing the IP address.
  - **Returns:** `0` on success, `<0` on failure.

- **`enet_address_set_host`**  
  _Resolves a hostname to an IP address and stores it in an `ENetAddress` structure._
  - **Parameters:** `ENetAddress` pointer and a hostname string.
  - **Returns:** `0` on success, `<0` on failure.

- **`enet_address_get_host_ip`**  
  _Retrieves the printable IP address from an `ENetAddress` structure._
  - **Parameters:** `ENetAddress` pointer and a buffer for storing the resulting string.
  - **Returns:** `0` on success, `<0` on failure.

- **`enet_address_get_host`**  
  _Performs a reverse lookup of the IP address in an `ENetAddress` structure._
  - **Parameters:** `ENetAddress` pointer and a buffer for storing the resulting hostname.
  - **Returns:** `0` on success, `<0` on failure.

## Conclusion

This documentation aims to elucidate the foundational concepts related to address management in RCENet. For further information or assistance, please consult the official RCENet documentation or the ENet programming guide.
