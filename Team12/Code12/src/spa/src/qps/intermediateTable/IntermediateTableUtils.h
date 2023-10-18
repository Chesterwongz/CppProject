#pragma once

#include <algorithm>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

#include "IntermediateTable.h"

using std::sort, std::string, std::vector;

class IntermediateTableUtils {
 public:
  static vector<string> getSharedColNames(IntermediateTable table1,
                                   IntermediateTable table2);

  static pair<vector<int>, vector<int>> getSharedColIndexes(IntermediateTable table1,
                                                     IntermediateTable table2);

  static IntermediateTable getCrossProduct(IntermediateTable table1,
                                    IntermediateTable table2);

  static IntermediateTable getInnerJoin(
      const pair<vector<int>, vector<int>>& sharedColumns,
      IntermediateTable table1, IntermediateTable table2);

  static vector<string> concatColNames(const vector<string>& vector1,
                                const vector<string>& vector2);

  static TableRowType concatRow(
      const TableRowType& row1,
      const TableRowType& row2);
};
