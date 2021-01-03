
#include <gtk/gtk.h>
typedef struct
{
int jour;
int mois;
int annee;
}Datee;


typedef struct
{
char type[30];
char identifiant[30];
char marque[30];
char valeur[30];
Datee date;
}CAPTEURS;

void ajout(CAPTEURS c);
void recherche(GtkWidget* AZtreeview);
void suppression(char id[30], CAPTEURS c);
void affichage(GtkWidget* AZtreeview);
void modification(char id[30], CAPTEURS c);
void affichagestat(GtkWidget* stattreeview);

int nombret(CAPTEURS c);
int nombreh(CAPTEURS c);
char marque(CAPTEURS c);
//void nombrecapteur(int *b,CAPTEURS c);
//void marque(int *b,CAPTEURS c);
