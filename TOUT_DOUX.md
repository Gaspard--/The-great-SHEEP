# MANTRA

- Accent sur l’aspect tactique.
- Peu d’actions par minutes.
- Beaucoup d’effets.
- Le plus de détails possibles.
- Le moins de choses coupant l’action possible (on évite les menus,
les boîtes de dialogue etc.)



# BAZARD INITIAL

(faudra tout bien trier un jour)

Un `//` au début d’une ligne signifie « à revoir ».

- jeu en survival.
- terrain généré aléatoirement.

- // gestion de hauteur (par plateau)
- monstres capturables différentiables / *typeables*.
- 3 monstres capturables par perso
- les monstres évoluent, et leur mort sera permanante.
- // map *streamable*

- Commande :
    - sélection des monstres avec A Z E R et action C V B (touche
      rebindable). On vise avec la souris. *Note: s’il vous plait, par
      pitié, pensez au bépoètes et au dvorakistes (motet-a)*

- Gagner -> battre *The great SHEEP* (qui est aussi un dresseur).

- pas d’inventaire.
- système jour nuit + mini écosystème. Pic de difficulté lors de la
  nuit.
- système de faim pour le perso et les créatures. (Pas strictement
  nécessaire pour le perso si on garde une pression constante)

- Le terrain est modifiable
    - // système d’agriculture (Chelou si on a pas d’inventaire non ?
      Peut-être pour des mobs herbivore ?)
    - environnement interactif (comme des arbres qu’on peu couper ou
      enflammer et qui servent aussi d’obstacle, ou encore une rivière
      glaceable)
    - // construction de base. (Pareil, cheloue sans inventaire, à
      voire...)
    - biomes. (avec des monstres qui changent)
    - donjons :
        - Espace séparés du reste du monde.
        - Boss capturable qui vaut beaucoup de nourriture.

- rencontrer d’autres dresseurs (qui font leur propre campement).

- actions :
    - peuvent avoir des effets sur l’environnement
    - peuvent avoir des effets sur les autres monstres
    - peu d’actions par secondes mais beaucoup d’effets. (pas d’action
      générique)
    - action de domptage

- type de monstre :
    - caractéristiques :
        // peuvent être montables.
        // volants.
        // besoins en sommeil plus ou moins faible.
    - stats **fixes**:
        - intelligence -> augmente la vitesse d’xp
        - metabolisme -> augmente la croissence
    - stats **croissantes**:
        - sagesse -> nb d’xp total accumullé (valeur de l’âme), donne
          des nouvelles actions.
        - croissance -> donne des évolutions.
        - puissance -> intensité des effets
        - pvmax -> vie
        - vitesse -> vitesse de déplacement
    - stats **variables**:
        - pv courant
        - faim



# ZONE DE FLOU
- états:
  - endormi ?
  - brulé ?
  - empoisonné ?
  - mort ?



# PROGRESSION DU JOUEUR

Moyen principal de progression -> monstres.

Deux systèmes de progression :

- corps & esprit
- croissance -> augmente quand le monstre mange, proportionellement à
la quantité mangée * le metabolisme.

Évolution quand pallier de croissance est atteind.

La taille d’un monstre est égale à la troisième racine de sa
croissance.

Action -> utiliser une action augmente ses xp. Chaque action a un
certain nombre de niveau qui ne font que l’amplifier (ne débloquent
pas d’effets supplémentaires). Tout xp gagné est aussi gagné en
sagesse. Le gain d’xp est divisé par le niveau de l’action, et
multiplié par l’intelligence. (i.e. au niveau 5 on xp 5 fois moins
vite l’action concernée)

Absorber une ame (manger un monstre vivant) -> boost de sagesse en
fonction de la sagesse du monstre.

Les actions sont débloquées à des seuils de sagesse.



# SUGGESTION

## Types

Un type affecte toutes les action d’un *mob*, plus ou moins selon
lesquelles, le mob est aussi insensible aux effets qu’il applique.

Coté negatif:

- *Feu*. Applique l’état enflammé. Dégats augmentés contre les cibles
  desséchées. Dégats réguliers au cours du temps de l’effet. Peu
  déglacer, ainsi que brûler des arbres ou de l’herbe.
- *Glace*. Applique l’état froid. Réduit la vitesse, et glace les
  choses mouillées, empechant d’agir ou rendant glissant.
- *Eau*. Mouille la cible. Suprimme et rend insensible à l’état
  enflammé. Permet de faire pousser des plantes plus facilement. Donne
  un recule suplémentaire.
- *Éclair*. Dégats augmentés contre les cible mouillées.
- *Terre*. Applique l’états desséché qui retire les états du à l’eau
  et au poison. Ne fait pas de dégats au cible glacés.
- *Poison*. Empoisonne pour des dégats au cours du temps. Dégats
  divisé par 2 face au cibles mouillées ou enflammées.

Actions proposées:

- Toutes les actions ont un cooldown.

## Humanité
- Bonté. soigne la cible. La dompte si assez de pv soignés.
- Faveur. augmente (temporairement) la puissance de la cible. La
  dompte si assez de faveurs appliqués.
- Pitié. Fait survivre la cible avec 1 pv à tous les dégats. Effet
  dure un cours instant. Dompte la cible si elle ramenée à 1 pv.

## Debout
- Coup de poing. Moins de dégats que griffe mais recule. La cible
  recule à l’endroit ciblé.
- Coup de pied. Plus fort que coups de poing au prix d’effet du au
  type plus faible.
- Grab. Saisie la cible. Peut-être lancée en reutilisant grab.
- Upercut. Gros dégats.
- Sprint. Gains de vitesse temporaire. Réduit les dégats des trois
  autres actions.

## Quatre pattes
- Bond. Ligne de vue necessaire. Saute à l’endroit ciblé. N’a pas
  besoin de sol entre les deux endroits.
- Encrage. Rend insensible au récule mais aussi incabable de se
  déplacer jusqu’a relance de l’action ou de bond. Ne marche pas
  contre les cibles beaucoup plus grande. Augmente la puissance de
  bond.
- Roulade. Va vers l’endroit ciblé. Insensible au dégats pendant le
  déplacement.

## Queue
Un monstre avec plusieur queue peut avoir plusieurs *'charges'* de dash.
- Dash. Ligne de vue necessaire. Dash à l’endroit ciblé. Peut
  interompre du recule subits. D’autre actions peuvent être éxecutées
  en même temps. (combo avec coups circulaire, souffle etc.)

## Griffes
Toutes ces attaques applique saignant qui inflige des dégats à la
cible à chaque fois qu’elle fais une action. Les effets dûs au type du
monstre sont faibles, hormi pour *poison* qui a ses effets augmentés, et
*glace* qui donne plus de dégats mais aucun effet.
- Griffures. Dommage à petite distance. Attaque par excelence pour
  couper des plantes.
- Grab. Comme au-dessus. Si on as des griffes on bénificies de dégats
  suplémentaires.
- Coup circulaire. Dommage en zone autour du lanceur. Attaque par
  excelence pour couper des plantes.

## Cornes
- Charge. Fonce tout droit. Cogne la première cible et la repousse
  fortement. La zone traversé est afecté par le type du monstre.
- Intimidation. Grande porté. Augmente la puissance du lanceur et
  baisse celle de la cible.
- Inspiration. Grande porté. Augmente la puissance du lanceur et
  augmente celle de la cible.

## Gueule
- Morsure. Beaucoup de dégats et d’effets à très courte porté. Permet
  de mangé les cibles vivante beaucoup plus faible que le
  lanceur. Moyen principale pour l’absorbtion d’ame.
- Cri. Grande zone moyene portée. Baisse la puissance de tous le monde
  hormi le lanceur.
- Cracha. Portée moyenne. Effet du au type du monstre puissant. Aucuns
  dégats de base.
- Souffle. Inspiration puis attaque sur une grande zone. Effet du au
  type du monstre puissant. Aucuns dégats de base.

## Quantique

Tous ces sorts ne nécéssitent pas de ligne de vue et sont des sorts de
zone. Aucun effet n’est dû au type du monstre.
- *Téléportation*. Téléporte tous ceux autour de soi vers l’endroit
  ciblé.
- *Venez !*. Teleporte tous les entités dans la zone ciblé autour de
  soi.
- *Échange*.  *venez !* et *téléportation* en même temps.
- *Oust !*. Comme *téleportation* mais ne téléporte pas le lanceur.
- *Déphasage*. Déplace tous les dégats et effets autour de soi vers
l’endroit ciblé (Oui, c’est une invincibilité temporaire).  Lancé
sur soi, ces effets ne font rien. À la place, ils pourraient téléporter
les cibles assez faible dans le ventre du lanceur permettant ainsi une
alternative à morsure pour l’absorbtion d’ame, mais même si ca serait
bien niveau gameplay, je pense que c’est peut-être pas assez RP.
