#pragma once

#include <algorithm>
#include <iterator>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "IntermediateTable.h"

using std::sort, std::string, std::vector;

namespace IntermediateTableUtils {
vector<string> getSharedColNames(const IntermediateTable& table1,
                                 const IntermediateTable& table2);

pair<vector<int>, vector<int>> getSharedColIndexes(IntermediateTable table1,
                                                   IntermediateTable table2);

IntermediateTable getCrossProduct(const IntermediateTable& table1,
                                  const IntermediateTable& table2);

IntermediateTable getInnerJoin(
    const pair<vector<int>, vector<int>>& sharedColumns,
    const IntermediateTable& t1, const IntermediateTable& t2);

IntermediateTable getInnerJoinOn(const IntermediateTable& t1,
                                 const IntermediateTable& t2,
                                 const pair<string, AttrRef>& joinColThis,
                                 const pair<string, AttrRef>& joinColOther);

vector<string> getJoinColNames(const vector<string>& vector1,
                               const vector<string>& vector2,
                               unordered_set<size_t> vector2JoinedColIndexes);

vector<string> concatColNames(const vector<string>& vector1,
                              const vector<string>& vector2);

static TableRowType concatRow(const TableRowType& row1,
                              const TableRowType& row2);

const int INVALID_COL_INDEX = -1;
}  // namespace IntermediateTableUtils
