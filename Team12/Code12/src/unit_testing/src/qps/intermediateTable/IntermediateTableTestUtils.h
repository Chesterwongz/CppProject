#pragma once

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/intermediateTable/synonymRes/SynonymResFactory.h"

bool isVectorSameAsPair(vector<string> vector1,
                        const pair<string, string>& pair1);

bool isVectorsSameAsPairs(vector<vector<string>> vectors,
                          vector<pair<string, string>> pairs);

TableDataType convertToSynonymResCol(const vector<vector<string>>& stringData);

bool isTableDataSame(TableDataType data1, TableDataType data2);
