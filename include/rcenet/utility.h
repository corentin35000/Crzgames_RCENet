#ifndef RCENET_UTILITY_H
#define RCENET_UTILITY_H

#ifdef __cplusplus
extern "C" {
#endif

#define ENET_MAX(x, y) ((x) > (y) ? (x) : (y))
#define ENET_MIN(x, y) ((x) < (y) ? (x) : (y))
#define ENET_DIFFERENCE(x, y) ((x) < (y) ? (y) - (x) : (x) - (y))

#ifdef __cplusplus
}
#endif

#endif /* RCENET_UTILITY_H */