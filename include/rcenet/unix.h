/** 
 * @file  unix.h
 * @brief Entête spécifique à Unix pour ENet.
 *
 * Ce fichier configure ENet pour l'utilisation dans des environnements Unix en incluant
 * les en-têtes nécessaires pour la programmation réseau et en définissant des types et macros
 * adaptés au système d'exploitation Unix.
 */

#ifndef RCENET_UNIX_H
#define RCENET_UNIX_H

#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

/**
 * Définit la taille maximale du buffer en fonction de la constante système MSG_MAXIOVLEN si disponible.
 * MSG_MAXIOVLEN représente le nombre maximal d'éléments dans un vecteur I/O pour les opérations d'entrée/sortie vecteurisées.
 */
#ifdef MSG_MAXIOVLEN
#define ENET_BUFFER_MAXIMUM MSG_MAXIOVLEN
#endif

/**
 * Type représentant un socket dans ENet. Les sockets sont des points de communication utilisés pour envoyer ou recevoir des paquets de données.
 */
typedef int ENetSocket;

/**
 * Valeur spéciale pour un socket invalide ou fermé.
 */
#define ENET_SOCKET_NULL -1

/**
 * Macro convertissant une valeur de 16 bits de l'ordre des octets hôte en ordre des octets réseau.
 */
#define ENET_HOST_TO_NET_16(value) (htons (value))

/**
 * Macro convertissant une valeur de 32 bits de l'ordre des octets hôte en ordre des octets réseau.
 */
#define ENET_HOST_TO_NET_32(value) (htonl (value))

/**
 * Macro convertissant une valeur de 16 bits de l'ordre des octets réseau en ordre des octets hôte.
 */
#define ENET_NET_TO_HOST_16(value) (ntohs (value))

/**
 * Macro convertissant une valeur de 32 bits de l'ordre des octets réseau en ordre des octets hôte.
 */
#define ENET_NET_TO_HOST_32(value) (ntohl (value))

/**
 * Structure pour la gestion des buffers de données. Utilisée pour encapsuler les données envoyées ou reçues via le réseau.
 * @property {void *} data - Pointeur vers les données.
 * @property {size_t} dataLength - Longueur des données en octets.
 */
typedef struct
{
    void * data;      
    size_t dataLength;
} ENetBuffer;

/**
 * Macro utilisée pour la compatibilité et potentiellement pour des callbacks futurs.
 */
#define ENET_CALLBACK

/**
 * Définit l'API d'ENet comme externe, permettant l'exportation des fonctions pour une utilisation hors de la bibliothèque.
 */
#define ENET_API extern

/**
 * Type représentant un ensemble de sockets pour les opérations de sélection.
 */
typedef fd_set ENetSocketSet;

/**
 * Vide un ensemble de sockets.
 */
#define ENET_SOCKETSET_EMPTY(sockset)          FD_ZERO(& (sockset))

/**
 * Ajoute un socket à un ensemble de sockets.
 */
#define ENET_SOCKETSET_ADD(sockset, socket)    FD_SET(socket, & (sockset))

/**
 * Retire un socket d'un ensemble de sockets.
 */
#define ENET_SOCKETSET_REMOVE(sockset, socket) FD_CLR(socket, & (sockset))

/**
 * Vérifie si un socket est dans un ensemble de sockets.
 */
#define ENET_SOCKETSET_CHECK(sockset, socket)  FD_ISSET(socket, & (sockset))
    
#endif // RCENET_UNIX_H