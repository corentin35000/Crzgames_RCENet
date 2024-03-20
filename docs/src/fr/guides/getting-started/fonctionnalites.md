# Caractéristiques et Architecture

L'utilisation combinée d'UDP et de TCP dans Cube aurait pu profiter quelque peu de leurs fonctionnalités respectives, mais les combinaisons de protocoles résultantes laissaient encore à désirer. TCP manquait de multiples flux de communication sans avoir à ouvrir de nombreux sockets et compliquait la délimitation des paquets en raison de son comportement de mise en tampon. UDP manquait de séquencement, de gestion de connexion, de gestion des ressources de bande passante et imposait des limitations sur la taille des paquets. Un investissement significatif était nécessaire pour intégrer ces deux protocoles, et le résultat final était inférieur en termes de fonctionnalités et de performances au protocole uniforme présenté par RCENet.

Ainsi, RCENet a tenté de résoudre ces problèmes et de fournir un seul protocole uniforme superposé sur UDP au développeur, avec les meilleures fonctionnalités d'UDP et de TCP, ainsi que certaines fonctionnalités utiles que ni l'un ni l'autre ne fournissent, avec une intégration beaucoup plus propre que celle résultant d'un mélange d'UDP et de TCP.

## Gestion de la Connexion

RCENet fournit une interface de connexion simple pour communiquer avec un hôte distant. La vitalité de la connexion est activement surveillée en envoyant des pings à l'hôte distant à intervalles fréquents, et surveille également les conditions du réseau de l'hôte local à l'hôte distant, telles que le temps moyen de trajet aller-retour et la perte de paquets.

## Séquencement

Au lieu d'un seul flux d'octets qui complique la délimitation des paquets, RCENet présente les connexions comme plusieurs flux de paquets correctement séquencés qui simplifient le transfert de divers types de données.

RCENet assure le séquencement de tous les paquets en attribuant à chaque paquet envoyé un numéro de séquence qui est incrémenté au fur et à mesure que les paquets sont envoyés. RCENet garantit qu'aucun paquet avec un numéro de séquence supérieur ne sera livré avant un paquet avec un numéro de séquence inférieur, assurant ainsi que les paquets sont livrés exactement dans l'ordre dans lequel ils ont été envoyés.

Pour les paquets non fiables, RCENet va simplement écarter le paquet au numéro de séquence inférieur si un paquet avec un numéro de séquence supérieur a déjà été livré. Cela permet de dispatcher immédiatement les paquets dès leur arrivée, et de réduire la latence des paquets non fiables à un minimum absolu. Pour les paquets fiables, si un paquet à numéro de séquence supérieur arrive mais que les paquets précédents dans la séquence ne sont pas encore arrivés, RCENet va retarder la livraison des paquets à numéro de séquence supérieur jusqu'à ce que ses prédécesseurs soient arrivés.

## Canaux

Puisque RCENet retarde la livraison des paquets fiables pour garantir un séquencement approprié, et par conséquent tout paquet de numéro de séquence supérieur, qu'il soit fiable ou non, dans l'éventualité où les prédécesseurs du paquet fiable ne sont pas encore arrivés, cela peut introduire de la latence dans la livraison d'autres paquets qui pourraient ne pas nécessiter d'être ordonnés aussi strictement par rapport au paquet qui a retardé leur livraison.

Pour combattre cette latence et réduire les restrictions d'ordre sur les paquets, RCENet offre plusieurs canaux de communication sur une connexion donnée. Chaque canal est séquencé indépendamment, de sorte que le statut de livraison d'un paquet dans un canal n'arrêtera pas la livraison d'autres paquets dans un autre canal.

## Fiabilité

RCENet assure la fiabilité optionnelle de la livraison des paquets en s'assurant que l'hôte distant accuse réception de tous les paquets fiables. RCENet tentera de renvoyer le paquet jusqu'à un nombre raisonnable de fois, si aucun accusé de réception du paquet n'est reçu dans un délai spécifié. Les délais de nouvelle tentative sont progressifs et deviennent plus cléments à chaque tentative échouée pour permettre des conditions de réseau temporairement turbulentes.

## Fragmentation et Réassemblage

RCENet enverra et livrera des paquets quelle que soit leur taille. Les grands paquets sont fragmentés en plusieurs petits paquets de taille appropriée et réassemblés sur l'hôte distant pour récupérer le paquet original pour la livraison. Le processus est entièrement transparent pour le développeur.

## Agrégation

RCENet agrège toutes les commandes du protocole, y compris les accusés de réception et le transfert de paquets, en paquets de protocole plus grands pour garantir l'utilisation correcte de la connexion et limiter les opportunités de perte de paquets qui pourraient autrement entraîner une latence supplémentaire de livraison.

## Adaptabilité

RCENet fournit une fenêtre de données en vol pour les paquets fiables pour s'assurer que les connexions ne sont pas submergées par des volumes de paquets. Il offre également un mécanisme d'allocation de bande passante statique pour garantir que le volume total des paquets envoyés et reçus à un hôte ne dépasse pas les capacités de l'hôte. De plus, ENet fournit également un régulateur dynamique qui répond aux écarts par rapport aux conditions normales de réseau pour rectifier divers types de congestion réseau en limitant davantage le volume des paquets envoyés.

## Portabilité

RCENet fonctionne sous Windows et tout autre plateforme Unix ou similaire à Unix fournissant une interface de sockets BSD. La bibliothèque a une base de code petite et stable qui peut facilement être étendue pour supporter d'autres plateformes et s'intègre facilement. RCENet ne fait aucune supposition sur l'endianness ou la taille des mots de la plateforme sous-jacente.