#include "WithEvaluatorFactory.h"

unique_ptr<IWithEvaluator> WithEvaluatorFactory::createWithEvaluator(
    unique_ptr<AbstractArgument> firstArg,
    unique_ptr<AbstractArgument> secondArg) {
  
  bool isFirstArgSynonym = firstArg->isSynonym();
  bool isSecondArgSynonym = secondArg->isSynonym();

  if (isFirstArgSynonym && isSecondArgSynonym) {
    // create bothSynWithEvaluator
  } else if (!isFirstArgSynonym && !isSecondArgSynonym){
    // create noSynWithEvaluator
  } else {
    if (firstArg->isSynonym()) {
      // firstArg is the synonym
      unique_ptr<SynonymArg> synonymArg =
          unique_ptr<SynonymArg>(dynamic_cast<SynonymArg*>(firstArg.release()));
      return make_unique<SingleSynWithEvaluator>(move(synonymArg),
                                                 move(secondArg));
    }
    // secondArg is the synonym
    unique_ptr<SynonymArg> synonymArg =
        unique_ptr<SynonymArg>(dynamic_cast<SynonymArg*>(secondArg.release()));

    return make_unique<SingleSynWithEvaluator>(move(synonymArg), move(firstArg));
  }
}
