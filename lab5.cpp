#include <iostream>

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

int main() {
    cout << AffichageCentre("SALUT",21);
    //Bonjour je fais un test de github KRAKEN

}