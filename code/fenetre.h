// contient l en-tete de notre classe fenetre qui herite de QWidget
#ifndef FENETRE_H
#define FENETRE_H

#include <QApplication>
#include <QWidget>
#include <QPushButton> // cette ligne vous permet de créer des objets de type QPushButton
#include <QVBoxLayout>
#include <QLineEdit>
// #include <QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <string.h> // chaque fois que vous utilisez des fonctions de manipulation de chaînes.
#include <stdlib.h>

using namespace std;

class fenetre : public QWidget{ // On herite de QWidget (IMPORTANT)

        Q_OBJECT // obligatoire pour utiliser les signaux et les slots

    public:
        fenetre(QWidget * owner = nullptr); // on doit toujours pouvoir passer un parent a un QWidget, c est comme ça que fonctionne le mecanisme de gestion de la memoire de Qt.

    public slots:
        void onClick();

    private:
        QLabel *titre; // enonce
        QLineEdit *reel; // champs d entree
        QPushButton *conversion; // bouton d enclenchement
        QLabel *resultat; // sortie
        /* inutile de garder un pointeur sur le layout
        QVBoxLayout *mise_en_forme_V; // mise en forme verticale */

};

#endif // FENETRE_H
