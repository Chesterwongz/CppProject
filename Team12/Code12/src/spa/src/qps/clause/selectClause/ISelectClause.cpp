#include "qps/clause/selectClause/ISelectClause.h"

vector<unique_ptr<AbstractArgument>> ISelectClause::getAllArguments() {
  vector<unique_ptr<AbstractArgument>> argVector;

  for (int i = 0; i < synonymsToSelect.size(); i++) {
    argVector.push_back(synonymsToSelect[i]->clone());
  }

  return argVector;
}
