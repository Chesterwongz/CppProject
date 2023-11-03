#include "ClauseDecorator.h"

#include <vector>


vector<AbstractArgument*> ClauseDecorator::getAllArguments() {
  return wrapeeClause->getAllArguments();
}
