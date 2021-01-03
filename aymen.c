#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include <gtk/gtk.h>
#include "aymen.h"


enum{TYPE,IDENTIFIANT,MARQUE,DATE,VALEUR,COLUMNS};
enum{TYPE1,IDENTIFIANT1,MARQUE1,VALEUR1,COLUMNS1};
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


//....................................................................................
int nombret(CAPTEURS c)
{
int t=0;
float max1=45, min1=0;
FILE *f;
f = fopen("capteurs.bin", "rb");
while (fread(&c,sizeof(c),1,f)){
if   ((strcmp(c.type,"temperature")==0)&&((atoi(c.valeur)<min1) || (atoi(c.valeur)>max1)))
t=t+1;


}fclose(f);

return t;
} 
//....................................................................................
int nombreh(CAPTEURS c)
{
int h=0;
float max2=300 ,  min2=10;
FILE *f;
f = fopen("capteurs.bin", "rb");
while (fread(&c,sizeof(c),1,f)){

if   ((strcmp(c.type,"humidite")==0)&&((atoi(c.valeur)<min2) || (atoi(c.valeur)>max2)))
h=h+1;
}
fclose(f);

return h;
} 
//....................................................................................
/*char marque(CAPTEURS c)
{
char marq[30];
int k,i,j=0,n=0,s=0;

float max=300 ,  min=10;

FILE *f;
f=fopen("capteurs.bin","rb");
while(fread(&c,sizeof(c),1,f)!=0){
	n++;}
fclose(f);
//--------------------
int t[n];
 m[n];
m[0]="";
f = fopen("capteurs.bin", "rb");
while (fread(&c,sizeof(c),1,f)){
	if(j<n){
                 strcpy(m[j],c.valeur);
	         if(atoi(c.valeur)<min || atoi(c.valeur)>max)
		 {t[j]=1;}
	         else {t[j]=0;}
                 j++;
			}}	
fclose(f); 
//suppression des marques dupliquées et somme des capteurs de chaque marque

   for (i=0;i<n;i++) {
      for (j=i+1;j<n;) {
         if (strcmp(m[j],m[i])==0) {t[i]=t[i]+t[i+1];
            for (k=j;k<n;k++) {
               strcpy(m[k],m[k+1]);
	       t[k]=t[k+1];
            }
            n--;
         } else
            j++;
      }
   }
//Determination de la marque
        strcpy(marq,m[0]);
	max=t[0];
    for(i=1;i<n;i++)
    {
       if(max<t[i])
          { max=t[i];
	   strcpy(marque,m[i]);;}
    }
	return marq;

*/	
//....................................................................................


void affichagestat(GtkWidget* stattreeview)
{
float max1=45, min1=0,max2=300 ,  min2=10;
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
CAPTEURS c;char Date[100];
store=NULL;
FILE *f;
store=gtk_tree_view_get_model(stattreeview);
if (store==NULL)
{
renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text",TYPE1, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (stattreeview), column);


renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",IDENTIFIANT1, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (stattreeview), column);

renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("Marque", renderer, "text",MARQUE1, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (stattreeview), column);

renderer=gtk_cell_renderer_text_new();
   column= gtk_tree_view_column_new_with_attributes("Valeur",renderer, "text",VALEUR1,NULL);
   gtk_tree_view_append_column(GTK_TREE_VIEW(stattreeview), column);}

store=gtk_list_store_new(COLUMNS1,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
f=fopen("capteurs.bin","rb");
if(f==NULL)
{return;}
else
{f=fopen("capteurs.bin","ab+");
while(fread(&c,sizeof(CAPTEURS),1,f))
{
if( ((strcmp(c.type,"temperature")==0)&&((atoi(c.valeur)<min1) || (atoi(c.valeur)>max1)))||((strcmp(c.type,"humidite")==0)&&((atoi(c.valeur)<min2) || (atoi(c.valeur)>max2))) ){
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,TYPE1,c.type,IDENTIFIANT1,c.identifiant,MARQUE1,c.marque,VALEUR1,c.valeur,-1);
}
}
fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(stattreeview),GTK_TREE_MODEL (store));
g_object_unref(store);}}


