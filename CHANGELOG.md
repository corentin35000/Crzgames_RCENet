# Changelog



<br /><br /><br ><br /><br /><br /><br ><br />

# ENet :

## [1.3.17](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.3.16...v1.3.17) - 2020-11-15

### 🐛 Bug Fixes

- Fixes for sender getting too far ahead of receiver that can cause instability with reliable packets.

## [1.3.16](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.3.15...v1.3.16) - 2020-09-08

### 🐛 Bug Fixes

- Fix bug in unreliable fragment queuing.
- Use single output queue for reliable and unreliable packets for saner ordering.
- Revert experimental throttle changes that were less stable than prior algorithm.

## [1.3.15](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.3.14...v1.3.15) - 2020-04-20

### 🐛 Bug Fixes

- Quicker RTT initialization.
- Use fractional precision for RTT calculations.
- Fixes for packet throttle with low RTT variance.
- Miscellaneous socket bug fixes.

## [1.3.14](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.3.13...v1.3.14) - 2019-01-27

### 🐛 Bug Fixes

- Bug fix for enet_peer_disconnect_later().
- Use getaddrinfo and getnameinfo where available.
- Miscellaneous cleanups.

## [1.3.13](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.3.12...v1.3.13) - 2015-04-30

### 🚀 Features

- Added premake and cmake support.
- Miscellaneous documentation cleanups.

### 🐛 Bug Fixes

- Miscellaneous bug fixes.

## [1.3.12](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.3.11...v1.3.12) - 2014-04-24

### 🚀 Features

- Added maximumPacketSize and maximumWaitingData fields to ENetHost to limit the amount of data waiting to be delivered on a peer. Beware that the default maximumPacketSize is 32MB and should be set higher if desired as should maximumWaitingData.

## [1.3.11](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.3.10...v1.3.11) - 2013-12-26

### 🐛 Bug Fixes

- Allow an ENetHost to connect to itself.
- Fixed possible bug with disconnect notifications during connect attempts.
- Fixed some preprocessor definition bugs.

## [1.3.10](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.3.9...v1.3.10) - 2013-10-23

### 🚀 Features

- Doubled maximum reliable window size.
- Fixed RCVTIMEO/SNDTIMEO socket options and also added NODELAY.

## [1.3.9](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.3.8...v1.3.9) - 2013-08-19

### 🚀 Features

- Added duplicatePeers option to ENetHost which can limit the number of peers from duplicate IPs.
- Added enet_socket_get_option() and ENET_SOCKOPT_ERROR.
- Added enet_host_random_seed() platform stub.

## [1.3.8](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.3.7...v1.3.8) - 2013-06-02

### 🚀 Features

- Added enet_linked_version() for checking the linked version.
- Added enet_socket_get_address() for querying the local address of a socket.
- Silenced some debugging prints unless ENET_DEBUG is defined during compilation.
- Handle EINTR in enet_socket_wait() so that enet_host_service() doesn't propagate errors from signals.
- Optimized enet_host_bandwidth_throttle() to be less expensive for large numbers of peers.

## [1.3.7](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.3.6...v1.3.7) - 2013-03-06

### 🚀 Features

- Added ENET_PACKET_FLAG_SENT to indicate that a packet is being freed because it has been sent.
- Added userData field to ENetPacket.
- Changed how random seed is generated on Windows to avoid import warnings.

### 🐛 Bug Fixes

- Fixed case where disconnects could be generated with no preceding connect event.

## [1.3.6](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.3.5...v1.3.6) - 2012-12-11

### 🚀 Features

- Added support for intercept callback in ENetHost that can be used to process raw packets before ENet.
- Added enet_socket_shutdown() for issuing shutdown on a socket.

### 🐛 Bug Fixes

- Fixed enet_socket_connect() to not error on non-blocking connects.
- Fixed bug in MTU negotiation during connections.

## [1.3.5](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.3.4...v1.3.5) - 2012-07-31

### 🐛 Bug Fixes

- Fixed bug in unreliable packet fragment queuing.

## [1.3.4](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.3.3...v1.3.4) - 2012-05-29

### 🚀 Features

- Added enet_peer_ping_interval() for configuring per-peer ping intervals.
- Added enet_peer_timeout() for configuring per-peer timeouts.
- Added protocol packet size limits.

## [1.3.3](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.3.2...v1.3.3) - 2011-06-28

### 🐛 Bug Fixes

- Fixed bug with simultaneous disconnects not dispatching events.

## [1.3.2](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.3.1...v1.3.2) - 2011-05-31

### 🚀 Features

- Added support for unreliable packet fragmenting via the packet flag ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT.
- Added check against received port to limit some forms of IP-spoofing.

### 🐛 Bug Fixes

- Fixed regression in unreliable packet queuing.

## [1.3.1](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.3.0...v1.3.1) - 2011-02-10

### 🐛 Bug Fixes

- Fixed bug in tracking of reliable data in transit.
- Reliable data window size now scales with the throttle.
- Fixed bug in fragment length calculation when checksums are used.

## [1.3.0](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.2.5...v1.3.0) - 2010-06-05

### 🚀 Features

- ENet host creation now requires the channel limit to be specified as a parameter.
- ENet host connect now accepts a data parameter which is supplied to the receiving host in the event data field for a connect event.
- Added an adaptive order-2 PPM range coder as a built-in compressor option which can be set with enet_host_compress_with_range_coder().
- Added support for packet compression configurable with a callback.
- Improved session number handling to not rely on the packet checksum field, saving 4 bytes per packet unless the checksum option is used.
- Removed the dependence on the rand callback for session number handling.

## [1.2.5](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.2.4...v1.2.5) - 2011-06-28

### 🐛 Bug Fixes

- Fixed bug with simultaneous disconnects not dispatching events.

## [1.2.4](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.2.3...v1.2.4) - 2011-05-31

### 🐛 Bug Fixes

- Fixed regression in unreliable packet queuing.
- Added check against received port to limit some forms of IP-spoofing.

## [1.2.3](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.2.2...v1.2.3) - 2011-02-10

### 🐛 Bug Fixes

- Fixed bug in tracking reliable data in transit.

## [1.2.2](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.2.1...v1.2.2) - 2010-06-05

### 🚀 Features

- Checksum functionality is now enabled by setting a checksum callback inside ENetHost.
- Added totalSentData, totalSentPackets, totalReceivedData, and totalReceivedPackets counters inside ENetHost for getting usage statistics.
- Added enet_host_channel_limit() for limiting the maximum number of channels allowed by connected peers.
- Now uses dispatch queues for event dispatch rather than potentially unscalable array walking.
- Added no_memory callback that is called when a malloc attempt fails.
- Now uses packed attribute for protocol structures on platforms with strange alignment rules.
- Improved autoconf build system allowing for easier building as a shared library.

## [1.2.1](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.2...v1.2.1) - 2009-11-12

### 🐛 Bug Fixes

- Fixed bug that could cause disconnect events to be dropped.
- Added thin wrapper around select() for portable usage.
- Added ENET_SOCKOPT_REUSEADDR socket option.
- Factored enet_socket_bind()/enet_socket_listen() out of enet_socket_create().
- Added contributed Code::Blocks build file.

## [1.2](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.1...v1.2) - 2008-02-12

### 🐛 Bug Fixes

- Fixed bug in VERIFY_CONNECT acknowledgement that could cause connect attempts to occasionally timeout.
- Fixed acknowledgements to check both the outgoing and sent queues when removing acknowledged packets.
- Fixed accidental bit rot in the MSVC project file.
- Revised sequence number overflow handling to address some possible disconnect bugs.
- Added enet_host_check_events() for getting only local queued events.
- Factored out socket option setting into enet_socket_set_option() so that socket options are now set separately from enet_socket_create().

## [1.1](https://github.com/corentin35000/Crzgames_RCENet/compare/v1.0...v1.1) - 2007-06-06

### 🚀 Features

- Optional CRC32 for those needing a stronger checksum than UDP provides (--enable-crc32 configure option).
- The size of packet headers are halved, reducing overhead when sending small packets.
- Added enet_peer_disconnect_later() that waits till all queued outgoing packets get sent before issuing an actual disconnect.
- FreeCallback field in individual packets for notification of when a packet is about to be freed.
- ENET_PACKET_FLAG_NO_ALLOCATE for supplying pre-allocated data to a packet.
- enet_address_get_host_ip() for printing address numbers.
- Promoted the enet_socket_*() functions to be part of the API.
- A few stability/crash fixes.
