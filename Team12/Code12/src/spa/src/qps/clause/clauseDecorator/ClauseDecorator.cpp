#include "ClauseDecorator.h"

vector<unique_ptr<AbstractArgument>> ClauseDecorator::getAllArguments() {
  return wrapeeClause->getAllArguments();
}
