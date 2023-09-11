#include "Storage.h"

// Constructor to initialize the table
Storage::Storage() {}

// Method to insert a row into the table
void Storage::insertRow(int col1, const std::string& col2) {
    data.push_back(std::make_pair(col1, col2));
}

// Method to retrieve the second column value based on the first column value
std::string Storage::getSecondColumnByFirstColumn(int col1) {
    for (const auto& row : data) {
        if (row.first == col1) {
            return row.second;
        }
    }
    throw std::runtime_error("Row not found");
}

// Method to calculate the number of rows in the table
size_t Storage::getRowCount() {
    return data.size();
}
