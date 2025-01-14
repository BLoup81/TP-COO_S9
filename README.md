# Projet de conception orieté objet en 2ème année de master ISTR
## 2024/2025
### Rebrab Dacine & Bessard Loup

## Onjectif

Ce projet est réalisé en Python (version 3.10.12) et C++ (version 11.4.0). Il créer une application web local accessible via l'url *http://localhost:8000/admin*. Cette application permet à une hypothétique entreprise de renseigner certaines de ses informations ci-après:
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

La classe **Usine** possède les méthodes **infoStock()**, **infoStockId()**, **infoMachine()** et **infoMachineId()** qui permettent de mettre dans un tableaux les données et les identifiants de toutes les machines et tous les stocks appartenant à l'usine avant de les sérialiser dans **json_extend()**. La méthode **achatStock()** réalise l'achat automatique d'un stock de ressource nécessaire à la production d'une certaine quantité de produit dans l'optique de réaliser des recettes précises.

## C++

Le code en C++ récupère les données sérialisées à l'aide de la libbrairie **cpr** pour réaliser quelconques traitements.

## Test en python

Les tests sont réalisés via le framework de Django en tapant la commande *./manage.py test*.

## Les dépendances
**Python**: *https://www.python.org/*  
Tester si python est installer et sa version: *python -V* ou *python3 -V*  
Pour installer Python: *sudo apt install python3*  

**venv**: https://docs.python.org/3/library/venv.html  
Création dans le répertoire de travail: *python -m venv nom_venv*  
Activation: *source nom_venv/bin/activate  

**pip**: *https://pypi.org/project/pip/*  
Installation de *pip*: *pip install -U pip*  

**Django**: *https://www.djangoproject.com/*  
Installation: *pip install django*  
Pour lancer l'application:  
*./manage.py makemigrations*  
*./manage.py migrate*  
*./manage.py createsuperuser*  
*./manage.py runserver*  

L'application est accessible en suivant le lien précédent. Il faut se connecter en tant qu'administrateur via le superuser.  

**CMake**: *https://cmake.org/documentation/*  
Installation: *pip install cmake*  
Compilation: *cmake --build build*  
Exécution: *./build/low_level*

**cpr/cpr.h**: *https://github.com/libcpr/cpr*  

**nlohmann/json.hpp**: *https://github.com/nlohmann/json/*  
