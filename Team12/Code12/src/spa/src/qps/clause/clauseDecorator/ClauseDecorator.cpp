#include "ClauseDecorator.h"

#include <vector>


vector<const AbstractArgument*> ClauseDecorator::getAllArguments() {
  return wrapeeClause->getAllArguments();
}
