#include "WithEvaluatorFactory.h"

#include "qps/withEvaluator/NoSynWithEvaluator.h"
#include "SingleSynWithEvaluator.h"

unique_ptr<WithEvaluator> WithEvaluatorFactory::createWithEvaluator(
    unique_ptr<AbstractArgument> firstArg,
    unique_ptr<AbstractArgument> secondArg) {
  
  bool isFirstArgSynonym = firstArg->isSynonym();
  bool isSecondArgSynonym = secondArg->isSynonym();

  if (isFirstArgSynonym && isSecondArgSynonym) {
    // create bothSynWithEvaluator
  } else if (!isFirstArgSynonym && !isSecondArgSynonym){
    return make_unique<NoSynWithEvaluator>(move(firstArg), move(secondArg));
  } else if (isFirstArgSynonym) {
    unique_ptr<SynonymArg> synonymArg =
        unique_ptr<SynonymArg>(dynamic_cast<SynonymArg*>(firstArg.release()));
    return make_unique<SingleSynWithEvaluator>(move(synonymArg),
                                               move(secondArg));
  } else {
    unique_ptr<SynonymArg> synonymArg =
        unique_ptr<SynonymArg>(dynamic_cast<SynonymArg*>(secondArg.release()));

    return make_unique<SingleSynWithEvaluator>(move(synonymArg),
                                               move(firstArg));
  }
}
