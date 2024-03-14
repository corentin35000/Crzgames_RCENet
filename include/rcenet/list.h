/** 
 * @file  list.h
 * @brief Gestion des listes chaînées pour RCENet.
 *
 * Ce fichier implémente les fonctions de base pour la gestion de listes chaînées doublement liées.
 * Il fournit des mécanismes pour insérer, supprimer, et itérer sur les éléments de la liste de manière efficace.
 * La structure de liste dans RCENet est utilisée dans diverses parties du framework pour gérer les collections d'objets.
 */

#ifndef RCENET_LIST_H
#define RCENET_LIST_H

#include <stdlib.h>

/**
 * Définit un nœud de la liste chaînée, utilisé comme élément de base pour la construction de listes.
 * Chaque nœud est lié à son prédécesseur et à son successeur, permettant une traversée bidirectionnelle de la liste.
 * 
 * @typedef {struct} _ENetListNode
 * @param next Pointeur vers le prochain nœud dans la liste. NULL si c'est le dernier nœud.
 * @param previous Pointeur vers le nœud précédent dans la liste. NULL si c'est le premier nœud.
 */
typedef struct _ENetListNode
{
   struct _ENetListNode * next;
   struct _ENetListNode * previous;
} ENetListNode;

/**
 * Utilisé pour parcourir la liste, cet iterateur est un pointeur vers un nœud de la liste.
 * Permet aux utilisateurs de RCENet de manipuler les éléments de la liste de manière intuitive.
 * 
 * @typedef ENetListIterator
 * @param ENetListNode* Pointeur vers un nœd de la liste.
 */
typedef ENetListNode * ENetListIterator;

/**
 * Représente la liste elle-même, contenant un nœud sentinelle qui sert de point d'ancrage pour la liste.
 * Le nœd sentinelle simplifie la logique d'insertion et de suppression en éliminant le besoin de traiter des cas spéciaux pour les extrémités de la liste.
 * 
 * @typedef {struct} _ENetList
 * @param sentinel Nœud sentinelle utilisé comme tête de liste fictive. Il ne contient pas de données utiles mais sert de pointeur de début et de fin pour la liste.
 */
typedef struct _ENetList
{
   ENetListNode sentinel;
} ENetList;

extern void enet_list_clear (ENetList *);

extern ENetListIterator enet_list_insert (ENetListIterator, void *);
extern void * enet_list_remove (ENetListIterator);
extern ENetListIterator enet_list_move (ENetListIterator, void *, void *);

extern size_t enet_list_size (ENetList *);

#define enet_list_begin(list) ((list) -> sentinel.next)
#define enet_list_end(list) (& (list) -> sentinel)

#define enet_list_empty(list) (enet_list_begin (list) == enet_list_end (list))

#define enet_list_next(iterator) ((iterator) -> next)
#define enet_list_previous(iterator) ((iterator) -> previous)

#define enet_list_front(list) ((void *) (list) -> sentinel.next)
#define enet_list_back(list) ((void *) (list) -> sentinel.previous)

#endif // RCENET_LIST_H