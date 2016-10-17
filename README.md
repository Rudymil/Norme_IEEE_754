ProjetPersonnel1-Rudolf_MILLET
==
Projet sur la norme IEEE 754
-
### Enoncé #

<p>Bonjour à toutes et à tous,</p>

<p>Voici le premier projet que vous avez à faire en devoir personnel. Les livrables
(ci-dessous) sont à rendre le 26/10/2016 à 23h59mn59s au plus tard par l'envoi d'un
courriel à admin.tsi@ensg.eu indiquant l'URL du projet (Cf. infra). Le projet
consiste en :</p>

<p>«<br/>
La saisie, la conversion et l'affichage sous forme d'une chaîne de caractères
représentant les bits (0,1) de nombres réels en simple précision (32 bits)
conformément à la norme IEE 754 (Cf. https://fr.wikipedia.org/wiki/IEEE_754).<br/>
Le logiciel permettra la saisie d'un nombre et l'affichage de sa représentation
textuelle.<br/>
Le choix du langage est laissé à l'appréciation de chacun-e.<br/>
Le livrable attendu est un projet sur gitlab (sous votre compte dans le groupe
TSI2106) avec le code source (analyse, code, chaîne de compilation/livraison) et une
vidéo démontrant le résultat (pas plus de 2mn).
»</p>

<p>La structure du logiciel sera la base de l'évaluation (découpage, ré-utilisabilité,
complexité à maintenir, documentation, tests et utilisation par l'équipe pédagogique
!).</p>

<p>Un bonus +1 sera attribué au premier livrable (dans la date de réception des
courriels indiquant que le projet est livré) qui obtiendra une note supérieure
strictement à 10.<br/>
Un bonus +1 sera attribué pour la documentation du livrable (modélisation,
algorithmie, code source, choix effectués, vidéo).<br/>
La remise des livrables hors délai sera sanctionnée par un malus de -2.<br/>
Une note de 0 sera attribuée en cas de plagiat ou similitude des livrables.</p>

<p>Bon courage</p>

####  Analyse

<p>Le code source se trouve dans le répertoire "code".<br/>
Le code a été écrit en C++11 dans Qt Creator 4.1.0 basé sur Qt 5.7.0 (MSVC 2013, 32 bit) et compilé sous MinGW 32bit (Debug, Profile, Release).</p>

<p>Voici la seule classe utilisée dans ce projet. Il s'agit d'une classe Qt qui permet la construction d'une simple fenêtre composée au moins d'un champs d'entrée et d'un bouton de validation. A cette classe est attachée une unique fonction connectée au bouton et qui lance le programme principal.</p>

<p>._________________________________________________<br/>
|.................................................|\<br/>
|...<strong>fenetre.h</strong>.....................................|.\<br/>
|....___________________________________________..|__\<br/>
|...|...........................................|.....|<br/>
|...|...fenetre : public QWidget................|.....|<br/>
|...|___________________________________________|.....|<br/>
|...|...........................................|.....|<br/>
|...|...public :................................|.....|<br/>
|...|.......fenetre(QWidget * owner = nullptr)..|.....|<br/>
|...|...........................................|.....|<br/>
|...|...private:................................|.....|<br/>
|...|.......QLabel *titre.......................|.....|<br/>
|...|.......QLineEdit *reel.....................|.....|<br/>
|...|.......QPushButton *conversion.............|.....|<br/>
|...|.......QLabel *resultat....................|.....|<br/>
|...|___________________________________________|.....|<br/>
|...|...........................................|.....|<br/>
|...|...public slots:...........................|.....|<br/>
|...|.......void onClick()......................|.....|<br/>
|...|___________________________________________|.....|<br/>
|_____________________________________________________|</p>

####  Description

<p>Après l'appel du constructeur de la fenêtre dans "main.cpp", le code se divise en deux parties.</p>

<p>Dans <strong>"fenetre.cpp"</strong> se trouve le constructeur de la fenêtre et la fonction connectée au bouton :</p>

<code>fenetre::fenetre(QWidget *owner):QWidget{owner},titre{new QLabel{"",this}},reel{new QLineEdit{"",this}},conversion{new QPushButton{"run_project",this}},resultat{new QLabel{"",this}}{...}</code>

<p>Cette classe gère les paramètres de la fenêtre.</p>

<code>void fenetre::onClick(){...}</code>

<p>Cette fonction s'assure que le réel à convertir est correctement écrit.</p>

<p>Dans <strong>"norme_ieee_754.cpp"</strong> se trouve la fonction principale appelée dans "fenetre.cpp" et toutes les fonctions annexes :</p>

<code>void norme_ieee_754(const char *const_reel, char *binaire_ieee_754){...}</code>

<p>Il s'agit du programme principale qui appelle dans l'ordre les fonctions en annexes.<br/>
Elle prend en entrée 2 chaînes de caractères : une constante et une à remplir.</p>

<code>void f_signe(char *reel, char *binaire_ieee_754){...}</code>

<p>Cette fonction ajoute 1 ou 0 au binaire en fonction du signe du reel en entrée.</p>

<code>void f_binaire(char *reel, char *binaire_sans_signe){...}</code>

<p>Cette fonction fabrique simplement le binaire du reel en entrée.<br/>
Elle appelle cependant les deux fonctions "binaire_post_coma" et "binaire_post_coma" pour traiter le réel en deux parties avant de concaténer les 2 binaires obtenus.</p>

<code>int f_virgule_mantisse(char *binaire_sans_signe, char *reel){...}</code>

<p>Cette fonction fabrique la mantisse du binaire normé en procédant au décalage de la virgule en fonction du réel d'entrée. Le décalage est renvoyé en sortie. La chaîne de caractères ainsi modifiée doit contenir toujours 25 caractères à la fin, à savoir la taille de la mantisse plus la virgule et le binaire implicite. On procède donc à un rajout ou à une suppression de bits.</p>

<code>void f_exposant(char *binaire_exposant, char *reel, int decalage){...}</code>

<p>Cette fonction fabrique l'exposant de taille 9 en fonction du décalage mesuré. Certaines exceptions sont prises en compte dans le processus d'où la présence du réel en entrée.</p>

<code>int binaire_ante_coma(int quotient, char *b_a_c){...}</code>

<p>Cette fonction convertie en binaire la partie entière d'un réel.</p>

<code>void binaire_post_coma(float decimale, int t_b_a_c, char *b_p_c){...}</code>

<p>Cette fonction convertie en binaire la partie décimale d'un réel.</p>

<code>void remove_coma(char *binaire_exposant){...}</code>

<p>Cette fonction supprime la virgule et le bit implicite de la mantisse. La mantisse possède donc bien 23 bits.</p>

<code>void affichage_console(char *binaire_ieee_754, char *reel){...}</code>

<p>Cette fonction gère un affichage propre du résultat final dans le terminal.</p>

####  Installation

<p>Pour utiliser l'application, il suffit tout simplement de lancer un des exécutables suivants :</p>

<p>build-code-Desktop_Qt_5_7_0_MinGW_32bit-Debug\debug\code.exe<br/>
build-code-Desktop_Qt_5_7_0_MinGW_32bit-Profile\release\code.exe<br/>
build-code-Desktop_Qt_5_7_0_MinGW_32bit-Release\release\code.exe</p>

####  Bibliographie

<a href="http://www.toutimages.com/codes_caracteres.htm">Codes    ASCII     ISO     HTML</a>

<a href="https://openclassrooms.com/courses/programmez-avec-le-langage-c/compiler-votre-premiere-fenetre-qt">Compiler votre première fenêtre Qt</a>

<a href="http://sebastienguillon.com/test/javascript/convertisseur.html">Convertisseur décimal, hexadécimal, binaire</a>

<a href="https://fr.wikipedia.org/wiki/IEEE_754#Exemple_complexe">Format simple précision (32 bits) exemple</a>

<a href="http://www.learncpp.com/cpp-tutorial/19-header-files/">Header files</a>

<a href="https://forum.qt.io/topic/4635/how-to-convert-qstring-to-const-char/2">How to convert QString to const char </a>

<a href="https://openclassrooms.com/courses/apprenez-a-programmer-en-c/les-chaines-de-caracteres">Les chaînes de caractères</a>

<a href="http://qt.developpez.com/doc/4.7/qmessagebox/#icon-enum">QMessageBox</a>

<a href="http://arsene.perez-mas.pagesperso-orange.fr/numeration/reels.htm">Représentation des nombres réels dite à virgule fixe</a>

<a href="https://www.youtube.com/watch?v=mtizhxkB-Zw">Standard IEEE 754 des nombres à virgule flottante </a>

<a href="http://shugo.developpez.com/tutoriels/regexqt/">Utilisation des Regex avec Qt</a>

<a href="http://blog.wax-o.com/2014/04/tutoriel-un-guide-pour-bien-commencer-avec-markdown/">[ Tutoriel ] un guide pour bien commencer avec markdown</a>

<p>Merci à tous ceux qui m'ont aidé en résolvant mes problèmes rencontrés :</p>

<a href="https://openclassrooms.com/forum/sujet/passage-de-valeur-par-la-methode-connect-qt?page=1#message-91333711">Passage de valeur par la méthode "connect" Qt</a>

<a href="https://openclassrooms.com/forum/sujet/conversion-qstring-const-char?page=1#message-91343120">Conversion : QString -> const char</a>