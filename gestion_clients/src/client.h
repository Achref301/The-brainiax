#include <gtk/gtk.h>
typedef struct
{
int jour;
int mois;
int annee;
}Datee;


typedef struct
{
char np[30];
char identifiant[30];
char sexe[30];
char valeur[30];
Datee date;
}CLIENT;

void ajout(CLIENT c);
void recherche(GtkWidget* KKtreeview);
void suppression(char id[30], CLIENT c);
void affichage(GtkWidget* KKtreeview);
void modification(char id[30], CLIENT c);

