#pragma once

#include "IntermediateTable.h"

class IntermediateTableFactory {
public:
    /**
     * Builds intermediate table without any WILDCARD columns
     */
    static IntermediateTable buildIntermediateTable(
            const string &firstColName,
            const string &secondColName,
            const vector<pair<string, string>> &data);

    /**
     * Builds intermediate table without any WILDCARD columns
     */
    static IntermediateTable buildIntermediateTable(
            const vector<string> &colNames,
            const vector<vector<string>> &data);

    static IntermediateTable buildEmptyIntermediateTable();

    static IntermediateTable buildWildcardIntermediateTable();
};


