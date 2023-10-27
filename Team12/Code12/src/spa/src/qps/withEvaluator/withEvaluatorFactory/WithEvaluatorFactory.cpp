#include "WithEvaluatorFactory.h"

#include <utility>

#include "qps/withEvaluator/doubleSynWithEvaluator/DoubleSynWithEvaluator.h"
#include "qps/withEvaluator/noSynWithEvaluator/NoSynWithEvaluator.h"
#include "qps/withEvaluator/singleSynWithEvaluator/SingleSynWithEvaluator.h"

unique_ptr<WithEvaluator> WithEvaluatorFactory::createWithEvaluator(
    AbstractArgument& firstArg, AbstractArgument& secondArg,
    PKBReader& pkbReader) {
  bool isFirstArgSynonym = firstArg.isSynonym();
  bool isSecondArgSynonym = secondArg.isSynonym();

  if (isFirstArgSynonym && isSecondArgSynonym) {
    SynonymArg* synonymArgPtr1 = dynamic_cast<SynonymArg*>(&firstArg);
    SynonymArg* synonymArgPtr2 = dynamic_cast<SynonymArg*>(&secondArg);

    return make_unique<DoubleSynWithEvaluator>(*synonymArgPtr1, *synonymArgPtr2,
                                               pkbReader);
  } else if (!isFirstArgSynonym && !isSecondArgSynonym) {
    return make_unique<NoSynWithEvaluator>(firstArg, secondArg, pkbReader);
  } else if (isFirstArgSynonym) {
    SynonymArg* synonymArgPtr = dynamic_cast<SynonymArg*>(&firstArg);
    return make_unique<SingleSynWithEvaluator>(*synonymArgPtr,
                                               std::move(secondArg), pkbReader);
  } else {
    SynonymArg* synonymArgPtr = dynamic_cast<SynonymArg*>(&secondArg);

    return make_unique<SingleSynWithEvaluator>(*synonymArgPtr, firstArg,
                                               pkbReader);
  }
}
