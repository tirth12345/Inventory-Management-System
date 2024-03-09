import mysql.connector

# Create a connection to the database
cnx = mysql.connector.connect(user='root', password='tirth2005', host='localhost', database='inventory_db')

# Create a cursor object
cursor = cnx.cursor()

# Function to add a new product to the inventory
def add_product(name, quantity, arrival_date, delivered_by):
    add_product_query = """
    INSERT INTO products (name, quantity, arrival_date, delivered_by)
    VALUES (%s, %s, %s, %s)
    """
    cursor.execute(add_product_query, (name, quantity, arrival_date, delivered_by))
    cnx.commit()

# Function to export a product
def export_product(product_id, export_date, export_quantity, exported_to):
    export_product_query = """
    UPDATE products
    SET quantity = quantity - %s, date_of_export = %s, client_exported = %s
    WHERE id = %s
    """
    cursor.execute(export_product_query, (export_quantity, export_date, exported_to, product_id))
    cnx.commit()

# Example usage
add_product('Product A', 10, '2024-03-08', 'Client X')
export_product(1, '2024-03-09', 5, 'Client Y')

# Close the cursor and connection
cursor.close()
cnx.close()


