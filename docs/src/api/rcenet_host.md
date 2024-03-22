# RCENet Host API Documentation
Welcome to the RCENet Host API documentation. This section provides an in-depth guide on managing ENet hosts for network communication, covering key functionalities and structures necessary for creating, managing, and interacting with network hosts and peers within the RCENet framework.

## Overview
The RCENet library offers a high-level abstraction for network communication, significantly simplifying the process of creating and managing network connections. Hosts in RCENet serve as the central nodes for network communication, handling incoming and outgoing connections, data transmission, and bandwidth management. This document explores the ENetHost structure, detailing its significance in network communication and the various functions available for effective host management.

<br /><br />


## Enumerations

### `ENetEventType`

Defines the types of events in ENet. These events are returned by `enet_host_service()` and describe various actions or state changes that can occur on a host or a peer.

- **Types:**
  - `ENET_EVENT_TYPE_NONE`: No event has occurred within the specified time limit.
  - `ENET_EVENT_TYPE_CONNECT`: A peer has successfully connected.
  - `ENET_EVENT_TYPE_DISCONNECT`: A peer has disconnected.
  - `ENET_EVENT_TYPE_RECEIVE`: A packet has been received from a peer.
  - `ENET_EVENT_TYPE_DISCONNECT_TIMEOUT`: A peer has disconnected due to a timeout.

```c
typedef enum _ENetEventType
{
   ENET_EVENT_TYPE_NONE              = 0,
   ENET_EVENT_TYPE_CONNECT           = 1,
   ENET_EVENT_TYPE_DISCONNECT        = 2,
   ENET_EVENT_TYPE_RECEIVE           = 3,
   ENET_EVENT_TYPE_DISCONNECT_TIMEOUT= 4
} ENetEventType;
```

<br /><br />


## Structures

### `ENetEvent`

Represents an ENet event as returned by `enet_host_service()`. This structure contains all the necessary information to process the event, including the event type, the concerned peer, and any associated data or packet.

- **Fields:**
  - `ENetEventType type`: The type of the event.
  - `ENetPeer* peer`: The peer that generated a connection, disconnection, or receive event. Null for `ENET_EVENT_TYPE_NONE` events.
  - `enet_uint8 channelID`: The channel on the peer that generated the event, if applicable. Relevant for `ENET_EVENT_TYPE_RECEIVE` events.
  - `enet_uint32 data`: Data associated with the event, if applicable. For `ENET_EVENT_TYPE_DISCONNECT` and `ENET_EVENT_TYPE_DISCONNECT_TIMEOUT` events, this can contain user-provided data describing the disconnection.
  - `ENetPacket* packet`: The packet associated with the event, if applicable. Relevant for `ENET_EVENT_TYPE_RECEIVE` events. The packet must be destroyed with `enet_packet_destroy` after use.

```c
typedef struct _ENetEvent {
   ENetEventType        type;
   ENetPeer *           peer;
   enet_uint8           channelID;
   enet_uint32          data;
   ENetPacket *         packet;
} ENetEvent;
```

<br /><br />

### `ENetHost`

The `ENetHost` structure is defined as follows:

- **Fields:**
  - `ENetSocket socket`: The UDP socket used for communications.
  - `ENetAddress address`: The address of the host.
  - `enet_uint32 incomingBandwidth`: The incoming bandwidth limit in bytes/second.
  - `enet_uint32 outgoingBandwidth`: The outgoing bandwidth limit in bytes/second.
  - `enet_uint32 bandwidthThrottleEpoch`: Used internally to manage bandwidth throttling.
  - `enet_uint32 mtu`: The Maximum Transmission Unit size.
  - `enet_uint32 randomSeed`: Used internally for random number generation.
  - `int recalculateBandwidthLimits`: Flag to recalculate bandwidth limits.
  - `ENetPeer *peers`: Array of peers connected to this host.
  - `size_t peerCount`: The number of peers.
  - `size_t channelLimit`: The maximum number of channels allowed per connection.
  - `enet_uint32 serviceTime`: Last service time.
  - `ENetList dispatchQueue`: Queue of events to be dispatched.
  - `enet_uint32 totalQueued`: Total number of packets queued.
  - `size_t packetSize`: Size of the last packet sent or received.
  - `enet_uint16 headerFlags`: Protocol header flags.
  - `ENetProtocol commands[]`: Array of protocol commands.
  - `size_t commandCount`: Number of commands in the array.
  - `ENetBuffer buffers[]`: Buffers for outgoing data.
  - `size_t bufferCount`: Number of buffers used.
  - `ENetChecksumCallback checksum`: Checksum callback function.
  - `ENetCompressor compressor`: Data compression callbacks.
  - `enet_uint8 packetData[][]`: Packet data arrays for send and receive.
  - `ENetAddress receivedAddress`: Address of the last received packet.
  - `enet_uint8 *receivedData`: Data of the last received packet.
  - `size_t receivedDataLength`: Length of the last received packet's data.
  - `enet_uint32 totalSentData`: Total data sent.
  - `enet_uint32 totalSentPackets`: Total packets sent.
  - `enet_uint32 totalReceivedData`: Total data received.
  - `enet_uint32 totalReceivedPackets`: Total packets received.
  - `ENetInterceptCallback intercept`: Packet intercept callback.
  - `size_t connectedPeers`: Number of connected peers.
  - `size_t bandwidthLimitedPeers`: Peers with bandwidth limit.
  - `size_t duplicatePeers`: Allowed duplicate IP peers.
  - `size_t maximumPacketSize`: Maximum packet size.
  - `size_t maximumWaitingData`: Maximum waiting data.
  - `ENetEncryptor encryptor`: Packet encryption callbacks.

```c
typedef struct _ENetHost {
   ENetSocket socket;
   ENetAddress address;
   enet_uint32 incomingBandwidth;
   enet_uint32 outgoingBandwidth;
   enet_uint32 bandwidthThrottleEpoch;
   enet_uint32 mtu;
   enet_uint32 randomSeed;
   int recalculateBandwidthLimits;
   ENetPeer *peers;
   size_t peerCount;
   size_t channelLimit;
   enet_uint32 serviceTime;
   ENetList dispatchQueue;
   enet_uint32 totalQueued;
   size_t packetSize;
   enet_uint16 headerFlags;
   ENetProtocol commands[ENET_PROTOCOL_MAXIMUM_PACKET_COMMANDS];
   size_t commandCount;
   ENetBuffer buffers[ENET_BUFFER_MAXIMUM];
   size_t bufferCount;
   ENetChecksumCallback checksum;
   ENetCompressor compressor;
   enet_uint8 packetData[2][ENET_PROTOCOL_MAXIMUM_MTU];
   ENetAddress receivedAddress;
   enet_uint8 *receivedData;
   size_t receivedDataLength;
   enet_uint32 totalSentData;
   enet_uint32 totalSentPackets;
   enet_uint32 totalReceivedData;
   enet_uint32 totalReceivedPackets;
   ENetInterceptCallback intercept;
   size_t connectedPeers;
   size_t bandwidthLimitedPeers;
   size_t duplicatePeers;
   size_t maximumPacketSize;
   size_t maximumWaitingData;
   ENetEncryptor encryptor;
} ENetHost;
```

## Compression and Encryption

### `ENetCompressor`

A structure for packet compression before their transmission or reception via the UDP socket.

- **Fields:**
  - `void* context`: Context data for the compressor. Must be non-NULL.
  - `compress`: Function to compress data. Takes an array of `ENetBuffer` as input, compresses the data into `outData`, and outputs at most `outLimit` bytes. Should return 0 on failure.
  - `decompress`: Function to decompress data. Takes `inData`, decompresses the data into `outData`, and outputs at most `outLimit` bytes. Should return 0 on failure.
  - `destroy`: Function called when compression is disabled or the host is destroyed. Can be NULL.

```c
typedef struct _ENetCompressor
{
   void * context;
   size_t (ENET_CALLBACK * compress) (void * context, const ENetBuffer * inBuffers, size_t inBufferCount, size_t inLimit, enet_uint8 * outData, size_t outLimit);
   size_t (ENET_CALLBACK * decompress) (void * context, const enet_uint8 * inData, size_t inLimit, enet_uint8 * outData, size_t outLimit);
   void (ENET_CALLBACK * destroy) (void * context);
} ENetCompressor;
```

<br /><br />

### `ENetEncryptor`

A structure for packet encryption before their transmission or reception, occurring before compression.

- **Fields:**
  - `void* context`: Context data for the encryptor. Must be non-NULL.
  - `encrypt`: Function to encrypt data. Takes an array of `ENetBuffer` as input, encrypts the data into `outData`, and outputs at most `outLimit` bytes. Should return 0 on failure.
  - `decrypt`: Function to decrypt received packets from the peer (can be NULL if a connection packet), from `inData`, decrypts the data into `outData`, and outputs at most `outLimit` bytes. Should return 0 on failure.
  - `destroy`: Function called when encryption is disabled or the host is destroyed. Can be NULL.

```c
typedef struct _ENetEncryptor
{
   void * context;
   size_t (ENET_CALLBACK * encrypt) (void * context, ENetPeer * peer, const ENetBuffer * inBuffers, size_t inBufferCount, size_t inLimit, enet_uint8 * outData, size_t outLimit);
   size_t (ENET_CALLBACK * decrypt) (void * context, ENetPeer * peer, const enet_uint8 * inData, size_t inLimit, enet_uint8 * outData, size_t outLimit);
   void (ENET_CALLBACK * destroy) (void * context);
} ENetEncryptor;
```

<br /><br />


## Callbacks

### `ENetChecksumCallback`

Callback for calculating the checksum of data contained within buffers. This function is used to verify the integrity of transmitted data.

```c
typedef enet_uint32 (ENET_CALLBACK * ENetChecksumCallback) (const ENetBuffer * buffers, size_t bufferCount);
```

<br /><br />

### `ENetInterceptCallback`

Callback to intercept raw UDP packets received. This function allows inspecting, modifying, or discarding packets before they are processed by ENet.

```c
typedef int (ENET_CALLBACK * ENetInterceptCallback) (struct _ENetHost * host, struct _ENetEvent * event);
```

<br /><br />


## Functions

### Host Management

### `enet_host_create`

_Creates an ENet host for communicating over the network. The host can act as a server, client, or both._

```c
ENET_API ENetHost * enet_host_create (ENetAddressType type, const ENetAddress *address, size_t peerCount, size_t channelLimit, enet_uint32 incomingBandwidth, enet_uint32 outgoingBandwidth);
```

- **Parameters:**
  - `type`: The type of address (IPv4, IPv6) the host will use.
  - `address`: The local address to bind the host to. Use NULL for an unspecified address.
  - `peerCount`: The maximum number of peers that the host should support. If 0, then this is equivalent to ENET_PROTOCOL_MAXIMUM_PEER_ID (65535).
  - `channelLimit`: The maximum number of channels allowed; if 0, then this is equivalent to ENET_PROTOCOL_MAXIMUM_CHANNEL_COUNT (255).
  - `incomingBandwidth`: The incoming bandwidth of the host in bytes/second.
  - `outgoingBandwidth`: The outgoing bandwidth of the host in bytes/second.

- **Returns:** A pointer to the newly created `ENetHost`, or NULL on failure.

<br /><br />

### `enet_host_destroy`

_Destroys the specified host, disconnecting any connected peers._

```c
ENET_API void enet_host_destroy (ENetHost *host);
```

- **Parameters:**
  - `host`: The host to destroy.

<br /><br />

### `enet_host_connect`

_Initiates a connection to a foreign host._

```c
ENET_API ENetPeer * enet_host_connect (ENetHost *host, const ENetAddress *address, size_t channelCount, enet_uint32 data);
```

- **Parameters:**
  - `host`: The local host attempting to initiate the connection.
  - `address`: The address of the foreign host to connect to.
  - `channelCount`: The number of channels to allocate for the connection.
  - `data`: User data supplied to the connection attempt.

- **Returns:** A pointer to an `ENetPeer` representing the connection, or NULL on failure.

<br /><br />

### `enet_host_service`

_Dispatches queued events and sends or receives packets._

```c
ENET_API int enet_host_service (ENetHost *host, ENetEvent *event, enet_uint32 timeout);
```

- **Parameters:**
  - `host`: The host to service.
  - `event`: Pointer to an `ENetEvent` structure where the event (if any) will be placed.
  - `timeout`: The number of milliseconds to wait for an event. A value of 0 will return immediately.

- **Returns:** > 0 if an event was dispatched, 0 if no events occurred, < 0 on failure.

<br /><br />

### `enet_host_flush`

_Sends any queued packets on the host immediately._

```c
ENET_API void enet_host_flush (ENetHost *host);
```

- **Parameters:**
  - `host`: The host whose packet queue will be flushed.


<br /><br />

### `enet_host_broadcast`

_Broadcasts a packet to all connected peers._

```c
ENET_API void enet_host_broadcast (ENetHost *host, enet_uint8 channelID, ENetPacket *packet);
```

- **Parameters:**
  - `host`: The host from which the packet will be broadcasted.
  - `channelID`: The channel ID on which the packet will be sent.
  - `packet`: The packet to broadcast.

<br /><br />

## Encrypt

### `enet_host_encrypt`

_Sets the packet encryptor the host should use to encrypt and decrypt packets._

```c
void enet_host_encrypt(ENetHost * host, const ENetEncryptor * encryptor);
```

- **Parameters:**
  - `host`: The host to enable or disable encryption for.
  - `encryptor`: Callbacks for the packet encryptor; if NULL, then encryption is disabled.

- **Remarks:**
  - Enabling encryption activates the RCENet extended protocol and breaks compatibility with the regular ENet protocol. It is crucial to ensure that encryption is consistently enabled or disabled across all communicating hosts in your application to maintain protocol compatibility.

<br /><br />

## Compress

### `enet_host_compress`

_Enables packet compression using the specified compression callbacks._

```c
ENET_API void enet_host_compress (ENetHost *host, const ENetCompressor *compressor);
```

- **Parameters:**
  - `host`: The host for which to enable compression.
  - `compressor`: A pointer to the compression callbacks to use.

<br /><br />

### `enet_host_compress_with_range_coder`

_Enables range coding compression for the specified host._

```c
ENET_API int enet_host_compress_with_range_coder(ENetHost * host);
```

- **Parameters:**
  - `host`: The host for which to enable range coder compression.

- **Returns:**
  - `0` on success, indicating that range coding compression has been enabled.
  - `< 0` on failure, indicating that range coding compression could not be enabled.

- **Remarks:**
  - Range coding is a form of entropy coding used in compression. Enabling this option may enhance data compression rates for certain types of data, potentially improving network efficiency.

<br /><br />

### `enet_host_bandwidth_throttle`

_Adjusts the bandwidth throttle for the host, recalculating the peer's window sizes based on current conditions._

```c
extern void enet_host_bandwidth_throttle(ENetHost * host);
```

- **Parameters:**
  - `host`: The host whose bandwidth throttle will be adjusted.

- **Remarks:**
  - This function is typically called to dynamically adjust the bandwidth usage based on current network conditions. It recalculates the window size for each connected peer, potentially increasing or decreasing the rate at which the host sends data to manage congestion and maintain efficient use of available bandwidth.

<br /><br />

### `enet_host_bandwidth_limit`

_Limits the incoming and outgoing bandwidth of the host._

```c
ENET_API void enet_host_bandwidth_limit (ENetHost *host, enet_uint32 incomingBandwidth, enet_uint32 outgoingBandwidth);
```

- **Parameters:**
  - `host`: The host for which to set bandwidth limits.
  - `incomingBandwidth`: The maximum incoming bandwidth in bytes/second.
  - `outgoingBandwidth`: The maximum outgoing bandwidth in bytes/second.

<br /><br />

### `enet_host_channel_limit`

_Limits the maximum number of channels allowed for future connections._

```c
ENET_API void enet_host_channel_limit (ENetHost *host, size_t channelLimit);
```

- **Parameters:**
  - `host`: The host for which to set the channel limit.
  - `channelLimit`: The maximum number of channels.

<br /><br />


## Statistics and Configuration

### `enet_host_get_peers_count`

_Returns the number of connected peers._

```c
ENET_API enet_uint32 enet_host_get_peers_count(const ENetHost *host);
```

<br /><br />

### `enet_host_get_packets_sent`

_Returns the number of packets sent by the host._

```c
ENET_API enet_uint32 enet_host_get_packets_sent(const ENetHost *host);
```

<br /><br />

### `enet_host_get_packets_received`

_Returns the number of packets received by the host._

```c
ENET_API enet_uint32 enet_host_get_packets_received(const ENetHost *host);
```

<br /><br />

### `enet_host_get_bytes_sent`

_Returns the total number of bytes sent by the host._

```c
ENET_API enet_uint32 enet_host_get_bytes_sent(const ENetHost *host);
```

<br /><br />

### `enet_host_get_bytes_received`

_Returns the total number of bytes received by the host._

```c
ENET_API enet_uint32 enet_host_get_bytes_received(const ENetHost *host);
```

<br /><br />

### `enet_host_set_max_duplicate_peers`

_Sets the maximum number of allowed peers with the same IP address._

```c
ENET_API void enet_host_set_max_duplicate_peers(ENetHost *host, enet_uint16 number);
```

- **Parameters:**
  - `host`: The host for which to set the maximum number of duplicate peers.
  - `number`: The maximum number of duplicate peers allowed.

<br /><br />

### `enet_host_set_intercept_callback`

_Sets a callback function for intercepting received packets._

```c
ENET_API void enet_host_set_intercept_callback(ENetHost *host, ENetInterceptCallback callback);
```

- **Parameters:**
  - `host`: The host for which to set the intercept callback.
  - `callback`: The callback function to be used for intercepting packets.

<br /><br />

### `enet_host_set_checksum_callback`

_Sets a callback function for computing packet checksums._

```c
ENET_API void enet_host_set_checksum_callback(ENetHost *host, ENetChecksumCallback callback);
```

- **Parameters:**
  - `host`: The host for which to set the checksum callback.
  - `callback`: The callback function to be used for computing packet checksums.