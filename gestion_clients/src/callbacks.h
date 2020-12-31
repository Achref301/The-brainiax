#include <gtk/gtk.h>


void
on_KKbuttonmenuprincipal_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_KKtreeview_row_activated            (GtkTreeView     *KKtreeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_KKbuttonrechercher_clicked          (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_KKbuttonactualiser_clicked          (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_KKbuttonsupprimer_clicked           (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_KKbuttonmodifier_clicked            (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_KKbuttonajouter_clicked             (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_KKbuttonconfirmermodif_clicked      (GtkWidget       *objet,
                                        gpointer         user_data);


void
on_KKtri_clicked                       (GtkButton       *button,
                                        gpointer         user_data);

void
on_topclientref_clicked                (GtkButton       *objet,
                                        gpointer         user_data);
