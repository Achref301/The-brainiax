#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include"client.h"


char id[30],idrech[30];
GtkWidget *windowclient;

void
on_KKbuttonmenuprincipal_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_KKbuttonrechercher_clicked          (GtkWidget       *objet,
                                        gpointer         user_data)
{

CLIENT c;
char idrech[30];
GtkWidget *windowclient;
GtkWidget *KKentryid;
GtkWidget *KKtreeview;
FILE*f;
FILE*f2;


windowclient=lookup_widget(objet,"windowclient");
KKentryid=lookup_widget(objet,"KKentryid");
strcpy(idrech,gtk_entry_get_text(GTK_ENTRY(KKentryid)));
f=fopen("clients.bin","rb");

 if(f!=NULL)
 {
  while(fread(&c,sizeof(CLIENT),1,f))
     {
       f2=fopen("recherche.bin","ab+");
       if  (f2!=NULL)
   {  
     
     if ((strcmp(c.np,idrech)==0) || (strcmp(c.identifiant,idrech)==0) || (strcmp(c.sexe,idrech)==0) || (strcmp(c.valeur,idrech)==0))
     { 
     fwrite(&c,sizeof(CLIENT),1,f2);
     }
   
     KKtreeview=lookup_widget(windowclient,"KKtreeview");
     recherche(KKtreeview);
    
        fclose(f2);
    }

 }
 fclose(f);
}
remove("recherche.bin");

}



void
on_KKbuttonactualiser_clicked          (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *KKtreeview;
windowclient=lookup_widget(objet,"windowclient");
KKtreeview=lookup_widget(windowclient,"KKtreeview");
affichage(KKtreeview);
}

void
on_KKbuttonsupprimer_clicked           (GtkWidget       *objet,
                                        gpointer         user_data)
{
CLIENT c;
	    GtkWidget *KKtreeview;
	    windowclient=lookup_widget(objet,"windowclient");
	    KKtreeview=lookup_widget(windowclient,"KKtreeview");
	    suppression(id,c);
            affichage(KKtreeview);
          
}


void
on_KKbuttonmodifier_clicked            (GtkWidget       *objet,
                                        gpointer         user_data)
{
                gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(windowclient,"KKnotebook")));
                gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(windowclient,"KKnotebook")));		

	char Sexe[30];
	CLIENT c;		
	
	GtkWidget *KKcomboboxmodifsexe;
	GtkWidget *KKentrymodifid;
	GtkWidget *KKentrymodifnp;
	GtkWidget *KKspinbuttonmodifjour;
	GtkWidget *KKspinbuttonmodifmois;
	GtkWidget *KKspinbuttonmodifannee;
	GtkWidget *KKentrymodifvaleur;
	GtkWidget *sortiem;    
	
	KKspinbuttonmodifjour=lookup_widget(objet, "KKspinbuttonmodifjour");
	KKspinbuttonmodifmois=lookup_widget(objet, "KKspinbuttonmodifmois");
	KKspinbuttonmodifannee=lookup_widget(objet, "KKspinbuttonmodifannee");
	KKcomboboxmodifsexe=lookup_widget(objet, "KKcomboboxmodifsexe");
	KKentrymodifid=lookup_widget(objet,"KKentrymodifid");
	KKentrymodifnp=lookup_widget(objet,"KKentrymodifnp");
	KKentrymodifvaleur=lookup_widget(objet,"KKentrymodifvaleur");

	
	gtk_spin_button_set_value(KKspinbuttonmodifjour,c.date.jour);
	gtk_spin_button_set_value(KKspinbuttonmodifmois,c.date.mois);
	gtk_spin_button_set_value(KKspinbuttonmodifannee,c.date.annee);
	
	gtk_entry_set_text(GTK_ENTRY(KKentrymodifid),c.identifiant);
	gtk_entry_set_text(GTK_ENTRY(KKentrymodifnp),c.np);
	gtk_entry_set_text(GTK_ENTRY(KKentrymodifvaleur),c.valeur);

}



void
on_KKbuttonajouter_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
char Sexe[30];
CLIENT c;
GtkWidget *KKentryajoutid;
GtkWidget *KKentryajoutnp;
GtkWidget *KKentryajoutvaleur;
GtkWidget *KKspinbuttonajoutjour;
GtkWidget *KKspinbuttonajoutmois;
GtkWidget *KKspinbuttonajoutannee;
GtkWidget *KKcomboboxajoutsexe;
GtkWidget *sortiea;

KKspinbuttonajoutjour=lookup_widget(objet, "KKspinbuttonajoutjour");
KKspinbuttonajoutmois=lookup_widget(objet, "KKspinbuttonajoutmois");
KKspinbuttonajoutannee=lookup_widget(objet, "KKspinbuttonajoutannee");
KKcomboboxajoutsexe=lookup_widget(objet, "KKcomboboxajoutsexe");
KKentryajoutid=lookup_widget(objet,"KKentryajoutid");
KKentryajoutnp=lookup_widget(objet,"KKentryajoutnp");
KKentryajoutvaleur=lookup_widget(objet,"KKentryajoutvaleur");
sortiea=lookup_widget(objet, "KKlabelmsgsucc");

strcpy(c.identifiant,gtk_entry_get_text(GTK_ENTRY(KKentryajoutid)));
strcpy(c.np,gtk_entry_get_text(GTK_ENTRY(KKentryajoutnp)));
strcpy(c.valeur,gtk_entry_get_text(GTK_ENTRY(KKentryajoutvaleur)));
c.date.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(KKspinbuttonajoutjour));
c.date.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(KKspinbuttonajoutmois));
c.date.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(KKspinbuttonajoutannee));

strcpy(Sexe,gtk_combo_box_get_active_text(GTK_COMBO_BOX(KKcomboboxajoutsexe)));
strcpy(c.sexe,Sexe);
ajout(c);
gtk_label_set_text(GTK_LABEL(sortiea),"Ajout effectué avec succès!");
}



void
on_KKbuttonconfirmermodif_clicked      (GtkWidget       *objet,
                                        gpointer         user_data)
{
CLIENT c;
char Sexe[30];
GtkWidget *KKcomboboxmodifsexe;
GtkWidget *KKentrymodifid;
GtkWidget *KKentrymodifnp;
GtkWidget *KKspinbuttonmodifjour;
GtkWidget *KKspinbuttonmodifmois;
GtkWidget *KKspinbuttonmodifannee;
GtkWidget *KKentrymodifvaleur;
GtkWidget *sortiem;    
	
KKspinbuttonmodifjour=lookup_widget(objet, "KKspinbuttonmodifjour");
KKspinbuttonmodifmois=lookup_widget(objet, "KKspinbuttonmodifmois");
KKspinbuttonmodifannee=lookup_widget(objet, "KKspinbuttonmodifannee");
KKcomboboxmodifsexe=lookup_widget(objet, "KKcomboboxmodifsexe");
KKentrymodifid=lookup_widget(objet,"KKentrymodifid");
KKentrymodifnp=lookup_widget(objet,"KKentrymodifnp");
KKentrymodifvaleur=lookup_widget(objet,"KKentrymodifvaleur");
sortiem=lookup_widget(objet, "KKlabelmodifreus");

strcpy(c.identifiant,gtk_entry_get_text(GTK_ENTRY(KKentrymodifid)));
strcpy(c.np,gtk_entry_get_text(GTK_ENTRY(KKentrymodifnp)));
strcpy(c.valeur,gtk_entry_get_text(GTK_ENTRY(KKentrymodifvaleur)));
c.date.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(KKspinbuttonmodifjour));
c.date.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(KKspinbuttonmodifmois));
c.date.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(KKspinbuttonmodifannee));
strcpy(Sexe,gtk_combo_box_get_active_text(GTK_COMBO_BOX(KKcomboboxmodifsexe)));
strcpy(c.sexe,Sexe);
modification(id,c);
gtk_label_set_text(GTK_LABEL(sortiem),"Modification effectuée avec succès!");
}

void
on_KKtreeview_row_activated            (GtkTreeView     *KKtreeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
	gchar* identifiant;
	GtkTreeModel *Model = gtk_tree_view_get_model(KKtreeview);

		if (gtk_tree_model_get_iter(Model, &iter, path)){
				gtk_tree_model_get(GTK_LIST_STORE(Model),&iter,1,&identifiant, -1);
				strcpy(id,identifiant);}
}



void
on_KKtri_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{

}
/*
CLIENT c;
GtkWidget *windowclient;
GtkWidget *KKtreeview;
FILE*f;
FILE*f2;
char t[50];
int n=50;


windowclient=lookup_widget(objet,"windowclient");
f=fopen("clients.bin","rb");

 if(f!=NULL)
 {
  while(fread(&c,sizeof(CLIENT),1,f))
     {
       f2=fopen("tri.bin","ab+");
       if  (f2!=NULL)
   {  
     
     
	for(int i=0;i<n;i++)
	{
		t[1]=c.np;
  	fwrite(t[1],sizeof(t[1]),n,f2);

	}

     
     
   
     KKtreeview=lookup_widget(windowclient,"KKtreeview");
     tri(KKtreeview);
    
        fclose(f2);
    }

 }
 fclose(f);
}
remove("tri.bin");

}
*/





void
on_topclientref_clicked                (GtkButton       *objet,
                                        gpointer         user_data)
{

GtkWidget *max , *nomp ;
FILE *f;
CLIENT c;
float j;
char maxpaim[20];
char nomprenom[20];
float mp=0;
f=fopen ("clients.bin","rb");
while (fread (&c,sizeof (CLIENT),1,f)!=0)
{      
strcpy(maxpaim,c.valeur);
sscanf (maxpaim,"%f",&j);

if (j>mp){
	mp =j;
	strcpy(nomprenom,c.np);}

}
fclose (f);

max=lookup_widget (objet,"label_max_paiments"); 
char *maxi = g_strdup_printf ("%f", mp);
gtk_label_set_text(GTK_LABEL(max),maxi);

nomp=lookup_widget (objet,"label_nompren");  
gtk_label_set_text(GTK_LABEL(nomp),nomprenom);


}
