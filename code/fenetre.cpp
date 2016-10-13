// contient l implementation des methodes de fenetre, notamment du constructeur.

#include "fenetre.h"
#include "norme_ieee_754.h"

// classe fenetre
fenetre::fenetre(QWidget *owner)
    :QWidget{owner},
    titre{new QLabel{"",this}}, // construction du titre
    reel{new QLineEdit{"",this}}, // construction du champs d entree
    conversion{new QPushButton{"run_project",this}}, // construction du bouton
    resultat{new QLabel{"",this}} // construction de la sortie
    {

// construction du layout vertical
    auto mise_en_forme_V = new QVBoxLayout{}; // le layout, il ne sert que dans le constructeur, donc variable locale du constructeur, pas variable membre de la classe

// personnalisation de la fenetre
    setFixedSize(400,175);
    setWindowIcon(QIcon("icone.png"));
    setWindowTitle("Norme IEEE 754");

// personalisation du titre
    titre->setText("Saisissez un nombre réel puis\nappliquez la conversion en simple précision (32 bits)\nconformément à la norme IEEE 754");
    titre->setFont(QFont("Helvetica", 11));
    titre->setAlignment(Qt::AlignCenter);

// personalisation du reel
    //reel->maxLength();
    reel->setAlignment(Qt::AlignCenter);
    reel->setFont(QFont("Helvetica", 11));

// personnalisation du bouton
    conversion->setText("Conversion"); // que nous appelons tout simplement "Conversion"
    conversion->setFont(QFont("Helvetica", 11));
    conversion->setToolTip("Convertit et affiche sous forme d'une chaîne de caractères représentant les bits (0,1)");
    //conversion->move(60, 50);

// personalisation du resultat
    resultat->setAlignment(Qt::AlignCenter);
    resultat->setFont(QFont("Helvetica", 13));

// ajout des widgets
    mise_en_forme_V->addWidget(titre);
    mise_en_forme_V->addWidget(reel);
    mise_en_forme_V->addWidget(conversion);
    mise_en_forme_V->addWidget(resultat);

    setLayout(mise_en_forme_V);

    // on connect le click sur le bouton a notre slot onClick
    connect(conversion, &QPushButton::clicked, this, &fenetre::onClick);

}

// fonction principale activee par le bouton
void fenetre::onClick(){
    char binaire_ieee_754[32]; // chaine de caractere qui contiendra le binaire final
    norme_ieee_754(reel->text().toStdString().c_str(),binaire_ieee_754); // fonction principale dans norme_ieee_754.cpp
    resultat->setText(binaire_ieee_754); // rajout du binaire final dans le text de resultat
}
