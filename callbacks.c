#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif



#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include"aymen.h"

char id[30],idrech[30];
GtkWidget *windowcapteurs;
void
on_AZbuttonmenuprincipal_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
//pas encore
}


void
on_AZtreeview_row_activated            (GtkTreeView     *AZtreeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
	gchar* identifiant;
	GtkTreeModel *Model = gtk_tree_view_get_model(AZtreeview);

		if (gtk_tree_model_get_iter(Model, &iter, path)){
				gtk_tree_model_get(GTK_LIST_STORE(Model),&iter,1,&identifiant, -1);
				strcpy(id,identifiant);}
}


void
on_AZbuttonrechercher_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

CAPTEURS c;
GtkWidget *windowcapteurs;
GtkWidget *AZentryid;
GtkWidget *AZtreeview;
FILE*f;
FILE*f2;


windowcapteurs=lookup_widget(button,"windowcapteurs");
AZentryid=lookup_widget(button,"AZentryid");
strcpy(idrech,gtk_entry_get_text(GTK_ENTRY(AZentryid)));
f=fopen("capteurs.bin","rb");

 if(f!=NULL)
 {
  while(fread(&c,sizeof(CAPTEURS),1,f))
     {
       f2=fopen("recherche.bin","ab+");
       if  (f2!=NULL)
   {  
     
     if ((strcmp(c.identifiant,idrech)==0))
     { 
     fwrite(&c,sizeof(CAPTEURS),1,f2);
     }
   
     AZtreeview=lookup_widget(windowcapteurs,"AZtreeview");
     recherche(AZtreeview);
    
        fclose(f2);
    }

 }
 fclose(f);
}
remove("recherche.bin");

}


void
on_AZbuttonactualiser_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *AZtreeview;
windowcapteurs=lookup_widget(button,"windowcapteurs");
AZtreeview=lookup_widget(windowcapteurs,"AZtreeview");
affichage(AZtreeview);
}


void
on_AZbuttonsupprimer_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
CAPTEURS c;
	    GtkWidget *AZtreeview;
	    windowcapteurs=lookup_widget(button,"windowcapteurs");
	    AZtreeview=lookup_widget(windowcapteurs,"AZtreeview");
	    suppression(id,c);
            affichage(AZtreeview);
          
}


void
on_AZbuttonmodifier_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
                gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(windowcapteurs,"AZnotebook")));
                gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(windowcapteurs,"AZnotebook")));		
}



void
on_AZbuttonajouter_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
char Type[30];
CAPTEURS c;
GtkWidget *AZentryajoutid;
GtkWidget *AZentryajoutmrq;
GtkWidget *AZentryajoutvaleur;
GtkWidget *AZspinbuttonajoutjour;
GtkWidget *AZspinbuttonajoutmois;
GtkWidget *AZspinbuttonajoutannee;
GtkWidget *AZcomboboxajouttype;
GtkWidget *sortiea;

AZspinbuttonajoutjour=lookup_widget(button, "AZspinbuttonajoutjour");
AZspinbuttonajoutmois=lookup_widget(button, "AZspinbuttonajoutmois");
AZspinbuttonajoutannee=lookup_widget(button, "AZspinbuttonajoutannee");
AZcomboboxajouttype=lookup_widget(button, "AZcomboboxajouttype");
AZentryajoutid=lookup_widget(button,"AZentryajoutid");
AZentryajoutmrq=lookup_widget(button,"AZentryajoutmrq");
AZentryajoutvaleur=lookup_widget(button,"AZentryajoutvaleur");
sortiea=lookup_widget(button, "AZlabelmsgsucc");

strcpy(c.identifiant,gtk_entry_get_text(GTK_ENTRY(AZentryajoutid)));
strcpy(c.marque,gtk_entry_get_text(GTK_ENTRY(AZentryajoutmrq)));
strcpy(c.valeur,gtk_entry_get_text(GTK_ENTRY(AZentryajoutvaleur)));
c.date.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(AZspinbuttonajoutjour));
c.date.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(AZspinbuttonajoutmois));
c.date.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(AZspinbuttonajoutannee));

strcpy(Type,gtk_combo_box_get_active_text(GTK_COMBO_BOX(AZcomboboxajouttype)));
strcpy(c.type,Type);
ajout(c);
gtk_label_set_text(GTK_LABEL(sortiea),"Ajout effectué avec succès!");
}


void
on_AZbuttonconfirmermodif_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
CAPTEURS c;char Type[30];
GtkWidget *AZcomboboxmodiftype;
GtkWidget *AZentrymodifid;
GtkWidget *AZentrymodifmrq;
GtkWidget *AZspinbuttonmodifjour;
GtkWidget *AZspinbuttonmodifmois;
GtkWidget *AZspinbuttonmodifannee;
GtkWidget *AZentrymodifvaleur;
GtkWidget *sortiem;    
	
AZspinbuttonmodifjour=lookup_widget(button, "AZspinbuttonmodifjour");
AZspinbuttonmodifmois=lookup_widget(button, "AZspinbuttonmodifmois");
AZspinbuttonmodifannee=lookup_widget(button, "AZspinbuttonmodifannee");
AZcomboboxmodiftype=lookup_widget(button, "AZcomboboxmodiftype");
AZentrymodifid=lookup_widget(button,"AZentrymodifid");
AZentrymodifmrq=lookup_widget(button,"AZentrymodifmrq");
AZentrymodifvaleur=lookup_widget(button,"AZentrymodifvaleur");
sortiem=lookup_widget(button, "AZlabelmodifreus");

strcpy(c.identifiant,gtk_entry_get_text(GTK_ENTRY(AZentrymodifid)));
strcpy(c.marque,gtk_entry_get_text(GTK_ENTRY(AZentrymodifmrq)));
strcpy(c.valeur,gtk_entry_get_text(GTK_ENTRY(AZentrymodifvaleur)));
c.date.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(AZspinbuttonmodifjour));
c.date.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(AZspinbuttonmodifmois));
c.date.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(AZspinbuttonmodifannee));
strcpy(Type,gtk_combo_box_get_active_text(GTK_COMBO_BOX(AZcomboboxmodiftype)));
strcpy(c.type,Type);
modification(id,c);
gtk_label_set_text(GTK_LABEL(sortiem),"Modification effectuée avec succès!");
}






void
on_AZbutton_stat_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
int t,h;
char chh[30],cht[30],chm[30];
CAPTEURS c;
GtkWidget *windowcapteurs;
GtkWidget *AZwindowstatistiques;
GtkWidget *labelt;
GtkWidget *labelh;
GtkWidget *labelm;
GtkWidget *stattreeview;

windowcapteurs = lookup_widget(button,"windowcapteurs");
gtk_widget_destroy(windowcapteurs);
AZwindowstatistiques = create_AZwindowstatistiques();
gtk_widget_show(AZwindowstatistiques);

t=nombret(c);
h=nombreh(c);

labelt=lookup_widget(AZwindowstatistiques,"labelt");
labelh=lookup_widget(AZwindowstatistiques,"labelh");
//labelm=lookup_widget(AZwindowstatistiques,"labelm");

sprintf(cht,"%d",t);
sprintf(chh,"%d",h);
//strcpy(chm,marque(c));
gtk_label_set_text(labelt,cht);
gtk_label_set_text(labelh,chh);
//gtk_label_set_text(labelm,chm);




}


void
on_AZbutton_retour_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowcapteurs;
GtkWidget *AZwindowstatistiques;

AZwindowstatistiques = lookup_widget(button,"AZwindowstatistiques");
gtk_widget_destroy(AZwindowstatistiques);
windowcapteurs= create_windowcapteurs();
gtk_widget_show(windowcapteurs);
}


void
on_buttonactu_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *AZwindowstatistiques;
GtkWidget *stattreeview;
AZwindowstatistiques=lookup_widget(button,"AZwindowstatistiques");
stattreeview=lookup_widget(AZwindowstatistiques,"stattreeview");
affichagestat(stattreeview);
}

