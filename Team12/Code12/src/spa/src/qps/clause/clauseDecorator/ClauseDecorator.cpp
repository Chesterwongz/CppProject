#include "ClauseDecorator.h"

#include <vector>


vector<unique_ptr<AbstractArgument>> ClauseDecorator::getAllArguments() {
  return wrapeeClause->getAllArguments();
}
