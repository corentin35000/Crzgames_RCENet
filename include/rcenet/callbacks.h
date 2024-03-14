/**
 * @file callbacks.h
 * @brief Gestion des rappels internes de RCENet pour les opérations d'allocation mémoire.
 *
 * Ce fichier définit un ensemble de callbacks (fonctions de rappel) utilisés par RCENet pour gérer dynamiquement
 * l'allocation et la libération de la mémoire pendant son exécution. Ces callbacks permettent une personnalisation
 * avancée de la gestion de la mémoire, pouvant être adaptée selon les besoins spécifiques de l'application utilisant RCENet.
 */

#ifndef RCENET_CALLBACKS_H
#define RCENET_CALLBACKS_H

#include <stdlib.h> // Required for : size_t

/**
 * Cette structure définit un ensemble de fonctions de rappel pour la personnalisation de l'allocation mémoire dans RCENet.
 * Les utilisateurs peuvent définir ces rappels pour utiliser leurs propres mécanismes d'allocation et de libération de mémoire,
 * permettant ainsi une intégration plus fine avec les systèmes de gestion de mémoire spécifiques de leurs applications.
 * 
 * @typedef {struct} ENetCallbacks
 * @param malloc Fonction de rappel pour allouer de la mémoire. Doit retourner un pointeur vers le bloc de mémoire alloué ou NULL en cas d'échec.
 * @param free Fonction de rappel pour libérer de la mémoire précédemment allouée, permettant une gestion de mémoire efficace et flexible.
 * @param no_memory Fonction de rappel invoquée lorsqu'une tentative d'allocation mémoire échoue, offrant une opportunité de gestion des erreurs liées à la mémoire.
 */
typedef struct _ENetCallbacks
{
    void * (ENET_CALLBACK * malloc) (size_t size);
    void (ENET_CALLBACK * free) (void * memory);
    void (ENET_CALLBACK * no_memory) (void);
} ENetCallbacks;

extern void * enet_malloc (size_t);
extern void   enet_free (void *);

#endif // RCENET_CALLBACKS_H