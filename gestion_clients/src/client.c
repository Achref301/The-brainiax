#include <stdlib.h>
#include <stdio.h>
#include<string.h>

#include "client.h"


enum{NP,IDENTIFIANT,SEXE,DATE,VALEUR,COLUMNS};
//------------------------------------------------------********---------------------------------------------------
void affichage(GtkWidget* KKtreeview)
{
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
CLIENT c;char Date[100];
store=NULL;
FILE *f;
store=gtk_tree_view_get_model(KKtreeview);
if (store==NULL)
{
renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Nom et Prenom", renderer, "text",NP, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (KKtreeview), column);


renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",IDENTIFIANT, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (KKtreeview), column);

renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Sexe", renderer, "text",SEXE, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (KKtreeview), column);

renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text",DATE, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (KKtreeview), column);

renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Valeur des achats", renderer, "text",VALEUR, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (KKtreeview), column);}

store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
f=fopen("clients.bin","rb");
if(f==NULL)
{return;}
else
{f=fopen("clients.bin","ab+");
while(fread(&c,sizeof(CLIENT),1,f))
{sprintf(Date,"%d/%d/%d",c.date.jour,c.date.mois,c.date.annee);
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,NP,c.np,IDENTIFIANT,c.identifiant,SEXE,c.sexe,DATE,Date,VALEUR,c.valeur,-1);
}
fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(KKtreeview),GTK_TREE_MODEL (store));
g_object_unref(store);}}


//-------------------------------------------------------*******-----------------------------------------------------------

void ajout (CLIENT c){
FILE*f=NULL; 
f=fopen("clients.bin","ab+");
fwrite(&c,sizeof(CLIENT),1,f);  
fclose(f);
 
}
//------------------------------------------------------------------------------------------------------------------------

void suppression(char id[30],CLIENT c){
FILE*f;
FILE*g;
f=fopen("clients.bin","rb+");
g=fopen("tmp.bin","wb+");
if(g!=NULL){
while(fread(&c,sizeof(CLIENT),1,f))
{
if (strcmp(c.identifiant,id)!=0){
fwrite(&c,sizeof(CLIENT),1,g);

}
}
}fclose(f);
fclose(g);
remove("clients.bin");
rename("tmp.bin","clients.bin");
}

//------------------------------------------------------------------------------------------------------------------------

void modification(char id[30],CLIENT c)
{

	suppression(id,c);
	ajout(c);

}
//------------------------------------------------------------------------------------------------------------------------
void recherche(GtkWidget* KKtreeview)
{
GtkCellRenderer *renderer;
 GtkTreeViewColumn *column;
 GtkTreeIter iter;
 GtkListStore *store;

store=NULL;CLIENT c;
 FILE *f2;char Date[100]; 
 store=gtk_tree_view_get_model(KKtreeview);
 if (store==NULL)
{
renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Nom et Prenom", renderer, "text",NP, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (KKtreeview), column);


renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",IDENTIFIANT, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (KKtreeview), column);

renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Sexe", renderer, "text",SEXE, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (KKtreeview), column);

renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text",DATE, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (KKtreeview), column);

renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Valeur des achats", renderer, "text",VALEUR, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (KKtreeview), column);}
  
store=gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
f2=fopen("recherche.bin", "rb");
if(f2==NULL)
{
 return;
}
else 
{ f2=fopen("recherche.bin", "ab+");
    while(fread(&c,sizeof(CLIENT),1,f2))
     {sprintf(Date,"%d/%d/%d",c.date.jour,c.date.mois,c.date.annee);
gtk_list_store_append (store,&iter);
gtk_list_store_set(store,&iter,NP,c.np,IDENTIFIANT,c.identifiant,SEXE,c.sexe,DATE,Date,VALEUR,c.valeur,-1);
}
fclose(f2);
gtk_tree_view_set_model (GTK_TREE_VIEW (KKtreeview), GTK_TREE_MODEL (store));
g_object_unref (store);
}
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------
void tri(GtkWidget* KKtreeview)
{
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
CLIENT c;char Date[100];
store=NULL;
FILE *f;
store=gtk_tree_view_get_model(KKtreeview);
if (store==NULL)
{
renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Nom et Prenom", renderer, "text",NP, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (KKtreeview), column);


renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",IDENTIFIANT, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (KKtreeview), column);

renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Sexe", renderer, "text",SEXE, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (KKtreeview), column);

renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text",DATE, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (KKtreeview), column);

renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Valeur des achats", renderer, "text",VALEUR, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (KKtreeview), column);}

store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
f=fopen("tri.bin","rb");
if(f==NULL)
{return;}
else
{f=fopen("tri.bin","ab+");
while(fread(&c,sizeof(CLIENT),1,f))
{sprintf(Date,"%d/%d/%d",c.date.jour,c.date.mois,c.date.annee);
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,NP,c.np,IDENTIFIANT,c.identifiant,SEXE,c.sexe,DATE,Date,VALEUR,c.valeur,-1);
}
fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(KKtreeview),GTK_TREE_MODEL (store));
g_object_unref(store);}}
*/

