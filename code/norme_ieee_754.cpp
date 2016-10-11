#include "norme_ieee_754.h"

// programme principal
void norme_ieee_754(const char *const_reel){

    printf("Le réel à convertir = %s\n\n",const_reel);
    char binaire_ieee_754[32];
    char binaire_sans_signe[32];
    char binaire_exposant[32];
    char reel[32];
    int decalage(0); // valeur
    int *ptr_decalage(0); // pointeur de la valeur
    ptr_decalage = &decalage; // transmission de l adresse
    printf("decalage = %d\n\n",decalage);
    printf("ptr_decalage = %p\n\n",ptr_decalage);
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
    decalage = f_virgule_mantisse(binaire_sans_signe);
    printf("Le binaire normé avec sa mantisse = %s\n",binaire_sans_signe);
    printf("Le décalage = %d\n\n", decalage);

// quatrieme partie, formation de l exposant
    printf("Quatrieme partie\n\n");
    f_exposant(binaire_exposant,decalage);
    printf("Le binaire de l'exposant = %s\n\n",binaire_exposant);

// concatenation
    strcat(binaire_ieee_754,binaire_exposant); // concatenation du signe avec l exposant
    printf("Le signe + l'exposant = %s\n\n",binaire_ieee_754);

    remove_coma(binaire_sans_signe); // enleve la virgule et le premier bit implicite
    printf("Le binaire de l'exposant sans virgule = %s\n\n",binaire_sans_signe);

    strcat(binaire_ieee_754,binaire_sans_signe); // concatenation du signe et de l exposant avec
    printf("Le binaire de %s selon la norme IEEE 754 = %s\n\n",reel,binaire_ieee_754);

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
    //int taille;
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
    strcat(b_a_c,"."); // concatenation de la virgule dans b_a_c
    strcat(b_a_c,b_p_c); // concatenation des 2 binaires dans b_a_c
    printf("Le binaire normé = %s\n\n",b_a_c);
    sprintf(binaire_sans_signe,b_a_c); // ecriture du binaire trouve dans le binaire final
    printf("Le binaire normé = %s\n\n",binaire_sans_signe);
    //taille = strlen(binaire_sans_signe);
    //printf("La taille du binaire sans signe = %d\n\n", taille);
}

void binaire_ante_coma(int quotient, char *b_a_c){ // calcule le binaire de la partie avant la virgule

    char binaire[32];
    int taille;
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
    printf("La taille du binaire-1 = %d\n", longueur);
    taille = longueur + 1; // taille du binaire
    printf("La taille du binaire = %d\n", taille);
    for(int i=0 ; i<(taille/2) ; i++){
        printf("L'occurence de l'inversion = %d vs %d\n", i, longueur);
        intermediaire=binaire[i];
        binaire[i]=binaire[longueur];
        binaire[longueur]=intermediaire;
        longueur--;
        printf("Le binaire avant la virgule = %s\n\n", binaire);
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

// troisieme partie, decalage de la virgule + mantisse + renvoie du decalage
int f_virgule_mantisse(char *binaire_sans_signe){
    int decalage = 0;
    printf("Le decalage = %d\n\n", decalage);
    int coma;
    int intermediaire;
    int taille = strlen(binaire_sans_signe);
    // recherche de l index de la variable
    for(int i=0; i<taille; i++){
        if (binaire_sans_signe[i] == 46){
            coma = i;
        }
    }
    printf("L'index de la virgule = %d\n\n", coma);
    // deplacement de la virgule
    if(coma != NULL){ // si il y en a une
        for (int k=coma; k>=2; k--){ // jusqu a la deuxieme case
            intermediaire = binaire_sans_signe[k];
            binaire_sans_signe[k] = binaire_sans_signe[k-1];
            binaire_sans_signe[k-1] = intermediaire;
            printf("Le nouveau binaire = %s\n\n", binaire_sans_signe);
            decalage++; // mesure du decalage de la virgule
            printf("Le decalage = %d\n\n", decalage);
        }
    }
    // rajout des zeros pour une mantisse (apres la virgule) de 23 bits
    if(taille < 25){ // si la taille du binaire n est pas superieur a 23 bits + 2
        for( int j=taille; j< 25; j++){ // alors pour chaque occurence de la difference
            printf("L'index de la virgule = %d\n\n", j);
            strcat(binaire_sans_signe,"0"); // on concatene un zero
            printf("Le nouveau binaire = %s\n\n", binaire_sans_signe);
        }
    }
    return decalage;
}

// quatrieme partie, formation de l exposant
void f_exposant(char *binaire_exposant, int decalage){ // quatrieme partie, formation de l exposant
    int taille;
    char binaire[32];
    int true_decalage = decalage + 127; // pour le format 32-bit IEEE 754, le décalage est 28−1−1 = 127
    printf("Le nouveau décalage = %d\n", true_decalage);
    binaire_ante_coma(true_decalage,binaire); // on reutilise la fonction pour transformer la partie avant la virgule en bianire
    sprintf(binaire_exposant,binaire); // ecrit le binaire trouver dans l exposant en binaire
    printf("Le binaire de l'exposant = %s\n\n", binaire_exposant);
    taille = strlen(binaire_exposant);
    printf("La taille du binaire sans signe = %d\n\n", taille);
}

void remove_coma(char *binaire_exposant){ // enleve la virgule et le premier bit implicite
    int taille = strlen(binaire_exposant); // extraction de la taille du binaire
    printf("Taille du binaire avec la virgule %d\n\n",taille);
    int index; // indice de la virgule
    int intermediaire;
    printf("Le binaire avec la virgule %s\n\n",binaire_exposant);
    for(int i=0; i<taille; i++){ // pour chaque case de la chaine
        if(binaire_exposant[i]==46){
            index = i; // extraction de la virgule
            printf("Index de la virgule %d\n\n",index);
        }
    }
    if(index!=NULL){ // s il y a une virgule
        for(int j=index; j<taille; j++){ // pour chaque case de la chaine
            printf("Occurence du remove coma =  %d\n\n",j);
            if(binaire_exposant[j]!='\0'){ // tant qu on est pas a la fin
                intermediaire = binaire_exposant[j];
                binaire_exposant[j] = binaire_exposant[j+1];
                binaire_exposant[j+1] = intermediaire;
            }
            printf("Le binaire sans la virgule = %s\n\n",binaire_exposant);
        }
    }
    // au passage on supprime egalement le premier bit implicite avant la virgule
    for(int k=0; k<taille; k++){ // pour chaque case de la chaine
        intermediaire = binaire_exposant[k];
        binaire_exposant[k] = binaire_exposant[k+1];
        binaire_exposant[k+1] = intermediaire;
    }
    printf("Le binaire sans le premier bit = %s\n\n",binaire_exposant);
}
