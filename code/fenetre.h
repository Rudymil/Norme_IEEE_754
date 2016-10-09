// contient l en-tete de notre classe fenetre qui herite de QWidget
#ifndef FENETRE_H
#define FENETRE_H

#include <QApplication>
#include <QWidget>
#include <QPushButton> // cette ligne vous permet de créer des objets de type QPushButton
#include <QInputDialog> // si vous souhaitez que votre utilisateur saisisse une information
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFormLayout>
#include <QLabel>

class fenetre : public QWidget{ // On herite de QWidget (IMPORTANT)


    public:
        fenetre();


    public slots:
        void norme_ieee_754(QLineEdit,QLabel); // fonction activee par le bouton "conversion"


    signals:
        //clicked();


    private:
        QLabel *titre; // enonce
        QLabel *resultat; // sortie

        QLineEdit *reel; // champs d entree

        QPushButton *conversion; // bouton d enclenchement

        QVBoxLayout *mise_en_forme_V; // mise en forme verticale


};

#endif // FENETRE_H
