#pragma once

#include <algorithm>
#include <iterator>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "IntermediateTable.h"

using std::sort, std::string, std::vector;

namespace IntermediateTableUtils {
vector<string> getSharedColNames(const IntermediateTable& table1,
                                 const IntermediateTable& table2);

pair<vector<int>, vector<int>> getSharedColIndexes(
    const IntermediateTable& table1, const IntermediateTable& table2);

IntermediateTable getCrossProduct(const IntermediateTable& table1,
                                  const IntermediateTable& table2);

IntermediateTable getNaturalJoin(
    const pair<vector<int>, vector<int>>& sharedColumnIndexes,
    const IntermediateTable& t1, const IntermediateTable& t2);

IntermediateTable getInnerJoinOn(const IntermediateTable& t1,
                                 const IntermediateTable& t2,
                                 const pair<string, AttrRef>& joinColThis,
                                 const pair<string, AttrRef>& joinColOther);

vector<string> getJoinColNames(const vector<string>& t1Names,
                               const vector<string>& t2Names,
                               const unordered_set<size_t>& t2SharedColIndexes);

static TableRowType concatRow(const TableRowType& row1,
                              const TableRowType& row2);

const int INVALID_COL_INDEX = -1;
}  // namespace IntermediateTableUtils
