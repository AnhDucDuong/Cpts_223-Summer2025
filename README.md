 Amazon Inventory Query System

 Description

This is a command-line REPL (Read-Eval-Print Loop) application built for CptS 223 Programming Assignment 4. It allows users to search and filter Amazon product data using two main commands:

- find <inventoryid> – Find and print details of a product by its unique ID.
- listInventory <category_string> – List all products that belong to a specific category.

 Dataset

- The CSV file used: marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data-1.csv
- Source: [Kaggle – Amazon Product Dataset 2020](https://www.kaggle.com/datasets/promptcloud/amazon-product-dataset-2020)

 Notes:
- A product can belong to multiple categories (separated by |).
- Missing categories are stored as "NA".
- Extra quotes in fields are stripped during parsing.

 Commands Supported

- :help – Show list of supported commands.
- find <inventoryid> – Print all details of a product.
- listInventory <category_string> – List product IDs and names for a category.
- :quit – Exit the program.

 Data Structures Used

- HashTable – Custom hash table for mapping:
  - uniqId → InventoryItem
  - category → LinkedList<InventoryItem>
- LinkedList – Custom singly linked list to store product pointers by category.

 Why These Structures?
- Hash table enables O(1) average case lookup for product ID and category.
- Linked list supports fast insertions per category without STL.





