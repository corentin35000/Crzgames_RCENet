/** 
 * @file  protocol.h
 * @brief Définition du protocole RCENet pour la communication réseau.
 *
 * Ce fichier contient les définitions essentielles du protocole RCENet, y compris les structures de données pour les en-têtes de protocole,
 * les commandes, et les différentes configurations de bande passante et de latence. Il définit également des constantes importantes
 * pour les paramètres du protocole, comme les tailles minimales et maximales de transmission unitaire (MTU), les limites de fenêtre,
 * et les nombres maximaux de commandes de paquets, permettant une communication réseau optimisée et adaptable.
 */

#ifndef RCENET_PROTOCOL_H
#define RCENET_PROTOCOL_H

#include "rcenet/types.h"

/**
 * Enumération des limites de configuration et des caractéristiques du protocole RCENet.
 * Ces constantes définissent les paramètres clés pour la transmission des données, y compris la taille unitaire de transmission maximale et minimale (MTU),
 * les dimensions de la fenêtre de transmission, les limites de commandes de paquets, et d'autres paramètres critiques pour la performance et la fiabilité du réseau.
 * 
 * @typedef {enum} ENetProtocolLimit
 * @property {number} ENET_PROTOCOL_MINIMUM_MTU - Taille minimale de MTU, assurant la compatibilité avec IPv4.
 * @property {number} ENET_PROTOCOL_MAXIMUM_MTU - Taille maximale de MTU, optimisée pour réduire la fragmentation.
 * @property {number} ENET_PROTOCOL_MAXIMUM_PACKET_COMMANDS - Nombre maximum de commandes pouvant être incluses dans un seul paquet.
 * @property {number} ENET_PROTOCOL_MINIMUM_WINDOW_SIZE - Taille minimale de la fenêtre de congestion, pour un contrôle de flux efficace.
 * @property {number} ENET_PROTOCOL_MAXIMUM_WINDOW_SIZE - Taille maximale de la fenêtre de congestion, permettant de grandes rafales de données.
 * @property {number} ENET_PROTOCOL_MINIMUM_CHANNEL_COUNT - Nombre minimal de canaux de communication, assurant au moins un canal.
 * @property {number} ENET_PROTOCOL_MAXIMUM_CHANNEL_COUNT - Nombre maximal de canaux de communication, pour une multiplexage efficace.
 * @property {number} ENET_PROTOCOL_MAXIMUM_PEER_ID - Identifiant maximal pour les pairs, limitant le nombre de pairs simultanés.
 * @property {number} ENET_PROTOCOL_MAXIMUM_FRAGMENT_COUNT - Nombre maximal de fragments pour un message segmenté, supportant de grandes données.
 */
enum
{
   ENET_PROTOCOL_MINIMUM_MTU             = 576,
   ENET_PROTOCOL_MAXIMUM_MTU             = 4096,
   ENET_PROTOCOL_MAXIMUM_PACKET_COMMANDS = 32,
   ENET_PROTOCOL_MINIMUM_WINDOW_SIZE     = 4096,
   ENET_PROTOCOL_MAXIMUM_WINDOW_SIZE     = 65536,
   ENET_PROTOCOL_MINIMUM_CHANNEL_COUNT   = 1,
   ENET_PROTOCOL_MAXIMUM_CHANNEL_COUNT   = 255,
   ENET_PROTOCOL_MAXIMUM_PEER_ID         = 0xFFFF, // 65535
   ENET_PROTOCOL_MAXIMUM_FRAGMENT_COUNT  = 1024 * 1024
};

/**
 * Enumération des commandes du protocole RCENet.
 * Ces commandes définissent les différentes opérations possibles dans la communication RCENet, permettant la gestion de la connectivité,
 * la fiabilité, l'ordonnancement, et le contrôle de flux entre les pairs.
 * 
 * @typedef {enum} ENetProtocolCommand
 * @property {number} ENET_PROTOCOL_COMMAND_NONE - Aucune commande, utilisée pour initialiser des séquences de commande.
 * @property {number} ENET_PROTOCOL_COMMAND_ACKNOWLEDGE - Accusé de réception pour confirmer la réception de paquets fiables.
 * @property {number} ENET_PROTOCOL_COMMAND_CONNECT - Commande pour établir une connexion avec un pair.
 * @property {number} ENET_PROTOCOL_COMMAND_VERIFY_CONNECT - Commande pour vérifier une connexion établie.
 * @property {number} ENET_PROTOCOL_COMMAND_DISCONNECT - Commande pour terminer une connexion avec un pair.
 * @property {number} ENET_PROTOCOL_COMMAND_PING - Commande pour vérifier la latence avec un pair.
 * @property {number} ENET_PROTOCOL_COMMAND_SEND_RELIABLE - Commande pour envoyer des données fiables qui nécessitent un accusé de réception.
 * @property {number} ENET_PROTOCOL_COMMAND_SEND_UNRELIABLE - Commande pour envoyer des données non fiables sans garantie de livraison.
 * @property {number} ENET_PROTOCOL_COMMAND_SEND_FRAGMENT - Commande pour envoyer des données fragmentées, permettant de dépasser la limite de taille de paquet.
 * @property {number} ENET_PROTOCOL_COMMAND_SEND_UNSEQUENCED - Commande pour envoyer des données sans ordre séquentiel défini.
 * @property {number} ENET_PROTOCOL_COMMAND_BANDWIDTH_LIMIT - Commande pour définir la limite de bande passante.
 * @property {number} ENET_PROTOCOL_COMMAND_THROTTLE_CONFIGURE - Commande pour configurer l'étranglement du trafic.
 * @property {number} ENET_PROTOCOL_COMMAND_SEND_UNRELIABLE_FRAGMENT - Commande pour envoyer des fragments de données de manière non fiable.
 * @property {number} ENET_PROTOCOL_COMMAND_COUNT - Nombre total de commandes définies dans le protocole.
 * @property {number} ENET_PROTOCOL_COMMAND_MASK - Masque utilisé pour isoler le type de commande dans un entête de protocole.
 */
typedef enum _ENetProtocolCommand
{
   ENET_PROTOCOL_COMMAND_NONE               = 0,
   ENET_PROTOCOL_COMMAND_ACKNOWLEDGE        = 1,
   ENET_PROTOCOL_COMMAND_CONNECT            = 2,
   ENET_PROTOCOL_COMMAND_VERIFY_CONNECT     = 3,
   ENET_PROTOCOL_COMMAND_DISCONNECT         = 4,
   ENET_PROTOCOL_COMMAND_PING               = 5,
   ENET_PROTOCOL_COMMAND_SEND_RELIABLE      = 6,
   ENET_PROTOCOL_COMMAND_SEND_UNRELIABLE    = 7,
   ENET_PROTOCOL_COMMAND_SEND_FRAGMENT      = 8,
   ENET_PROTOCOL_COMMAND_SEND_UNSEQUENCED   = 9,
   ENET_PROTOCOL_COMMAND_BANDWIDTH_LIMIT    = 10,
   ENET_PROTOCOL_COMMAND_THROTTLE_CONFIGURE = 11,
   ENET_PROTOCOL_COMMAND_SEND_UNRELIABLE_FRAGMENT = 12,
   ENET_PROTOCOL_COMMAND_COUNT              = 13,

   ENET_PROTOCOL_COMMAND_MASK               = 0x0F
} ENetProtocolCommand;

/**
 * Enumération des drapeaux de commande du protocole RCENet.
 * Ces drapeaux sont utilisés pour modifier le comportement des commandes du protocole,
 * permettant une gestion fine du contrôle de flux, de la fiabilité et de la séquence des paquets.
 * 
 * @typedef {enum} ENetProtocolFlag
 * @property {number} ENET_PROTOCOL_COMMAND_FLAG_ACKNOWLEDGE - Indique qu'une commande nécessite un accusé de réception.
 * @property {number} ENET_PROTOCOL_COMMAND_FLAG_UNSEQUENCED - Indique qu'une commande est envoyée sans séquence définie.
 * @property {number} ENET_PROTOCOL_HEADER_FLAG_COMPRESSED - Indique que l'en-tête du paquet est compressé.
 * @property {number} ENET_PROTOCOL_HEADER_FLAG_SENT_TIME - Indique que le temps d'envoi est inclus dans l'en-tête du paquet.
 * @property {number} ENET_PROTOCOL_HEADER_FLAG_MASK - Masque combinant les drapeaux de l'en-tête pour une vérification rapide.
 * @property {number} ENET_PROTOCOL_HEADER_SESSION_MASK - Masque pour isoler les bits de session dans l'en-tête.
 * @property {number} ENET_PROTOCOL_HEADER_SESSION_SHIFT - Décalage pour les bits de session dans l'en-tête.
 */
typedef enum _ENetProtocolFlag
{
   ENET_PROTOCOL_COMMAND_FLAG_ACKNOWLEDGE = (1 << 7),
   ENET_PROTOCOL_COMMAND_FLAG_UNSEQUENCED = (1 << 6),

   ENET_PROTOCOL_HEADER_FLAG_COMPRESSED = (1 << 14),
   ENET_PROTOCOL_HEADER_FLAG_SENT_TIME  = (1 << 15),
   ENET_PROTOCOL_HEADER_FLAG_MASK       = ENET_PROTOCOL_HEADER_FLAG_COMPRESSED | ENET_PROTOCOL_HEADER_FLAG_SENT_TIME,

   ENET_PROTOCOL_HEADER_SESSION_MASK    = (3 << 12),
   ENET_PROTOCOL_HEADER_SESSION_SHIFT   = 12
} ENetProtocolFlag;

/**
 * Enumération des drapeaux étendus pour les en-têtes de protocole RCENet.
 * Ces drapeaux permettent d'ajouter des fonctionnalités supplémentaires et des extensions futures au protocole sans perturber la compatibilité.
 * 
 * @typedef {enum} ENetProtocolExtendedFlag
 * @property {number} ENET_PROTOCOL_HEADER_EXTENDED_FLAG_ENCRYPTED - Indique que le paquet est chiffré.
 * @property {number} ENET_PROTOCOL_HEADER_EXTENDED_FLAG_MASK - Masque combinant les drapeaux étendus pour une vérification rapide.
 */
typedef enum _ENetProtocolExtendedFlag
{
   /* bits [0-3] are reserved for future peer id extension */

   ENET_PROTOCOL_HEADER_EXTENDED_FLAG_ENCRYPTED  = (1 << 4),
   ENET_PROTOCOL_HEADER_EXTENDED_FLAG_MASK       = ENET_PROTOCOL_HEADER_EXTENDED_FLAG_ENCRYPTED,
} ENetProtocolExtendedFlag;

#ifdef _MSC_VER
#pragma pack(push, 1)
#define ENET_PACKED
#elif defined(__GNUC__) || defined(__clang__)
#define ENET_PACKED __attribute__ ((packed))
#else
#define ENET_PACKED
#endif

/**
 * Structure représentant l'en-tête de protocole ENet.
 * Elle contient l'identifiant du pair et le temps d'envoi du paquet, utilisé pour la gestion du délai et la détection des pertes.
 * 
 * @typedef {struct} _ENetProtocolHeader
 * @property {enet_uint16} peerID - L'identifiant du pair. Utilisé pour identifier la source ou la destination du paquet.
 * @property {enet_uint16} sentTime - Le temps d'envoi du paquet. Utilisé pour calculer le round-trip time (RTT) et le délai.
 */
typedef struct _ENetProtocolHeader
{
   enet_uint16 peerID;
   enet_uint16 sentTime;
} ENET_PACKED ENetProtocolHeader;

/**
 * Structure représentant l'en-tête d'une commande du protocole ENet.
 * Inclut le type de commande, l'ID du canal sur lequel la commande est envoyée, et le numéro de séquence fiable pour le suivi des paquets.
 * 
 * @typedef {struct} _ENetProtocolCommandHeader
 * @property {enet_uint8} command - Le type de commande.
 * @property {enet_uint8} channelID - L'ID du canal de communication.
 * @property {enet_uint16} reliableSequenceNumber - Le numéro de séquence fiable pour le suivi des paquets.
 */
typedef struct _ENetProtocolCommandHeader
{
   enet_uint8 command;
   enet_uint8 channelID;
   enet_uint16 reliableSequenceNumber;
} ENET_PACKED ENetProtocolCommandHeader;

/**
 * Structure pour la commande d'acquittement.
 * Contient les informations nécessaires pour accuser réception de paquets fiables.
 * 
 * @typedef {struct} _ENetProtocolAcknowledge
 * @property {ENetProtocolCommandHeader} header - L'en-tête de la commande.
 * @property {enet_uint16} receivedReliableSequenceNumber - Le numéro de séquence du paquet reçu.
 * @property {enet_uint16} receivedSentTime - Le temps d'envoi du paquet reçu.
 */
typedef struct _ENetProtocolAcknowledge
{
   ENetProtocolCommandHeader header;
   enet_uint16 receivedReliableSequenceNumber;
   enet_uint16 receivedSentTime;
} ENET_PACKED ENetProtocolAcknowledge;

/**
 * Structure pour la commande de connexion.
 * Contient les paramètres nécessaires pour établir une connexion entre pairs.
 * 
 * @typedef {struct} _ENetProtocolConnect
 * @property {ENetProtocolCommandHeader} header - L'en-tête de la commande.
 * @property {enet_uint16} outgoingPeerID - L'ID du pair sortant.
 * @property {enet_uint8} incomingSessionID - L'ID de session entrante.
 * @property {enet_uint8} outgoingSessionID - L'ID de session sortante.
 * @property {enet_uint32} mtu - La taille maximale de l'unité de transmission.
 * @property {enet_uint32} windowSize - La taille de la fenêtre de congestion.
 * @property {enet_uint32} channelCount - Le nombre de canaux de communication.
 * @property {enet_uint32} incomingBandwidth - La bande passante entrante.
 * @property {enet_uint32} outgoingBandwidth - La bande passante sortante.
 * @property {enet_uint32} packetThrottleInterval - L'intervalle de régulation des paquets.
 * @property {enet_uint32} packetThrottleAcceleration - L'accélération de la régulation des paquets.
 * @property {enet_uint32} packetThrottleDeceleration - La décélération de la régulation des paquets.
 * @property {enet_uint32} connectID - L'ID de connexion.
 * @property {enet_uint32} data - Données supplémentaires pour la connexion.
 */
typedef struct _ENetProtocolConnect
{
   ENetProtocolCommandHeader header;
   enet_uint16 outgoingPeerID;
   enet_uint8  incomingSessionID;
   enet_uint8  outgoingSessionID;
   enet_uint32 mtu;
   enet_uint32 windowSize;
   enet_uint32 channelCount;
   enet_uint32 incomingBandwidth;
   enet_uint32 outgoingBandwidth;
   enet_uint32 packetThrottleInterval;
   enet_uint32 packetThrottleAcceleration;
   enet_uint32 packetThrottleDeceleration;
   enet_uint32 connectID;
   enet_uint32 data;
} ENET_PACKED ENetProtocolConnect;

/**
 * Structure pour la vérification de la connexion.
 * Utilisée pour confirmer les paramètres de la connexion après un processus initial de connexion.
 * 
 * @typedef {struct} _ENetProtocolVerifyConnect
 * @property {ENetProtocolCommandHeader} header - L'en-tête de la commande.
 * @property {enet_uint16} outgoingPeerID - L'ID du pair sortant.
 * @property {enet_uint8} incomingSessionID - L'ID de session entrante, vérifie la session du connecteur.
 * @property {enet_uint8} outgoingSessionID - L'ID de session sortante, vérifie la session de connexion.
 * @property {enet_uint32} mtu - La taille maximale de l'unité de transmission confirmée.
 * @property {enet_uint32} windowSize - La taille de la fenêtre de congestion confirmée.
 * @property {enet_uint32} channelCount - Le nombre de canaux de communication confirmés.
 * @property {enet_uint32} incomingBandwidth - La bande passante entrante confirmée.
 * @property {enet_uint32} outgoingBandwidth - La bande passante sortante confirmée.
 * @property {enet_uint32} packetThrottleInterval - L'intervalle de régulation des paquets confirmé.
 * @property {enet_uint32} packetThrottleAcceleration - L'accélération de la régulation des paquets confirmée.
 * @property {enet_uint32} packetThrottleDeceleration - La décélération de la régulation des paquets confirmée.
 * @property {enet_uint32} connectID - L'ID de connexion unique pour cette session.
 */
typedef struct _ENetProtocolVerifyConnect
{
   ENetProtocolCommandHeader header;
   enet_uint16 outgoingPeerID;
   enet_uint8  incomingSessionID;
   enet_uint8  outgoingSessionID;
   enet_uint32 mtu;
   enet_uint32 windowSize;
   enet_uint32 channelCount;
   enet_uint32 incomingBandwidth;
   enet_uint32 outgoingBandwidth;
   enet_uint32 packetThrottleInterval;
   enet_uint32 packetThrottleAcceleration;
   enet_uint32 packetThrottleDeceleration;
   enet_uint32 connectID;
} ENET_PACKED ENetProtocolVerifyConnect;

/**
 * Structure pour la limite de bande passante.
 * Permet de configurer la limite de bande passante entrante et sortante pour un pair.
 * 
 * @typedef {struct} _ENetProtocolBandwidthLimit
 * @property {ENetProtocolCommandHeader} header - L'en-tête de la commande.
 * @property {enet_uint32} incomingBandwidth - La nouvelle limite de bande passante entrante.
 * @property {enet_uint32} outgoingBandwidth - La nouvelle limite de bande passante sortante.
 */
typedef struct _ENetProtocolBandwidthLimit
{
   ENetProtocolCommandHeader header;
   enet_uint32 incomingBandwidth;
   enet_uint32 outgoingBandwidth;
} ENET_PACKED ENetProtocolBandwidthLimit;

/**
 * Structure pour la configuration de la régulation des paquets.
 * Définit comment les paquets sont régulés en termes d'intervalle, d'accélération, et de décélération.
 * 
 * @typedef {struct} _ENetProtocolThrottleConfigure
 * @property {ENetProtocolCommandHeader} header - L'en-tête de la commande.
 * @property {enet_uint32} packetThrottleInterval - L'intervalle de temps entre les régulations.
 * @property {enet_uint32} packetThrottleAcceleration - Combien la régulation des paquets peut s'accélérer.
 * @property {enet_uint32} packetThrottleDeceleration - Combien la régulation des paquets peut ralentir.
 */
typedef struct _ENetProtocolThrottleConfigure
{
   ENetProtocolCommandHeader header;
   enet_uint32 packetThrottleInterval;
   enet_uint32 packetThrottleAcceleration;
   enet_uint32 packetThrottleDeceleration;
} ENET_PACKED ENetProtocolThrottleConfigure;

/**
 * Structure pour la déconnexion.
 * Envoie une demande de déconnexion ou confirme une déconnexion reçue d'un pair.
 * 
 * @typedef {struct} _ENetProtocolDisconnect
 * @property {ENetProtocolCommandHeader} header - L'en-tête de la commande.
 * @property {enet_uint32} data - Données supplémentaires ou code de déconnexion.
 */   
typedef struct _ENetProtocolDisconnect
{
   ENetProtocolCommandHeader header;
   enet_uint32 data;
} ENET_PACKED ENetProtocolDisconnect;

/**
 * Structure pour le ping.
 * Utilisé pour mesurer la latence entre les pairs.
 * 
 * @typedef {struct} _ENetProtocolPing
 * @property {ENetProtocolCommandHeader} header - L'en-tête de la commande.
 */
typedef struct _ENetProtocolPing
{
   ENetProtocolCommandHeader header;
} ENET_PACKED ENetProtocolPing;

/**
 * Structure pour l'envoi de données fiables.
 * Ces paquets nécessitent un accusé de réception par le destinataire.
 * 
 * @typedef {struct} _ENetProtocolSendReliable
 * @property {ENetProtocolCommandHeader} header - L'en-tête de la commande.
 * @property {enet_uint16} dataLength - La longueur des données envoyées.
 */
typedef struct _ENetProtocolSendReliable
{
   ENetProtocolCommandHeader header;
   enet_uint16 dataLength;
} ENET_PACKED ENetProtocolSendReliable;

/**
 * Structure pour l'envoi de données non fiables.
 * Ces paquets ne nécessitent pas d'accusé de réception et peuvent être perdus.
 * 
 * @typedef {struct} _ENetProtocolSendUnreliable
 * @property {ENetProtocolCommandHeader} header - L'en-tête de la commande.
 * @property {enet_uint16} unreliableSequenceNumber - Le numéro de séquence non fiable pour le suivi.
 * @property {enet_uint16} dataLength - La longueur des données envoyées.
 */
typedef struct _ENetProtocolSendUnreliable
{
   ENetProtocolCommandHeader header;
   enet_uint16 unreliableSequenceNumber;
   enet_uint16 dataLength;
} ENET_PACKED ENetProtocolSendUnreliable;

/**
 * Structure pour l'envoi de données non séquencées.
 * Ces paquets sont envoyés sans garantie d'ordre par rapport aux autres paquets.
 * 
 * @typedef {struct} _ENetProtocolSendUnsequenced
 * @property {ENetProtocolCommandHeader} header - L'en-tête de la commande.
 * @property {enet_uint16} unsequencedGroup - Le groupe auquel appartient ce paquet non séquencé.
 * @property {enet_uint16} dataLength - La longueur des données envoyées.
 */
typedef struct _ENetProtocolSendUnsequenced
{
   ENetProtocolCommandHeader header;
   enet_uint16 unsequencedGroup;
   enet_uint16 dataLength;
} ENET_PACKED ENetProtocolSendUnsequenced;

/**
 * Structure pour l'envoi de fragments de données.
 * Permet de transmettre des données qui dépassent la taille maximale de l'unité de transmission.
 * 
 * @typedef {struct} _ENetProtocolSendFragment
 * @property {ENetProtocolCommandHeader} header - L'en-tête de la commande.
 * @property {enet_uint16} startSequenceNumber - Le numéro de séquence du premier fragment.
 * @property {enet_uint16} dataLength - La longueur des données du fragment.
 * @property {enet_uint32} fragmentCount - Le nombre total de fragments.
 * @property {enet_uint32} fragmentNumber - Le numéro de ce fragment.
 * @property {enet_uint32} totalLength - La longueur totale des données fragmentées.
 * @property {enet_uint32} fragmentOffset - Le décalage de ce fragment dans les données totales.
 */
typedef struct _ENetProtocolSendFragment
{
   ENetProtocolCommandHeader header;
   enet_uint16 startSequenceNumber;
   enet_uint16 dataLength;
   enet_uint32 fragmentCount;
   enet_uint32 fragmentNumber;
   enet_uint32 totalLength;
   enet_uint32 fragmentOffset;
} ENET_PACKED ENetProtocolSendFragment;

/**
 * Union représentant les différents types de paquets pouvant être envoyés ou reçus dans le protocole ENet.
 * Cette structure permet de manipuler facilement les différents types de paquets comme s'ils étaient du même type,
 * tout en accédant facilement aux champs spécifiques à chaque type de paquet grâce à la nature de l'union.
 * Utiliser le bon membre de l'union dépend du contexte d'envoi ou de réception des paquets, et est généralement déterminé par le type de commande spécifié dans l'en-tête du paquet.
 * 
 * @typedef {union} _ENetProtocol
 * @property {ENetProtocolCommandHeader} header - Un en-tête commun à tous les types de paquets, contenant le type de commande et d'autres informations de base.
 * @property {ENetProtocolAcknowledge} acknowledge - Paquet d'acquittement utilisé pour confirmer la réception de paquets fiables.
 * @property {ENetProtocolConnect} connect - Paquet de demande de connexion ou de confirmation de connexion.
 * @property {ENetProtocolVerifyConnect} verifyConnect - Paquet de vérification des paramètres de la connexion après établissement.
 * @property {ENetProtocolDisconnect} disconnect - Paquet signalant la fermeture d'une connexion.
 * @property {ENetProtocolPing} ping - Paquet de test de latence entre les pairs.
 * @property {ENetProtocolSendReliable} sendReliable - Paquet contenant des données devant être reçues de manière fiable par le destinataire.
 * @property {ENetProtocolSendUnreliable} sendUnreliable - Paquet contenant des données pouvant être perdues sans nécessiter d'acquittement.
 * @property {ENetProtocolSendUnsequenced} sendUnsequenced - Paquet contenant des données sans ordre de séquence défini.
 * @property {ENetProtocolSendFragment} sendFragment - Paquet contenant un fragment de données plus grandes que la taille maximale de paquet.
 * @property {ENetProtocolBandwidthLimit} bandwidthLimit - Paquet définissant les limites de bande passante entrante et sortante.
 * @property {ENetProtocolThrottleConfigure} throttleConfigure - Paquet configurant la gestion de la régulation du débit de paquets.
 */
typedef union _ENetProtocol
{
   ENetProtocolCommandHeader header;
   ENetProtocolAcknowledge acknowledge;
   ENetProtocolConnect connect;
   ENetProtocolVerifyConnect verifyConnect;
   ENetProtocolDisconnect disconnect;
   ENetProtocolPing ping;
   ENetProtocolSendReliable sendReliable;
   ENetProtocolSendUnreliable sendUnreliable;
   ENetProtocolSendUnsequenced sendUnsequenced;
   ENetProtocolSendFragment sendFragment;
   ENetProtocolBandwidthLimit bandwidthLimit;
   ENetProtocolThrottleConfigure throttleConfigure;
} ENET_PACKED ENetProtocol;

#ifdef _MSC_VER
#pragma pack(pop)
#endif

#endif // RCENET_PROTOCOL_H