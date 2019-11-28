/*
 -----------------------------------------------------------------------------------
 Laboratoire : 05
 Fichier     : main.cpp
 Auteur(s)   : Luca Zacheo, Enzo Allemano, David Darmanger
 Date        : 04/11/2019

 But         : Le but de ce laboratoire est d'afficher dans la console le calendrier d'une année.
			Vous demandez à l'utilisateur de rentrer une année entre 1600 et 3000, et la place du lundi dans l'ordre des 7 jours de la semaine (entre 1 et 7).
			En sortie, vous affichez par exemple pour 2016 et le lundi en position 1.

 Remarque(s) :

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */

#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

/**
\brief Permet de positionner le lundi selon le choix de l'utilisateur
\param[in] pos un nombre entier qui représente la position du lundi
\return Retourne la chaîne formatée selon la position du lundi

 Fonction permettant de placer le lundi selon le choix de l'utilisateur.
 La chaîne représentant la semaine est formaté comme ceci : "LMMJVSD" pour
 lundi, mardi, mercredi, ... puis on va la modifier par rapport à la postion que
 l'utilisateur aura choisi. Donc s'il décide que le lundi sera en postition 2
 alors la chaîne devient "DLMMJVS".
*/
string semaineFormatee(int pos){
    string strSemaine = "LMMJVSD", resultat = "";
    if(pos==0){ //Si on veut une semaine "normale", on retourne simplement strSemaine

        for (int i = 0; i < strSemaine.length(); ++i) {
            resultat += "  ";
            resultat += strSemaine[i];
        }
        
    }else{
        const int NBR_JOUR_SEMAINE = 7;
        int iPremierJour = NBR_JOUR_SEMAINE - pos; //On definis le premier jour à afficher en fonction de la position

        for (int j = 0; j < strSemaine.length(); j++){
            resultat += "  ";
            resultat += strSemaine[iPremierJour];
            iPremierJour++;
            if(iPremierJour == strSemaine.length()){ //Au moment où on arrive à la dernière position du jour de la semaine, on remet le compteur à 0 pour afficher les jours restant. (ex: 4560123 ou encore 5601234, 0 étant le lundi)
                iPremierJour = 0;
            }
        }
    }

    return resultat + "\n";
}

/**
\brief Fonction qui détermine si l'année est bissextile
\param[in] annee un nombre entier qui représente l'année qui va être testée
\return Retourne un bool: s'il vaut 1, l'année est bissextile sinon elle ne l'est pas
\link http://calendrier.24h00.org/ab/
 
 Fonction permettant de déterminer si l'année choisie est bissextile. 
*/
bool estBissextile(int annee)
{
    //Formule permettant de connaître si une année est bissextile
    if(annee%4==0 && annee%100!=0 || annee%400==0)
    {
        return 1;
    }
    return 0;
}

/**
\brief Fonction qui permet de connaître quel est le premier jour du mois
\param[in] annee un nombre entier qui représente l'année qui va être testée
\return Retourne un entier qui représente la position du lundi dans la semaine
\link https://fr.wikibooks.org/wiki/Curiosit%C3%A9s_math%C3%A9matiques/Trouver_le_jour_de_la_semaine_avec_une_date_donn%C3%A9e
 
 Fonction qui va calculer grâce à une formule mathématique, le premier jour du mois
 selon l'année choisie par l'utilisatuer.
*/
int calculDuJour (int annee){

    //Nous n'avons besoin que du premier jour du premier mois le 01 Janvier.
    const int MOIS = 1;
    const int JOUR = 1;

    //Ces deux calculs vienent de la formule citée plus haut, nous faisons donc "-1" et "+10" car nous ne voulons que le mois de Janvier
    int anneeFormule = annee-1;
    int moisFormule = MOIS + 10;

    int premierJourDuMois = (JOUR + anneeFormule + anneeFormule/4 - anneeFormule/100 + anneeFormule/400 + (31*moisFormule)/12) % 7;

    /*Décalage du résultat pour avoir le lundi à 0, mardi à 1 etc.. car la formule de base ressort le dimanche à 0.
    or pour la suite du labo nous voulons que le dimanche soit à la position 6.*/
    if (premierJourDuMois == 0) {
        premierJourDuMois = 6;
    }else{
        premierJourDuMois--;
    }

    return premierJourDuMois;
}

/**
\brief Permet de vérifier les entrées utilisateur et afficher des messages
\param[in] msgQuestion chaîne qui sera le texte affiché lors de la saisie
\param[in] msgErreur chaîne qui sera le texte affiché lors d'une erreur de saisie
\param[in] iMin entier qui représente la borne minimum pour la saisie
\param[in] iMax entier qui représente la borne maximum pour la saisie
\return Retourne un entier qui représente l'année choisie par l'utilisateur
 
 Fonction qui va permettre d'afficher les messages de saisies et d'erreurs de saisies
 à l'utilisateur. Permet également de vérifier la saisie de l'utilisateur.
 (Vérifie si la saisie se trouve entre les bornes minimale et maximale)
*/
int checkEntree(string msgQuestion, string msgErreur, int iMin, int iMax){
   
    //Entrée de l'utilisateur qui est l'année séléctionnée
    int iEntree;

    cout << msgQuestion << " " << "(" << iMin << "-" << iMax << ") ";
    cin >> iEntree;

    //Si l'entrée se trouve en dehors des bornes min/max
    while (iEntree < iMin || iEntree > iMax){
        //on redemande à l'utilisateur de saisir une année
        cout << msgErreur << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << msgQuestion << " " << "(" << iMin << "-" << iMax << ") ";
        cin >> iEntree;
    }

    return iEntree;
}

/**
\brief Fonction qui permet d'afficher du texte au centre d'une ligne
\param[in] texte chaîne qui représente le texte à centrer
\param[in] largeur entier qui représente la largeur d'une ligne
\return Retourne la chaîne avec le texte centré au milieu de la ligne
 
 Fonction qui va permettre d'afficher n'importe quel texte au centre d'une ligne
 d'une largeur quelconque.
*/
string AffichageCentre(string texte, int largeur) {
    int espaceGauche = 0, espaceDroite = 0, espaceRestant = largeur;
    espaceRestant -= texte.length();

    espaceGauche = espaceRestant / 2;

    if(espaceRestant%2 == 0){
        espaceDroite = espaceGauche;
    }else{
        espaceDroite = espaceGauche + 1;
    }

    for (int i = 0; i < espaceGauche; ++i) {
        texte = " " + texte;
    }
    for (int i = 0; i < espaceDroite; ++i) {
        texte += " ";
    }
    return texte + "\n";
}

/**
\brief Fonction qui permet d'afficher tous les jours d'un mois
\param[in] iPremierJour entier qui contient le premier jour du mois à afficher
\param[in] iNumeroMois entier qui représente quelle mois sera affiché (0 -> Janvier)
\param[in] positionLundi entier qui contient la position du lundi dans la semaine
\param[in] iAnnee entier de l'année entrée par l'utilisateur
 
 Fonction qui va permettre d'afficher tous les jours d'un mois selon un format
 spécifique. Cette fonction est utilisée de manière récursive pour permettre 
 d'afficher tous les mois d'une année. 
*/
void afficheMois(int iPremierJour, int iNumeroMois, int positionLundi, int iAnnee){

    int iJourParMois[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    string nomMois[] = {"Janvier","Fevrier","Mars","Avril","Mai","Juin","Juillet","Aout","Septembre","Octobre","Novembre","Decembre"};

    string strResultatFinalMois = "";

    int iCptEspace = 0;
    int iJour = 1;

	//Permet de ne pas avoir une ligne entière vide en première position
    if(iPremierJour > 7){
        iPremierJour -= 7;
    }

	//Rajoute un jour au mois de février si l'année est bissextile
    if(estBissextile(iAnnee) && iNumeroMois == 1){
        iJourParMois[iNumeroMois]++;
    }

	
    static int iCptJourSemaine = iPremierJour;

    strResultatFinalMois += AffichageCentre(nomMois[iNumeroMois], 21);
    strResultatFinalMois += semaineFormatee(positionLundi);

	//On crée un "cadrillage" de 6 lignes et 7 colonnes, ce qui donne 42 "cases". On déplace les jours du mois courant dans ce "cadrillage".
    for (int i = 0; i < 42 ; i++) {

		//Quand on arrive à la fin de la semaine on fait un retour à la ligne
        if(i%7==0 && i!=0){
            strResultatFinalMois += "\n";
        }
        
        if(i == iPremierJour && iJour <= iJourParMois[iNumeroMois]){
            if(iJour <= 9){
                strResultatFinalMois += "  " + to_string(iJour);
            }else{
                strResultatFinalMois += " " + to_string(iJour);
            }

            //A quel jour de la semaine le premier jour du moi correspond
            iPremierJour++;

            //Incrémentation des jours du mois
            iJour++;

            //Compteur servant à incrémenter jusqu'a 6
            iCptJourSemaine++;

            if(iCptJourSemaine > 6){
                iCptJourSemaine = 0;
            }
			
            iCptEspace = 0;

        }else{
            strResultatFinalMois += "   ";
            iCptEspace++;
        }
    }

    cout << strResultatFinalMois << endl;

    if(iCptEspace >= 7){

    }else{
        cout << string(21,' ') << endl; //Permet de correspondre au format demandé dans le codecheck
    }

	//Ici on rapelle la fonction en augmentant le mois de +1 jusqu'à Décembre
    if(iNumeroMois < 11){
        afficheMois(iCptJourSemaine,iNumeroMois+1, positionLundi, iAnnee);
    }
}

int main() {
    int iAnnee, iPosLundi;

	//Récupération de l'année
    iAnnee = checkEntree("Quelle annee voulez-vous afficher?","Entree non valide", 1600, 3000);
	//Récupération de la position du lundi dans la semaine
    iPosLundi = checkEntree("Quel jour de la semaine est le lundi?","Entree non valide", 1, 7);
    iPosLundi--;

	//Récpération du premier jour du mois de janvier selon l'année choisie
    int iPremierJour = calculDuJour(iAnnee);

	//Affichage au centre de l'année
    cout << endl << AffichageCentre(to_string(iAnnee),21);
    cout << string(21,' ') << endl;

	//Affichage des mois
    afficheMois(iPremierJour + iPosLundi,0, iPosLundi , iAnnee);
}