#pragma once

#include <algorithm>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

#include "IntermediateTable.h"

using std::sort, std::string, std::vector;

vector<string> getSharedColNames(IntermediateTable table1,
                                 IntermediateTable table2);

pair<vector<int>, vector<int>> getSharedColIndexes(IntermediateTable table1,
                                                   IntermediateTable table2);

IntermediateTable getCrossProduct(IntermediateTable table1,
                                  IntermediateTable table2);

IntermediateTable getInnerJoin(
    const pair<vector<int>, vector<int>>& sharedColumns,
    IntermediateTable table1, IntermediateTable table2);

vector<string> concatColNames(const vector<string>& vector1,
                              const vector<string>& vector2);

TableRowType concatRow(
    const TableRowType& row1,
    const TableRowType& row2);
