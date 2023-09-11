#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include <string>
#include <stdexcept>

class Storage {
public:
    // Constructor to initialize the table
    Storage();

    // Method to insert a row into the table
    void insertRow(int col1, const std::string& col2);

    // Method to retrieve the second column value based on the first column value
    std::string getSecondColumnByFirstColumn(int col1);

    // Method to calculate the number of rows in the table
    size_t getRowCount();

private:
    std::vector<std::pair<int, std::string>> data;
};

#endif // STORAGE_H