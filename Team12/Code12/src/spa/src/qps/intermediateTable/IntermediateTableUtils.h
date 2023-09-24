#pragma once

#include "IntermediateTable.h"

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

using std::sort, std::string, std::vector;

vector<string> getSharedColNames(
        IntermediateTable table1,
        IntermediateTable table2);

pair<vector<int>, vector<int>> getSharedColIndexes(
        IntermediateTable table1,
        IntermediateTable table2);

IntermediateTable getCrossProduct(
        IntermediateTable table1,
        IntermediateTable table2);

IntermediateTable getInnerJoin(
        const pair<vector<int>, vector<int>>& sharedColumns,
        IntermediateTable table1,
        IntermediateTable table2);
