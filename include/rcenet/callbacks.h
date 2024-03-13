/** 
 @file  callbacks.h
 @brief ENet callbacks
*/
#ifndef RCENET_CALLBACKS_H
#define RCENET_CALLBACKS_H

#include <stdlib.h>

typedef struct _ENetCallbacks
{
    void * (ENET_CALLBACK * malloc) (size_t size);
    void (ENET_CALLBACK * free) (void * memory);
    void (ENET_CALLBACK * no_memory) (void);
} ENetCallbacks;

/** @defgroup callbacks ENet internal callbacks
    @{
    @ingroup private
*/
extern void * enet_malloc (size_t);
extern void   enet_free (void *);

/** @} */

#endif /* RCENET_CALLBACKS_H */

