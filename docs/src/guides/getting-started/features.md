# 📋 Features and Architecture

The combined use of UDP and TCP in Cube could have potentially benefited from their respective features, but the resulting mix of protocols still left much to be desired. TCP lacked multiple streams of communication without having to open numerous sockets and complicated packet delineation due to its buffering behavior. UDP lacked sequencing, connection management, bandwidth resource management, and imposed limitations on packet size. Significant investment was required to integrate these two protocols, and the end result was inferior in terms of features and performance compared to the uniform protocol presented by RCENet.

Thus, RCENet aims to solve these issues and provide a single, uniform protocol layered over UDP to developers, incorporating the best features of both UDP and TCP, along with some useful features that neither provides, with a much cleaner integration than any resulting from a mix of UDP and TCP.

## Connection Management

RCENet provides a simple connection interface for communicating with a remote host. The vitality of the connection is actively monitored by sending pings to the remote host at frequent intervals, and it also monitors the network conditions from the local host to the remote host, such as the mean round trip time and packet loss.

## Sequencing

Instead of a single byte stream that complicates packet delineation, RCENet presents connections as multiple, properly sequenced packet streams that simplify the transfer of various types of data.

RCENet ensures sequencing for all packets by assigning a sequence number to each packet sent, incrementing as packets are sent. RCENet guarantees that no packet with a higher sequence number will be delivered before a packet with a lower sequence number, thus ensuring packets are delivered exactly in the order they were sent.

For unreliable packets, RCENet will simply discard the lower sequence number packet if a packet with a higher sequence number has already been delivered. This allows packets to be dispatched immediately upon arrival, and reduces the latency of unreliable packets to an absolute minimum. For reliable packets, if a higher sequence number packet arrives but the preceding packets in the sequence have not yet arrived, RCENet will delay the delivery of the higher sequence number packets until its predecessors have arrived.

## Channels

Since RCENet delays the delivery of reliable packets to ensure proper sequencing, and consequently any packets of higher sequence number whether reliable or not, in the event the reliable packet's predecessors have not yet arrived, this can introduce latency into the delivery of other packets which might not need to be as strictly ordered relative to the packet that delayed their delivery.

To combat this latency and reduce the ordering restrictions on packets, RCENet provides multiple channels of communication over a given connection. Each channel is independently sequenced, so the delivery status of a packet in one channel will not stall the delivery of other packets in another channel.

## Reliability

RCENet ensures optional reliability of packet delivery by ensuring the remote host acknowledges receipt of all reliable packets. RCENet will attempt to resend the packet up to a reasonable number of times, if no acknowledgment of the packet's receipt occurs within a specified timeout. Retry timeouts are progressive and become more lenient with every failed attempt to allow for temporary turbulence in network conditions.

## Fragmentation and Reassembly

RCENet will send and deliver packets regardless of size. Large packets are fragmented into many smaller packets of suitable size and reassembled on the remote host to recover the original packet for delivery. The process is entirely transparent to the developer.

## Aggregation

RCENet aggregates all protocol commands, including acknowledgments and packet transfer, into larger protocol packets to ensure proper utilization of the connection and to limit the opportunities for packet loss that might otherwise result in further delivery latency.

## Adaptability

RCENet provides an in-flight data window for reliable packets to ensure connections are not overwhelmed by volumes of packets. It also provides a static bandwidth allocation mechanism to ensure the total volume of packets sent and received to a host does not exceed the host's capabilities. Furthermore, RCENet also provides a dynamic throttle that responds to deviations from normal network conditions to rectify various types of network congestion by further limiting the volume of packets sent.

## Portability

RCENet works on Windows and any other Unix or Unix-like platform providing a BSD sockets interface. The library has a small and stable code base that can easily be extended to support other platforms and integrates easily. RCENet makes no assumptions about the underlying platform's endianness or word size.