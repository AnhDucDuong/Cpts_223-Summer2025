#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "HashTable.h"
#include "LinkedList.h"

using namespace std;

struct InventoryItem {
    string uniqId;
    string productName;
    string category;
    string sellingPrice;
    string modelNumber;
    string aboutProduct;
    string productDimensions;
    string shippingWeight;
    string productUrl;
};

HashTable<string, InventoryItem> inventoryById;
HashTable<string, LinkedList<InventoryItem*>*> inventoryByCategory;
vector<InventoryItem*> allocatedItems;

string trimQuotes(const string& str) {
    if (str.size() >= 2 && str.front() == '"' && str.back() == '"') {
        return str.substr(1, str.size() - 2);
    }
    return str;
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");
    return (first == string::npos) ? "" : str.substr(first, last - first + 1);
}

vector<string> splitCSVLine(const string& line) {
    vector<string> tokens;
    string token;
    bool inQuotes = false;

    for (char c : line) {
        if (c == '"') inQuotes = !inQuotes;
        else if (c == ',' && !inQuotes) {
            tokens.push_back(token);
            token.clear();
        } else token += c;
    }
    tokens.push_back(token);
    return tokens;
}

void loadInventoryData() {
    ifstream file("marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data-1.csv");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        vector<string> tokens = splitCSVLine(line);
        if (tokens.size() < 28) continue;

        InventoryItem* item = new InventoryItem;
        allocatedItems.push_back(item);

        item->uniqId = trimQuotes(tokens[0]);
        item->productName = trimQuotes(tokens[1]);
        item->category = trimQuotes(tokens[4].empty() ? "NA" : tokens[4]);
        item->sellingPrice = trimQuotes(tokens[7]);
        item->modelNumber = trimQuotes(tokens[9]);
        item->aboutProduct = trimQuotes(tokens[10]);
        item->productDimensions = trimQuotes(tokens[14]);
        item->shippingWeight = trimQuotes(tokens[13]);
        item->productUrl = trimQuotes(tokens[18]);

        inventoryById.insert(item->uniqId, *item);

        stringstream catStream(item->category);
        string cat;
        while (getline(catStream, cat, '|')) {
            cat = trim(cat);
            if (!cat.empty() && cat[0] == ' ') cat = cat.substr(1);

            LinkedList<InventoryItem*>* listPtr;
            if (inventoryByCategory.get(cat, listPtr)) {
                listPtr->insertFront(item);
            } else {
                listPtr = new LinkedList<InventoryItem*>();
                listPtr->insertFront(item);
                inventoryByCategory.insert(cat, listPtr);
            }
        }
    }
    file.close();
}

void printItemDetails(const InventoryItem& item) {
    cout << "ID: " << item.uniqId << endl;
    cout << "Product Name: " << item.productName << endl;
    cout << "Category: " << item.category << endl;
    cout << "Price: " << item.sellingPrice << endl;
    cout << "Model: " << item.modelNumber << endl;
    cout << "Description: " << item.aboutProduct << endl;
    cout << "Dimensions: " << item.productDimensions << endl;
    cout << "Weight: " << item.shippingWeight << endl;
    cout << "URL: " << item.productUrl << endl;
    cout << "----------------------------------------" << endl;
}

void printHelp() {
    cout << "Supported list of commands:\n";
    cout << " 1. find <inventoryid>\n";
    cout << " 2. listInventory <category_string>\n";
    cout << " 3. :quit\n\n";
}

bool validCommand(const string& line) {
    return line == ":help" ||
           line.rfind("find ", 0) == 0 ||
           line.rfind("listInventory ", 0) == 0;
}

void evalCommand(const string& line) {
    if (line == ":help") printHelp();
    else if (line.rfind("find ", 0) == 0) {
        string id = trim(line.substr(5));
        InventoryItem item;
        if (inventoryById.get(id, item)) printItemDetails(item);
        else cout << "Inventory not found" << endl;
    } else if (line.rfind("listInventory ", 0) == 0) {
        string category = trim(line.substr(14));
        LinkedList<InventoryItem*>* listPtr;
        if (inventoryByCategory.get(category, listPtr)) {
            listPtr->printAll([](InventoryItem* p) {
                cout << p->uniqId << " - " << p->productName << endl;
            });
        } else cout << "Invalid Category" << endl;
    }
}

void bootStrap() {
    cout << "\nWelcome to Amazon Inventory Query System" << endl;
    cout << "Enter :quit to exit. Type :help to list supported commands.\n" << endl;
    loadInventoryData();
    cout << "> ";
}

int main() {
    string line;
    bootStrap();
    while (getline(cin, line) && line != ":quit") {
        if (validCommand(line)) evalCommand(line);
        else cout << "Command not supported. Enter :help for list of supported commands" << endl;
        cout << "> ";
    }
    for (InventoryItem* p : allocatedItems) delete p;
    return 0;
}
