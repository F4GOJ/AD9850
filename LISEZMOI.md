# Librairie Arduino pour AD9850 #
F4GOJ Christophe f4goj@free.fr

Août 2014

Documentation de l'AD9850 à http://www.analog.com/static/imported-files/data_sheets/AD9850.pdf

Utilisez cette librairie librement.

## Installation ##
Pour utiliser la librairie **AD9850** :
- Allez à https://github.com/F4GOJ/AD9850, cliquez le bouton [Download ZIP](https://github.com/F4GOJ/AD9850/archive/master.zip) et enregistrez le fichier ZIP à l'endroit de votre convenance.
- Décompressez le fichier. Vous obtiendrez un répertoire contenant tous les fichiers de la librairie avec un nom comprenant le nom de branche, typiquement **AD9850-master**.
- Renommez le répertoire en **AD9850**.
- Copiez le répertoire renommé dans le répertoire Arduino \libraries.


## Notes d'utilisation##

La librairie **AD9850** crée une instance de l'objet **DDS**, l'utilisateur n'a pas pas besoin de le faire.

```c++
#include <AD9850.h> //http://github.com/F4GOJ/AD9850
```
## Connexions : ##

![ad9850](https://raw.githubusercontent.com/F4GOJ/AD9850/master/images/AD9850.png)

- W_CLK   -> n'importe quelle broche.
- FQ_UD   -> n'importe quelle broche.
- DATA/D7 -> n'importe quelle broche.
- RESET   -> n'importe quelle broche.

## Fonctions : ##

###begin(int w_clk_pin, int fq_ud_pin, int data_pin, int reset_pin)
#####Description
Initialise les broches de sortie et effectue une remise à zéro générale de l'AD9850.
#####Syntaxe
`DDS.begin(w_clk, fq_ud, data, reset);`
#####Paramètres
**w_clk :** Broche de sortie SCK, n'importe quelle broche *(int)*<br>
**fq_ud :** Broche de sortie de mise à jour de la fréquence, n'importe quelle broche. *(int)*<br>
**data :** Broche de sortie de données, n'importe quelle broche *(int)*<br>
**reset :** Broche de sortie de RàZ, n'importe quelle broche. *(int)*
#####Retourne
Rien.
#####Exemple
```c++
void setup(){
 DDS.begin(6, 7, 8, 9);
}
```
###calibrate(double trim_frequency)
#####Description
Compensation de la féquence de l'oscillateur.<br>
Peut être utilisée à n'importe quel moment après l'initialisation.
#####Syntaxe
`DDS.calibrate(trim_freq);`
#####Paramètres
**trim_freq :** Ajuster autour de 125000000 pour correspondre à la fréquence réelle de l'oscillateur. *(double)*
#####Retourne
Rien.
#####Exemple
```c++
void setup(){
 DDS.begin(6, 7, 8, 9);
}

void loop(){
 DDS.calibrate(124999000);
}
```
###setfreq(double frequency, int phase)
#####Description
Détermine la fréquence de sortie de l'AD9850 et la phase du signal.
#####Syntaxe
`DDS.setfreq(frequency, phase);`
#####Paramètres
**frequency :** Fréquence de sortie en HZ. *(double)*<br>
**phase :** Phase du signal, codée sur 5 bits permet 32 pas de phase de 11,25° *(int)*
#####Retourne
Rien.
#####Exemple
```c++
double frequency = 10000000;
int phase = 0;
DDS.setfreq(frequency, phase);
```
###down()
#####Description
Mode "extinction" réduisant la puissance dissipée de 380mW à 30mW sous 5V
#####Syntaxe
`DDS.down();`
#####Paramètres
Aucun.
#####Retourne
Rien.
#####Exemple
```c++
DDS.down();
```
###up()
#####Description
Sort l'AD9850 du mode "extinction"
#####Syntaxe
`DDS.up();`
#####Paramètres
Aucun.
#####Retourne
Rien.
#####Exemple
```c++
DDS.down(); // Entrée en mode "extinction"

// du code faisant quelquechose

...

DDS.up(); // REVEIL !!! :)
```
