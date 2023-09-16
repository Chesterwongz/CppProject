#pragma once

#include <utility>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using std::pair, std::unordered_map, std::string, std::vector;
class IntermediateTable {
private:
    unordered_map<string, int> colNameToIndexMap = {};
    vector<vector<string>> table;
    int currentColCount = 0;
    vector<string> getCol(int colIndex);
    vector<string> getRow(int rowIndex);
    /**
     * Add an empty column to the table
     * @param colName takes in name of new column
     * @return index of new column
     */
    int createNewCol(const string& colName);

public:
    /**
     * for initialising table from vector of pairs.
     * only can initialise 2 columns.
     * @param data data as vector of pairs
     */
    explicit IntermediateTable(
            const string &firstColName,
            const string &secondColName,
            const vector<pair<string, string>> &data);

    /**
     * for initialising table from vector of vectors
     * @param data data as vector of vectors
     */
    explicit IntermediateTable(
            const vector<string> &colNames,
            const vector<vector<string>> &data);

    /**
     * @return the entire table's data
     */
    vector<vector<string>> getTable();

    /**
     * @param colName
     * @return data in specified column as vector
     */
    vector<string> getSingleCol(const string& colName);

    /**
     * @param colNameVector vector of column names to retrieve
     * @return vector of columns, with each column as a vector
     */
    vector<vector<string>> getCol(const vector<string>& colNameVector);

    /**
     * Join a different intermediateTable into this
     * @param intermediateTable seperate table to be joined into
     *                          this table
     */
    void join(IntermediateTable intermediateTable);
};
