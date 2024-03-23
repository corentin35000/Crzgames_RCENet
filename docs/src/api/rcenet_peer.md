
# RCENet Peer API Documentation

Welcome to the RCENet Peer API documentation. This section offers an in-depth guide on peer management within RCENet, highlighting key functions, structures, and enumerations essential for peer interaction and management.

## Overview

Peers represent the other endpoints in a networked environment with which a host can communicate. This document covers the functionalities provided by RCENet to manage these peers, including querying peer state, managing connections, and handling data transmission and reception.

<br /><br />


## Structures

### `ENetPeer`

Represents a network peer, a remote endpoint with which data packets can be exchanged.

- **Fields:**
    - `dispatchList`: Internally used for queuing events for this peer.
    - `host`: The host object this peer is associated with.
    - `outgoingPeerID`/`incomingPeerID`: Identifiers used for distinguishing this peer in outgoing/incoming connections.
    - `connectID`: A unique identifier for the connection to this peer.
    - `outgoingSessionID`/`incomingSessionID`: Session identifiers for tracking session changes.
    - `address`: The network address of the peer.
    - `data`: User-defined data associated with the peer, can be used to store application-specific information.
    - `state`: The current state of the peer (e.g., connected, disconnecting, etc.).
    - `channels`: An array of channels over which data is sent and received. Channels provide separate streams of communication.
    - `channelCount`: The number of channels allocated for this peer.
    - `incomingBandwidth`/`outgoingBandwidth`: The configured incoming/outgoing bandwidth limits for this peer.
    - `incomingBandwidthThrottleEpoch`/`outgoingBandwidthThrottleEpoch`: Used internally to manage bandwidth throttling.
    - `incomingDataTotal`/`outgoingDataTotal`: The total amount of incoming/outgoing data since the last reset or initialization.
    - `lastSendTime`/`lastReceiveTime`: Timestamps of the last send/receive operations.
    - `nextTimeout`/`earliestTimeout`: Used internally to manage connection timeouts and retransmissions.
    - `packetLossEpoch`: Used internally for calculating packet loss over time.
    - `packetsSent`/`packetsLost`: Counters for the total number of packets sent and lost.
    - `packetLoss`/`packetLossVariance`: Measures of packet loss ratio and its variance.
    - `packetThrottle`: The current packet throttle value, affecting data transmission rate.
    - `packetThrottleLimit`/`packetThrottleCounter`: Control the throttling mechanism.
    - `packetThrottleEpoch`: Timestamp for the last throttle evaluation.
    - `packetThrottleAcceleration`/`Deceleration`: Controls how quickly the throttle value changes.
    - `packetThrottleInterval`: Time interval for packet throttle evaluations.
    - `pingInterval`: Frequency at which ping messages are sent to keep the connection alive.
    - `timeoutLimit`/`Minimum`/`Maximum`: Configuration for connection timeout thresholds.
    - `lastRoundTripTime`/`lowestRoundTripTime`/`Variance`: Statistics on the round-trip time (RTT) for packets to this peer.
    - `roundTripTime`/`roundTripTimeVariance`: Average RTT and its variance.
    - `mtu`: Maximum transmission unit size, impacting the size of packets sent.
    - `windowSize`: Flow control window size for reliable packet delivery.
    - `reliableDataInTransit`: Amount of reliable data that has been sent but not yet acknowledged.
    - `outgoingReliableSequenceNumber`: Sequence number for the next reliable packet to be sent.
    - `ENetList acknowledgements`: A list of acknowledgements to be sent. This list contains acknowledgements for packets that have been received and acknowledged by this peer.
    - `ENetList sentReliableCommands`: A list of reliable commands that have been sent but not yet acknowledged. This ensures reliable delivery of packets.
    - `ENetList outgoingSendReliableCommands`: A list of reliable commands that are ready to be sent. These commands are queued for sending in a reliable manner.
    - `ENetList outgoingCommands`: A list of commands that are ready to be sent, including both reliable and unreliable commands.
    - `ENetList dispatchedCommands`: A list of commands that have been dispatched. This list is used for managing commands that have been processed and are awaiting further action, such as acknowledgement.
    - `enet_uint16 flags`: Flags for behavior control of the peer. This includes flags like `ENET_PEER_FLAG_NEEDS_DISPATCH` and `ENET_PEER_FLAG_CONTINUE_SENDING`, which control the peer's behavior regarding message dispatch and sending packets.
    - `enet_uint16 reserved`: A reserved field for future use, ensuring compatibility with future versions of the protocol or library extensions.
    - `enet_uint16 incomingUnsequencedGroup`: Used to track incoming unsequenced packets. This field is part of managing packets that are sent without a specific order.
    - `enet_uint16 outgoingUnsequencedGroup`: Similar to the incoming unsequenced group but for outgoing packets. It tracks the group number for unsequenced packets that are sent.
    - `enet_uint32 unsequencedWindow[ENET_PEER_UNSEQUENCED_WINDOW_SIZE / 32]`: A window used to track received unsequenced packets. This array helps in managing and filtering out duplicate unsequenced packets that may be received.
    - `enet_uint32 eventData`: This field is used to store custom event data that can be associated with specific actions or triggers in the network communication.
    - `size_t totalWaitingData`: Represents the total amount of data that is waiting to be sent to this peer. This includes all queued packets and commands that have not yet been transmitted.

```c
typedef struct _ENetPeer { 
   ENetListNode dispatchList;
   struct _ENetHost * host;
   enet_uint16 outgoingPeerID;
   enet_uint16 incomingPeerID;
   enet_uint32 connectID;
   enet_uint8 outgoingSessionID;
   enet_uint8 incomingSessionID;
   ENetAddress address;
   void * data;
   ENetPeerState state;
   ENetChannel * channels;
   size_t channelCount;
   enet_uint32 incomingBandwidth;
   enet_uint32 outgoingBandwidth;
   enet_uint32 incomingBandwidthThrottleEpoch;
   enet_uint32 outgoingBandwidthThrottleEpoch;
   enet_uint32 incomingDataTotal;
   enet_uint32 outgoingDataTotal;
   enet_uint32 lastSendTime;
   enet_uint32 lastReceiveTime;
   enet_uint32 nextTimeout;
   enet_uint32 earliestTimeout;
   enet_uint32 packetLossEpoch;
   enet_uint32 packetsSent;
   enet_uint32 packetsLost;
   enet_uint32 packetLoss;
   enet_uint32 packetLossVariance;
   enet_uint32 packetThrottle;
   enet_uint32 packetThrottleLimit;
   enet_uint32 packetThrottleCounter;
   enet_uint32 packetThrottleEpoch;
   enet_uint32 packetThrottleAcceleration;
   enet_uint32 packetThrottleDeceleration;
   enet_uint32 packetThrottleInterval;
   enet_uint32 pingInterval;
   enet_uint32 timeoutLimit;
   enet_uint32 timeoutMinimum;
   enet_uint32 timeoutMaximum;
   enet_uint32 lastRoundTripTime;
   enet_uint32 lowestRoundTripTime;
   enet_uint32 lastRoundTripTimeVariance;
   enet_uint32 highestRoundTripTimeVariance;
   enet_uint32 roundTripTime;
   enet_uint32 roundTripTimeVariance;
   enet_uint32 mtu;
   enet_uint32 windowSize;
   enet_uint32 reliableDataInTransit;
   enet_uint16 outgoingReliableSequenceNumber;
   ENetList      acknowledgements;
   ENetList      sentReliableCommands;
   ENetList      outgoingSendReliableCommands;
   ENetList      outgoingCommands;
   ENetList      dispatchedCommands;
   enet_uint16   flags;
   enet_uint16   reserved;
   enet_uint16   incomingUnsequencedGroup;
   enet_uint16   outgoingUnsequencedGroup;
   enet_uint32   unsequencedWindow [ENET_PEER_UNSEQUENCED_WINDOW_SIZE / 32]; 
   enet_uint32   eventData;
   size_t        totalWaitingData;
} ENetPeer;
```

This section covers the initial set of fields in the `ENetPeer` structure. The subsequent parts will delve into the remaining fields, explaining their purposes and how they contribute to the management of network peers.

<br /><br />

### `ENetAcknowledgement`

Represents an acknowledgement in ENet, sent to confirm the receipt of a packet.

- **Fields:**
    - `acknowledgementList`: Node in the list of acknowledgements.
    - `sentTime`: The time when the corresponding packet was sent.
    - `command`: The protocol command sent as an acknowledgement.

```c
typedef struct _ENetAcknowledgement {
   ENetListNode acknowledgementList;
   enet_uint32  sentTime;
   ENetProtocol command;
} ENetAcknowledgement;
```

<br /><br />

### `ENetOutgoingCommand`

Represents an outgoing command in ENet, a packet or action to be sent to a peer.

- **Fields:**
    - `outgoingCommandList`: Node in the list of outgoing commands.
    - `reliableSequenceNumber`: Reliable sequence number for tracking packets.
    - `unreliableSequenceNumber`: Unreliable sequence number for tracking packets.
    - `sentTime`: The time when the command was sent.
    - `roundTripTimeout`: Timeout before considering the command lost.
    - `queueTime`: Time before the command is queued for sending.
    - `fragmentOffset`: Offset of the fragment in the packet, if the command is fragmented.
    - `fragmentLength`: Length of the command's fragment.
    - `sendAttempts`: Number of attempts to send the command.
    - `command`: The protocol command to be sent.
    - `packet`: The packet associated with the command, if any.

```c
typedef struct _ENetOutgoingCommand {
   ENetListNode outgoingCommandList;
   enet_uint16  reliableSequenceNumber;
   enet_uint16  unreliableSequenceNumber;
   enet_uint32  sentTime;
   enet_uint32  roundTripTimeout;
   enet_uint32  queueTime;
   enet_uint32  fragmentOffset;
   enet_uint16  fragmentLength;
   enet_uint16  sendAttempts;
   ENetProtocol command;
   ENetPacket * packet;
} ENetOutgoingCommand;
```

<br /><br />

### `ENetIncomingCommand`

Represents an incoming command in ENet, data or actions received from a peer.

- **Fields:**
    - `incomingCommandList`: Node in the list of incoming commands.
    - `reliableSequenceNumber`: Reliable sequence number for tracking packets.
    - `unreliableSequenceNumber`: Unreliable sequence number for tracking packets.
    - `command`: The received protocol command.
    - `fragmentCount`: Total number of fragments for this packet.
    - `fragmentsRemaining`: Number of remaining fragments to receive.
    - `fragments`: Bitfield for tracking received fragments.
    - `packet`: The packet associated with the command, once all fragments are received.

```c
typedef struct _ENetIncomingCommand {
   ENetListNode     incomingCommandList;
   enet_uint16      reliableSequenceNumber;
   enet_uint16      unreliableSequenceNumber;
   ENetProtocol     command;
   enet_uint32      fragmentCount;
   enet_uint32      fragmentsRemaining;
   enet_uint32 *    fragments;
   ENetPacket *     packet;
} ENetIncomingCommand;
```

<br /><br />


## Enumerations

### `_ENetPeerFlag`

Flags controlling peer state and behavior:

- `ENET_PEER_FLAG_NEEDS_DISPATCH`: Indicates that the peer has pending messages that need to be dispatched.
- `ENET_PEER_FLAG_CONTINUE_SENDING`: Allows the peer to continue sending packets even if the bandwidth limit has been reached.

```c
typedef enum _ENetPeerFlag {
   ENET_PEER_FLAG_NEEDS_DISPATCH   = (1 << 0),
   ENET_PEER_FLAG_CONTINUE_SENDING = (1 << 1)
} ENetPeerFlag;
```

<br /><br />

### `ENetPeerState`

Enumerates the possible states of a peer in ENet. These states represent the lifecycle of a peer's connection to the ENet network.

- **States:**
  - `ENET_PEER_STATE_DISCONNECTED`: The peer is disconnected.
  - `ENET_PEER_STATE_CONNECTING`: The peer is in the process of connecting.
  - `ENET_PEER_STATE_ACKNOWLEDGING_CONNECT`: The peer is acknowledging the connection.
  - `ENET_PEER_STATE_CONNECTION_PENDING`: The peer's connection is pending.
  - `ENET_PEER_STATE_CONNECTION_SUCCEEDED`: The peer's connection succeeded.
  - `ENET_PEER_STATE_CONNECTED`: The peer is connected.
  - `ENET_PEER_STATE_DISCONNECT_LATER`: The peer will be disconnected later.
  - `ENET_PEER_STATE_DISCONNECTING`: The peer is disconnecting.
  - `ENET_PEER_STATE_ACKNOWLEDGING_DISCONNECT`: The peer is acknowledging disconnection.
  - `ENET_PEER_STATE_ZOMBIE`: The peer is in a zombie state, waiting for cleanup.

```c
typedef enum _ENetPeerState
{
   ENET_PEER_STATE_DISCONNECTED                = 0,
   ENET_PEER_STATE_CONNECTING                  = 1,
   ENET_PEER_STATE_ACKNOWLEDGING_CONNECT       = 2,
   ENET_PEER_STATE_CONNECTION_PENDING          = 3,
   ENET_PEER_STATE_CONNECTION_SUCCEEDED        = 4,
   ENET_PEER_STATE_CONNECTED                   = 5,
   ENET_PEER_STATE_DISCONNECT_LATER            = 6,
   ENET_PEER_STATE_DISCONNECTING               = 7,
   ENET_PEER_STATE_ACKNOWLEDGING_DISCONNECT    = 8,
   ENET_PEER_STATE_ZOMBIE                      = 9 
} ENetPeerState;
```

<br /><br />


## Functions

### Peer Management

### `enet_peer_get_id`

_Retrieves the unique identifier of a peer._

```c
ENET_API enet_uint32 enet_peer_get_id(const ENetPeer *peer);
```

- **Parameters:**
  - `peer`: Pointer to the peer whose ID is being retrieved.
- **Returns:** The unique identifier for the peer.

<br /><br />

### `enet_peer_get_ip`

_Retrieves the IP address of a peer._

```c
ENET_API int enet_peer_get_ip(const ENetPeer *peer, char *ip, size_t ipLength);
```

- **Parameters:**
  - `peer`: Pointer to the peer whose IP address is being retrieved.
  - `ip`: Buffer where the IP address will be stored.
  - `ipLength`: Length of the `ip` buffer.
- **Returns:** `0` on success, `< 0` on failure.

<br /><br />

### `enet_peer_get_port`

_Retrieves the port number of a peer._

```c
ENET_API enet_uint16 enet_peer_get_port(const ENetPeer *peer);
```

- **Parameters:**
  - `peer`: Pointer to the peer whose port number is being retrieved.
- **Returns:** The port number of the peer.

<br /><br />

### `enet_peer_get_mtu`

_Retrieves the Maximum Transmission Unit (MTU) size of a peer._

```c
ENET_API enet_uint32 enet_peer_get_mtu(const ENetPeer *peer);
```

- **Parameters:**
  - `peer`: Pointer to the peer whose MTU size is being retrieved.
- **Returns:** The MTU size of the peer.

<br /><br />

### `enet_peer_get_state`

_Retrieves the current state of a peer._

```c
ENET_API ENetPeerState enet_peer_get_state(const ENetPeer *peer);
```

- **Parameters:**
  - `peer`: Pointer to the peer whose state is being retrieved.
- **Returns:** The current state of the peer, as an `ENetPeerState` enum value.

<br /><br />

### `enet_peer_get_rtt`

_Retrieves the round-trip time (RTT) to a peer._

```c
ENET_API enet_uint32 enet_peer_get_rtt(const ENetPeer *peer);
```

- **Parameters:**
  - `peer`: Pointer to the peer whose RTT is being retrieved.
- **Returns:** The RTT to the peer in milliseconds.

<br /><br />

### `enet_peer_get_last_rtt`

_Retrieves the last calculated Round-Trip Time (RTT) to a peer._

```c
ENET_API enet_uint32 enet_peer_get_last_rtt(const ENetPeer *peer);
```

- **Parameters:**
  - `peer`: Pointer to the peer whose last RTT is being retrieved.
- **Returns:** The last calculated RTT to the peer in milliseconds.

<br /><br />

### `enet_peer_get_lastsendtime`

_Retrieves the last time a packet was sent to a peer._

```c
ENET_API enet_uint32 enet_peer_get_lastsendtime(const ENetPeer *peer);
```

- **Parameters:**
  - `peer`: Pointer to the peer.
- **Returns:** The timestamp of the last packet sent to the peer.

<br /><br />

### `enet_peer_get_lastreceivetime`

_Retrieves the last time a packet was received from a peer._

```c
ENET_API enet_uint32 enet_peer_get_lastreceivetime(const ENetPeer *peer);
```

- **Parameters:**
  - `peer`: Pointer to the peer.
- **Returns:** The timestamp of the last packet received from the peer.

<br /><br />

### `enet_peer_get_packets_throttle`

_Retrieves the packet throttle value for a peer._

```c
ENET_API float enet_peer_get_packets_throttle(const ENetPeer *peer);
```

- **Parameters:**
  - `peer`: Pointer to the peer whose packet throttle value is being retrieved.
- **Returns:** The packet throttle value of the peer.

<br /><br />

### `enet_peer_get_data`

_Retrieves user-defined data associated with a peer._

```c
ENET_API void * enet_peer_get_data(const ENetPeer *peer);
```

- **Parameters:**
  - `peer`: Pointer to the peer from which to retrieve the user data.
- **Returns:** A pointer to the user-defined data associated with the peer.

<br /><br />

### `enet_peer_set_data`

_Associates user-defined data with a peer._

```c
ENET_API void enet_peer_set_data(ENetPeer *peer, void *data);
```

- **Parameters:**
  - `peer`: Pointer to the peer with which to associate the user data.
  - `data`: Pointer to the user-defined data to associate with the peer.

<br /><br />

### Data Transmission and Reception

### `enet_peer_send`

_Sends a packet to a specific peer._

```c
ENET_API int enet_peer_send(ENetPeer *peer, enet_uint8 channelID, ENetPacket *packet);
```

- **Parameters:**
  - `peer`: The target peer to which the packet will be sent.
  - `channelID`: The channel ID on which to send the packet.
  - `packet`: The packet to send.
- **Returns:** `0` on success, `< 0` on failure.

<br /><br />

### `enet_peer_receive`

_Receives the next packet from a specific peer, if available._

```c
ENET_API ENetPacket *enet_peer_receive(ENetPeer *peer, enet_uint8 *channelID);
```

- **Parameters:**
  - `peer`: The peer from which to receive the packet.
  - `channelID`: A pointer to an `enet_uint8` where the channel ID of the received packet will be stored.
- **Returns:** A pointer to the received `ENetPacket`, or `NULL` if no packet is available.

<br /><br />

### `enet_peer_ping`

_Sends a ping to a peer._

```c
ENET_API void enet_peer_ping(ENetPeer *peer);
```

- **Parameters:**
  - `peer`: The peer to ping.
- **Remarks:** This function can be used to measure the round-trip time or to keep the connection alive.

<br /><br />

### `enet_peer_ping_interval`

_Sets the interval at which pings are sent to a peer automatically._

```c
ENET_API void enet_peer_ping_interval(ENetPeer *peer, enet_uint32 interval);
```

- **Parameters:**
  - `peer`: The peer for which to set the ping interval.
  - `interval`: The ping interval in milliseconds.
- **Remarks:** Useful for configuring the keepalive behavior of connections.

<br /><br />

### `enet_peer_timeout`

_Sets the timeout limits for a peer._

```c
ENET_API void enet_peer_timeout(ENetPeer *peer, enet_uint32 timeoutLimit, enet_uint32 timeoutMinimum, enet_uint32 timeoutMaximum);
```

- **Parameters:**
  - `peer`: The peer for which to set the timeout limits.
  - `timeoutLimit`: The limit after which the connection is considered timed out.
  - `timeoutMinimum`: The minimum timeout limit.
  - `timeoutMaximum`: The maximum timeout limit.

<br /><br />

### `enet_peer_reset`

_Resets a peer to its initial state._

```c
ENET_API void enet_peer_reset(ENetPeer *peer);
```

- **Parameters:**
  - `peer`: The peer to reset.
- **Remarks:** This function is typically used to quickly reuse a peer object for a new connection.

<br /><br />

### `enet_peer_disconnect`

_Initiates a graceful disconnection from a peer._

```c
ENET_API void enet_peer_disconnect(ENetPeer *peer, enet_uint32 data);
```

- **Parameters:**
  - `peer`: The peer to disconnect.
  - `data`: An optional user-specified data value that can be retrieved by the peer being disconnected.

<br /><br />

### `enet_peer_disconnect_now`

_Immediately disconnects a peer without waiting for any pending transmissions to complete._

```c
ENET_API void enet_peer_disconnect_now(ENetPeer *peer, enet_uint32 data);
```

- **Parameters:**
  - `peer`: The peer to disconnect immediately.
  - `data`: An optional user-specified data value that can be retrieved by the peer being disconnected.

<br /><br />

### `enet_peer_disconnect_later`

_Schedules a disconnection from a peer to occur after all sent packets have been delivered._

```c
ENET_API void enet_peer_disconnect_later(ENetPeer *peer, enet_uint32 data);
```

- **Parameters:**
  - `peer`: The peer to disconnect later.
  - `data`: An optional user-specified data value that can be retrieved by the peer being disconnected.

<br /><br />

### `enet_peer_throttle_configure`

_Configures packet throttle settings for a peer._

```c
ENET_API void enet_peer_throttle_configure(ENetPeer *peer, enet_uint32 interval, enet_uint32 acceleration, enet_uint32 deceleration);
```

- **Parameters:**
  - `peer`: The peer for which to configure throttle settings.
  - `interval`: The time window over which the throttle conditions are measured.
  - `acceleration`: The rate at which the packet throttle value is increased when conditions allow.
  - `deceleration`: The rate at which the packet throttle value is decreased when conditions require.

<br /><br />

### `enet_peer_reset_queues`

_Resets the packet queues for a peer._

```c
extern void enet_peer_reset_queues(ENetPeer *peer);
```

- **Description**: This function clears all packet queues associated with the peer, effectively resetting its communication state.
- **Parameters**:
  - `peer`: Pointer to the peer whose packet queues are to be reset.

<br /><br />

### `enet_peer_has_outgoing_commands`

_Checks if there are outgoing commands that need to be sent to a peer._

```c
extern int enet_peer_has_outgoing_commands(ENetPeer *peer);
```

- **Description**: Determines whether there are any commands in the outgoing queue that have not yet been sent to the peer. This is useful for deciding whether to flush the host or continue accumulating commands.
- **Parameters**:
  - `peer`: Pointer to the peer being checked for outgoing commands.
- **Returns**: `1` if there are outgoing commands, `0` otherwise.

<br /><br />

### `enet_peer_setup_outgoing_command`

_Prepare an outgoing command to be sent to a peer._

```c
extern void enet_peer_setup_outgoing_command (ENetPeer *peer, ENetOutgoingCommand *command);
```

- **Parameters:**
  - `peer`: The peer to which the command is to be sent.
  - `command`: The outgoing command to be set up.

- **Example Usage:**
  ```c
  ENetOutgoingCommand command;
  // Initialize command...
  enet_peer_setup_outgoing_command(peer, &command);
  ```

<br /><br />

### `enet_peer_queue_outgoing_command`

_Queue an outgoing command for transmission to a peer._

```c
extern ENetOutgoingCommand * enet_peer_queue_outgoing_command (ENetPeer *peer, const ENetProtocol *protocol, ENetPacket *packet, enet_uint32 offset, enet_uint16 length);
```

- **Parameters:**
  - `peer`: The peer to which the command will be sent.
  - `protocol`: The protocol command to be sent.
  - `packet`: The packet to be sent with the command.
  - `offset`: The offset within the packet where the command starts.
  - `length`: The length of the command data.

- **Example Usage:**
  ```c
  ENetPacket *packet = enet_packet_create(data, length, ENET_PACKET_FLAG_RELIABLE);
  enet_peer_queue_outgoing_command(peer, &protocol, packet, 0, packet->dataLength);
  ```

<br /><br />

### `enet_peer_queue_incoming_command`

_Queue an incoming command received from a peer._

```c
extern ENetIncomingCommand * enet_peer_queue_incoming_command (ENetPeer *peer, const ENetProtocol *protocol, const void *data, size_t dataLength, enet_uint32 flags, enet_uint32 fragmentCount);
```

- **Parameters:**
  - `peer`: The peer from which the command was received.
  - `protocol`: The protocol command received.
  - `data`: The command data received.
  - `dataLength`: The length of the command data.
  - `flags`: The flags associated with the incoming command.
  - `fragmentCount`: The number of fragments for the command.

- **Example Usage:**
  ```c
  enet_peer_queue_incoming_command(peer, &protocol, receivedData, dataLength, flags, fragmentCount);
  ```

<br /><br />

### `enet_peer_queue_acknowledgement`

_Queue an acknowledgement for a received command._

```c
extern ENetAcknowledgement * enet_peer_queue_acknowledgement (ENetPeer *peer, const ENetProtocol *protocol, enet_uint16 sentTime);
```

- **Parameters:**
  - `peer`: The peer for which the acknowledgement is being queued.
  - `protocol`: The protocol command being acknowledged.
  - `sentTime`: The time the command was sent.

- **Example Usage:**
  ```c
  enet_peer_queue_acknowledgement(peer, &protocol, sentTime);
  ```

<br /><br />

### `enet_peer_dispatch_incoming_unreliable_commands`

_Dispatch all incoming unreliable commands for a peer._

```c
extern void enet_peer_dispatch_incoming_unreliable_commands (ENetPeer *peer, ENetChannel *channel, ENetIncomingCommand *command);
```

- **Parameters:**
  - `peer`: The peer for which the commands are being dispatched.
  - `channel`: The channel on which the commands were received.
  - `command`: The first command in the queue of incoming unreliable commands.

- **Example Usage:**
  ```c
  enet_peer_dispatch_incoming_unreliable_commands(peer, &channel, &command);
  ```

<br /><br />

### `enet_peer_dispatch_incoming_reliable_commands`

_Dispatch all incoming reliable commands for a peer._

```c
extern void enet_peer_dispatch_incoming_reliable_commands (ENetPeer *peer, ENetChannel *channel, ENetIncomingCommand *command);
```

- **Parameters:**
  - `peer`: The peer for which the commands are being dispatched.
  - `channel`: The channel on which the commands were received.
  - `command`: The first command in the queue of incoming reliable commands.

- **Example Usage:**
  ```c
  enet_peer_dispatch_incoming_reliable_commands(peer, &channel, &command);
  ```

<br /><br />

#### `enet_peer_on_connect`

_Handles the event of a peer connecting._

```c
extern void enet_peer_on_connect(ENetPeer *peer);
```

- **Description**: This function is called when a peer successfully connects. It is responsible for initializing any state specific to the new connection.
- **Parameters**:
  - `peer`: Pointer to the peer that has just connected.

<br /><br />

#### `enet_peer_on_disconnect`

_Handles the event of a peer disconnecting._

```c
extern void enet_peer_on_disconnect(ENetPeer *peer);
```

- **Description**: Invoked when a peer disconnects or is disconnected. It cleans up the peer's state and prepares it for potential re-use.
- **Parameters**:
  - `peer`: Pointer to the peer that is disconnecting.