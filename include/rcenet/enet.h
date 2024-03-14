/** 
 * @file  enet.h
 * @brief En-tête public d'ENet, fournissant les interfaces principales de la bibliothèque.
 *
 * Ce fichier contient les définitions centrales utilisées par ENet, incluant les versions de la bibliothèque,
 * les types de sockets, les options de socket, les structures d'adresse, et d'autres définitions essentielles
 * pour initialiser et utiliser ENet dans des applications réseau.
 */

#ifndef RCENET_ENET_H
#define RCENET_ENET_H

#ifdef __cplusplus
extern "C" {
#endif

// Inclusions et configurations basées sur la plateforme.
#include <stdlib.h>
#ifdef _WIN32
#include "rcenet/win32.h"
#else
#include "rcenet/unix.h"
#endif

// Inclusions des composants internes d'ENet.
#include "rcenet/types.h"
#include "rcenet/protocol.h"
#include "rcenet/list.h"
#include "rcenet/callbacks.h"

// Définitions de version d'ENet.
#define ENET_VERSION_MAJOR 6
#define ENET_VERSION_MINOR 1
#define ENET_VERSION_PATCH 0
// Macros pour la manipulation des numéros de version.
#define ENET_VERSION_CREATE(major, minor, patch) (((major)<<16) | ((minor)<<8) | (patch))
#define ENET_VERSION_GET_MAJOR(version) (((version)>>16)&0xFF)
#define ENET_VERSION_GET_MINOR(version) (((version)>>8)&0xFF)
#define ENET_VERSION_GET_PATCH(version) ((version)&0xFF)
#define ENET_VERSION ENET_VERSION_CREATE(ENET_VERSION_MAJOR, ENET_VERSION_MINOR, ENET_VERSION_PATCH)

// Définition du type de version.
typedef enet_uint32 ENetVersion;

// Pré-déclaration de structures.
struct _ENetHost;
struct _ENetEvent;
struct _ENetPacket;

/**
 * Enumération des types de socket supportés par ENet.
 * Ces types définissent le comportement et les caractéristiques des sockets utilisés dans les communications réseau.
 * 
 * @typedef {enum} _ENetSocketType
 * @property {number} ENET_SOCKET_TYPE_STREAM - Socket de type flux (TCP), fournissant des connexions orientées connexion, fiables et en séquence.
 * @property {number} ENET_SOCKET_TYPE_DATAGRAM - Socket de type datagramme (UDP), utilisé pour les transmissions de paquets sans connexion.
 */
typedef enum _ENetSocketType
{
   ENET_SOCKET_TYPE_STREAM   = 1,
   ENET_SOCKET_TYPE_DATAGRAM = 2
} ENetSocketType;

/**
 * Enumération des conditions d'attente pour les sockets.
 * Ces constantes sont utilisées pour spécifier les opérations pour lesquelles un socket doit attendre lors d'une sélection.
 * 
 * @typedef {enum} _ENetSocketWait
 * @property {number} ENET_SOCKET_WAIT_NONE - Aucune condition d'attente.
 * @property {number} ENET_SOCKET_WAIT_SEND - Attendre que le socket soit prêt à envoyer des données.
 * @property {number} ENET_SOCKET_WAIT_RECEIVE - Attendre que le socket soit prêt à recevoir des données.
 * @property {number} ENET_SOCKET_WAIT_INTERRUPT - Attendre une interruption.
 */
typedef enum _ENetSocketWait
{
   ENET_SOCKET_WAIT_NONE      = 0,
   ENET_SOCKET_WAIT_SEND      = (1 << 0),
   ENET_SOCKET_WAIT_RECEIVE   = (1 << 1),
   ENET_SOCKET_WAIT_INTERRUPT = (1 << 2)
} ENetSocketWait;

/**
 * Enumération des options de socket.
 * Ces options peuvent être utilisées pour configurer le comportement des sockets au niveau du système d'exploitation.
 * 
 * @typedef {enum} _ENetSocketOption
 * @property {number} ENET_SOCKOPT_NONBLOCK - Activer le mode non bloquant pour le socket.
 * @property {number} ENET_SOCKOPT_BROADCAST - Permettre l'envoi de paquets broadcast.
 * @property {number} ENET_SOCKOPT_RCVBUF - Taille du buffer de réception.
 * @property {number} ENET_SOCKOPT_SNDBUF - Taille du buffer d'envoi.
 * @property {number} ENET_SOCKOPT_REUSEADDR - Autoriser la réutilisation des adresses locales.
 * @property {number} ENET_SOCKOPT_RCVTIMEO - Délai d'attente pour la réception.
 * @property {number} ENET_SOCKOPT_SNDTIMEO - Délai d'attente pour l'envoi.
 * @property {number} ENET_SOCKOPT_ERROR - Obtenir le code d'erreur en attente sur le socket.
 * @property {number} ENET_SOCKOPT_NODELAY - Désactiver l'algorithme de Nagle (pour les sockets TCP).
 * @property {number} ENET_SOCKOPT_TTL - Définir la durée de vie des paquets IP.
 * @property {number} ENET_SOCKOPT_IPV6ONLY - Socket IPv6 uniquement, sans prise en charge des adresses IPv4 mappées.
 */
typedef enum _ENetSocketOption
{
   ENET_SOCKOPT_NONBLOCK  = 1,
   ENET_SOCKOPT_BROADCAST = 2,
   ENET_SOCKOPT_RCVBUF    = 3,
   ENET_SOCKOPT_SNDBUF    = 4,
   ENET_SOCKOPT_REUSEADDR = 5,
   ENET_SOCKOPT_RCVTIMEO  = 6,
   ENET_SOCKOPT_SNDTIMEO  = 7,
   ENET_SOCKOPT_ERROR     = 8,
   ENET_SOCKOPT_NODELAY   = 9,
   ENET_SOCKOPT_TTL       = 10,
   ENET_SOCKOPT_IPV6ONLY  = 11
} ENetSocketOption;

/**
 * Enumération des modes de fermeture de socket.
 * 
 * @typedef {enum} _ENetSocketShutdown
 * @property {number} ENET_SOCKET_SHUTDOWN_READ - Ferme la réception sur le socket.
 * @property {number} ENET_SOCKET_SHUTDOWN_WRITE - Ferme l'envoi sur le socket.
 * @property {number} ENET_SOCKET_SHUTDOWN_READ_WRITE - Ferme à la fois la réception et l'envoi sur le socket.
 */
typedef enum _ENetSocketShutdown
{
    ENET_SOCKET_SHUTDOWN_READ       = 0,
    ENET_SOCKET_SHUTDOWN_WRITE      = 1,
    ENET_SOCKET_SHUTDOWN_READ_WRITE = 2
} ENetSocketShutdown;

/**
 * Enumération des types d'adresse supportés par ENet.
 * 
 * @typedef {enum} _ENetAddressType
 * @property {number} ENET_ADDRESS_TYPE_ANY - Adresse non spécifiée (peut être utilisée pour écouter sur toutes les adresses).
 * @property {number} ENET_ADDRESS_TYPE_IPV4 - Utilise une adresse IPv4.
 * @property {number} ENET_ADDRESS_TYPE_IPV6 - Utilise une adresse IPv6.
 */
typedef enum _ENetAddressType
{
    ENET_ADDRESS_TYPE_ANY  = 0,
    ENET_ADDRESS_TYPE_IPV4 = 1,
    ENET_ADDRESS_TYPE_IPV6 = 2
} ENetAddressType;

/**
 * Structure représentant une adresse Internet portable.
 * 
 * L'hôte doit être spécifié dans l'ordre des octets réseau, et le port doit être dans l'ordre des octets hôte.
 * 
 * @typedef {struct} _ENetAddress
 * @property {ENetAddressType} type - Le type d'adresse (IPv4, IPv6).
 * @property {enet_uint16} port - Le port, en ordre des octets hôte.
 * @property {union} host - L'adresse IP, en ordre des octets réseau. Utilise `v4` pour IPv4 ou `v6` pour IPv6.
 */
typedef struct _ENetAddress
{
   ENetAddressType type;
   enet_uint16 port;
   union 
   {
       enet_uint8 v4[4];
       enet_uint16 v6[8];
   } host;
} ENetAddress;

/**
 * Définit la valeur du port utilisée pour spécifier n'importe quel port disponible lors de la création d'un hôte ENet.
 * Utiliser cette constante permet à ENet de sélectionner automatiquement un port disponible pour l'hôte, 
 * facilitant la configuration d'hôtes sans nécessiter la spécification d'un port spécifique.
 */
#define ENET_PORT_ANY       0

/**
 * Drapeaux de paquet pour contrôler le comportement des paquets dans ENet.
 * Ces drapeaux permettent de spécifier des caractéristiques importantes pour la livraison et le traitement des paquets.
 *
 * @typedef {enum} _ENetPacketFlag
 * @property {number} ENET_PACKET_FLAG_RELIABLE - Assure que le paquet doit être reçu par le destinataire. Des tentatives de renvoi seront effectuées jusqu'à la livraison du paquet.
 * @property {number} ENET_PACKET_FLAG_UNSEQUENCED - Indique que le paquet ne sera pas séquencé avec d'autres paquets. Non pris en charge pour les paquets fiables.
 * @property {number} ENET_PACKET_FLAG_NO_ALLOCATE - Signifie que le paquet n'allouera pas de données, l'utilisateur doit fournir la mémoire pour les données du paquet.
 * @property {number} ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT - Permet au paquet d'être fragmenté en utilisant des envois non fiables si sa taille dépasse l'unité de transmission maximale (MTU).
 * @property {number} ENET_PACKET_FLAG_SENT - Indique si le paquet a été envoyé depuis toutes les files dans lesquelles il a été inséré.
 */
typedef enum _ENetPacketFlag
{
   ENET_PACKET_FLAG_RELIABLE    = (1 << 0),
   ENET_PACKET_FLAG_UNSEQUENCED = (1 << 1),
   ENET_PACKET_FLAG_NO_ALLOCATE = (1 << 2),
   ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT = (1 << 3),
   ENET_PACKET_FLAG_SENT = (1<<8)
} ENetPacketFlag;

/**
 * Type de fonction callback appelée lorsqu'un paquet est accusé réception par le destinataire.
 * Cette callback permet de gérer des actions spécifiques à la confirmation de réception d'un paquet.
 * 
 * @param packet Pointeur vers le paquet pour lequel l'accusé de réception a été reçu.
 */
typedef void (ENET_CALLBACK * ENetPacketAcknowledgedCallback) (struct _ENetPacket *);
/**
 * Type de fonction callback appelée lorsqu'un paquet est libéré.
 * Cette callback permet de gérer des actions spécifiques lors de la libération de la mémoire d'un paquet, par exemple pour libérer des ressources allouées par l'utilisateur.
 * 
 * @param packet Pointeur vers le paquet à libérer.
 */
typedef void (ENET_CALLBACK * ENetPacketFreeCallback) (struct _ENetPacket *);

/**
 * Structure représentant un paquet ENet.
 * Ce paquet contient les données à envoyer ou reçues via le réseau.
 *
 * @property referenceCount - Compteur de références utilisé en interne par ENet pour la gestion de la mémoire du paquet.
 * @property flags - Drapeaux du paquet, combinant les valeurs de _ENetPacketFlag pour spécifier le comportement du paquet.
 * @property data - Pointeur vers les données allouées du paquet.
 * @property dataLength - Longueur des données contenues dans le paquet.
 * @property freeCallback - Fonction de rappel appelée lorsque le paquet n'est plus utilisé.
 * @property userData - Données utilisateur pouvant être modifiées librement par l'application.
 * @property remainingFragments - Nombre de fragments non acquittés par le destinataire. Lorsque ce nombre atteint 0, `acknowledgeCallback` est déclenché.
 * @property acknowledgeCallback - Fonction de rappel appelée lorsque le paquet fiable a été acquitté par le destinataire.
 */
typedef struct _ENetPacket
{
   size_t                         referenceCount;
   enet_uint32                    flags;
   enet_uint8 *                   data;
   size_t                         dataLength;
   ENetPacketFreeCallback         freeCallback;
   void *                         userData;
   enet_uint32                    remainingFragments;
   ENetPacketAcknowledgedCallback acknowledgeCallback;
} ENetPacket;

/**
 * Structure représentant un acquittement dans ENet.
 * Un acquittement est envoyé pour confirmer la réception d'un paquet.
 *
 * @property acknowledgementList - Nœud dans la liste d'acquittements.
 * @property sentTime - Le moment où le paquet correspondant a été envoyé.
 * @property command - La commande protocolaire envoyée comme acquittement.
 */
typedef struct _ENetAcknowledgement
{
   ENetListNode acknowledgementList;
   enet_uint32  sentTime;
   ENetProtocol command;
} ENetAcknowledgement;

/**
 * Structure pour une commande sortante dans ENet.
 * Représente une action ou un paquet devant être envoyé à un pair.
 *
 * @property outgoingCommandList - Nœud dans la liste des commandes sortantes.
 * @property reliableSequenceNumber - Numéro de séquence fiable pour le suivi des paquets.
 * @property unreliableSequenceNumber - Numéro de séquence non fiable pour le suivi des paquets.
 * @property sentTime - Le moment où la commande a été envoyée.
 * @property roundTripTimeout - Délai avant considération de la perte de la commande.
 * @property queueTime - Temps avant que la commande soit mise en file d'attente pour l'envoi.
 * @property fragmentOffset - Décalage du fragment dans le paquet, si la commande est fragmentée.
 * @property fragmentLength - Longueur du fragment de la commande.
 * @property sendAttempts - Nombre de tentatives d'envoi de la commande.
 * @property command - La commande protocolaire à envoyer.
 * @property packet - Le paquet associé à la commande, le cas échéant.
 */
typedef struct _ENetOutgoingCommand
{
   ENetListNode outgoingCommandList;
   enet_uint16  reliableSequenceNumber;
   enet_uint16  unreliableSequenceNumber;
   enet_uint32  sentTime;
   enet_uint32  roundTripTimeout;
   enet_uint32  queueTime;
   enet_uint32  fragmentOffset;
   enet_uint16  fragmentLength;
   enet_uint16  sendAttempts;
   ENetProtocol command;
   ENetPacket * packet;
} ENetOutgoingCommand;

/**
 * Structure pour une commande entrante dans ENet.
 * Représente des données ou des actions reçues d'un pair.
 *
 * @property incomingCommandList - Nœud dans la liste des commandes entrantes.
 * @property reliableSequenceNumber - Numéro de séquence fiable pour le suivi des paquets.
 * @property unreliableSequenceNumber - Numéro de séquence non fiable pour le suivi des paquets.
 * @property command - La commande protocolaire reçue.
 * @property fragmentCount - Nombre total de fragments pour ce paquet.
 * @property fragmentsRemaining - Nombre de fragments restants à recevoir.
 * @property fragments - Tableau de bits pour le suivi des fragments reçus.
 * @property packet - Le paquet associé à la commande, une fois tous les fragments reçus.
 */
typedef struct _ENetIncomingCommand
{  
   ENetListNode     incomingCommandList;
   enet_uint16      reliableSequenceNumber;
   enet_uint16      unreliableSequenceNumber;
   ENetProtocol     command;
   enet_uint32      fragmentCount;
   enet_uint32      fragmentsRemaining;
   enet_uint32 *    fragments;
   ENetPacket *     packet;
} ENetIncomingCommand;

/**
 * Enumération des états possibles d'un pair dans ENet.
 * Ces états représentent le cycle de vie de la connexion d'un pair au réseau ENet.
 *
 * @typedef {enum} _ENetPeerState
 * @property {number} ENET_PEER_STATE_DISCONNECTED - Le pair est déconnecté.
 * @property {number} ENET_PEER_STATE_CONNECTING - Le pair est en cours de connexion.
 * @property {number} ENET_PEER_STATE_ACKNOWLEDGING_CONNECT - Le pair est en train d'acquitter la connexion.
 * @property {number} ENET_PEER_STATE_CONNECTION_PENDING - La connexion du pair est en attente.
 * @property {number} ENET_PEER_STATE_CONNECTION_SUCCEEDED - La connexion du pair a réussi.
 * @property {number} ENET_PEER_STATE_CONNECTED - Le pair est connecté.
 * @property {number} ENET_PEER_STATE_DISCONNECT_LATER - Le pair sera déconnecté plus tard.
 * @property {number} ENET_PEER_STATE_DISCONNECTING - Le pair est en cours de déconnexion.
 * @property {number} ENET_PEER_STATE_ACKNOWLEDGING_DISCONNECT - Le pair est en train d'acquitter la déconnexion.
 * @property {number} ENET_PEER_STATE_ZOMBIE - Le pair est dans un état zombie, en attente de nettoyage.
 */
typedef enum _ENetPeerState
{
   ENET_PEER_STATE_DISCONNECTED                = 0,
   ENET_PEER_STATE_CONNECTING                  = 1,
   ENET_PEER_STATE_ACKNOWLEDGING_CONNECT       = 2,
   ENET_PEER_STATE_CONNECTION_PENDING          = 3,
   ENET_PEER_STATE_CONNECTION_SUCCEEDED        = 4,
   ENET_PEER_STATE_CONNECTED                   = 5,
   ENET_PEER_STATE_DISCONNECT_LATER            = 6,
   ENET_PEER_STATE_DISCONNECTING               = 7,
   ENET_PEER_STATE_ACKNOWLEDGING_DISCONNECT    = 8,
   ENET_PEER_STATE_ZOMBIE                      = 9 
} ENetPeerState;

/**
 * Définit les constantes de configuration pour les hôtes ENet. Ces valeurs régulent des aspects tels que les tailles des buffers,
 * les intervalles pour le contrôle de bande passante, et les paramètres par défaut pour les unités de transmission maximale (MTU) et
 * pour les tailles maximales de paquets et de données en attente.
 */
#ifndef ENET_BUFFER_MAXIMUM
#define ENET_BUFFER_MAXIMUM (1 + 2 * ENET_PROTOCOL_MAXIMUM_PACKET_COMMANDS)
#endif

/**
 * @enum
 * Constantes de configuration pour les hôtes et pairs ENet.
 * Ces valeurs définissent les paramètres par défaut et les limites pour la gestion de la bande passante,
 * les tailles de paquets et les comportements de transmission.
 * 
 * @typedef {enum} _ENetPeerState
 * @property {number} ENET_HOST_RECEIVE_BUFFER_SIZE - Définit la taille du buffer de réception pour l'hôte à 256 Ko (Kilooctets).
 * @property {number} ENET_HOST_SEND_BUFFER_SIZE - Définit la taille du buffer d'envoi pour l'hôte à 256 Ko.
 * @property {number} ENET_HOST_BANDWIDTH_THROTTLE_INTERVAL - Intervalle en millisecondes pour le calcul de la régulation de la bande passante.
 * @property {number} ENET_HOST_DEFAULT_MTU - Taille par défaut de l'Unité de Transmission Maximale (MTU) à 1392 octets.
 * @property {number} ENET_HOST_DEFAULT_MAXIMUM_PACKET_SIZE - Taille maximale par défaut d'un paquet à 32 Mo (Mégaoctets).
 * @property {number} ENET_HOST_DEFAULT_MAXIMUM_WAITING_DATA - Quantité maximale par défaut de données en attente avant la suspension de l'envoi, fixée à 32 Mo.
 * @property {number} ENET_PEER_DEFAULT_ROUND_TRIP_TIME - Temps d'aller-retour (RTT) par défaut utilisé pour les estimations de latence, fixé à 500 millisecondes.
 * @property {number} ENET_PEER_DEFAULT_PACKET_THROTTLE - Taux de limitation de paquets par défaut, exprimé en pourcentage.
 * @property {number} ENET_PEER_PACKET_THROTTLE_SCALE - Échelle utilisée pour le calcul de la limitation dynamique des paquets.
 * @property {number} ENET_PEER_PACKET_THROTTLE_COUNTER - Compteur initial pour le calcul de la limitation des paquets.
 * @property {number} ENET_PEER_PACKET_THROTTLE_ACCELERATION - Taux d'accélération de la limitation des paquets lors des transmissions réussies.
 * @property {number} ENET_PEER_PACKET_THROTTLE_DECELERATION - Taux de décélération de la limitation des paquets lors des pertes de paquets.
 * @property {number} ENET_PEER_PACKET_THROTTLE_INTERVAL - Intervalle de temps pour l'évaluation et l'ajustement de la limitation des paquets.
 * @property {number} ENET_PEER_PACKET_LOSS_SCALE - Échelle utilisée pour le calcul de la perte de paquets.
 * @property {number} ENET_PEER_PACKET_LOSS_INTERVAL - Intervalle de temps pour l'évaluation de la perte de paquets.
 * @property {number} ENET_PEER_WINDOW_SIZE_SCALE - Facteur d'échelle pour la taille de la fenêtre de fiabilité.
 * @property {number} ENET_PEER_TIMEOUT_LIMIT - Limite de temps avant considération comme déconnecté en cas de non-réponse.
 * @property {number} ENET_PEER_TIMEOUT_MINIMUM - Temps minimum avant déclaration de déconnexion en cas de non-réponse.
 * @property {number} ENET_PEER_TIMEOUT_MAXIMUM - Temps maximum avant déclaration de déconnexion en cas de non-réponse.
 * @property {number} ENET_PEER_PING_INTERVAL - Intervalle de temps entre chaque ping automatique envoyé aux pairs.
 * @property {number} ENET_PEER_UNSEQUENCED_WINDOWS - Nombre de fenêtres pour le suivi des paquets non séquencés.
 * @property {number} ENET_PEER_UNSEQUENCED_WINDOW_SIZE - Taille d'une fenêtre pour le suivi des paquets non séquencés.
 * @property {number} ENET_PEER_FREE_UNSEQUENCED_WINDOWS - Nombre de fenêtres non séquencées libres avant leur réinitialisation.
 * @property {number} ENET_PEER_RELIABLE_WINDOWS - Nombre de fenêtres pour le suivi des paquets fiables.
 * @property {number} ENET_PEER_RELIABLE_WINDOW_SIZE - Taille d'une fenêtre pour le suivi des paquets fiables.
 * @property {number} ENET_PEER_FREE_RELIABLE_WINDOWS - Nombre de fenêtres fiables libres avant leur réinitialisation.
 */
enum
{
   ENET_HOST_RECEIVE_BUFFER_SIZE          = 256 * 1024,
   ENET_HOST_SEND_BUFFER_SIZE             = 256 * 1024,
   ENET_HOST_BANDWIDTH_THROTTLE_INTERVAL  = 1000,
   ENET_HOST_DEFAULT_MTU                  = 1392,
   ENET_HOST_DEFAULT_MAXIMUM_PACKET_SIZE  = 32 * 1024 * 1024,
   ENET_HOST_DEFAULT_MAXIMUM_WAITING_DATA = 32 * 1024 * 1024,
   ENET_PEER_DEFAULT_ROUND_TRIP_TIME      = 500,
   ENET_PEER_DEFAULT_PACKET_THROTTLE      = 32,
   ENET_PEER_PACKET_THROTTLE_SCALE        = 32,
   ENET_PEER_PACKET_THROTTLE_COUNTER      = 7, 
   ENET_PEER_PACKET_THROTTLE_ACCELERATION = 2,
   ENET_PEER_PACKET_THROTTLE_DECELERATION = 2,
   ENET_PEER_PACKET_THROTTLE_INTERVAL     = 5000,
   ENET_PEER_PACKET_LOSS_SCALE            = (1 << 16),
   ENET_PEER_PACKET_LOSS_INTERVAL         = 10000,
   ENET_PEER_WINDOW_SIZE_SCALE            = 64 * 1024,
   ENET_PEER_TIMEOUT_LIMIT                = 32,
   ENET_PEER_TIMEOUT_MINIMUM              = 5000,
   ENET_PEER_TIMEOUT_MAXIMUM              = 30000,
   ENET_PEER_PING_INTERVAL                = 500,
   ENET_PEER_UNSEQUENCED_WINDOWS          = 64,
   ENET_PEER_UNSEQUENCED_WINDOW_SIZE      = 1024,
   ENET_PEER_FREE_UNSEQUENCED_WINDOWS     = 32,
   ENET_PEER_RELIABLE_WINDOWS             = 16,
   ENET_PEER_RELIABLE_WINDOW_SIZE         = 0x1000,
   ENET_PEER_FREE_RELIABLE_WINDOWS        = 8
};

/**
 * Représente un canal de communication entre pairs dans ENet. Chaque canal maintient son propre séquençage de paquets fiables et non fiables.

 * @typedef {struct} ENetChannel 
 * @property {enet_uint16} outgoingReliableSequenceNumber - Numéro de séquence pour le prochain paquet fiable sortant.
 * @property {enet_uint16} outgoingUnreliableSequenceNumber - Numéro de séquence pour le prochain paquet non fiable sortant.
 * @property {enet_uint16} usedReliableWindows - Fenêtres fiables actuellement utilisées (pour le contrôle de flux et la retransmission).
 * @property {enet_uint16[]} reliableWindows - État des fenêtres de séquence fiable pour la retransmission.
 * @property {enet_uint16} incomingReliableSequenceNumber - Numéro de séquence du dernier paquet fiable reçu.
 * @property {enet_uint16} incomingUnreliableSequenceNumber - Numéro de séquence du dernier paquet non fiable reçu.
 * @property {ENetList} incomingReliableCommands - Liste des commandes fiables entrantes en attente d'être traitées.
 * @property {ENetList} incomingUnreliableCommands - Liste des commandes non fiables entrantes en attente d'être traitées.
 */
typedef struct _ENetChannel
{
   enet_uint16  outgoingReliableSequenceNumber;
   enet_uint16  outgoingUnreliableSequenceNumber;
   enet_uint16  usedReliableWindows;
   enet_uint16  reliableWindows [ENET_PEER_RELIABLE_WINDOWS];
   enet_uint16  incomingReliableSequenceNumber;
   enet_uint16  incomingUnreliableSequenceNumber;
   ENetList     incomingReliableCommands;
   ENetList     incomingUnreliableCommands;
} ENetChannel;

/**
 * @enum _ENetPeerFlag
 * Drapeaux utilisés pour contrôler l'état et le comportement des pairs ENet.
 * 
 * @property {number} ENET_PEER_FLAG_NEEDS_DISPATCH - Indique que le pair nécessite une expédition de messages en attente.
 * @property {number} ENET_PEER_FLAG_CONTINUE_SENDING - Indique que le pair doit continuer à envoyer des paquets même après avoir atteint la limite de bande passante.
 */
typedef enum _ENetPeerFlag
{
   ENET_PEER_FLAG_NEEDS_DISPATCH   = (1 << 0),
   ENET_PEER_FLAG_CONTINUE_SENDING = (1 << 1)
} ENetPeerFlag;

/**
 * @typedef {struct} ENetPeer
 * Représente un pair distant avec lequel des paquets de données peuvent être échangés.
 * 
 * @property {ENetListNode} dispatchList - Utilisé en interne pour la gestion des messages.
 * @property {struct _ENetHost *} host - Pointeur vers l'hôte associé à ce pair.
 * @property {enet_uint16} outgoingPeerID - Identifiant du pair pour les connexions sortantes.
 * @property {enet_uint16} incomingPeerID - Identifiant du pair pour les connexions entrantes.
 * @property {enet_uint32} connectID - Identifiant unique de la connexion.
 * @property {enet_uint8} outgoingSessionID - Identifiant de session pour les données sortantes.
 * @property {enet_uint8} incomingSessionID - Identifiant de session pour les données entrantes.
 * @property {ENetAddress} address - Adresse Internet du pair.
 * @property {void *} data - Données privées de l'application, modifiables librement.
 * @property {ENetPeerState} state - État actuel de la connexion du pair.
 * @property {ENetChannel *} channels - Tableau des canaux de communication avec ce pair.
 * @property {size_t} channelCount - Nombre de canaux alloués pour ce pair.
 * @property {enet_uint32} incomingBandwidth - Bande passante entrante en octets par seconde.
 * @property {enet_uint32} outgoingBandwidth - Bande passante sortante en octets par seconde.
 * @property {enet_uint32} incomingBandwidthThrottleEpoch - Utilisé en interne pour le contrôle de la bande passante.
 * @property {enet_uint32} outgoingBandwidthThrottleEpoch - Utilisé en interne pour le contrôle de la bande passante.
 * @property {enet_uint32} incomingDataTotal - Total des données entrantes depuis la dernière évaluation.
 * @property {enet_uint32} outgoingDataTotal - Total des données sortantes depuis la dernière évaluation.
 * @property {enet_uint32} lastSendTime - Dernier moment où des données ont été envoyées.
 * @property {enet_uint32} lastReceiveTime - Dernier moment où des données ont été reçues.
 * @property {enet_uint32} nextTimeout - Moment du prochain délai d'attente pour le contrôle de la connexion.
 * @property {enet_uint32} earliestTimeout - Plus proche délai d'attente pour le contrôle de la connexion.
 * @property {enet_uint32} packetLossEpoch - Utilisé en interne pour le calcul de la perte de paquets.
 * @property {enet_uint32} packetsSent - Nombre total de paquets envoyés.
 * @property {enet_uint32} packetsLost - Nombre total de paquets perdus.
 * @property {enet_uint32} packetLoss - Perte de paquets moyenne en tant que ratio.
 * @property {enet_uint32} packetLossVariance - Variance de la perte de paquets.
 * @property {enet_uint32} packetThrottle - Limite actuelle de la régulation des paquets.
 * @property {enet_uint32} packetThrottleLimit - Limite maximale de la régulation des paquets.
 * @property {enet_uint32} packetThrottleCounter - Compteur utilisé pour la régulation des paquets.
 * @property {enet_uint32} packetThrottleEpoch - Dernière évaluation de la régulation des paquets.
 * @property {enet_uint32} packetThrottleAcceleration - Accélération de la régulation des paquets lors des transmissions réussies.
 * @property {enet_uint32} packetThrottleDeceleration - Décélération de la régulation des paquets lors des pertes.
 * @property {enet_uint32} packetThrottleInterval - Intervalle d'évaluation de la régulation des paquets.
 * @property {enet_uint32} pingInterval - Intervalle entre les pings automatiques envoyés à ce pair.
 * @property {enet_uint32} timeoutLimit - Limite de temps avant que le pair soit considéré comme déconnecté.
 * @property {enet_uint32} timeoutMinimum - Temps minimum avant déclaration de déconnexion.
 * @property {enet_uint32} timeoutMaximum - Temps maximum avant déclaration de déconnexion.
 * @property {enet_uint32} lastRoundTripTime - Dernier temps d'aller-retour mesuré.
 * @property {enet_uint32} lowestRoundTripTime - Plus bas temps d'aller-retour mesuré.
 * @property {enet_uint32} lastRoundTripTimeVariance - Variance du dernier temps d'aller-retour.
 * @property {enet_uint32} highestRoundTripTimeVariance - Plus haute variance du temps d'aller-retour mesurée.
 * @property {enet_uint32} roundTripTime - Temps d'aller-retour moyen.
 * @property {enet_uint32} roundTripTimeVariance - Variance du temps d'aller-retour.
 * @property {enet_uint32} mtu - Unité de transmission maximale pour ce pair.
 * @property {enet_uint32} windowSize - Taille de la fenêtre de contrôle de flux.
 * @property {enet_uint32} reliableDataInTransit - Quantité de données fiables en transit.
 * @property {enet_uint16} outgoingReliableSequenceNumber - Numéro de séquence pour le prochain paquet fiable sortant.
 * @property {ENetList} acknowledgements - Liste des accusés de réception à envoyer.
 * @property {ENetList} sentReliableCommands - Liste des commandes fiables envoyées mais pas encore acquittées.
 * @property {ENetList} outgoingSendReliableCommands - Liste des commandes fiables prêtes à être envoyées.
 * @property {ENetList} outgoingCommands - Liste des commandes prêtes à être envoyées.
 * @property {ENetList} dispatchedCommands - Liste des commandes déjà expédiées.
 * @property {enet_uint16} flags - Drapeaux de comportement pour ce pair.
 * @property {enet_uint16} reserved - Champ réservé pour un usage futur.
 * @property {enet_uint16} incomingUnsequencedGroup - Groupe pour les paquets non séquencés entrants.
 * @property {enet_uint16} outgoingUnsequencedGroup - Groupe pour les paquets non séquencés sortants.
 * @property {enet_uint32[]} unsequencedWindow - Fenêtre pour le suivi des paquets non séquencés.
 * @property {enet_uint32} eventData - Données d'événement associées à la dernière action de ce pair.
 * @property {size_t} totalWaitingData - Quantité totale de données en attente d'être envoyées à ce pair.
 */
typedef struct _ENetPeer
{ 
   ENetListNode  dispatchList;
   struct _ENetHost * host;
   enet_uint16   outgoingPeerID;
   enet_uint16   incomingPeerID;
   enet_uint32   connectID;
   enet_uint8    outgoingSessionID;
   enet_uint8    incomingSessionID;
   ENetAddress   address;
   void *        data;
   ENetPeerState state;
   ENetChannel * channels;
   size_t        channelCount;
   enet_uint32   incomingBandwidth;
   enet_uint32   outgoingBandwidth;
   enet_uint32   incomingBandwidthThrottleEpoch;
   enet_uint32   outgoingBandwidthThrottleEpoch;
   enet_uint32   incomingDataTotal;
   enet_uint32   outgoingDataTotal;
   enet_uint32   lastSendTime;
   enet_uint32   lastReceiveTime;
   enet_uint32   nextTimeout;
   enet_uint32   earliestTimeout;
   enet_uint32   packetLossEpoch;
   enet_uint32   packetsSent;
   enet_uint32   packetsLost;
   enet_uint32   packetLoss;
   enet_uint32   packetLossVariance;
   enet_uint32   packetThrottle;
   enet_uint32   packetThrottleLimit;
   enet_uint32   packetThrottleCounter;
   enet_uint32   packetThrottleEpoch;
   enet_uint32   packetThrottleAcceleration;
   enet_uint32   packetThrottleDeceleration;
   enet_uint32   packetThrottleInterval;
   enet_uint32   pingInterval;
   enet_uint32   timeoutLimit;
   enet_uint32   timeoutMinimum;
   enet_uint32   timeoutMaximum;
   enet_uint32   lastRoundTripTime;
   enet_uint32   lowestRoundTripTime;
   enet_uint32   lastRoundTripTimeVariance;
   enet_uint32   highestRoundTripTimeVariance;
   enet_uint32   roundTripTime;
   enet_uint32   roundTripTimeVariance;
   enet_uint32   mtu;
   enet_uint32   windowSize;
   enet_uint32   reliableDataInTransit;
   enet_uint16   outgoingReliableSequenceNumber;
   ENetList      acknowledgements;
   ENetList      sentReliableCommands;
   ENetList      outgoingSendReliableCommands;
   ENetList      outgoingCommands;
   ENetList      dispatchedCommands;
   enet_uint16   flags;
   enet_uint16   reserved;
   enet_uint16   incomingUnsequencedGroup;
   enet_uint16   outgoingUnsequencedGroup;
   enet_uint32   unsequencedWindow [ENET_PEER_UNSEQUENCED_WINDOW_SIZE / 32]; 
   enet_uint32   eventData;
   size_t        totalWaitingData;
} ENetPeer;

/**
 * @typedef {struct} ENetCompressor
 * Structure pour la compression des paquets UDP avant leur envoi ou réception par le socket.
 *
 * @property {void*} context - Données de contexte pour le compresseur. Doit être non NULL.
 * @property {function} compress - Fonction pour compresser des données. Prend un tableau de ENetBuffer comme entrée,
 * contenant inLimit octets, compresse les données dans outData, et sort au maximum outLimit octets. Devrait retourner 0 en cas d'échec.
 * @property {function} decompress - Fonction pour décompresser des données. Prend inData, contenant inLimit octets,
 * décompresse les données dans outData, et sort au maximum outLimit octets. Devrait retourner 0 en cas d'échec.
 * @property {function} destroy - Fonction appelée lorsque la compression est désactivée ou que l'hôte est détruit. Peut être NULL.
 */
typedef struct _ENetCompressor
{
   void * context;
   size_t (ENET_CALLBACK * compress) (void * context, const ENetBuffer * inBuffers, size_t inBufferCount, size_t inLimit, enet_uint8 * outData, size_t outLimit);
   size_t (ENET_CALLBACK * decompress) (void * context, const enet_uint8 * inData, size_t inLimit, enet_uint8 * outData, size_t outLimit);
   void (ENET_CALLBACK * destroy) (void * context);
} ENetCompressor;

/**
 * @typedef {struct} ENetEncryptor
 * Structure pour le chiffrement des paquets UDP avant leur envoi ou réception (se produit avant la compression).
 * Similaire à ENetCompressor, mais reçoit également le pair expéditeur/récepteur comme paramètre et peut produire un paquet plus grand lors du chiffrement.
 *
 * @property {void*} context - Données de contexte pour l'encrypteur. Doit être non NULL.
 * @property {function} encrypt - Fonction pour chiffrer des données. Prend un tableau de ENetBuffer comme entrée,
 * contenant inLimit octets, chiffre les données dans outData, et sort au maximum outLimit octets. Devrait retourner 0 en cas d'échec.
 * @property {function} decrypt - Fonction pour déchiffrer un paquet reçu du pair (peut être NULL si paquet de connexion),
 * à partir de inData, contenant inLimit octets, déchiffre les données dans outData, et sort au maximum outLimit octets. Devrait retourner 0 en cas d'échec.
 * @property {function} destroy - Fonction appelée lorsque le chiffrement est désactivé ou que l'hôte est détruit. Peut être NULL.
 */
typedef struct _ENetEncryptor
{
   void * context;
   size_t (ENET_CALLBACK * encrypt) (void * context, ENetPeer * peer, const ENetBuffer * inBuffers, size_t inBufferCount, size_t inLimit, enet_uint8 * outData, size_t outLimit);
   size_t (ENET_CALLBACK * decrypt) (void * context, ENetPeer * peer, const enet_uint8 * inData, size_t inLimit, enet_uint8 * outData, size_t outLimit);
   void (ENET_CALLBACK * destroy) (void * context);
} ENetEncryptor;

/**
 * @callback ENetChecksumCallback
 * Callback qui calcule le checksum des données contenues dans les buffers. Cette fonction est utilisée pour
 * vérifier l'intégrité des données transmises.
 *
 * @param {ENetBuffer[]} buffers - Tableau des buffers contenant les données pour lesquelles calculer le checksum.
 * @param {size_t} bufferCount - Nombre de buffers dans le tableau.
 * @returns {enet_uint32} Le checksum calculé des données.
 */
typedef enet_uint32 (ENET_CALLBACK * ENetChecksumCallback) (const ENetBuffer * buffers, size_t bufferCount);

/**
 * @callback ENetInterceptCallback
 * Callback pour intercepter les paquets UDP bruts reçus. Cette fonction permet d'inspecter, de modifier ou d'ignorer
 * des paquets avant qu'ils soient traités par ENet.
 *
 * @param {struct _ENetHost*} host - L'hôte ENet recevant le paquet.
 * @param {struct _ENetEvent*} event - L'événement ENet associé au paquet reçu.
 * @returns {int} Doit retourner 1 pour intercepter le paquet, 0 pour l'ignorer, ou -1 pour propager une erreur.
 */
typedef int (ENET_CALLBACK * ENetInterceptCallback) (struct _ENetHost * host, struct _ENetEvent * event);
 
/**
 * Représente un hôte ENet pour la communication avec les pairs. C'est le point central pour gérer les connexions réseau.
 *
 * IMPORTANT: Aucun champ ne doit être modifié sauf indication contraire.
 *   @sa enet_host_create()
 *   @sa enet_host_destroy()
 *   @sa enet_host_connect()
 *   @sa enet_host_service()
 *   @sa enet_host_flush()
 *   @sa enet_host_broadcast()
 *   @sa enet_host_compress()
 *   @sa enet_host_compress_with_range_coder()
 *   @sa enet_host_channel_limit()
 *   @sa enet_host_bandwidth_limit()
 *   @sa enet_host_bandwidth_throttle()
 * 
 * @typedef {struct} ENetHost
 * @property {ENetSocket} socket - Socket de l'hôte utilisé pour la communication UDP.
 * @property {ENetAddress} address - Adresse Internet de l'hôte.
 * @property {enet_uint32} incomingBandwidth - Bande passante descendante de l'hôte en octets par seconde.
 * @property {enet_uint32} outgoingBandwidth - Bande passante montante de l'hôte en octets par seconde.
 * @property {enet_uint32} bandwidthThrottleEpoch - Utilisé en interne pour le calcul de la limitation de la bande passante.
 * @property {enet_uint32} mtu - Unité de transmission maximale pour les paquets envoyés par cet hôte.
 * @property {enet_uint32} randomSeed - Graine aléatoire utilisée en interne par ENet.
 * @property {int} recalculateBandwidthLimits - Indique si les limites de bande passante doivent être recalculées.
 * @property {ENetPeer*} peers - Tableau de pairs alloués pour cet hôte.
 * @property {size_t} peerCount - Nombre de pairs alloués pour cet hôte.
 * @property {size_t} channelLimit - Limite maximale du nombre de canaux autorisés pour les pairs connectés.
 * @property {enet_uint32} serviceTime - Horodatage du dernier appel à enet_host_service().
 * @property {ENetList} dispatchQueue - File d'attente des événements à dispatcher vers l'utilisateur.
 * @property {enet_uint32} totalQueued - Total des paquets en file d'attente pour l'envoi.
 * @property {size_t} packetSize - Taille du dernier paquet envoyé ou reçu.
 * @property {enet_uint16} headerFlags - Drapeaux d'en-tête pour les paquets envoyés.
 * @property {ENetProtocol[]} commands - Tableau des commandes du protocole à envoyer.
 * @property {size_t} commandCount - Nombre de commandes dans le tableau `commands`.
 * @property {ENetBuffer[]} buffers - Tableau de buffers pour les données à envoyer.
 * @property {size_t} bufferCount - Nombre de buffers utilisés.
 * @property {ENetChecksumCallback} checksum - Callback pour le calcul de checksum des paquets.
 * @property {ENetCompressor} compressor - Compresseur pour la compression des données des paquets.
 * @property {enet_uint8[][]} packetData - Deux tableaux de données de paquets pour l'envoi et la réception.
 * @property {ENetAddress} receivedAddress - Adresse de l'expéditeur du dernier paquet reçu.
 * @property {enet_uint8*} receivedData - Données du dernier paquet reçu.
 * @property {size_t} receivedDataLength - Longueur des données du dernier paquet reçu.
 * @property {enet_uint32} totalSentData - Total des données envoyées.
 * @property {enet_uint32} totalSentPackets - Total des paquets UDP envoyés.
 * @property {enet_uint32} totalReceivedData - Total des données reçues.
 * @property {enet_uint32} totalReceivedPackets - Total des paquets UDP reçus.
 * @property {ENetInterceptCallback} intercept - Callback pour l'interception des paquets UDP bruts reçus.
 * @property {size_t} connectedPeers - Nombre de pairs actuellement connectés.
 * @property {size_t} bandwidthLimitedPeers - Nombre de pairs avec la bande passante limitée.
 * @property {size_t} duplicatePeers - Nombre autorisé de pairs depuis des adresses IP dupliquées.
 * @property {size_t} maximumPacketSize - Taille maximale autorisée des paquets pouvant être envoyés ou reçus.
 * @property {size_t} maximumWaitingData - Quantité maximale agrégée de données qu'un pair peut utiliser en attente de la livraison des paquets.
 * @property {ENetEncryptor} encryptor - Encrypteur pour le chiffrement des paquets UDP avant leur envoi ou réception.
 */
typedef struct _ENetHost
{
   ENetSocket           socket;
   ENetAddress          address;
   enet_uint32          incomingBandwidth;
   enet_uint32          outgoingBandwidth;
   enet_uint32          bandwidthThrottleEpoch;
   enet_uint32          mtu;
   enet_uint32          randomSeed;
   int                  recalculateBandwidthLimits;
   ENetPeer *           peers;
   size_t               peerCount;
   size_t               channelLimit;
   enet_uint32          serviceTime;
   ENetList             dispatchQueue;
   enet_uint32          totalQueued;
   size_t               packetSize;
   enet_uint16          headerFlags;
   ENetProtocol         commands [ENET_PROTOCOL_MAXIMUM_PACKET_COMMANDS];
   size_t               commandCount;
   ENetBuffer           buffers [ENET_BUFFER_MAXIMUM];
   size_t               bufferCount;
   ENetChecksumCallback checksum;
   ENetCompressor       compressor;
   enet_uint8           packetData [2][ENET_PROTOCOL_MAXIMUM_MTU];
   ENetAddress          receivedAddress;
   enet_uint8 *         receivedData;
   size_t               receivedDataLength;
   enet_uint32          totalSentData;
   enet_uint32          totalSentPackets;
   enet_uint32          totalReceivedData;
   enet_uint32          totalReceivedPackets;
   ENetInterceptCallback intercept;
   size_t               connectedPeers;
   size_t               bandwidthLimitedPeers;
   size_t               duplicatePeers;
   size_t               maximumPacketSize;
   size_t               maximumWaitingData;
   /* rcenet fields start here */
   ENetEncryptor        encryptor;
} ENetHost;

/**
 * Enumération des types d'événements dans ENet. Ces événements sont renvoyés par enet_host_service() et décrivent les différentes actions ou changements d'état qui peuvent survenir sur un hôte ou un pair.
 
 * @typedef {enum} _ENetEventType
 * @property {number} ENET_EVENT_TYPE_NONE - Aucun événement ne s'est produit dans le délai spécifié. Utilisé pour indiquer qu'aucune action ou requête n'a été reçue.
 * @property {number} ENET_EVENT_TYPE_CONNECT - Un pair s'est connecté avec succès. Cet événement est généré après la complétion réussie d'une requête de connexion initiée par enet_host_connect(). Le champ peer contient le pair qui s'est connecté.
 * @property {number} ENET_EVENT_TYPE_DISCONNECT - Un pair s'est déconnecté. Cet événement est généré lorsqu'une déconnexion initiée par enet_peer_disconnect() se termine avec succès. Le champ peer contient le pair qui s'est déconnecté. Le champ data contient des données fournies par l'utilisateur décrivant la déconnexion, ou 0 s'il n'y en a pas.
 * @property {number} ENET_EVENT_TYPE_RECEIVE - Un paquet a été reçu d'un pair. Le champ peer spécifie le pair qui a envoyé le paquet. Le champ channelID spécifie le numéro de canal sur lequel le paquet a été reçu. Le champ packet contient le paquet qui a été reçu; ce paquet doit être détruit avec enet_packet_destroy après utilisation.
 * @property {number} ENET_EVENT_TYPE_DISCONNECT_TIMEOUT - Un pair s'est déconnecté en raison d'un délai d'expiration. Cet événement est généré si un pair se déconnecte après un délai d'expiration, ou si une requête de connexion initiée par enet_host_connect() expire. Le champ peer contient le pair qui s'est déconnecté. Le champ data contient des données fournies par l'utilisateur décrivant la déconnexion, ou 0 s'il n'y en a pas.
 */
typedef enum _ENetEventType
{
   ENET_EVENT_TYPE_NONE       = 0,  
   ENET_EVENT_TYPE_CONNECT    = 1,  
   ENET_EVENT_TYPE_DISCONNECT = 2,  
   ENET_EVENT_TYPE_RECEIVE    = 3,
   ENET_EVENT_TYPE_DISCONNECT_TIMEOUT = 4,
} ENetEventType;

/**
 * @typedef {struct} ENetEvent
 * Représente un événement ENet tel que renvoyé par enet_host_service(). Cette structure contient toutes les informations nécessaires pour traiter l'événement, y compris le type d'événement, le pair concerné, et toute donnée ou paquet associé.
 *
 * @property {ENetEventType} type - Le type de l'événement. Décrit l'action ou le changement d'état qui s'est produit.
 * @property {ENetPeer*} peer - Le pair qui a généré un événement de connexion, de déconnexion ou de réception. Null pour les événements ENET_EVENT_TYPE_NONE.
 * @property {enet_uint8} channelID - Le canal sur le pair qui a généré l'événement, le cas échéant. Pertinent pour les événements de type ENET_EVENT_TYPE_RECEIVE.
 * @property {enet_uint32} data - Données associées à l'événement, le cas échéant. Pour les événements de type ENET_EVENT_TYPE_DISCONNECT et ENET_EVENT_TYPE_DISCONNECT_TIMEOUT, cela peut contenir des données fournies par l'utilisateur lors de la déconnexion.
 * @property {ENetPacket*} packet - Le paquet associé à l'événement, le cas échéant. Pertinent pour les événements de type ENET_EVENT_TYPE_RECEIVE. Le paquet doit être détruit avec enet_packet_destroy après utilisation.
 */
typedef struct _ENetEvent 
{
   ENetEventType        type;
   ENetPeer *           peer;
   enet_uint8           channelID;
   enet_uint32          data;
   ENetPacket *         packet;
} ENetEvent;

/** 
  Initializes ENet globally.  Must be called prior to using any functions in
  ENet.
  @returns 0 on success, < 0 on failure
*/
ENET_API int enet_initialize (void);

/** 
  Initializes ENet globally and supplies user-overridden callbacks. Must be called prior to using any functions in ENet. Do not use enet_initialize() if you use this variant. Make sure the ENetCallbacks structure is zeroed out so that any additional callbacks added in future versions will be properly ignored.

  @param version the constant ENET_VERSION should be supplied so ENet knows which version of ENetCallbacks struct to use
  @param inits user-overridden callbacks where any NULL callbacks will use ENet's defaults
  @returns 0 on success, < 0 on failure
*/
ENET_API int enet_initialize_with_callbacks (ENetVersion version, const ENetCallbacks * inits);

/** 
  Shuts down ENet globally.  Should be called when a program that has
  initialized ENet exits.
*/
ENET_API void enet_deinitialize (void);

/**
  Gives the linked version of the ENet library.
  @returns the version number 
*/
ENET_API ENetVersion enet_linked_version (void);

/** @defgroup private ENet private implementation functions */

/**
  Returns the wall-time in milliseconds.  Its initial value is unspecified
  unless otherwise set.
  */
ENET_API enet_uint32 enet_time_get (void);
/**
  Sets the current wall-time in milliseconds.
  */
ENET_API void enet_time_set (enet_uint32);

/** @defgroup socket ENet socket functions
*/
ENET_API ENetSocket enet_socket_create (ENetAddressType, ENetSocketType);
ENET_API int        enet_socket_bind (ENetSocket, const ENetAddress *);
ENET_API int        enet_socket_get_address (ENetSocket, ENetAddress *);
ENET_API int        enet_socket_listen (ENetSocket, int);
ENET_API ENetSocket enet_socket_accept (ENetSocket, ENetAddress *);
ENET_API int        enet_socket_connect (ENetSocket, const ENetAddress *);
ENET_API int        enet_socket_send (ENetSocket, const ENetAddress *, const ENetBuffer *, size_t);
ENET_API int        enet_socket_receive (ENetSocket, ENetAddress *, ENetBuffer *, size_t);
ENET_API int        enet_socket_wait (ENetSocket, enet_uint32 *, enet_uint32);
ENET_API int        enet_socket_set_option (ENetSocket, ENetSocketOption, int);
ENET_API int        enet_socket_get_option (ENetSocket, ENetSocketOption, int *);
ENET_API int        enet_socket_shutdown (ENetSocket, ENetSocketShutdown);
ENET_API void       enet_socket_destroy (ENetSocket);
ENET_API int        enet_socketset_select (ENetSocket, ENetSocketSet *, ENetSocketSet *, enet_uint32);

/** Compares two addresses (only the host part)
    @param firstAddress first address to compare
    @param secondAddress second address to compare
    @retval 1 if addresses are equal
    @retval 0 if addresses are different
    @returns if the addresses are equal
*/
ENET_API int enet_address_equal_host (const ENetAddress * firstAddress, const ENetAddress * secondAddress);

/** Compares two addresses and their port
    @param firstAddress first address to compare
    @param secondAddress second address to compare
    @retval 1 if addresses are equal
    @retval 0 if addresses are different
    @returns if the addresses are equal
*/
ENET_API int enet_address_equal(const ENetAddress * firstAddress, const ENetAddress * secondAddress);

/** Checks if an address is the special any address
    @param address address to check
    @retval 1 if address is any
    @returns if the address is the any one for its family
*/
ENET_API int enet_address_is_any(const ENetAddress * address);

/** Checks if an address is the special broadcast address
    @param address address to check
    @retval 1 if address is broadcast
    @returns if the address is the broadcast one for its family
*/
ENET_API int enet_address_is_broadcast(const ENetAddress * address);

/** Checks if an address is a loopback one
    @param address address to check
    @retval 1 if address is loopback
    @returns if the address is a loopback one for its family
*/
ENET_API int enet_address_is_loopback(const ENetAddress * address);

/** Attempts to parse the printable form of the IP address in the parameter hostName
    and sets the host field in the address parameter if successful.
    @param address destination to store the parsed IP address
    @param hostName IP address to parse
    @retval 0 on success
    @retval < 0 on failure
    @returns the address of the given hostName in address on success
*/
ENET_API int enet_address_set_host_ip (ENetAddress * address, const char * hostName);

/** Attempts to resolve the host named by the parameter hostName and sets
    the host field in the address parameter if successful.
    @param type address type (any/ipv4/ipv6)
    @param address destination to store resolved address
    @param hostName host name to lookup
    @retval 0 on success
    @retval < 0 on failure
    @returns the address of the given hostName in address on success
*/
ENET_API int enet_address_set_host (ENetAddress * address, ENetAddressType type, const char * hostName);

#define ENET_ADDRESS_MAX_LENGTH 40 /*full IPv6 addresses take 39 characters + 1 null byte */

/** Gives the printable form of the IP address specified in the address parameter.
    @param address    address printed
    @param hostName   destination for name, must not be NULL
    @param nameLength maximum length of hostName.
    @returns the null-terminated name of the host in hostName on success
    @retval 0 on success
    @retval < 0 on failure
*/
ENET_API int enet_address_get_host_ip (const ENetAddress * address, char * hostName, size_t nameLength);

/** Attempts to do a reverse lookup of the host field in the address parameter.
    @param address    address used for reverse lookup
    @param hostName   destination for name, must not be NULL
    @param nameLength maximum length of hostName.
    @returns the null-terminated name of the host in hostName on success
    @retval 0 on success
    @retval < 0 on failure
*/
ENET_API int enet_address_get_host (const ENetAddress * address, char * hostName, size_t nameLength);

ENET_API void enet_address_build_any(ENetAddress * address, ENetAddressType type);
ENET_API void enet_address_build_loopback(ENetAddress * address, ENetAddressType type);
ENET_API void enet_address_convert_ipv6(ENetAddress * address);

ENET_API ENetPacket * enet_packet_create (const void *, size_t, enet_uint32);
ENET_API void         enet_packet_destroy (ENetPacket *);
ENET_API int          enet_packet_resize  (ENetPacket *, size_t);
ENET_API enet_uint32  enet_crc32 (const ENetBuffer *, size_t);

ENET_API ENetHost * enet_host_create (ENetAddressType type, const ENetAddress *, size_t, size_t, enet_uint32, enet_uint32);
ENET_API void       enet_host_destroy (ENetHost *);
ENET_API ENetPeer * enet_host_connect (ENetHost *, const ENetAddress *, size_t, enet_uint32);
ENET_API int        enet_host_check_events (ENetHost *, ENetEvent *);
ENET_API int        enet_host_service (ENetHost *, ENetEvent *, enet_uint32);
ENET_API void       enet_host_flush (ENetHost *);
ENET_API void       enet_host_broadcast (ENetHost *, enet_uint8, ENetPacket *);
ENET_API void       enet_host_compress (ENetHost *, const ENetCompressor *);
ENET_API int        enet_host_compress_with_range_coder (ENetHost * host);
ENET_API void       enet_host_channel_limit (ENetHost *, size_t);
ENET_API void       enet_host_bandwidth_limit (ENetHost *, enet_uint32, enet_uint32);
extern   void       enet_host_bandwidth_throttle (ENetHost *);
extern  enet_uint32 enet_host_random_seed (void);
extern  enet_uint32 enet_host_random (ENetHost *);
ENET_API void       enet_host_encrypt(ENetHost*, const ENetEncryptor*);

ENET_API int                 enet_peer_send (ENetPeer *, enet_uint8, ENetPacket *);
ENET_API ENetPacket *        enet_peer_receive (ENetPeer *, enet_uint8 * channelID);
ENET_API void                enet_peer_ping (ENetPeer *);
ENET_API void                enet_peer_ping_interval (ENetPeer *, enet_uint32);
ENET_API void                enet_peer_timeout (ENetPeer *, enet_uint32, enet_uint32, enet_uint32);
ENET_API void                enet_peer_reset (ENetPeer *);
ENET_API void                enet_peer_disconnect (ENetPeer *, enet_uint32);
ENET_API void                enet_peer_disconnect_now (ENetPeer *, enet_uint32);
ENET_API void                enet_peer_disconnect_later (ENetPeer *, enet_uint32);
ENET_API void                enet_peer_throttle_configure (ENetPeer *, enet_uint32, enet_uint32, enet_uint32);
extern int                   enet_peer_throttle (ENetPeer *, enet_uint32);
extern void                  enet_peer_reset_queues (ENetPeer *);
extern int                   enet_peer_has_outgoing_commands (ENetPeer *);
extern void                  enet_peer_setup_outgoing_command (ENetPeer *, ENetOutgoingCommand *);
extern ENetOutgoingCommand * enet_peer_queue_outgoing_command (ENetPeer *, const ENetProtocol *, ENetPacket *, enet_uint32, enet_uint16);
extern ENetIncomingCommand * enet_peer_queue_incoming_command (ENetPeer *, const ENetProtocol *, const void *, size_t, enet_uint32, enet_uint32);
extern ENetAcknowledgement * enet_peer_queue_acknowledgement (ENetPeer *, const ENetProtocol *, enet_uint16);
extern void                  enet_peer_dispatch_incoming_unreliable_commands (ENetPeer *, ENetChannel *, ENetIncomingCommand *);
extern void                  enet_peer_dispatch_incoming_reliable_commands (ENetPeer *, ENetChannel *, ENetIncomingCommand *);
extern void                  enet_peer_on_connect (ENetPeer *);
extern void                  enet_peer_on_disconnect (ENetPeer *);

ENET_API void * enet_range_coder_create (void);
ENET_API void   enet_range_coder_destroy (void *);
ENET_API size_t enet_range_coder_compress (void *, const ENetBuffer *, size_t, size_t, enet_uint8 *, size_t);
ENET_API size_t enet_range_coder_decompress (void *, const enet_uint8 *, size_t, enet_uint8 *, size_t);

extern size_t enet_protocol_command_size (enet_uint8);

/** @defgroup Extended API for easier binding in other programming languages
   For binding ENet to other programming languages, 
   the following functions are provided to make it easier to use ENet in those languages.
    @{
*/

ENET_API void* enet_packet_get_data(const ENetPacket*);
ENET_API void* enet_packet_get_user_data(const ENetPacket*);
ENET_API void enet_packet_set_user_data(ENetPacket*, void* userData);
ENET_API int enet_packet_get_length(const ENetPacket*);
ENET_API void enet_packet_set_acknowledge_callback(ENetPacket*, ENetPacketAcknowledgedCallback);
ENET_API void enet_packet_set_free_callback(ENetPacket*, ENetPacketFreeCallback);
ENET_API int enet_packet_check_references(const ENetPacket*);
ENET_API void enet_packet_dispose(ENetPacket*);

ENET_API enet_uint32 enet_host_get_peers_count(const ENetHost*);
ENET_API enet_uint32 enet_host_get_packets_sent(const ENetHost*);
ENET_API enet_uint32 enet_host_get_packets_received(const ENetHost*);
ENET_API enet_uint32 enet_host_get_bytes_sent(const ENetHost*);
ENET_API enet_uint32 enet_host_get_bytes_received(const ENetHost*);
ENET_API void enet_host_set_max_duplicate_peers(ENetHost*, enet_uint16);
ENET_API void enet_host_set_intercept_callback(ENetHost*, ENetInterceptCallback);
ENET_API void enet_host_set_checksum_callback(ENetHost*, ENetChecksumCallback);

ENET_API enet_uint32 enet_peer_get_id(const ENetPeer*);
ENET_API int enet_peer_get_ip(const ENetPeer*, char*, size_t);
ENET_API enet_uint16 enet_peer_get_port(const ENetPeer*);
ENET_API enet_uint32 enet_peer_get_mtu(const ENetPeer*);
ENET_API ENetPeerState enet_peer_get_state(const ENetPeer*);
ENET_API enet_uint32 enet_peer_get_rtt(const ENetPeer*);
ENET_API enet_uint32 enet_peer_get_last_rtt(const ENetPeer* peer);
ENET_API enet_uint32 enet_peer_get_lastsendtime(const ENetPeer*);
ENET_API enet_uint32 enet_peer_get_lastreceivetime(const ENetPeer*);
ENET_API float enet_peer_get_packets_throttle(const ENetPeer*);
ENET_API void* enet_peer_get_data(const ENetPeer*);
ENET_API void enet_peer_set_data(ENetPeer*, const void*);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // RCENET_ENET_H