#ifndef NORME_IEEE_754_H
#define NORME_IEEE_754_H

#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // chaque fois que vous utilisez des fonctions de manipulation de chaînes.

using namespace std;

void norme_ieee_754(const char *const_reel, char *binaire_ieee_754); // fonction principale

void f_signe(char *reel, char *binaire_ieee_754); // premiere partie, decouverte du signe

void f_binaire(char *reel, char *binaire_sans_signe); // deuxieme partie, conversion en binaire

int binaire_ante_coma(int quotient, char *b_a_c); // calcule le binaire de la partie avant la virgule

void binaire_post_coma(float decimale, int t_b_a_c, char *b_p_c); // calcule le binaire de la partie apres la virgule

int f_virgule_mantisse(char *binaire_sans_signe, char *reel); // troisieme partie, decalage de la virgule + mantisse + renvoie du decalage

void f_exposant(char *binaire_sans_signe, char *reel, int decalage); // quatrieme partie, formation de l exposant

void remove_coma(char *binaire_exposant); // enleve la virgule et le premier bit implicite

void affichage_console(char *binaire_ieee_754, char *reel); // affichage du resultat final dans la console

#endif // NORME_IEEE_754_H
