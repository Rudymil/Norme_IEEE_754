#include "norme_ieee_754.h"

// programme principal
void norme_ieee_754(const char* const_reel){

    printf(const_reel);

    char reel = const_reel; // probleme de conversion du const char* au char

    char binaire_final[32];

// premiere partie, decouverte du signe
    char signe[32] = f_signe(reel);
    printf(signe);

// deuxieme partie, conversion en binaire
    char binaire[32] = f_binaire(reel);
    printf(binaire);

}

// premiere partie, decouverte du signe
char f_signe(char reel){
    if (reel[0] == '-'){ // s il s agit d un nombre negatif
        return "1"; // on renvoie le bit 1
    }else{
        return "0"; // sinon on renvoie le bit 0
    }
}

// deuxieme partie, conversion en binaire
char f_binaire(char reel){
    float chiffre;
    float entier; // garder le float !!!
    float decimale;
    int quotient;
    char b_a_c[32]; // binaire de la partie avant la virgule
    char b_p_c[32]; // binaire de la partie apres la virgule
    chiffre = atof(reel); // conversion char -> float
    entier = floor(chiffre); // determination de la partie entiere
    decimale = chiffre - entier; // determination de la partie decimale
    if (reel[0] == '-'){ // s il s agit d un nombre negatif
        decimale = 1 - decimale;
        printf("Le chiffre est : %f c-a-d %f + %f\n\n", chiffre,entier,decimale);
        quotient = abs((int)chiffre); // conversion float -> int puis en absolu
    }else{ // s il s agit d un nombre positif
        printf("Le chiffre est %f c-a-d %f + %f\n\n", chiffre,entier,decimale);
        quotient = (int)chiffre; // conversion float -> int
    }
    b_a_c = binaire_ante_coma(quotient); // calcule le binaire de la partie avant la virgule
    b_p_c = binaire_post_coma(decimale); // calcule le binaire de la partie apres la virgule
    strcat(b_a_c,","); // concatenation de la virgule dans b_a_c
    strcat(b_a_c,b_p_c); // concatenation des 2 binaires dans b_a_c
    printf("Le binaire = %s\n\n", b_a_c);
    return b_a_c; // renvoie du binaire final
}

char binaire_ante_coma(int quotient){ // calcule le binaire de la partie avant la virgule

    char binaire[32];
    int longueur;
    int i;
    int intermediaire;

    if (quotient%2 == 0){ // s il ne reste rien a la division par 2
        sprintf(binaire, "0"); // on ecrit 0
    }
    if (quotient%2 == 1){ // s il reste quelque chose a la division par 2
        sprintf(binaire, "1"); // on ecrit 1
    }
    printf("Le binaire avant la virgule = %s\n\n", binaire);
    quotient = quotient/2;
    printf("Le quotient = %d\n\n", quotient);
    while(quotient >= 2){ // tant que le quotient n est pas inferieur a 2
        if (quotient%2 == 0){ // s il ne reste rien a la division par 2
            strcat(binaire, "0"); // on rajoute 0
        }
        if (quotient%2 == 1){ // s il reste quelque chose a la division par 2
            strcat(binaire, "1"); // on rajoute 1
        }
        printf("Le binaire avant la virgule = %s\n\n", binaire);
        quotient = quotient/2;
        printf("Le quotient = %d\n\n", quotient);
    }
    strcat(binaire, "1"); // le binaire de la fin !
    printf("Le binaire avant la virgule = %s\n\n", binaire);

    // ecriture du binaire a l endroit
    longueur=strlen(binaire)-1; // taille du binaire -1
    for (i=0 ; i<strlen(binaire)/2 ; i++){
        intermediaire=binaire[i];
        binaire[i]=binaire[longueur];
        binaire[longueur]=intermediaire;
        longueur--;
        //printf("Le binaire avant la virgule = %s\n\n", binaire);
    }
    printf("Le binaire avant la virgule = %s\n\n", binaire);

    return binaire;
}

char binaire_post_coma(float decimale){ // calcule le binaire de la partie apres la virgule
    char binaire[32]; // bianaire final
    decimale=decimale*2; // multiplications par deux successives
    if(decimale>=1){
        sprintf(binaire,"1"); // on ecrit 0
        decimale--;
    }
    else{
        sprintf(binaire,"0"); // on ecrit 1
    }
    for(int i=0;i<23;i++){ // pour obenir 23 chiffres ???????????????????????????
        decimale=decimale*2; // multiplications par deux successives
        if(decimale>=1){
            strcat(binaire,"1"); // on rajoute 1
            decimale--;
        }
        else{
            strcat(binaire,"0"); // on rajoute 0
        }
        printf("Le binaire : %s\n\n", binaire);
    }
    return binaire;
}
