// cet include vous permet d acceder a la classe QApplication, qui est la classe de base de tout programme Qt.
#include <QApplication>

#include "fenetre.h"

int main(int argc, char *argv[]){

    QApplication app(argc,argv); // la premiere ligne du main() cree un nouvel objet de type QApplication

    fenetre window; // appel au constructeur de la fenetre

    window.show(); // affichage de la fenetre

    return app.exec(); // cette methode demarre notre programme et lance donc l affichage des fenetres.
}
