# Logger
Petite bibliothèque de journalisation en C pour déboguer et tracer des programmes.
Chaque message est affiché sur `stderr` avec l'heure, un niveau coloré et le contexte d'appel (nom du fichier et ligne).
```
11:32:23 [INFO ] examples/example1.c:9: Voici un log d'info
11:32:23 [WARN ] examples/example1.c:10: Voici un log d'avertissement
11:32:23 [ERROR] examples/example1.c:11: Voici un log d'erreur
11:32:23 [FATAL] examples/example1.c:12: Voici un log d'erreur critique
```
*(les niveaux sont colorés dans un terminal compatible ANSI)*

## Sommaire

---

## Points clés
| Critère | Détail |
|---|---|
| **Langage** | C99 |
| **Dépendances** | Aucune dépendance tierce, uniquement la bibliothèque standard C |
| **Agnostique** | Indépendant de tout framework, OS ou projet. Fonction sous Linux et cross-compilation pour Windows (MinGW-w64) |
| **Intégration** | Bibliothèque statique (`.a`) ou dynamique (`.so`), un seul header à inclure |
| **Niveaux d'affichage** | `TRACE` , `DEBUG`, `INFO`, `WARN`, `ERROR`, `FATAL` (+ `NONE` pour tout désactiver) |
| **Contexte** | Heure (`HH:MM:SS`), fichier et ligne capturés automatiquement via un système de macros |
| **Format** | Messages au format `printf` (arguments variables) |
| **Sortie** | `stderr`, ce qui laisse `stdout` pour l'utilisateur |

### Agnostique
La librairie ne suppose rien sur le programme hôte. Elle n'impose ni allocation dynamique, ni initialisation préalable, ni fichier de configuration : on inclut l'en-tête et on appelle les macros. Le niveau par défaut est `INFO`.

Deux hypothèses restent tout de même codées en dur : la sortie est sur `stderr` et l'usage des séquences d'échappement ANSI pour les couleurs sont prédéfinis.

### Dépendances
Cette librairie ne repose sur aucun autre module externe, uniquement la librairie C standard.

### Performance
- Aucune allocation dynamique
- Empreinte minimale : une seule unité de compilation d'environ 50 lignes et une variable globale

Notes :
Les macros appellent toujours la fonction `logger_log`. Les arguments du message sont donc évalués même si le niveau est filtré. Il n'existe pas (encore) de suppresion à la compilation.
Un message émis effectue un appel à `localtime` et plusieurs `fprintf` sur `stderr` (non tamponné), ce qui reste adapté au débogage mais pas à un log très haute fréquence.

---

## Compilation

### Prérequis
**Pour compiler sous Linux**
- `gcc` : compilateur C
- `make` : exécution du makefile
- `ar` (binutils) : création de la lib statique
- (optionnel) `x86_64-w64-mingw32-gcc` et `x86_64-w64-mingw32-ar` (paquet `mingw-w64`) : cross compilation windows
- `zip` : création de l'archive zip

### Commandes

``make linux`` : compilation de la librairie en .a et .so à destination de Linux
``make windows`` : compilation de la librairie en .a à destionation de Windows
``make clean`` : Nettoyage total des compilations
``make package`` : création d'une archive zip du projet (appel à ``make clean`` automatique)

### Arborescence produite

Pour Linux :
```
.
├── build
│   ├── linux
│   │   └── logger
│   │       ├── include
│   │       │   └── logger.h
│   │       └── lib
│   │           ├── liblogger.a
│   │           └── liblogger.so
│   └── logger.o
├── examples
│   └── example1.c
├── include
│   └── logger
│       └── logger.h
├── Makefile
├── README.md
├── src
│   └── logger.c
├── tests
└── TODO.md

11 directories, 10 files
```

Pour Windows :
```
.
├── build
│   ├── logger.o
│   └── win
│       └── logger
│           ├── include
│           │   └── logger.h
│           └── lib
│               └── liblogger_win.a
├── examples
│   └── example1.c
├── include
│   └── logger
│       └── logger.h
├── Makefile
├── README.md
├── src
│   └── logger.c
├── tests
└── TODO.md

11 directories, 9 files
```

---
## Guide d'utilisation
### 1. Inclure l'en-tête
Depuis les sources du dépôt (option `-I./include`) :
```c
#include <logger/logger.h>
```

Depuis un paquet généré par `make linux` ou `make windows` (option `-I<...>/logger/include`) :
```c
#include <logger.h>
```

### 2. Journaliser
Les six macros ont un fonctionnement similaire à `printf` :
| Macro | Usage | Couleur |
|---|---|---|
| `LOG_TRACE(...)` | Suivi très détaillé | Gris |
| `LOG_DEBUG(...)` | Débogage | Cyan |
| `LOG_INFO(...)` | Informations générales | Vert |
| `LOG_WARN(...)` | Avertissements | Jaune |
| `LOG_ERROR(...)` | Erreurs | Rouge |
| `LOG_FATAL(...)` | Erreurs critiques | Blanc sur fond rouge |

### 3. Régler le niveau
Le niveau par défaut est `APP_LOG_INFO`. Ainsi, par défaut, `TRACE` et `DEBUG` sont masqués. Pour changer :
```c
logger_set_lever(APP_LOG_DEBUG);
```

Valeurs possibles, de la plus bavarde à la plus silencieuse :
- `APP_LOG_TRACE`
- `APP_LOG_DEBUG`
- `APP_LOG_INFO`
- `APP_LOG_WARN`
- `APP_LOG_ERROR`
- `APP_LOG_FATAL`
- `APP_LOG_NONE` (aucun message).

### 4. Exemple complet
Voir `example1.c`

### 5. Rediriger les logs
Logs partent sur `stderr` et les données du programme sur `stdout`, ce qui permet de les séparer :
```bash
./mon_programme 2> logs.txt     # logs dans un fichier
./mon_programme 2> /dev/null    # aucun log
```

*Attention :* Les codes couleur ANSI sont écrits tels quels dans le fichier

---

## Structure du projet
```
.
├── examples            
│   └── example1.c          # Exemple d'utilisation
├── include
│   └── logger
│       └── logger.h        # API publique
├── Makefile                # Règles de compilation
├── README.md
├── src
│   └── logger.c            # Implémentation
├── tests                   # Vide pour l'instant
└── TODO.md

6 directories, 6 files
```

--- 

## Licence
Pas de licence