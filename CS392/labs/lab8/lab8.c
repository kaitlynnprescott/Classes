#include <gtk/gtk.h>
#include <stdlib.h>

int flip()
{
	int i = rand() % 2;
	if (i == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/* This callback quits the program */
static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    gtk_main_quit ();
    return FALSE;
}

/* Our callback.
 * The data passed to this function is printed to stdout */
static void callback( GtkWidget *widget,
                      gpointer   data )
{
    g_print ("Hello again - %s was pressed\n", (char *) data);
}

int main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *table;

	gtk_init(&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Flip Coin");
	g_signal_connect(window, "delete_event", G_CALLBACK(delete_event), NULL);
	gtk_container_set_boarder_width(GTK_CONTAINER(window), 20);

	table = gtk_table_new(2, 2, TRUE);
	gtk_conatiner_add(GTK_CONTAINER(window), table);

	button = gtk_button_new_with_label("Flip");
	g_signal_connect(button, "clicked", G_CALLBACK(callback), (gpointer) "Flip");

	gtk_table_attach_defaults(GTK_TABLE(table), button, 1, 1, 0, 1);
	gtk_widget_show(button);


	button - gtk_button_new_with_label("Quit");
	g_signal_connect(button, "clicked", G_CALLBACK(delete_event), NULL);
	gtk_table_attach_defaults(GTK_TABLE(table), button, 0, 2, 1, 2);
	gtk_widget_show(button);

	gtk_widget_show(table);
	gtk_widget_show(window);

	gtk_main();
	return 0;
}