#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<mysql.h>






typedef struct Program {
    char name[100];
    int quantity;
    char date_of_arrival[20];
    int quantity_exported;
    char customer[100];
    char date_of_export[20];
} Program;

void add_program(Program **inventory, int *size, MYSQL *conn) {
    (*size)++;
    *inventory = (Program *)realloc(*inventory, (*size) * sizeof(Program));
    Program *new_program = &((*inventory)[(*size) - 1]);

    printf("Enter the program name: ");
    scanf("%s", new_program->name);

    printf("Enter the quantity: ");
    scanf("%d", &new_program->quantity);

    printf("Enter the date of arrival: ");
    scanf("%s", new_program->date_of_arrival);
    new_program->quantity_exported = 0;
    strcpy(new_program->customer, "");

    // Insert the program data into the MySQL database
    char query[256];
    sprintf(query, "INSERT INTO inventory (name, quantity, date_of_arrival) VALUES ('%s', %d, '%s')", new_program->name, new_program->quantity, new_program->date_of_arrival);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error inserting program: %s\n", mysql_error(conn));
    }
}


void display_inventory(Program *inventory, int size) {
    if (size == 0) {
        printf("Inventory is empty.\n");
        return;
    }
    printf("-------------------------------------------------------------\n");
    printf("|%-20s|%-20s|%-20s|%-20s|%-20s|\n", "Name", "Quantity", "Date of Arrival", "Quantity Exported", "Customer");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("|%-20s|%-20d|%-20s|%-20d|%-20s|\n", inventory[i].name, inventory[i].quantity, inventory[i].date_of_arrival, inventory[i].quantity_exported, inventory[i].customer, inventory[i].date_of_export);
    }
    printf("-------------------------------------------------------------\n");
}

void export_program(Program *inventory, int size, MYSQL *conn) {
    if (size == 0) {
        printf("Inventory is empty.\n");
        return;
    }

    char program_name[100];
    printf("Enter the program name to export: ");
    scanf("%s", program_name);

    for (int i = 0; i < size; i++) {
        if (strcmp(inventory[i].name, program_name) == 0) {
            printf("Enter the quantity to export: ");
            int quantity;
            scanf("%d", &quantity);
            if (quantity <= inventory[i].quantity) {
                inventory[i].quantity -= quantity;
                inventory[i].quantity_exported += quantity;

                printf("Enter the customer name: ");
                scanf("%s", inventory[i].customer);

                printf("Enter the date of export: ");
                scanf("%s", inventory[i].date_of_export);

                // Update the program data in the MySQL database
                char query[256];
                sprintf(query, "UPDATE inventory SET quantity = %d, customer = '%s', date_of_export = '%s' WHERE name = '%s'", inventory[i].quantity, inventory[i].customer, inventory[i].date_of_export, inventory[i].name);
                if (mysql_query(conn, query)) {
                     fprintf(stderr, "Error updating program: %s\n", mysql_error(conn));
                }
                break;
            } else {
                printf("Quantity exceeds the available quantity.\n");
            }
        }
    }
}
int main() {
    Program *inventory = NULL;
    int size = 0;
    int choice;

    // Initialize the MySQL connection
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "Error connecting to database: %s\n", mysql_error(conn));
        return 1;
    }

    while (1) {
        // ...
    }

    // Close the MySQL connection
    mysql_close(conn);

    return 0;
}