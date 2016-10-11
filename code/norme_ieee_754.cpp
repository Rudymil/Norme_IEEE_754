#include "norme_ieee_754.h"

// programme principal
void norme_ieee_754(const char *const_reel){

    printf("Le réel à convertir = %s\n\n",const_reel);
    char binaire_ieee_754[32];
    char reel[32];
    char binaire_sans_signe[32];
    sprintf(reel, const_reel); // converti ou plutot copie const char* -> char
    printf("Le réel à convertir = %s\n\n",reel);

// premiere partie, decouverte du signe
    printf("Première partie\n\n");
    f_signe(reel,binaire_ieee_754);
    printf("Le signe du binaire normé = %s\n\n",binaire_ieee_754);

// deuxieme partie, conversion en binaire
    printf("Deuxième partie\n\n");
    f_binaire(reel,binaire_sans_signe);
    printf("Le binaire normé = %s\n\n",binaire_sans_signe);

// troisieme partie, decalage de la virgule + mantisse
    printf("Troisième partie\n\n");
    f_virgule_mantisse(binaire_sans_signe);
    printf("Le binaire normé avec sa mantisse = %s\n\n",binaire_sans_signe);

}

// premiere partie, decouverte du signe
void f_signe(char *reel, char *binaire_ieee_754){
    if (reel[0] == '-'){ // s il s agit d un nombre negatif
        sprintf(binaire_ieee_754, "1"); // on ecrit le bit 1
    }else{
        sprintf(binaire_ieee_754, "0"); // sinon on ecrit le bit 0
    }
}

// deuxieme partie, conversion en binaire
void f_binaire(char *reel, char *binaire_sans_signe){
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
    binaire_ante_coma(quotient,b_a_c); // calcule le binaire de la partie avant la virgule
    binaire_post_coma(decimale,b_p_c); // calcule le binaire de la partie apres la virgule
    strcat(b_a_c,","); // concatenation de la virgule dans b_a_c
    strcat(b_a_c,b_p_c); // concatenation des 2 binaires dans b_a_c
    printf("Le binaire normé = %s\n\n",b_a_c);
    sprintf(binaire_sans_signe,b_a_c); // ecriture du binaire trouve dans le binaire final
    printf("Le binaire normé = %s\n\n",binaire_sans_signe);
}

void binaire_ante_coma(int quotient, char *b_a_c){ // calcule le binaire de la partie avant la virgule

    char binaire[32];
    int longueur;
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
    for (int i=0 ; i<(strlen(binaire)/2) ; i++){ // avertissement : comparison between signed and unsigned integer expressions [-Wsign-compare] !!!
        intermediaire=binaire[i];
        binaire[i]=binaire[longueur];
        binaire[longueur]=intermediaire;
        longueur--;
        //printf("Le binaire avant la virgule = %s\n\n", binaire);
    }
    printf("Le binaire avant la virgule = %s\n\n", binaire);
    sprintf(b_a_c,binaire); // on ecrit le binaire trouve dans le binaire de la partie avant la virgule
    printf("Le binaire avant la virgule = %s\n\n", b_a_c);

}

void binaire_post_coma(float decimale, char *b_p_c){ // calcule le binaire de la partie apres la virgule
    char binaire[32]; // bianaire final
    int precision = 10; // nombre de bit apres la virgule
    decimale=decimale*2; // multiplications par deux successives
    if(decimale>=1){
        sprintf(binaire,"1"); // on ecrit 0
        decimale--;
        printf("Le binaire après la virgule = %s\n\n", binaire);
    }
    else{
        sprintf(binaire,"0"); // on ecrit 1
        printf("Le binaire après la virgule = %s\n\n", binaire);
    }
    for(int i=0; i<precision-1; i++){ // pour chaque occurence de la precision moins 1 car une occurence deja faite !
        decimale=decimale*2; // multiplications par deux successives
        if(decimale>=1){
            strcat(binaire,"1"); // on rajoute 1
            decimale--;
            printf("Le binaire après la virgule = %s\n\n", binaire);
        }
        else{
            strcat(binaire,"0"); // on rajoute 0
            printf("Le binaire après la virgule = %s\n\n", binaire);
        }
    }
    printf("Le binaire après la virgule = %s\n\n", binaire);
    sprintf(b_p_c,binaire); // on ecrit le binaire trouve dans le binaire de la partie après la virgule
    printf("Le binaire après la virgule = %s\n\n", b_p_c);
}

void f_virgule_mantisse(char *binaire_sans_signe){

}
