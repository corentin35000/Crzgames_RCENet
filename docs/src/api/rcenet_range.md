
# RCENet Range Coder API Documentation

Welcome to the RCENet Range Coder API documentation. This section offers a comprehensive guide on the usage of range coding within the RCENet library, emphasizing the key functions and their applications in data compression and decompression.

## Overview

The RCENet library includes support for range coding, an efficient form of entropy coding used in data compression. Range coding is particularly effective for compressing data with known probability distributions. This document details the functions available in RCENet to utilize range coding for packet data compression and decompression.

<br /><br />


## Functions

### `enet_range_coder_create`

_Creates a new instance of a range coder for use with compression and decompression operations._

```c
ENET_API void * enet_range_coder_create(void);
```

- **Returns:** A pointer to the newly created range coder instance, or `NULL` on failure.

<br /><br />

### `enet_range_coder_destroy`

_Destroys a previously created range coder instance._

```c
ENET_API void enet_range_coder_destroy(void * context);
```

- **Parameters:**
  - `context`: A pointer to the range coder instance to be destroyed.

<br /><br />

### `enet_range_coder_compress`

_Compresses data using the range coder._

```c
ENET_API size_t enet_range_coder_compress(void * context, const ENetBuffer * buffers, size_t bufferCount, size_t inLimit, enet_uint8 * outData, size_t outLimit);
```

- **Parameters:**
  - `context`: A pointer to the range coder instance.
  - `buffers`: An array of ENetBuffer structures containing the data to compress.
  - `bufferCount`: The number of buffers in the array.
  - `inLimit`: The maximum number of bytes to compress.
  - `outData`: The buffer to store compressed data.
  - `outLimit`: The maximum size of the `outData` buffer.

- **Returns:** The size of the compressed data in bytes, or `0` on failure.

<br /><br />

### `enet_range_coder_decompress`

_Decompresses data that was previously compressed with a range coder._

```c
ENET_API size_t enet_range_coder_decompress(void * context, const enet_uint8 * inData, size_t inLimit, enet_uint8 * outData, size_t outLimit);
```

- **Parameters:**
  - `context`: A pointer to the range coder instance.
  - `inData`: The buffer containing the compressed data.
  - `inLimit`: The size of the `inData` buffer in bytes.
  - `outData`: The buffer to store decompressed data.
  - `outLimit`: The maximum size of the `outData` buffer.

- **Returns:** The size of the decompressed data in bytes, or `0` on failure.

<br /><br />

## Conclusion

The RCENet Range Coder API provides a powerful set of functions for compressing and decompressing data using range coding. By leveraging these functionalities, applications can achieve efficient data transmission, especially when dealing with predictable data patterns. For further details or assistance, refer to the official RCENet documentation or the range coding literature.
