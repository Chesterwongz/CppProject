#include <utility>
#include <vector>

#include "qps/argument/AbstractArgument.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/patternClause/PatternClause.h"
#include "qps/exceptions/QPSParserError.h"
#include "qps/parser/BaseParserState.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/parser/clauseTransitionParserState/ClauseTransitionParserState.h"
#include "qps/parser/patternParserState/expressionParser/ExpressionValidator.h"

class IfPatternParserState : public BaseParserState {
 private:
  static constexpr int expectedNumberOfArgs = 3;
  unique_ptr<SynonymArg> synIf;
  static PredictiveMap predictiveMap;
  vector<unique_ptr<AbstractArgument>> patternArg;
  int nonFirstArgWildcardCount;
  void processSynonymToken(PQLToken& curr);
  bool checkSafeExit();
  void checkIsValidIdent(const string& ref) const;

 public:
  explicit IfPatternParserState(PQLParserContext& parserContext,
                                PQLTokenType prev,
                                unique_ptr<SynonymArg> synIf);
  void handleToken() override;
  ~IfPatternParserState() override = default;
};
