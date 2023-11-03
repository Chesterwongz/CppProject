#include "qps/clause/selectClause/ISelectClause.h"

vector<AbstractArgument*> ISelectClause::getAllArguments() {
  vector<AbstractArgument*> argVector;

  for (int i = 0; i < synonymsToSelect.size(); i++) {
    argVector.push_back(synonymsToSelect[i].get());
  }

  return argVector;
}
