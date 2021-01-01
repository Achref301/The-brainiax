#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include <gtk/gtk.h>
#include "aymen.h"


enum{TYPE,IDENTIFIANT,MARQUE,DATE,VALEUR,COLUMNS};
//------------------------------------------------------********---------------------------------------------------
void affichage(GtkWidget* AZtreeview)
{
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
CAPTEURS c;char Date[100];
store=NULL;
FILE *f;
store=gtk_tree_view_get_model(AZtreeview);
if (store==NULL)
{
renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text",TYPE, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (AZtreeview), column);


renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",IDENTIFIANT, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (AZtreeview), column);

renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Marque", renderer, "text",MARQUE, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (AZtreeview), column);

renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text",DATE, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (AZtreeview), column);

renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Valeur", renderer, "text",VALEUR, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (AZtreeview), column);}

store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
f=fopen("capteurs.bin","rb");
if(f==NULL)
{return;}
else
{f=fopen("capteurs.bin","ab+");
while(fread(&c,sizeof(CAPTEURS),1,f))
{sprintf(Date,"%d/%d/%d",c.date.jour,c.date.mois,c.date.annee);
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,TYPE,c.type,IDENTIFIANT,c.identifiant,MARQUE,c.marque,DATE,Date,VALEUR,c.valeur,-1);
}
fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(AZtreeview),GTK_TREE_MODEL (store));
g_object_unref(store);}}


//-------------------------------------------------------*******-----------------------------------------------------------

void ajout (CAPTEURS c){
FILE*f=NULL; 
f=fopen("capteurs.bin","ab+");
fwrite(&c,sizeof(CAPTEURS),1,f);  
fclose(f);
 
}
//------------------------------------------------------------------------------------------------------------------------

void suppression(char id[30],CAPTEURS c){
FILE*f;
FILE*g;
f=fopen("capteurs.bin","rb+");
g=fopen("tmp.bin","wb+");
if(g!=NULL){
while(fread(&c,sizeof(CAPTEURS),1,f))
{
if (strcmp(c.identifiant,id)!=0){
fwrite(&c,sizeof(CAPTEURS),1,g);

}
}
}fclose(f);
fclose(g);
remove("capteurs.bin");
rename("tmp.bin","capteurs.bin");
}

//------------------------------------------------------------------------------------------------------------------------

void modification(char id[30],CAPTEURS c)
{

	suppression(id,c);
	ajout(c);

}
//------------------------------------------------------------------------------------------------------------------------
void recherche(GtkWidget* AZtreeview)
{
GtkCellRenderer *renderer;
 GtkTreeViewColumn *column;
 GtkTreeIter iter;
 GtkListStore *store;

store=NULL;CAPTEURS c;
 FILE *f2;char Date[100]; 
 store=gtk_tree_view_get_model(AZtreeview);
 if (store==NULL)
{

   renderer=gtk_cell_renderer_text_new();
   column= gtk_tree_view_column_new_with_attributes("Type",renderer, "text",TYPE,NULL);
   gtk_tree_view_append_column(GTK_TREE_VIEW(AZtreeview), column);
 
   renderer=gtk_cell_renderer_text_new();
   column= gtk_tree_view_column_new_with_attributes("Identifiant",renderer, "text",IDENTIFIANT,NULL);
   gtk_tree_view_append_column(GTK_TREE_VIEW(AZtreeview), column);
  
   renderer=gtk_cell_renderer_text_new();
   column= gtk_tree_view_column_new_with_attributes("Marque",renderer, "text",MARQUE,NULL);
   gtk_tree_view_append_column(GTK_TREE_VIEW(AZtreeview), column);
   
   renderer=gtk_cell_renderer_text_new();
   column= gtk_tree_view_column_new_with_attributes("Date",renderer, "text",DATE,NULL);
   gtk_tree_view_append_column(GTK_TREE_VIEW(AZtreeview), column);
   
   renderer=gtk_cell_renderer_text_new();
   column= gtk_tree_view_column_new_with_attributes("Valeur",renderer, "text",VALEUR,NULL);
   gtk_tree_view_append_column(GTK_TREE_VIEW(AZtreeview), column);}
  
store=gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
f2=fopen("recherche.bin", "rb");
if(f2==NULL)
{
 return;
}
else 
{ f2=fopen("recherche.bin", "ab+");
    while(fread(&c,sizeof(CAPTEURS),1,f2))
     {sprintf(Date,"%d/%d/%d",c.date.jour,c.date.mois,c.date.annee);
gtk_list_store_append (store,&iter);
gtk_list_store_set (store,&iter,TYPE,c.type,IDENTIFIANT,c.identifiant,MARQUE,c.marque,DATE,Date,VALEUR,c.valeur, -1);
}
fclose(f2);
gtk_tree_view_set_model (GTK_TREE_VIEW (AZtreeview), GTK_TREE_MODEL (store));
g_object_unref (store);
}
}


//...................................................................................................................................

/*void nombre(int *b,int *v)
{
FILE *f;
ANIMAL a;
f = fopen("animaux.bin", "rb");
while (fread(&a,sizeof(a),1,f))
if(strcmp(a.type,"Brebi")==0)
*b+=1;
else
if(strcmp(a.type,"Veau")==0)
*v+=1;

fclose(f);


}*/ 
//....................................................................................
void nombre(int *t,int *h, CAPTEURS c)
{

float max2=300 ,  min2=10,  max1=45, min1=0;
//float v=(float)(*c.valeur);
FILE *f;
CAPTEURS c
f = fopen("capteurs.bin", "rb");
while (fread(&c,sizeof(c),1,f))
if((strcmp(c.type,"température")==0)&&((atoi(valeur)>=min1) || (atoi(valeur)<=max1)))
*t+=1;
else
if((strcmp(c.type,"humidité")==0)&&(atoi(valeur)<=min2 || atoi(valeur)>=max2))
*h+=1;

fclose(f);


} 
//....................................................................................

/*void
on_button12_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
// capteur temperature
float max2=100 , min2=1,max1=300 , min1=10;
int id ,n=1 ,i, j , a,mo,nt,ct [50];
float val;
char texte [200]="";
GtkWidget *output;
FILE *f; 
f= fopen ("temperature.txt","r");
if (f!=NULL) {
while(fscanf (f,"%d %d %d %d %f",&id,&j,&mo ,&a, &val)!=EOF){
	if ((val<max1 && val>min1)||(val<max2 && val>min2)) {
		i =0;
while ((i <n) && (ct[i]!=id ))
i++;
if (i==n) {ct[i]=id ; n++ ;}} }
sprintf (texte,"il y a : %d capteurs de temperature alarmentes ",n);
output=lookup_widget(button,("label29"));
gtk_label_set_text(GTK_LABEL(output),texte);
fclose (f);
return (n);}
}
void
on_button13_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{ // capteur humidite
float max2=100 , min2=1,max1=300 , min1=10;
int id ,n=1 ,i, j , a,mo,nh,ch [50];
float val;
char texte [200]="";
GtkWidget *output;
FILE *f; 
f= fopen ("humidite.txt","r");
if (f!=NULL) {
while(fscanf (f,"%d %d %d %d %f",&id,&j,&mo ,&a, &val)!=EOF){
		if ((val<max1 && val>min1)||(val<max2 && val>min2)) {
		i =0;
while ((i <n) && (ch[i]!=id ))
i++;
if (i==n) {ch[i]=id ; n++ ;}} }
sprintf (texte,"il y a : %d capteurs de humidité alarmentes ",n);
output=lookup_widget(button,("label30"));
gtk_label_set_text(GTK_LABEL(output),texte);
fclose (f);
return (n);}
}*/

