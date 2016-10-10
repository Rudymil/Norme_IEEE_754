#ifndef NORME_IEEE_754_H
#define NORME_IEEE_754_H

#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // chaque fois que vous utilisez des fonctions de manipulation de chaînes.

using namespace std;

void norme_ieee_754(const char* const_reel); // fonction principale

char f_signe(char reel); // premiere partie

char f_binaire(char flotant); // deuxieme partie, conversion en binaire

char binaire_ante_coma(int quotient); // calcule le binaire de la partie avant la virgule

char binaire_post_coma(float decimale); // calcule le binaire de la partie apres la virgule

#endif // NORME_IEEE_754_H
