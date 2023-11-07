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

void ClauseGroup::evaluateClauseToTables(PKBReader& pkb) {
  for (const unique_ptr<Clause>& clause : this->clauseRefList) {
    string clauseKey = clause->getKey();
    if (this->evaluatedClauses.find(clauseKey) !=
        this->evaluatedClauses.end()) {
      // ignore clauses we evaluated before
      continue;
    }
    IntermediateTable clauseRes = clause->evaluate(pkb);
    bool isEmpty = clauseRes.isTableEmptyAndNotWildcard();
    this->tableQueue.addTable(std::move(clauseRes));
    if (isEmpty) {
      // stop evaluation if we get empty table
      break;
    }
    this->evaluatedClauses.insert(clauseKey);
  }
}

IntermediateTable ClauseGroup::evaluate(PKBReader& pkb,
                                        set<string>& selectedSynonyms) {
  this->evaluateClauseToTables(pkb);
  IntermediateTable joinResult = this->tableQueue.getJoinResult();

  bool hasSelectedSynonyms = this->hasSelectedSynonyms(selectedSynonyms);
  if (hasSelectedSynonyms) {
    return joinResult;
  } else {
    // if ClauseGroup does not involve selected synonym,
    // only need to return Wildcard or Empty table
    return joinResult.isTableEmptyAndNotWildcard()
               ? joinResult
               : IntermediateTableFactory::buildWildcardIntermediateTable();
  }
}

bool ClauseGroup::hasSelectedSynonyms(set<string>& selectedSynonyms) {
  return std::any_of(selectedSynonyms.begin(), selectedSynonyms.end(),
                     [this](const string& syn) {
                       return this->synonymsSet.find(syn) !=
                              this->synonymsSet.end();
                     });
}
