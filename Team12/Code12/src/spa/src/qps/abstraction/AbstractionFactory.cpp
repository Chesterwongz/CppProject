#include "AbstractionFactory.h"

#include <memory>

#include "qps/abstraction/stmtOrProcToVarAbstraction/modifiesAbstraction/ModifiesAbstraction.h"
#include "qps/abstraction/stmtOrProcToVarAbstraction/usesAbstraction/UsesAbstraction.h"
#include "qps/abstraction/stmtToStmtAbstraction/followsAbstraction/FollowsAbstraction.h"
#include "qps/abstraction/stmtToStmtAbstraction/followsStarAbstraction/FollowsStarAbstraction.h"
#include "qps/abstraction/stmtToStmtAbstraction/nextAbstraction/NextAbstraction.h"
#include "qps/abstraction/stmtToStmtAbstraction/nextStarAbstraction/NextStarAbstraction.h"
#include "qps/abstraction/stmtToStmtAbstraction/parentsAbstraction/ParentsAbstraction.h"
#include "qps/abstraction/stmtToStmtAbstraction/parentsStarAbstraction/ParentsStarAbstraction.h"

using std::unique_ptr, std::make_unique;

unique_ptr<BaseAbstraction> AbstractionFactory::createAbstraction(
    AbstractionParams &abstractionParams) {
  switch (abstractionParams.abstraction) {
    case AFFECTS_ENUM:
      // TODO(YQ)
    case CALLS_ENUM:
      // TODO(YQ)
    case CALLS_STAR_ENUM:
      // TODO(YQ)
    case FOLLOWS_ENUM:
      return make_unique<FollowsAbstraction>(abstractionParams);
    case FOLLOWS_STAR_ENUM:
      return make_unique<FollowsStarAbstraction>(abstractionParams);
    case MODIFIES_ENUM:
      return make_unique<ModifiesAbstraction>(abstractionParams);
    case NEXT_ENUM:
      return make_unique<NextAbstraction>(abstractionParams);
    case NEXT_STAR_ENUM:
      return make_unique<NextStarAbstraction>(abstractionParams);
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
