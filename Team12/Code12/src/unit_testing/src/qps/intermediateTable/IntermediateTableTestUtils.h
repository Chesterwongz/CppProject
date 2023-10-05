#pragma once

#include <string>
#include <utility>
#include <vector>

#include "qps/intermediateTable/IntermediateTable.h"

bool isVectorSameAsPair(vector<string> vector1,
                        const pair<string, string>& pair1);

bool isVectorsSameAsPairs(vector<vector<string>> vectors,
                          vector<pair<string, string>> pairs);
