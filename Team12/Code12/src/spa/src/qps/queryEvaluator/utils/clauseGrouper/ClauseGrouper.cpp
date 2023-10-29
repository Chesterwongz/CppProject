#include "ClauseGrouper.h"

ClauseGrouper::ClauseGrouper(ClauseUtil::ClauseList& clauses)
    : clauses(clauses) {
  for (unique_ptr<Clause>& clause : clauses) {
    set<string> synonyms = clause->getClauseSynonyms();
    for (const string& syn : synonyms) {
      // each synonym's parent is itself
      this->parentMap[syn] = syn;
      // each clause's tree only contains itself (rank = 0)
      this->rankMap[syn] = ClauseGrouper::INITIAL_RANK;
    }
  }
}

ClauseGroupQueue ClauseGrouper::groupClauses() {
  for (const unique_ptr<Clause>& clause : this->clauses) {
    set<string> synonyms = clause->getClauseSynonyms();
    if (synonyms.empty()) {
      continue;
    }
    // union all synonyms in a clause to the first synonym
    for (auto it = next(synonyms.begin()); it != synonyms.end(); it++) {
      this->unionSynonym(*(synonyms.begin()), *it);
    }
  }

  ClauseGroupQueue res {};
  // maps root synonym to the clauseRefList of clauses in group
  unordered_map<string, ClauseUtil::ClauseRefList> groupMap {};
  for (unique_ptr<Clause>& clause : this->clauses) {
    set<string> synonyms = clause->getClauseSynonyms();
    // if no synonyms in clause, clause belongs in its own group
    if (synonyms.empty()) {
      // create a single group with clause and add to res queue
      res.addClauseGroup(ClauseGroup(clause));
      continue;
    }
    // find the root that the clause belongs to and add
    // it to the clauseRefList the root maps to
    string root = this->findSynonymParent(*(synonyms.begin()));
    if (groupMap.find(root) == groupMap.end()) {
      groupMap[root] = {};
    }
    groupMap[root].emplace_back(clause);
  }

  // for each <root, clauseRefList> pair, create a group and add to res queue
  for (auto& [root, clausesInGroup] : groupMap) {
    res.addClauseGroup(ClauseGroup(clausesInGroup));
  }

  return res;
}

ClauseGroupQueue ClauseGrouper::groupClauses(ClauseUtil::ClauseList& clauses) {
  ClauseGrouper grouper(clauses);
  return grouper.groupClauses();
}

void ClauseGrouper::unionSynonym(const string& syn1, const string& syn2) {
  string syn1Root = findSynonymParent(syn1);
  string syn2Root = findSynonymParent(syn2);

  if (syn1Root == syn2Root) {
    return;
  }

  if (this->rankMap.at(syn1Root) > this->rankMap.at(syn2Root)) {
    this->parentMap[syn2Root] = syn1Root;
  } else if (this->rankMap.at(syn2Root) > this->rankMap.at(syn1Root)) {
    this->parentMap[syn1Root] = syn2Root;
  } else {
    this->parentMap[syn1Root] = syn2Root;
    this->rankMap[syn2Root] += ClauseGrouper::RANK_INCREMENT;
  }
}

string ClauseGrouper::findSynonymParent(const string& syn) {
  string currNode = syn;
  while (this->parentMap.at(currNode) != currNode) {
    string parent = this->parentMap.at(currNode);
    string grandparent = this->parentMap.at(parent);
    // if curr is not root, set curr's parent
    // as grandparent
    this->parentMap[currNode] = grandparent;
    currNode = grandparent;
  }
  return currNode;
}
