// contient l implementation des methodes de fenetre, notamment du constructeur.

#include "fenetre.h"

fenetre::fenetre() : QWidget(){

    // construction du titre
    titre = new QLabel("", this);
    // construction du champs d entree
    reel = new QLineEdit;
    // construction du bouton
    conversion = new QPushButton("run_project", this);
    // construction de la sortie
    resultat = new QLabel("", this);
    // construction du layout vertical
    mise_en_forme_V = new QVBoxLayout;
    // declaration de la fonction
    void norme_ieee_754(QLineEdit,QLabel);

    // personnalisation de la fenetre
    setFixedSize(350,200);
    setWindowIcon(QIcon("icone.png"));
    setWindowTitle("Norme IEEE 754");

    // personalisation du titre
    titre->setText("Saisissez un nombre réel puis convertissez-le en\nsimple précision (32 bits) conformément à la\nnorme IEEE 754");
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

    // ajout des widgets
    mise_en_forme_V->addWidget(titre);
    mise_en_forme_V->addWidget(reel);
    mise_en_forme_V->addWidget(conversion);
    mise_en_forme_V->addWidget(resultat);

    setLayout(mise_en_forme_V);

    // lien entre l event du bouton et la fonction a effectuer
    connect(conversion, SIGNAL(clicked()),this,SLOT(norme_ieee_754(reel,resultat)));

}

void norme_ieee_754(QLineEdit reel, QLabel resultat){
    QString test = reel.text(); // stockage du reel dans une variable intermediaire
    resultat.setText(test); // placement du reel dans le widget "resultat"
}
