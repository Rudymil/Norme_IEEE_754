#include <iostream>
#include <vector>
#include<cmath>
#include <stdio.h>
#include <stdlib.h>
//chaque fois que vous utilisez des fonctions de manipulation de chaînes.
#include <string.h>

using namespace std;

int main(int argc, char *argv[]){
    int i,j;
    char intermediaire;
    float entier;
    float decimale;
    int position = -1;
    int longueur_chaine = -1;
    int quotient;
    char *separateur;
    float chiffre;
    char reel[] = "-118.625";
    char binaire_exposant[8];
    char binaire_signe[9];
    char binaire_reel[9];
    char binaire_mantisse[23];
    char binaire[32];
    printf("Le réel à convertir : %s\n\n", reel);
    // On récupère la longueur de la chaîne dans longueurChaine
    /* = strlen(reel);
    printf("La longueur du réel à convertir : %d\n\n", longueur_chaine);
    for(i=0;i<longueur_chaine;i++){
        if (reel[i] == ',' || reel[i] == '.'){
            position = i;
        }
    }
    printf("La position est à la case: %d\n\n", position);*/
    chiffre = atof(reel);
    entier = floor(chiffre);
    decimale = chiffre - entier;
    if (reel[0] == '-'){
        sprintf(binaire_signe, "1");
        quotient = abs((int)chiffre);
        decimale = 1 - decimale;
    }else{
        sprintf(binaire_signe, "0");
        quotient = (int)chiffre;
    }
    printf("Le chiffre est : %f cad %f + %f\n\n", chiffre,entier,decimale);
    printf("Le signe est : %s\n\n", binaire_signe);
    if (quotient%2 == 0){
            sprintf(binaire_exposant, "0");
        }
        if (quotient%2 == 1){
            sprintf(binaire_exposant, "1");
        }
        printf("Le binaire de l'exposant : %s\n\n", binaire_exposant);
        quotient = quotient/2;
        printf("Le quotient est : %d\n\n", quotient);
    while(quotient >= 2){
        if (quotient%2 == 0){
            strcat(binaire_exposant, "0");
        }
        if (quotient%2 == 1){
            strcat(binaire_exposant, "1");
        }
        printf("Le binaire de l'exposant : %s\n\n", binaire_exposant);
        quotient = quotient/2;
        printf("Le quotient est : %d\n\n", quotient);
    }
    strcat(binaire_exposant, "1");
    printf("Le binaire de l'exposant : %s\n\n", binaire_exposant);
    j=strlen(binaire_exposant)-1;
    for (i = 0;i<strlen(binaire_exposant)/2; i++){
        intermediaire=binaire_exposant[i];
        binaire_exposant[i]=binaire_exposant[j];
        binaire_exposant[j]=intermediaire;
        j--;
    }
    printf("Le binaire de l'exposant : %s\n\n", binaire_exposant);
    strcat(binaire_signe,binaire_exposant);
    sprintf(binaire,binaire_signe);
    printf("Le binaire du réel : %s\n\n", binaire);
    strcat(binaire,",");
    for(i=0;i<23;i++){ //Pour obenir 23 chiffres
        decimale=decimale*2;
        if(decimale>=1){
            strcat(binaire,"1");
            decimale--;
        }
        else{
            strcat(binaire,"0");; //Ajout en fin de chaîne
        }
        printf("Le binaire : %s\n\n", binaire);
    }
    return 0;
}
