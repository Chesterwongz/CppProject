#include <utility>

#include "WithEvaluatorFactory.h"

#include "qps/withEvaluator/noSynWithEvaluator/NoSynWithEvaluator.h"
#include "qps/withEvaluator/singleSynWithEvaluator/SingleSynWithEvaluator.h"

unique_ptr<WithEvaluator> WithEvaluatorFactory::createWithEvaluator(
    unique_ptr<AbstractArgument> firstArg,
    unique_ptr<AbstractArgument> secondArg, PKBReader& pkbReader) {
  bool isFirstArgSynonym = firstArg->isSynonym();
  bool isSecondArgSynonym = secondArg->isSynonym();

  if (isFirstArgSynonym && isSecondArgSynonym) {
    // create bothSynWithEvaluator
  } else if (!isFirstArgSynonym && !isSecondArgSynonym) {
    return make_unique<NoSynWithEvaluator>(move(firstArg), move(secondArg),
                                           pkbReader);
  } else if (isFirstArgSynonym) {
    unique_ptr<SynonymArg> synonymArg =
        unique_ptr<SynonymArg>(dynamic_cast<SynonymArg*>(firstArg.release()));
    return make_unique<SingleSynWithEvaluator>(move(synonymArg),
                                               move(secondArg), pkbReader);
  } else {
    unique_ptr<SynonymArg> synonymArg =
        unique_ptr<SynonymArg>(dynamic_cast<SynonymArg*>(secondArg.release()));

    return make_unique<SingleSynWithEvaluator>(move(synonymArg), move(firstArg),
                                               pkbReader);
  }
}
