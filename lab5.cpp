#include <iostream>
#include <limits>

using namespace std;

string semaineFormatee(int pos){
    string strSemaine = "LMMJVSD", resultat = "";
    //pos--; //Dès le début on fait -1 à la position pour la faire correspondre au position des jours dans le string "strSemaine"
    if(pos==0){ //Si on veut une semaine "normale", on retourne simplement strSemaine

        for (int i = 0; i < strSemaine.length(); ++i) {
            resultat += "..";
            resultat += strSemaine[i];
        }

    }else{
        const int NBR_JOUR_SEMAINE = 7;
        int iPremierJour = NBR_JOUR_SEMAINE - pos; //On definis le premier jour à afficher en fonction de la position

        for (int j = 0; j < strSemaine.length(); j++){
            resultat += "..";
            resultat += strSemaine[iPremierJour];
            iPremierJour++;
            if(iPremierJour == strSemaine.length()){ //Au moment où on arrive à la dernière position du jour de la semaine, on remet le compteur à 0 pour afficher les jours restant. (ex: 4560123 ou encore 5601234, 0 étant le lundi)
                iPremierJour = 0;
            }
        }
    }

    return resultat + "\n";

}

/*Fonction qui détermine si l'année est bissectile*/
bool estBissextile(int annee)
{
    if(annee%4==0 && annee%100!=0 || annee%400==0)
    {
        return 1;
    }
    return 0;
}

//Formule trouvée sur (méthode 2) :https://fr.wikibooks.org/wiki/Curiosit%C3%A9s_math%C3%A9matiques/Trouver_le_jour_de_la_semaine_avec_une_date_donn%C3%A9e
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

int checkEntree(string msgQuestion, string msgErreur, int iMin, int iMax){

    int iEntree;

    cout << msgQuestion << " " << "(" << iMin << "-" << iMax << ") ";
    cin >> iEntree;




    while (iEntree < iMin || iEntree > iMax){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << msgQuestion << " " << "(" << iMin << "-" << iMax << ") ";
        cin >> iEntree;
    }

    return iEntree;
}

string AffichageCentre(string texte, int largeur) {
    int espaceGauche = 0;
    largeur -= texte.length();
    espaceGauche = largeur / 2;

    for (int i = 0; i < espaceGauche; ++i) {
        texte = "." + texte;
    }
    for (int i = 0; i < espaceGauche; ++i) {
        texte += ".";
    }
    return texte + "\n";
}

void afficheMois(int iPremierJour, int iNumeroMois, int positionLundi){

    int iJourParMois[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    string nomMois[] = {"Janvier","Fevrier","Mars","Avril","Mai","Juin","Juillet","Aout","Septembre","Octobre","Novembre","Decembre"};

    string strResultatFinalMois = "";

    int iJour = 1;
    iPremierJour += positionLundi;
    static int iCptJourSemaine = iPremierJour;

    strResultatFinalMois += AffichageCentre(nomMois[iNumeroMois], 21);
    strResultatFinalMois += semaineFormatee(positionLundi);

    for (int i = 0; i < 42 ; i++) {

        if(i%7==0 && i!=0){
            strResultatFinalMois += "\n";
        }

        if(i == iPremierJour && iJour <= iJourParMois[iNumeroMois]){
            if(iJour <= 9){
                strResultatFinalMois += ".." + to_string(iJour);
            }else{
                strResultatFinalMois += "." + to_string(iJour);
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

        }else{
            strResultatFinalMois += "...";
        }

    }
    cout << strResultatFinalMois + "\n";

    if(iNumeroMois < 11){
        afficheMois(iCptJourSemaine,iNumeroMois+1, positionLundi);
    }

}

int main() {
    int iAnnee, iPosLundi;

    iAnnee = checkEntree("Quelle annee voulez-vous afficher?","Entree non valide", 1600, 3000);
    iPosLundi = checkEntree("Quel jour de la semaine est le lundi?","Entree non valide", 1, 7);
    iPosLundi--;

    int iPremierJour = calculDuJour(iAnnee);

    cout << AffichageCentre(to_string(iAnnee),21);
    afficheMois(iPremierJour,0, iPosLundi);
}