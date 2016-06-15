# Identificateurs

## Termes

Voici les différents types de casses de caractères utilisés par la suite :

- camelCase (`lolLel`)
- PascalCase (`LolLel`)
- miniscule (`lol_lel`)
- MAJUSCULE (`LOL_LEL`)

## Règles

Nom de classe en PascalCase.

Nom de structure & union & enum en minuscule.

PAS DE FONCTION DANS LES STRUCTURES !!! Utiliser les classes pour les objets
complexes.

Nom de variable et de namespace en camelCase.

Nom de constant en MAJUSCULE.

Nom de fichier en minuscule.



# Espaces

Un espace après les mots clefs.

Espaces autour des opérateurs, hormi les opérateurs unaires (comme ! et ~).
(Nb : `+` et `-` sont parfois des opérateurs unaires)

Pas d'espace entre le nom d'une fonction et ses parenthèses lors de l'appelle
d'une fonction.

Espace après une virgule.



# Déclarations

Vous pouvez déclarer et affecter une variable sur la même ligne.

Allgnement des déclarations de variable avec des tabulations pas nécessaire.

Pointeurs à droite, références a gauche :

```c
int   *a
int&   b
```

Les pointeurs sont découragés.



# Autres

Pas de fonction hors d’un namespace ou d’une classe hormi le main().

Pas d'inclusion de .cpp. Un seul .cpp et un .hpp par classe.

On prédeclare les classes, puis on les inclut dans le .cpp :
Garde dans les .hpp.

**a.hpp :**

```cpp
#ifndef A_HPP_
# define A_HPP_
class B;

class A
{
  B b;
};

#endif !A_HPP_
```

**a.cpp :**

```cpp
#include "a.hpp"
#include "b.hpp"

/* ... */
```

Pas de fonction dans les .hpp hormi pour les templates.
Acollades à la ligne.

Pas de code redondant.

Tous les mots clefs sont autorisés hormi `auto`.
*Note : Ceci est discutable, `auto` est un mot-clé très utilisé en C++
11, il a pris un sens différent de celui qu’il avait en C auparavant
(motet-a)*
