# Contribuer au zappy

Dépendances du projet :

* gcc
* clang
* cmocka
* bc
* git

Pour compiler le serveur, lancez la commande `make`.

Pour lancer la suite de tests unitaires, lancez la commande `make test`. Cette
commande affichera également de le pourcentage de code couvert par les tests
unitaires. L'objectif est de couvrir au moins **80%** de couverture avec les
tests unitaires.

Toute contribution au serveur entrainant plus de deux commits devra passer par
une merge request et être approuvé par au moins un membre de l'équipe.

Toute contribution devra être à la norme. La norme sera automatiquement vérifiée
via le système d'intégration continue. La seule exception à cette règle concerne
les tests unitaires qui n'ont pas besoin d'être à la norme.
