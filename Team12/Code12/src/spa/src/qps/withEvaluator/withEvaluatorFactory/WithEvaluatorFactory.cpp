#include "WithEvaluatorFactory.h"

#include <utility>

#include "qps/withEvaluator/doubleSynWithEvaluator/DoubleSynWithEvaluator.h"
#include "qps/withEvaluator/noSynWithEvaluator/NoSynWithEvaluator.h"
#include "qps/withEvaluator/singleSynWithEvaluator/SingleSynWithEvaluator.h"

unique_ptr<WithEvaluator> WithEvaluatorFactory::createWithEvaluator(
    unique_ptr<AbstractArgument> firstArg,
    unique_ptr<AbstractArgument> secondArg, PKBReader& pkbReader) {
  bool isFirstArgSynonym = firstArg->isSynonym();
  bool isSecondArgSynonym = secondArg->isSynonym();

  if (isFirstArgSynonym && isSecondArgSynonym) {
    unique_ptr<SynonymArg> synonymArg1 =
        unique_ptr<SynonymArg>(dynamic_cast<SynonymArg*>(firstArg.release()));
    unique_ptr<SynonymArg> synonymArg2 =
        unique_ptr<SynonymArg>(dynamic_cast<SynonymArg*>(secondArg.release()));

    return make_unique<DoubleSynWithEvaluator>(
        std::move(synonymArg1), std::move(synonymArg2), pkbReader);
  } else if (!isFirstArgSynonym && !isSecondArgSynonym) {
    return make_unique<NoSynWithEvaluator>(std::move(firstArg),
                                           std::move(secondArg), pkbReader);
  } else if (isFirstArgSynonym) {
    unique_ptr<SynonymArg> synonymArg =
        unique_ptr<SynonymArg>(dynamic_cast<SynonymArg*>(firstArg.release()));
    return make_unique<SingleSynWithEvaluator>(std::move(synonymArg),
                                               std::move(secondArg), pkbReader);
  } else {
    unique_ptr<SynonymArg> synonymArg =
        unique_ptr<SynonymArg>(dynamic_cast<SynonymArg*>(secondArg.release()));

    return make_unique<SingleSynWithEvaluator>(std::move(synonymArg),
                                               std::move(firstArg), pkbReader);
  }
}
