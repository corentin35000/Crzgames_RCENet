/** 
 * @file  utility.h
 * @brief En-tête pour les utilitaires d'ENet.
 *
 * Ce fichier définit des macros utilitaires générales pour effectuer des opérations courantes,
 * telles que calculer le maximum ou le minimum de deux valeurs, ou la différence entre elles.
 * Ces macros sont conçues pour être utilisées à travers l'ensemble d'ENet pour simplifier le code
 * et améliorer la lisibilité.
 */

#ifndef RCENET_UTILITY_H
#define RCENET_UTILITY_H

/**
 * Macro pour obtenir le maximum de deux valeurs.
 * 
 * @param x Première valeur pour la comparaison.
 * @param y Deuxième valeur pour la comparaison.
 * @return La valeur la plus élevée entre `x` et `y`.
 */
#define ENET_MAX(x, y) ((x) > (y) ? (x) : (y))

/**
 * Macro pour obtenir le minimum de deux valeurs.
 * 
 * @param x Première valeur pour la comparaison.
 * @param y Deuxième valeur pour la comparaison.
 * @return La valeur la plus basse entre `x` et `y`.
 */
#define ENET_MIN(x, y) ((x) < (y) ? (x) : (y))

/**
 * Macro pour calculer la différence absolue entre deux valeurs.
 * 
 * @param x Première valeur pour le calcul.
 * @param y Deuxième valeur pour le calcul.
 * @return La différence absolue entre `x` et `y`.
 */
#define ENET_DIFFERENCE(x, y) ((x) < (y) ? (y) - (x) : (x) - (y))

#endif // RCENET_UTILITY_H