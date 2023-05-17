# Générateur de site web en C

Ce projet consiste en un générateur de site web simple développé en utilisant la bibliothèque libmicrohttpd en langage C. Le site généré affiche "Bonjour, @name !" où @name est substitué par une autre variable.

## Installation

Assurez-vous que vous avez installé la bibliothèque libmicrohttpd. Si ce n'est pas le cas, exécutez la commande suivante pour l'installer :

```bash
apt install libmicrohttpd-dev
```

## Compilation

Pour compiler le générateur de site web, exécutez la commande suivante :

```bash
gcc -o webGenerator webGenerator.c -lmicrohttpd
```

## Utilisation

Lancez l'exécutable `webGenerator` en exécutant la commande suivante :

```bash
 ./webGenerator
```

Le site web généré sera disponible sur le port 8080. Il affichera "Bonjour, World !" par défaut. Pour modifier le nom affiché modifier la variable `name`. 
Exemple pour John :

```c
const char *name = "John";  // Variable contenant le nom à substituer
```
