#include "NotDecorator.h"

#include <string>
#include <vector>

#include "qps/intermediateTable/IntermediateTableFactory.h"
#include "qps/intermediateTable/synonymRes/SynonymResFactory.h"
#include "qps/clause/utils/ClauseUtil.h"

IntermediateTable NotDecorator::evaluate(PKBReader& pkb) {
  IntermediateTable wrapeeClauseResult = wrapeeClause->evaluate(pkb);

  vector<const AbstractArgument*> wrapeeClauseArgs =
      wrapeeClause->getAllArguments();

  IntermediateTable minuend = generateMinuend(pkb, wrapeeClauseArgs);

  IntermediateTable notResult = minuend.getDifference(wrapeeClauseResult);

  return notResult;
}

IntermediateTable NotDecorator::generateMinuend(
    PKBReader& pkb, vector<const AbstractArgument*>& wrapeeClauseArgs) {
  IntermediateTable minuend =
      IntermediateTableFactory::buildWildcardIntermediateTable();

  for (auto wrapeeClauseArg : wrapeeClauseArgs) {
    if (!wrapeeClauseArg->isSynonym()) {
      // not synonym, ignore
      continue;
    }

    SynonymArg* wrapeeClauseSynArg = dynamic_cast<SynonymArg*>(
        const_cast<AbstractArgument*>(wrapeeClauseArg));

    string synonymVal = wrapeeClauseSynArg->getValue();

    if (currentTable.isColExists(synonymVal)) {
      // no need to query PKB, treat existing data in current table as
      // 'universe'
      IntermediateTable existingColData =
          currentTable.getSingleColData(synonymVal);
      minuend = minuend.join(existingColData);
    } else {
      // since synonymVal doesnt exist yet, no choice but to query pkb
      vector<std::reference_wrapper<SynonymRes>> synonymResObjsOfEntityType =
          notDecoratorFuncMap[wrapeeClauseSynArg->getEntityType()](pkb);

      IntermediateTable tableOfEntityType =
          IntermediateTableFactory::buildSingleColTable(
              wrapeeClauseSynArg->getValue(), synonymResObjsOfEntityType);
      minuend = minuend.join(tableOfEntityType);
    }
  }

  return minuend;
}

bool NotDecorator::isEquals(const BaseClause& other) {
  const auto* otherDecorator = dynamic_cast<const NotDecorator*>(&other);

  if (!otherDecorator) return false;

  return wrapeeClause->isEquals(*otherDecorator->wrapeeClause);
}

void NotDecorator::setCurrentTable(const IntermediateTable& currentTable) {
  this->currentTable = currentTable;
}

ClauseKey NotDecorator::getKey() {
  return NOT_KEYWORD + wrapeeClause->getKey();
}
