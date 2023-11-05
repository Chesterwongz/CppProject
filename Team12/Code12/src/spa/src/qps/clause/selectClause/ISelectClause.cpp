#include "qps/clause/selectClause/ISelectClause.h"

vector<const AbstractArgument*> ISelectClause::getAllArguments() {
  vector<const AbstractArgument*> argVector;

  for (int i = 0; i < synonymsToSelect.size(); i++) {
    argVector.push_back(synonymsToSelect[i].get());
  }

  return argVector;
}
