#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "rapidcsv/rapidcsv.h"

using namespace std;

int main() {
    rapidcsv::Document customerData("customers.csv");
    vector<int> id = customerData.GetColumn<int>("id");
    vector<string> names = customerData.GetColumn<string>("name");
    vector<string> addresses = customerData.GetColumn<string>("address");
    int customerCount = id.size();
    for (int i = 0; i < customerCount; i++) {
        cout << "Customer: " << names[i] << ", " << addresses[i] << endl;
    }

    rapidcsv::Document productData("products.csv");
    vector<int> pro_id = productData.GetColumn<int>("id");
    vector<string> product_names = productData.GetColumn<string>("name");
    vector<int> product_prices = productData.GetColumn<int>("price");
    int productCount = pro_id.size();
    for (int i = 0; i < productCount; i++) {
        cout << "Product: " << product_names[i] << ", " << product_prices[i] << endl;
    }

    rapidcsv::Document orderData("orders.csv");
    vector<int> orderId = orderData.GetColumn<int>("id");
    vector<int> customerId = orderData.GetColumn<int>("customerid");
    vector<int> productId = orderData.GetColumn<int>("productid");
    vector<int> amounts = orderData.GetColumn<int>("amount");
    int orderCount = orderId.size();
    map<int, int> productQuantity;
    for (int i = 0; i < orderCount; i++) {
        int product_id = productId[i];
        int quantity = amounts[i];
        productQuantity[product_id] += quantity;
    }
    cout << "Total amount ordered per product:" << endl;
    for (int i = 0; i < productCount; i++) {
        int p_id = pro_id[i];
        int quantity = productQuantity[p_id];
        string product_name = product_names[i];
        cout << product_name << " amount: " << quantity << endl;
    }
    map<int, int> productRevenue;
    for (int i = 0; i < orderCount; i++) {
        int prod_id = productId[i];
        int quantity = amounts[i];
        int price = product_prices[prod_id - 1];
        productRevenue[prod_id] += quantity * price;
    }

    cout << "Total money spent per product:" << endl;
    for (int i = 0; i < productCount; i++) {
        int p_id = pro_id[i];
        int revenue = productRevenue[p_id];
        string product_name = product_names[i];
        cout << product_name << " gross income: " << revenue << endl;
    }
    map<int, int> customerExpenditure;
    for (int i = 0; i < orderCount; i++) {
        int c_id = customerId[i];
        int quantity = amounts[i];
        int prod_id = productId[i];
        int price = product_prices[prod_id - 1];
        int cost = quantity * price;
        customerExpenditure[c_id] += cost;
    }

    cout << "Total money spent per customer:" << endl;
    for (int i = 0; i < customerCount; i++) {
        int c_id = id[i];
        int expenditure = customerExpenditure[c_id];
        string c_name = names[i];
        cout << c_name << " money spent: " << expenditure << endl;
    }
    int totalMoneySpent = 0;
    for (const auto& revenue : productRevenue) {
        totalMoneySpent += revenue.second;
    }   cout << "Total money spent on all products: " << totalMoneySpent << endl;

    return 0;
}
