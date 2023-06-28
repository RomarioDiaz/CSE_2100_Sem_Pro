#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

// Global variables for GTK widgets
GtkWidget *createButton;
GtkWidget *loginButton;
GtkWidget *nameEntry;
GtkWidget *emailEntry;
GtkWidget *passwordEntry;
GtkWidget *verifyEntry;
GtkWidget *resultLabel;

// Callback function for the login button click event
void login_button_clicked(GtkWidget *widget, gpointer data);

// Callback function for the create account button click event
void create_button_clicked(GtkWidget *widget, gpointer data)
{
    // Remove the "Create Account" button from the UI
    gtk_widget_hide(createButton);

    // Create the account input fields
    GtkWidget *nameLabel = gtk_label_new("Enter your name:");
    GtkWidget *emailLabel = gtk_label_new("Enter your email address:");
    GtkWidget *passwordLabel = gtk_label_new("Create a password:");
    GtkWidget *verifyLabel = gtk_label_new("Verify password:");

    nameEntry = gtk_entry_new();
    emailEntry = gtk_entry_new();
    passwordEntry = gtk_entry_new();
    verifyEntry = gtk_entry_new();

    // Create the create button
    GtkWidget *confirmButton = gtk_button_new_with_label("Create");
    g_signal_connect(confirmButton, "clicked", G_CALLBACK(login_button_clicked), NULL);

    // Pack the widgets into a vertical box
    GtkWidget *vbox = GTK_WIDGET(data);
    gtk_box_pack_start(GTK_BOX(vbox), nameLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), nameEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), emailLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), emailEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), passwordLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), passwordEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), verifyLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), verifyEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), confirmButton, FALSE, FALSE, 0);

    // Show all the widgets
    gtk_widget_show_all(vbox);
}

// Callback function for the login button click event
void login_button_clicked(GtkWidget *widget, gpointer data)
{
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(nameEntry));
    const gchar *email = gtk_entry_get_text(GTK_ENTRY(emailEntry));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(passwordEntry));
    const gchar *verifyPassword = gtk_entry_get_text(GTK_ENTRY(verifyEntry));

    // Existing create account logic goes here
    // ...

    // Update the result label
    gchar *resultText = g_strdup_printf("Account created");
    gtk_label_set_text(GTK_LABEL(resultLabel), resultText);
    g_free(resultText);
}

int main(int argc, char *argv[])
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK Integration Example");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    // Create a vertical box to hold the widgets
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create the initial buttons
    loginButton = gtk_button_new_with_label("Login");
    createButton = gtk_button_new_with_label("Create Account");

    // Connect the login button click event to the callback function
    g_signal_connect(loginButton, "clicked", G_CALLBACK(login_button_clicked), NULL);

    // Connect the create account button click event to the callback function
    g_signal_connect(createButton, "clicked", G_CALLBACK(create_button_clicked), vbox);

    // Pack the initial buttons into the vertical box
    gtk_box_pack_start(GTK_BOX(vbox), loginButton, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), createButton, FALSE, FALSE, 0);

    // Create a label to display the result
    resultLabel = gtk_label_new("Result: ");
    gtk_box_pack_start(GTK_BOX(vbox), resultLabel, FALSE, FALSE, 0);

    // Show all the widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();

    return 0;
}
