#include "AbstractionFactory.h"

#include <memory>

#include "qps/abstraction/followsAbstraction/FollowsAbstraction.h"
#include "qps/abstraction/modifiesAbstraction/ModifiesAbstraction.h"
#include "qps/abstraction/parentsAbstraction/ParentsAbstraction.h"
#include "qps/abstraction/usesAbstraction/UsesAbstraction.h"
#include "qps/abstraction/followsStarAbstraction/FollowsStarAbstraction.h"
#include "qps/abstraction/parentsStarAbstraction/ParentsStarAbstraction.h"

using std::unique_ptr, std::make_unique;

unique_ptr<BaseAbstraction> AbstractionFactory::createAbstraction(
    AbstractionParams &abstractionParams) {
  switch (abstractionParams.abstraction) {
    case FOLLOWS_ENUM:
      return make_unique<FollowsAbstraction>(abstractionParams);
    case FOLLOWS_STAR_ENUM:
      return make_unique<FollowsStarAbstraction>(abstractionParams);
    case MODIFIES_ENUM:
      return make_unique<ModifiesAbstraction>(abstractionParams);
    case PARENTS_ENUM:
      return make_unique<ParentsAbstraction>(abstractionParams);
    case PARENTS_STAR_ENUM:
      return make_unique<ParentsStarAbstraction>(abstractionParams);
    case USES_ENUM:
      return make_unique<UsesAbstraction>(abstractionParams);
  }
  throw QPSInvalidAbstractionException(
      QPS_INVALID_ABSTRACTION_ERR_UNKNOWN_ABSTRACTION);
}
