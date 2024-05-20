
# RCENet Time API Documentation

Welcome to the RCENet Time API documentation. This section provides detailed information on managing time within the RCENet library, highlighting functions related to time measurement and management.

## Overview

Time management is crucial in networked applications for tasks such as measuring round-trip times, implementing timeouts, and scheduling events. RCENet provides a simple yet effective set of functions to work with time in a cross-platform manner.

<br /><br />

## Functions

### `enet_time_get`

_Returns the current wall-time in milliseconds._

This function returns the current time as a number of milliseconds. The initial value is unspecified unless set by `enet_time_set`. This can be used for timing operations, implementing timeouts, or measuring intervals.

```c
ENET_API enet_uint32 enet_time_get(void);
```

- **Returns:** The current time in milliseconds.

<br /><br />

### `enet_time_set`

_Sets the current wall-time in milliseconds._

This function allows manually setting the current wall-time, which can be useful in scenarios where synchronized time management is needed across different components of an application.

```c
ENET_API void enet_time_set(enet_uint32 time);
```

- **Parameters:**
  - `time`: The new current time in milliseconds.

<br /><br />

## Conclusion

The RCENet Time API provides essential functionalities for handling time-related tasks in networked applications, offering both time retrieval and setting capabilities. Proper time management is key to achieving efficient communication and ensuring timely execution of network operations.
