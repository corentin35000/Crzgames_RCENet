
# RCENet Packet API Documentation

Welcome to the RCENet Packet API documentation. This section provides an in-depth guide on packet management within RCENet, highlighting key structures, enumerations, and callback types essential for packet transmission and reception.

## Overview

The RCENet library offers a comprehensive approach to packet handling, emphasizing reliability, sequencing, and efficiency. This document explores the core components of packet communication in RCENet, including packet flags, callbacks for packet events, and the `ENetPacket` structure.

<br /><br />


## Enumerations

### `ENetPacketFlag`

Defines flags to control packet behavior in ENet. These flags specify important characteristics for packet delivery and processing.

- **Flags:**
  - `ENET_PACKET_FLAG_RELIABLE`: Ensures the packet must be received by the destination. Retransmissions are made until the packet is delivered.
  - `ENET_PACKET_FLAG_UNSEQUENCED`: Indicates the packet will not be sequenced with other packets. Not supported for reliable packets.
  - `ENET_PACKET_FLAG_NO_ALLOCATE`: Signals that the packet will not allocate data; the user must provide memory for the packet data.
  - `ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT`: Allows the packet to be fragmented using unreliable transmissions if its size exceeds the maximum transmission unit (MTU).
  - `ENET_PACKET_FLAG_SENT`: Indicates if the packet has been sent from all queues it was inserted into.

```c
typedef enum _ENetPacketFlag
{
   ENET_PACKET_FLAG_RELIABLE          = (1 << 0),
   ENET_PACKET_FLAG_UNSEQUENCED       = (1 << 1),
   ENET_PACKET_FLAG_NO_ALLOCATE       = (1 << 2),
   ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT = (1 << 3),
   ENET_PACKET_FLAG_SENT              = (1 << 8)
} ENetPacketFlag;
```

<br /><br />

## Structures

### `ENetPacket`

Represents an ENet packet. This packet contains data to be sent or received over the network.

- **Fields:**
  - `size_t referenceCount`: Reference count used internally by ENet for packet memory management.
  - `enet_uint32 flags`: Packet flags, combining `ENetPacketFlag` values to specify packet behavior.
  - `enet_uint8 * data`: Pointer to the allocated packet data.
  - `size_t dataLength`: Length of the data contained in the packet.
  - `ENetPacketFreeCallback freeCallback`: Callback function called when the packet is no longer used.
  - `void * userData`: User data that can be freely modified by the application.
  - `enet_uint32 remainingFragments`: Number of unacknowledged fragments. When this number reaches 0, `acknowledgeCallback` is triggered.
  - `ENetPacketAcknowledgedCallback acknowledgeCallback`: Callback function called when a reliable packet has been acknowledged by the recipient.

```c
typedef struct _ENetPacket
{
   size_t                         referenceCount;
   enet_uint32                    flags;
   enet_uint8 *                   data;
   size_t                         dataLength;
   ENetPacketFreeCallback         freeCallback;
   void *                         userData;
   enet_uint32                    remainingFragments;
   ENetPacketAcknowledgedCallback acknowledgeCallback;
} ENetPacket;
```

<br /><br />


## Callback Types

### `ENetPacketAcknowledgedCallback`

A callback function type called when a packet is acknowledged by the recipient. This callback allows for specific actions to be taken upon packet acknowledgment.

```c
typedef void (ENET_CALLBACK * ENetPacketAcknowledgedCallback) (struct _ENetPacket *);
```

<br /><br />

### `ENetPacketFreeCallback`

A callback function type called when a packet is freed. This callback allows for specific actions to be taken when freeing a packet's memory, such as releasing user-allocated resources.

```c
typedef void (ENET_CALLBACK * ENetPacketFreeCallback) (struct _ENetPacket *);
```

<br /><br />


## Functions

### `enet_packet_create`

_Creates a new packet for transmission._

```c
ENET_API ENetPacket * enet_packet_create (const void * data, size_t dataLength, enet_uint32 flags);
```

- **Parameters:**
  - `data`: The data to be included in the packet.
  - `dataLength`: The length of the data in bytes.
  - `flags`: Packet flags to control the packet's delivery and handling.

- **Returns:** A pointer to the newly created `ENetPacket`, or NULL on failure.

<br /><br />

### `enet_packet_destroy`

_Destroys a packet._

```c
ENET_API void enet_packet_destroy (ENetPacket * packet);
```

- **Parameters:**
  - `packet`: The packet to be destroyed.

<br /><br />

### `enet_packet_resize`

_Resizes the data in a packet._

```c
ENET_API int enet_packet_resize (ENetPacket * packet, size_t dataLength);
```

- **Parameters:**
  - `packet`: The packet to be resized.
  - `dataLength`: The new size for the packet data.

- **Returns:** `0` on success, `< 0` on failure.

<br /><br />

### `enet_crc32`

_Computes the CRC32 (Cyclic Redundancy Check) for the given buffers._

```c
ENET_API enet_uint32 enet_crc32 (const ENetBuffer * buffers, size_t bufferCount);
```

- **Parameters:**
  - `buffers`: An array of buffers over which to compute the CRC32.
  - `bufferCount`: The number of buffers in the array.

- **Returns:** The computed CRC32 value.

<br /><br />

### `enet_packet_get_data`

_Retrieves the data contained in a packet._

```c
ENET_API void* enet_packet_get_data(const ENetPacket * packet);
```

- **Parameters:**
  - `packet`: The packet from which to retrieve the data.

- **Returns:** A pointer to the data contained in the packet.

<br /><br />

### `enet_packet_get_user_data`

_Retrieves user-defined data associated with a packet._

```c
ENET_API void* enet_packet_get_user_data(const ENetPacket * packet);
```

- **Parameters:**
  - `packet`: The packet from which to retrieve the user data.

- **Returns:** A pointer to the user data.

<br /><br />

### `enet_packet_set_user_data`

_Associates user-defined data with a packet._

```c
ENET_API void enet_packet_set_user_data(ENetPacket * packet, void * userData);
```

- **Parameters:**
  - `packet`: The packet with which to associate the user data.
  - `userData`: The user data to associate with the packet.

<br /><br />

### `enet_packet_get_length`

_Retrieves the length of the data contained in a packet._

```c
ENET_API int enet_packet_get_length(const ENetPacket * packet);
```

- **Parameters:**
  - `packet`: The packet from which to retrieve the data length.

- **Returns:** The length of the packet data.

<br /><br />

### `enet_packet_set_acknowledge_callback`

_Sets a callback function to be called when the packet is acknowledged._

```c
ENET_API void enet_packet_set_acknowledge_callback(ENetPacket * packet, ENetPacketAcknowledgedCallback callback);
```

- **Parameters:**
  - `packet`: The packet to associate with the acknowledge callback.
  - `callback`: The callback function to be called upon acknowledgment.

<br /><br />

### `enet_packet_set_free_callback`

_Sets a callback function to be called when the packet is freed._

```c
ENET_API void enet_packet_set_free_callback(ENetPacket * packet, ENetPacketFreeCallback callback);
```

- **Parameters:**
  - `packet`: The packet to associate with the free callback.
  - `callback`: The callback function to be called when the packet is freed.

<br /><br />

### `enet_packet_check_references`

_Checks if a packet is still referenced within ENet._

```c
ENET_API int enet_packet_check_references(const ENetPacket * packet);
```

- **Parameters:**
  - `packet`: The packet to check for references.

- **Returns:** `1` if the packet is still referenced, `0` otherwise.

<br /><br />

### `enet_packet_dispose`

_Disposes of a packet and its associated resources._

```c
ENET_API void enet_packet_dispose(ENetPacket * packet);
```

- **Parameters:**
  - `packet`: The packet to dispose of.