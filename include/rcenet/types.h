/** 
 * @file  types.h
 * @brief Définitions des types pour ENet.
 *
 * Ce fichier définit les types de données utilisés dans ENet pour assurer une portabilité
 * et une clarté maximales dans l'implémentation du protocole. Ces types sont utilisés pour garantir
 * la taille des variables à travers différentes plateformes et compilateurs.
 */

#ifndef RCENET_TYPES_H
#define RCENET_TYPES_H

/**
 * @typedef enet_uint8
 * @brief Type entier non signé de 8 bits.
 * 
 * Utilisé pour stocker des données de petite taille, comme des identifiants de commande ou des drapeaux,
 * assurant un usage minimal de la mémoire.
 */
typedef unsigned char enet_uint8;

/**
 * @typedef enet_uint16
 * @brief Type entier non signé de 16 bits.
 * 
 * Employé pour des valeurs moyennes, telles que des numéros de séquence ou des tailles de paquets,
 * fournissant un équilibre entre l'efficacité de la mémoire et la capacité de stockage.
 */
typedef unsigned short enet_uint16;

/**
 * @typedef enet_uint32
 * @brief Type entier non signé de 32 bits.
 * 
 * Utilisé pour des données plus larges, comme des adresses IP ou des identifiants de connexion,
 * offrant une large gamme de valeurs pour la gestion de réseaux et de sessions.
 */
typedef unsigned int enet_uint32;

#endif // RCENET_TYPES_H