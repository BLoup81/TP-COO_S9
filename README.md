# Projet de conception orieté objet en 2ème année de master ISTR
## 2024/2025
### Rebrab Dacine & Bessard Loup

## Onjectif

Ce projet est réalisé en python et C++. Il créer une application web local accessible via l'url *http://localhost:8000/admin*. Cette application permet à une hypothétique entreprise de renseigner certaines de ses informations ci-après:
- Nom
- Ville
- Siège social
- Produit
- Usine
- Stock
- Machine

Telles que montrées dans la figure suivante:
![UML](https://github.com/user-attachments/assets/96ab3bbe-fa03-408e-8648-1e76dc1d42ac)

## Python

L'application est développée à l'aide de *Django* depuis un environnement python.
Les méthodes **__str__()** permettent d'afficher les instances des classes dans l'application.

L'utilisation de Django permet la création d'une base de données qui est ensuite sérialisée au format *JSON*. Ainsi, les méthodes **json()** sérialisent les données propres aux instances quant aux **json_extend()**, elles sérialisent les données propres aux instances ainsi que les données de leurs instances en attribut.

La classe **Usine** possède les méthodes **infoStock()**, **infoStockId()**, **infoMachine()** et **infoMachineId** qui permettent de mettre dans un tableaux les données et les identifiants de toutes les machines et tous les stocks appartenant à l'usine avant de les sérialiser dans **json_extend()**. La méthode **achatStock()** réalise l'achat automatique d'un stock de ressource nécessaire à la production d'une certaine quantité de produit dans l'optique de réaliser des recettes précises.

## C++

Le code en C++ récupère les données sérialisées à l'aide de la libbrairie **cpr** pour réaliser quelconques traitements.

