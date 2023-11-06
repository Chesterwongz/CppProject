#include "ClauseGroup.h"

ClauseGroup::ClauseGroup(ClauseUtil::ClauseRefList& clauseList) {
  for (unique_ptr<Clause>& clause : clauseList) {
    for (const string& syn : clause->getClauseSynonyms()) {
      this->synonymsSet.insert(syn);
    }
    this->clauseRefList.emplace_back(clause);
  }
}

ClauseGroup::ClauseGroup(unique_ptr<Clause>& clause) {
  this->clauseRefList.emplace_back(clause);
}

void ClauseGroup::evaluateClauseToTables(PKBReader& pkb,
                                         set<string>& selectedSynonyms) {
  bool hasSelectedSynonyms = this->hasSelectedSynonyms(selectedSynonyms);
  for (const unique_ptr<Clause>& clause : this->clauseRefList) {
    string clauseKey = clause->getKey();
    if (this->evaluatedClauses.find(clauseKey) !=
        this->evaluatedClauses.end()) {
      // ignore clauses we evaluated before
      continue;
    }
    IntermediateTable clauseRes = clause->evaluate(pkb);
    bool isEmpty = clauseRes.isTableEmptyAndNotWildcard();
    if (hasSelectedSynonyms || isEmpty) {
      this->tableQueue.addTable(std::move(clauseRes));
    }
    // if no selected synonyms in group, then we can treat
    // results as wildcard or empty tables
    // since TableQueue is treated as wildcard table if it is empty,
    // we do not need to insert anything if table is wildcard
    if (isEmpty) {
      // stop evaluation if we get empty table
      break;
    }
    this->evaluatedClauses.insert(clauseKey);
  }
}

IntermediateTable ClauseGroup::evaluate(PKBReader& pkb,
                                        set<string>& selectedSynonyms) {
  this->evaluateClauseToTables(pkb, selectedSynonyms);
  return this->tableQueue.getJoinResult();
}

bool ClauseGroup::hasSelectedSynonyms(set<string>& selectedSynonyms) {
  return std::any_of(selectedSynonyms.begin(), selectedSynonyms.end(),
                     [this](const string& syn) {
                       return this->synonymsSet.find(syn) !=
                              this->synonymsSet.end();
                     });
}
