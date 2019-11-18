#include <iostream>
#include <limits>

using namespace std;

string semaineFormatee(int pos){
    string strSemaine = "LMMJVSD", resultat = "";
    pos -= 1; //Dès le début en fait -1 à la position pour la faire correspondre au position des jours dans le string "strSemaine"
    if(pos==0){ //Si on veut une semaine "normale", on retourne simplement strSemaine
        resultat = strSemaine;
        return resultat;
    }else{
        const int NBR_JOUR_SEMAINE = 7;
        int iPremierJour = NBR_JOUR_SEMAINE - pos; //On definis le premier jour à afficher en fonction de la position

        for (int i = 0; i < strSemaine.length(); i++){
            resultat += strSemaine[iPremierJour];
            iPremierJour++;
            if(iPremierJour == strSemaine.length()){ //Au moment où on arrive à la dernière position du jour de la semaine, on remet le compteur à 0 pour afficher les jours restant. (ex: 4560123 ou encore 5601234, 0 étant le lundi)
                iPremierJour = 0;
            }
        }
        return resultat;
    }
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
    }
    else {
        premierJourDuMois -= 1;
    }
    return premierJourDuMois;
}

int checkEntree(string msgQuestion, string msgErreur, int iMin, int iMax){

    int iEntree = 0;

    do{
        cin.clear();
        cout << msgQuestion << " " << "(" << iMax << "-" << iMin << ") ";
        cin >> iEntree;
        // Flush toute la ligne de l'entrée standard pour "réinitialiser"
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }while (iEntree < iMin || iEntree > iMax || cin.fail());

    return iEntree;
}

string AffichageCentre(string texte, int largeur){
    int espaceGauche = 0;
    largeur -= texte.length();
    espaceGauche =  largeur/2;

    for (int i = 0; i <espaceGauche ; ++i) {
        texte = "." + texte;
    }
    for (int i = 0; i <espaceGauche ; ++i) {
        texte += ".";
    }

    return texte;
}

string afficheMois(int iPremierJour, int iNumeroMois){
    //iPremierJour--; iNumeroMois--;
    string resultat = "";
    int iJourParMois[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    string nomMois[] = {"Janvier","Février","Mars","Avril","Mai","Juin","Juillet","Août","Septembre","Octobre","Novembre","Décembre"};
    int iJour = 1, iCpt7 = iPremierJour;

    resultat += AffichageCentre(nomMois[iNumeroMois], 21) + "\n";

    for (int i = 0; i < 42 ; i++) {

        if(i%7==0 && i!=0){
            resultat += "\n";
        }

        if(i == iPremierJour && iJour <= iJourParMois[iNumeroMois]){
            if(iJour <= 9){
                resultat += " " + to_string(iJour);
            }else{
                resultat += to_string(iJour);
            }
            iPremierJour++;
            iJour++;
        }else{
            resultat += " -";
        }

        resultat += " ";
    }

    return resultat;
}

int main() {
    //Bonjour je fais un test de github KRAKEN

    //checkEntree("Quelle annee voulez-vous afficher?","Entree non valide", 1, 7);

    //Quelle année vouleu-vous afficher ?
    int annee = 1992;
    //Position du Lundi (1-7)
    int lundiPos = 4;

    int iPremierJour = calculDuJour(annee);
    cout << afficheMois(iPremierJour,1);

}