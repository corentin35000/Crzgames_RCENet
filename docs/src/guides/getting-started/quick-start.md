# 🚀 Quick Start

This guide will help you set up a basic project structure.

## 📂 Project Structure

- `client.c`
- `server.c`

### client.c

::: details Click me to view the code
```c
#include <rcenet/enet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    enet_uint32 key;
    int enabled;
} encryption_context;

/* Very simple byte rotation algorithm, of course for encryption you should consider a serious algorithm like xchacha20 */
size_t simple_encrypt(void* context, ENetPeer* peer, const ENetBuffer* inBuffers, size_t inBufferCount, size_t inLimit, enet_uint8* outData, size_t outLimit)
{
    size_t i, j;
    encryption_context* encryptionContext = (encryption_context*) context;

    /* Wait until server sends us an encrypted message before enabling encryption */
    if (!encryptionContext->enabled)
        return 0;

    for (i = 0; i < inBufferCount; ++i)
    {
        const enet_uint8* src = (const enet_uint8*)inBuffers[i].data;
        for (j = 0; j < inBuffers[i].dataLength; ++j)
            *outData++ = (enet_uint8) (src[j] + encryptionContext->key);
    }

    return inLimit;
}

size_t simple_decrypt(void* context, ENetPeer* peer, const enet_uint8* inData, size_t inLimit, enet_uint8* outData, size_t outLimit)
{
    size_t i, j;
    encryption_context* encryptionContext = (encryption_context*)context;
    encryptionContext->enabled = 1;

    for (i = 0; i < inLimit; ++i)
        *outData++ = (enet_uint8)(inData[i] - encryptionContext->key);

    return inLimit;
}

int main(int argc, char **argv)
{
    ENetAddress address;
    ENetHost* clientHost;
    ENetPeer* serverPeer;
    ENetEvent event;
    int eventStatus;
    char message[1024];
    char addressBuffer[ENET_ADDRESS_MAX_LENGTH];
    encryption_context encryptionContext = { 0, 0 };
    ENetEncryptor encryptor = {
        &encryptionContext,
        simple_encrypt,
        simple_decrypt,
        NULL
    };

    srand(time(NULL));
    encryptionContext.key = rand();

    /* Initialize enet6 */
    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occured while initializing ENet6.\n");
        return EXIT_FAILURE;
    }

    atexit(enet_deinitialize);

    /* Build an IPv6 or IPv4 address, depending on what the domain resolves to */
    enet_address_set_host(&address, ENET_ADDRESS_TYPE_ANY, "localhost");
    address.port = 1234;

    enet_address_get_host_ip(&address, addressBuffer, ENET_ADDRESS_MAX_LENGTH);
    printf("Connecting to %s...\n", addressBuffer);

    /* Create a non-listening host using enet_host_create */
    /* Note we create a host using the same address family we resolved earlier */
    clientHost = enet_host_create(address.type, NULL, 1, 255, 0, 0);
    if (clientHost == NULL)
    {
        fprintf(stderr, "An error occured while trying to create an ENet6 server host\n");
        exit(EXIT_FAILURE);
    }

    /* Enable ENet builtin compressor */
    enet_host_compress_with_range_coder(clientHost);

    /* Also enable builtin CRC32 checksum */
    enet_host_set_checksum_callback(clientHost, enet_crc32);

    /* Enables encryption after connection succeeded */
    enet_host_encrypt(clientHost, &encryptor);

    /* Connect and send our key */
    serverPeer = enet_host_connect(clientHost, &address, 2, encryptionContext.key);
    if (serverPeer == NULL)
    {
        fprintf(stderr, "No available peers for initializing an ENet connection");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        eventStatus = enet_host_service(clientHost, &event, 100);

        /* Inspect events */
        if (eventStatus > 0)
        {
            switch(event.type)
            {
                case ENET_EVENT_TYPE_CONNECT:
                    printf("(Client) Connected to server %s\n", addressBuffer);
                    break;

                case ENET_EVENT_TYPE_RECEIVE:
                    printf("(Client) Message from server: %s\n", event.packet->data);
                    enet_packet_destroy(event.packet);
                    break;

                case ENET_EVENT_TYPE_DISCONNECT:
                    printf("(Client) Disconnected from server.\n");
                    return EXIT_SUCCESS;
            }
        }
        else if (serverPeer->state == ENET_PEER_STATE_CONNECTED)
        {
            /* Prompt some message to send to the server, be quick to prevent timeout (TODO: Read asynchronously) */
            printf("> ");
            fgets(message, sizeof(message), stdin);

            if (strlen(message) > 0)
            {
                /* Build a packet passing our bytes, length and flags (reliable means this packet will be resent if lost) */
                ENetPacket* packet = enet_packet_create(message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);
                /* Send the packet to the server on channel 0 */
                enet_peer_send(serverPeer, 0, packet);
            }
        }
    }
}
```
:::

### server.c

::: details Click me to view the code
```c
#include <rcenet/enet.h>
#include <stdio.h>

typedef struct
{
    enet_uint32 key;
} encryption_data;

/* Very simple byte rotation algorithm, of course for encryption you should consider a serious algorithm like xchacha20 */
size_t simple_encrypt(void* context, ENetPeer* peer, const ENetBuffer* inBuffers, size_t inBufferCount, size_t inLimit, enet_uint8* outData, size_t outLimit)
{
    size_t i, j;
    encryption_data* peerData;

    /* get per-peer key */
    peerData = (encryption_data*) peer->data;

    /* if encryption has not yet been enabled, stop here */
    if (!peerData)
        return 0;

    for (i = 0; i < inBufferCount; ++i)
    {
        const enet_uint8* src = (const enet_uint8*) inBuffers[i].data;
        for (j = 0; j < inBuffers[i].dataLength; ++j)
            *outData++ = (enet_uint8) (src[j] + peerData->key);
    }

    return inLimit;
}

size_t simple_decrypt(void* context, ENetPeer* peer, const enet_uint8* inData, size_t inLimit, enet_uint8* outData, size_t outLimit)
{
    size_t i;
    encryption_data* peerData;

    /* a NULL peer can happen on connection requests */
    if (!peer)
        return 0;

    peerData = (encryption_data*) peer->data;
    if (!peerData)
        return 0;

    for (i = 0; i < inLimit; ++i)
        *outData++ = (enet_uint8) (inData[i] - peerData->key);

    return inLimit;
}

static ENetEncryptor encryptor = {
    &encryptor, /* can't be null but irrelevant here */
    simple_encrypt,
    simple_decrypt,
    NULL
};

int main(int argc, char **argv)
{
    ENetAddress address;
    ENetHost* serverHost;
    ENetEvent event;
    int eventStatus;
    char addressBuffer[ENET_ADDRESS_MAX_LENGTH];

    /* Initialize enet6 */
    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occured while initializing ENet6.\n");
        return EXIT_FAILURE;
    }

    atexit(enet_deinitialize);

    /* Build the listen address (any + port) */
    enet_address_build_any(&address, ENET_ADDRESS_TYPE_IPV6);
    address.port = 1234;

    /* Create a host using enet_host_create, address type has to match the address,  */
    /* except for the combination IPv6 + Any which enables dual stack (IPv6 socket allowing IPv4 connection)  */
    serverHost = enet_host_create(ENET_ADDRESS_TYPE_ANY, &address, 32, 255, 0, 0);
    if (serverHost == NULL)
    {
        fprintf(stderr, "An error occured while trying to create an ENet6 server host\n");
        exit(EXIT_FAILURE);
    }

    /* Enable ENet builtin compressor */
    enet_host_compress_with_range_coder(serverHost);

    /* Also enable builtin CRC32 checksum */
    enet_host_set_checksum_callback(serverHost, enet_crc32);

    /* Enables encryption */
    enet_host_encrypt(serverHost, &encryptor);

    /* Connect and user service */
    eventStatus = 1;

    while (1)
    {
        eventStatus = enet_host_service(serverHost, &event, 100);

        /* If we had some event that interested us */
        if (eventStatus > 0)
        {
            switch (event.type)
            {
                case ENET_EVENT_TYPE_CONNECT:
                {
                    encryption_data* peerData;

                    enet_address_get_host_ip(&event.peer->address, addressBuffer, ENET_ADDRESS_MAX_LENGTH);
                    printf("(Server) We got a new connection from %s using %u as encryption key\n", addressBuffer, event.data);

                    peerData = (encryption_data*) malloc(sizeof(encryption_data));
                    peerData->key = event.data;

                    event.peer->data = peerData;
                    break;
                }

                case ENET_EVENT_TYPE_RECEIVE:
                    printf("(Server) Message from client : %s\n", event.packet->data);
                    /* Re-send the message to all clients */
                    enet_host_broadcast(serverHost, 0, event.packet);
                    break;

                case ENET_EVENT_TYPE_DISCONNECT:
                case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
                {
                    enet_address_get_host_ip(&event.peer->address, addressBuffer, ENET_ADDRESS_MAX_LENGTH);
                    printf("Client %s disconnected%s.\n", addressBuffer, (event.type == ENET_EVENT_TYPE_DISCONNECT_TIMEOUT) ? " (timeout)" : "");
                    free(event.peer->data);
                    break;
                }
            }
        }
    }
}
```