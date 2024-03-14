/** 
 * @file  win32.h
 * @brief Configuration spécifique à l'environnement Windows pour ENet.
 *
 * Ce fichier inclut les configurations nécessaires pour compiler et exécuter ENet sous Windows.
 * Il ajuste les paramètres de compilation pour éviter les avertissements communs avec MSVC,
 * définit des types et macros compatibles avec l'API Windows pour la programmation réseau,
 * et gère l'exportation ou l'importation des fonctions de la bibliothèque en fonction de la compilation
 * de ENet comme DLL ou comme librairie statique.
 */

#ifndef RCENET_WIN32_H
#define RCENET_WIN32_H

#ifdef _MSC_VER
#ifdef ENET_BUILDING_LIB
#pragma warning (disable: 4267) /* Désactive l'avertissement pour la conversion de size_t en int. */
#pragma warning (disable: 4244) /* Désactive l'avertissement pour la conversion de 64 bits en 32 bits. */
#pragma warning (disable: 4018) /* Désactive l'avertissement pour les comparaisons signées/non signées. */
#pragma warning (disable: 4146) /* Désactive l'avertissement pour l'opérateur moins unaire sur un type non signé. */
#define _CRT_SECURE_NO_DEPRECATE /* Désactive les avertissements pour les fonctions CRT considérées comme non sécurisées. */
#define _CRT_SECURE_NO_WARNINGS /* Désactive les avertissements pour l'utilisation de fonctions CRT non sécurisées. */
#endif
#endif

#include <stdlib.h>
#include <winsock2.h> /* Inclut les définitions de sockets Windows. */

/**
 * Type représentant un socket dans ENet. Les sockets Windows utilisent le type SOCKET.
 */
typedef SOCKET ENetSocket;

/**
 * Valeur spéciale pour un socket invalide ou fermé sous Windows.
 */
#define ENET_SOCKET_NULL INVALID_SOCKET

/**
 * Macros pour la conversion d'ordre des octets entre l'hôte et le réseau.
 */
#define ENET_HOST_TO_NET_16(value) (htons (value))
#define ENET_HOST_TO_NET_32(value) (htonl (value))
#define ENET_NET_TO_HOST_16(value) (ntohs (value))
#define ENET_NET_TO_HOST_32(value) (ntohl (value))

/**
 * Structure pour la gestion des buffers de données. Utilisée pour encapsuler les données envoyées ou reçues via le réseau.
 * @property {size_t} dataLength Longueur des données en octets.
 * @property {void*} data Pointeur vers les données.
 */
typedef struct
{
    size_t dataLength;
    void * data;
} ENetBuffer;

/**
 * Convention d'appel pour les callbacks dans ENet sous Windows.
 */
#define ENET_CALLBACK __cdecl

/**
 * Définitions pour l'exportation ou l'importation des symboles de la DLL.
 */
#ifdef ENET_DLL
#ifdef ENET_BUILDING_LIB
#define ENET_API __declspec(dllexport) /* Exporte les symboles de la DLL. */
#else
#define ENET_API __declspec(dllimport) /* Importe les symboles de la DLL. */
#endif /* ENET_BUILDING_LIB */
#else /* !ENET_DLL */
#define ENET_API extern /* Si pas une DLL, déclare simplement comme externe. */
#endif /* ENET_DLL */

/**
 * Type et macros pour la gestion des ensembles de sockets avec select() sous Windows.
 */
typedef fd_set ENetSocketSet;
#define ENET_SOCKETSET_EMPTY(sockset)          FD_ZERO(&(sockset))
#define ENET_SOCKETSET_ADD(sockset, socket)    FD_SET(socket, &(sockset))
#define ENET_SOCKETSET_REMOVE(sockset, socket) FD_CLR(socket, &(sockset))
#define ENET_SOCKETSET_CHECK(sockset, socket)  FD_ISSET(socket, &(sockset))

#endif // RCENET_WIN32_H