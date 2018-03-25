#include <nc/chart.h>
#include <gtk/gtk.h>
static GHashTable* windows;

chart*
chart_new() {

}

cwindow*
chart_show(char* name, chart* c) {
  cwindow* self = NULL;
  if(g_hash_table_contains(windows,name)) {
    self = g_hash_table_lookup(windows,name);
  } else {
    self = cwindow_new();
    g_hash_table_insert(windows,(gpointer)name,self);
    //g_signal_connect(self,"delete-event",G_CALLBACK(gtk_widget_hide_on_delete),NULL);
    g_signal_connect(self,"destroy",G_CALLBACK(gtk_main_quit),NULL);
  }

  cwindow_set(self,c);
  gtk_widget_show_all(GTK_WIDGET(self));
  gtk_main();
  return self;
}
