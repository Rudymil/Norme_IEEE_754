#include "norme_ieee_754.h"

// programme principal*********************************************************************************************
void norme_ieee_754(const char *const_reel, char *binaire_ieee_754){

    // printf("Le réel à convertir = %s\n\n",const_reel);
    char binaire_sans_signe[50];
    char binaire_exposant[50];
    char reel[85];
    int decalage(0); // valeur
    sprintf(reel, const_reel); // converti ou plutot copie const char* -> char

    // tests unittaires
    // sprintf(reel,"-0"); // 1000 0000 0000 0000 0000 0000 0000 0000
    // sprintf(reel,"0"); // 0000 0000 0000 0000 0000 0000 0000 0000
    // sprintf(reel,"-1"); // 1011 1111 1111 0000 0000 0000 0000 0000
    // sprintf(reel,"1"); // 0011 1111 1111 0000 0000 0000 0000 0000
    // sprintf(reel,"-118.625"); // 1100 0010 1110 1101 0100 0000 0000 0000
    // sprintf(reel,"-6.625"); // 1100 0000 1101 0100 0000 0000 0000 0000

    printf("\n******************************************\n");
    printf("* Le réel à convertir = %s *\n",reel);
    printf("******************************************\n\n");

// premiere partie, decouverte du signe---------------
    // printf("Première partie\n\n");
    f_signe(reel,binaire_ieee_754);
    printf("****************\n");
    printf("* Le signe = %s *\n",binaire_ieee_754);
    printf("****************\n\n");

// deuxieme partie, conversion en binaire-------------
    // printf("Deuxième partie\n\n");
    f_binaire(reel,binaire_sans_signe);
    printf("****************************************\n");
    printf("* Le binaire = %s *\n",binaire_sans_signe);
    printf("****************************************\n\n");

// troisieme partie, decalage de la virgule + mantisse-
    // printf("Troisième partie\n\n");
    decalage = f_virgule_mantisse(binaire_sans_signe,reel);
    printf("*******************************************\n");
    printf("* La mantisse = %s *\n",binaire_sans_signe);
    printf("*******************************************\n");
    printf("* Le décalage = %d                       *\n", decalage);
    printf("*******************************************\n\n");

// quatrieme partie, formation de l exposant-----------
    // printf("Quatrieme partie\n\n");
    f_exposant(binaire_exposant,reel,decalage);
    printf("*************************\n");
    printf("* L'exposant = %s *\n",binaire_exposant);
    printf("*************************\n\n");

// concatenation---------------------------------------
    strcat(binaire_ieee_754,binaire_exposant); // concatenation du signe avec l exposant
    // printf("Le signe + l'exposant = %s\n\n",binaire_ieee_754);

    remove_coma(binaire_sans_signe); // enleve la virgule et le premier bit implicite
    // printf("La mantisse = %s\n\n",binaire_sans_signe);

    strcat(binaire_ieee_754,binaire_sans_signe); // concatenation du signe et de l exposant avec la mantisse
// affichage du resultat final dans la console---
    affichage_console(binaire_ieee_754,reel);

}

//*****************************************************************************************************************
// premiere partie, decouverte du signe----------------------------------------------
void f_signe(char *reel, char *binaire_ieee_754){
    if (reel[0] == '-'){ // s il s agit d un nombre negatif
        sprintf(binaire_ieee_754, "1"); // on ecrit le bit 1
    }else{
        sprintf(binaire_ieee_754, "0"); // sinon on ecrit le bit 0
    }
}

// deuxieme partie, conversion en binaire--------------------------------------------
void f_binaire(char *reel, char *binaire_sans_signe){

    float chiffre;
    float entier; // garder le float !!!
    float decimale;
    int quotient;
    int t_b_a_c; // taille de la partie binaire avant la virgule
    char b_a_c[32]; // binaire de la partie avant la virgule
    char b_p_c[32]; // binaire de la partie apres la virgule

    chiffre = abs(atof(reel)); // conversion char -> float
    entier = floor(chiffre); // determination de la partie entiere
    decimale = chiffre - entier; // determination de la partie decimale
    // printf("Le chiffre = %f\n", chiffre);
    // printf("L entier = %f\n", entier);
    // printf("La decimale = %f\n", decimale);
    // printf("Le signe = %c\n", reel[0]);
    // printf("Le signe = %d\n\n", reel[0]);
    // printf("Le chiffre est : %f c-a-d %f + %f\n\n", chiffre,entier,decimale);
    quotient = (int)chiffre; // conversion float -> int

    t_b_a_c = binaire_ante_coma(quotient,b_a_c); // calcule le binaire de la partie avant la virgule
    binaire_post_coma(decimale,t_b_a_c,b_p_c); // calcule le binaire de la partie apres la virgule
    strcat(b_a_c,"."); // concatenation de la virgule dans b_a_c
    strcat(b_a_c,b_p_c); // concatenation des 2 binaires dans b_a_c
    // printf("Le binaire normé = %s\n\n",b_a_c);
    sprintf(binaire_sans_signe,b_a_c); // ecriture du binaire trouve dans le binaire final
    // printf("Le binaire normé = %s\n\n",binaire_sans_signe);
    // taille = strlen(binaire_sans_signe);
    // printf("La taille du binaire sans signe = %d\n\n", taille);
}

// troisieme partie, decalage de la virgule + mantisse + renvoie du decalage----------
int f_virgule_mantisse(char *binaire_sans_signe, char *reel){

    float chiffre;
    float entier; // garder le float !!!
    float decimale;
    int decalage = 0;
    // printf("Le decalage = %d\n\n", decalage);
    int coma = NULL;
    int intermediaire;
    int taille = strlen(binaire_sans_signe);
    // printf("La taille = %d\n\n", taille);

    chiffre = abs(atof(reel)); // conversion char -> float
    entier = floor(chiffre); // determination de la partie entiere
    decimale = chiffre - entier; // determination de la partie decimale
    // printf("Le chiffre = %f\n", chiffre);
    // printf("L entier = %f\n", entier);
    // printf("La decimale = %f\n", decimale);
    // printf("Le signe = %c\n", reel[0]);
    // printf("Le signe = %d\n\n", reel[0]);

    // printf("Le nouveau binaire = %s\n\n", binaire_sans_signe);
    // recherche de l index de la variable
    for(int i=0; i<taille; i++){
        if (binaire_sans_signe[i] == 46){
            coma = i;
        }
    }
    // printf("L'index de la virgule = %d\n\n", coma);
    // deplacement de la virgule
    if(coma != NULL){ // si il y en a une
        if(entier!=0){ // si s agit d un nombre absolument strictement superieur a 1
            for (int k=coma; k>=2; k--){ // jusqu a la deuxieme case
                intermediaire = binaire_sans_signe[k];
                binaire_sans_signe[k] = binaire_sans_signe[k-1];
                binaire_sans_signe[k-1] = intermediaire;
                // printf("Le nouveau binaire = %s\n\n", binaire_sans_signe);
                decalage++; // mesure du decalage de la virgule
                // printf("Le decalage = %d\n\n", decalage);
            }
        }else if(decimale!=0){ // si s agit d un nombre absolument inferieur ou egal a 1 mais different de zero
            int un;
            for(int m=taille-1; m>=0; m--){ // recherche de...
                if (binaire_sans_signe[m] == 49){ // l index du dernier bit 1
                    // printf("%c\n\n", binaire_sans_signe[m]);
                    un = m;
                }
            }
            // printf("L'index du premier bit 1 = %d\n\n", un);
            for (int l=coma; l<un; l++){ // jusqu apres le premier bit 1
                intermediaire = binaire_sans_signe[l];
                binaire_sans_signe[l] = binaire_sans_signe[l+1];
                binaire_sans_signe[l+1] = intermediaire;
                // printf("Le nouveau binaire = %s\n\n", binaire_sans_signe);
                decalage--; // mesure du decalage de la virgule
                // printf("Le decalage = %d\n\n", decalage);
            }
            for(int n=0; n<(un-coma); n++){ // suppression des zeros avant le premier avant ou avant la virgule
                for(int o=0; o<taille; o++){
                    intermediaire = binaire_sans_signe[o];
                    binaire_sans_signe[o] = binaire_sans_signe[o+1];
                    binaire_sans_signe[o+1] = intermediaire;
                    // printf("Le nouveau binaire = %s\n\n", binaire_sans_signe);
                }
            }
        }
    }
    taille = strlen(binaire_sans_signe);
    // printf("La taille = %d\n\n", taille);
    // rajout des zeros pour une mantisse (apres la virgule) de 23 bits
    if(taille < 25){ // si la taille du binaire n est pas superieur a 23 bits + 2
        for( int j=taille; j< 25; j++){ // alors pour chaque occurence de la difference
            //printf("La taille = %d\n\n", j);
            strcat(binaire_sans_signe,"0"); // on concatene un zero
            // printf("Le nouveau binaire = %s\n\n", binaire_sans_signe);
        }
    }
    taille = strlen(binaire_sans_signe);
    // printf("La taille = %d\n\n", taille);
    // rajout des zeros pour une mantisse (apres la virgule) de 23 bits
    if(taille > 25){ // si la taille du binaire est superieur a 23 bits + 2
            binaire_sans_signe [25] = '\0'; // on coupe la chaîne a la 25eme case
            // printf("Le nouveau binaire = %s\n\n", binaire_sans_signe);
    }
    taille = strlen(binaire_sans_signe);
    // printf("La taille = %d\n\n", taille);
    return decalage;
}

// quatrieme partie, formation de l exposant------------------------------------------
void f_exposant(char *binaire_exposant, char *reel, int decalage){

    float chiffre = abs(atof(reel)); // conversion char -> float
    float entier = floor(chiffre); // determination de la partie entiere
    float decimale = chiffre - entier; // determination de la partie decimale
    // printf("Le chiffre = %f\n", chiffre);
    // printf("L entier = %f\n", entier);
    // printf("La decimale = %f\n", decimale);
    // printf("Le signe = %c\n", reel[0]);
    // printf("Le signe = %d\n\n", reel[0]);
    // printf("Le chiffre est : %f c-a-d %f + %f\n\n", chiffre,entier,decimale);

    if(entier == 0 && decimale == 0){ // s il s agit de zero a convertir
        sprintf(binaire_exposant,"00000000"); // l exposant comportera que des zeros (8 zeros)
    }else{ // sinon
        int taille;
        char binaire[32];
        int true_decalage = decalage + 127; // pour le format 32-bit IEEE 754, le décalage est 28−1−1 = 127
        if(true_decalage < 255 && true_decalage > 0){ // si le decalage est compris entre 0 et 255
            // printf("Le nouveau décalage = %d\n", true_decalage);
            binaire_ante_coma(true_decalage,binaire); // on reutilise la fonction pour transformer la partie avant la virgule en bianire
            sprintf(binaire_exposant,binaire); // ecrit le binaire trouver dans l exposant en binaire
            // printf("Le binaire de l'exposant = %s\n\n", binaire_exposant);
            taille = strlen(binaire_exposant);
            // printf("La taille du binaire sans signe = %d\n\n", taille);
            if(taille<8){ // si l exposant ne contient pas 8 bit !
                char zero[32];
                sprintf(zero,"0"); // on rempli la new chaine d au moins un 1
                taille++; // la taille augmente
                while(taille<8){ // mais tant que ce n est pas suffisant
                    strcat(zero,"0"); // on rempli la new chaine d un 0
                    taille++; // la taille augmente
                }
                strcat(zero,binaire_exposant); // on concatene la chaine de 0 avec le binaire
                sprintf(binaire_exposant,zero); // on eccrase le tout dans la chaine a renvoyer
            }
        }else if(true_decalage > 255){ // les NaNs et les infinis ont un exposant decale de 128+127=255 ; tous les bits du champ "exposant" sont donc à 1.
            sprintf(binaire_exposant,"11111111"); // l exposant comportera que des un (8 un)
        }
    }
}

// Fonctions Annexes------------------------------------------------------------------
int binaire_ante_coma(int quotient, char *b_a_c){ // calcule le binaire de la partie avant la virgule

    char binaire[32];
    int taille;
    int longueur;
    int intermediaire;

    // printf("Le quotient = %d\n\n", quotient);
    if (quotient%2 == 0){ // s il ne reste rien a la division par 2
        sprintf(binaire, "0"); // on ecrit 0
    }
    if (quotient%2 == 1){ // s il reste quelque chose a la division par 2
        sprintf(binaire, "1"); // on ecrit 1
    }
    // printf("Le binaire avant la virgule = %s\n\n", binaire);
    quotient = quotient/2;
    // printf("Le quotient = %d\n\n", quotient);
    while(quotient > 0){ // tant que le quotient  est superieur ou egal a 2
        if (quotient%2 == 0){ // s il ne reste rien a la division par 2
            strcat(binaire, "0"); // on rajoute 0
        }
        if (quotient%2 == 1){ // s il reste quelque chose a la division par 2
            strcat(binaire, "1"); // on rajoute 1
        }
        // printf("Le binaire avant la virgule = %s\n\n", binaire);
        quotient = quotient/2;
        // printf("Le quotient = %d\n\n", quotient);
    };
    // printf("Le binaire avant la virgule = %s\n\n", binaire);

    // ecriture du binaire a l endroit
    longueur=strlen(binaire)-1; // taille du binaire -1
    // printf("La taille du binaire-1 = %d\n", longueur);
    taille = longueur + 1; // taille du binaire
    // printf("La taille du binaire = %d\n", taille);
    for(int i=0 ; i<(taille/2) ; i++){
        // printf("L'occurence de l'inversion = %d vs %d\n", i, longueur);
        intermediaire=binaire[i];
        binaire[i]=binaire[longueur];
        binaire[longueur]=intermediaire;
        longueur--;
        // printf("Le binaire avant la virgule = %s\n\n", binaire);
    }
    // printf("Le binaire avant la virgule = %s\n\n", binaire);
    sprintf(b_a_c,binaire); // on ecrit le binaire trouve dans le binaire de la partie avant la virgule
    // printf("Le binaire avant la virgule = %s\n\n", b_a_c);
    return taille; // renvoie la taille du binaire

}

void binaire_post_coma(float decimale, int t_b_a_c, char *b_p_c){ // calcule le binaire de la partie apres la virgule

    char binaire[32]; // binaire final
    int precision = 23 - (t_b_a_c + 1); // nombre de bit apres la virgule
    decimale=decimale*2; // multiplications par deux successives
    // printf("La decimale x2 = %f\n\n", decimale);

    if(decimale>=1){
        sprintf(binaire,"1"); // on ecrit 0
        decimale--;
        // printf("Le binaire après la virgule = %s\n\n", binaire);
        // printf("La decimale x2 = %f\n\n", decimale);
    }
    else{
        sprintf(binaire,"0"); // on ecrit 1
        // printf("Le binaire après la virgule = %s\n\n", binaire);
        // printf("La decimale x2 = %f\n\n", decimale);
    }
    for(int i=0; i<precision-1; i++){ // pour chaque occurence de la precision moins 1 car une occurence deja faite !
        decimale=decimale*2; // multiplications par deux successives
        if(decimale>=1){
            strcat(binaire,"1"); // on rajoute 1
            decimale--;
            // printf("Le binaire après la virgule = %s\n\n", binaire);
            // printf("La decimale x2 = %f\n\n", decimale);
        }
        else{
            strcat(binaire,"0"); // on rajoute 0
            // printf("Le binaire après la virgule = %s\n\n", binaire);
            // printf("La decimale x2 = %f\n\n", decimale);
        }
    }
    // printf("Le binaire après la virgule = %s\n\n", binaire);
    sprintf(b_p_c,binaire); // on ecrit le binaire trouve dans le binaire de la partie après la virgule
    // printf("Le binaire après la virgule = %s\n\n", b_p_c);
}

void remove_coma(char *binaire_exposant){ // enleve la virgule et le premier bit implicite

    int taille = strlen(binaire_exposant); // extraction de la taille du binaire
    // printf("Taille du binaire avec la virgule = %d\n\n",taille);
    int index = NULL; // indice de la virgule
    int intermediaire;
    // printf("Le binaire avec la virgule = %s\n\n",binaire_exposant);

    for(int i=0; i<taille; i++){ // pour chaque case de la chaine
        if(binaire_exposant[i]==46){
            index = i; // extraction de la virgule
            // printf("Index de la virgule = %d\n\n",index);
        }
    }
    if(index!=NULL){ // s il y a une virgule
        for(int j=index; j<taille; j++){ // pour chaque case de la chaine
            // printf("Occurence du remove coma = %d\n\n",j);
            if(binaire_exposant[j]!='\0'){ // tant qu on est pas a la fin
                intermediaire = binaire_exposant[j];
                binaire_exposant[j] = binaire_exposant[j+1];
                binaire_exposant[j+1] = intermediaire;
            }
            // printf("Le binaire sans la virgule = %s\n\n",binaire_exposant);
        }
    }
    // au passage on supprime egalement le premier bit implicite avant la virgule
    for(int k=0; k<taille; k++){ // pour chaque case de la chaine
        intermediaire = binaire_exposant[k];
        binaire_exposant[k] = binaire_exposant[k+1];
        binaire_exposant[k+1] = intermediaire;
    }
    // printf("Le binaire sans le premier bit = %s\n\n",binaire_exposant);
}

void affichage_console(char *binaire_ieee_754, char *reel){ // affichage du resultat final dans la console

    int taille;
    printf("**************************************************************************************************\n");
    printf("* Le binaire de %s selon la norme IEEE 754 = ",reel);
    taille = strlen(binaire_ieee_754); // extraction de la taille du binaire final

    for(int i=0; i<taille; i++){
        if(i == 1 || i == 9){
            printf(" ");
        }
        printf("%c",binaire_ieee_754[i]); // %c pour afficher la valeur en ASCII !
    }
    printf("      *\n");
    printf("* Le binaire de %s selon la norme IEEE 754 =",reel);
    taille = strlen(binaire_ieee_754); // extraction de la taille du binaire final
    for(int i=0; i<taille; i++){
        if(i%4 == 0){
            printf(" ");
        }
        printf("%c",binaire_ieee_754[i]); // %c pour afficher la valeur en ASCII !
    }
    printf(" *\n**************************************************************************************************\n\n");

}
// *****************************************************************************************************************
