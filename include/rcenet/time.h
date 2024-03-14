/** 
 * @file  time.h
 * @brief Définit les constantes et les macros pour la gestion du temps dans ENet.
 *
 * Ce fichier inclut des définitions essentielles pour manipuler et comparer les valeurs de temps
 * dans le contexte du protocole ENet, prenant en compte l'overflow potentiel dû à la représentation du temps.
 */

#ifndef RCENET_TIME_H
#define RCENET_TIME_H

/**
 * Constante représentant le seuil d'overflow du temps.
 * Si la différence entre deux temps dépasse cette valeur, un overflow est considéré avoir eu lieu.
 * Cette constante est utilisée pour gérer correctement les cas où le temps s'enroule autour de sa valeur maximale.
 */
#define ENET_TIME_OVERFLOW 86400000

/**
 * Macro pour comparer si un temps est inférieur à un autre, en tenant compte de l'overflow.
 * 
 * @param a Le premier instant temporel à comparer.
 * @param b Le second instant temporel à comparer.
 * @return Vrai si `a` est considéré inférieur à `b` en tenant compte de l'overflow.
 */
#define ENET_TIME_LESS(a, b) ((a) - (b) >= ENET_TIME_OVERFLOW)

/**
 * Macro pour comparer si un temps est supérieur à un autre, en tenant compte de l'overflow.
 * 
 * @param a Le premier instant temporel à comparer.
 * @param b Le second instant temporel à comparer.
 * @return Vrai si `b` est considéré inférieur à `a` en tenant compte de l'overflow.
 */
#define ENET_TIME_GREATER(a, b) ((b) - (a) >= ENET_TIME_OVERFLOW)

/**
 * Macro pour comparer si un temps est inférieur ou égal à un autre, en tenant compte de l'overflow.
 * 
 * @param a Le premier instant temporel à comparer.
 * @param b Le second instant temporel à comparer.
 * @return Vrai si `a` est considéré inférieur ou égal à `b` en tenant compte de l'overflow.
 */
#define ENET_TIME_LESS_EQUAL(a, b) (! ENET_TIME_GREATER (a, b))

/**
 * Macro pour comparer si un temps est supérieur ou égal à un autre, en tenant compte de l'overflow.
 * 
 * @param a Le premier instant temporel à comparer.
 * @param b Le second instant temporel à comparer.
 * @return Vrai si `a` est considéré supérieur ou égal à `b` en tenant compte de l'overflow.
 */
#define ENET_TIME_GREATER_EQUAL(a, b) (! ENET_TIME_LESS (a, b))

/**
 * Macro pour calculer la différence entre deux temps, en tenant compte de l'overflow.
 * 
 * @param a Le premier instant temporel.
 * @param b Le second instant temporel.
 * @return La différence de temps entre `a` et `b`, ajustée pour l'overflow.
 */
#define ENET_TIME_DIFFERENCE(a, b) ((a) - (b) >= ENET_TIME_OVERFLOW ? (b) - (a) : (a) - (b))

#endif // RCENET_TIME_H