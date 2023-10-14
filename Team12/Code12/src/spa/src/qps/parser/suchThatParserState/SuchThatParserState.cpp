#include "SuchThatParserState.h"

#include "qps/parser/relationshipParserState/procProcParserState/ProcProcParserState.h"
#include "qps/parser/relationshipParserState/stmtStmtParserState/StmtStmtParserState.h"
#include "qps/parser/relationshipParserState/stmtVarParserState/StmtVarParserState.h"

PredictiveMap SuchThatParserState::predictiveMap = {
    {PQL_SUCH_TOKEN, {PQL_THAT_TOKEN}},
    {PQL_THAT_TOKEN,
     {PQL_STMT_STMT_TOKEN, PQL_STMT_VAR_TOKEN, PQL_PROC_PROC_TOKEN}}};

SuchThatParserState::SuchThatParserState(PQLParserContext &parserContext,
                                         PQLTokenType prev)
    : BaseParserState(parserContext, prev) {}

void SuchThatParserState::processNameToken(PQLToken &curr) {
  auto tokenType = PQLParserUtils::getTokenTypeFromKeyword(curr.getValue());
  curr.updateTokenType(tokenType);
}

void SuchThatParserState::handleToken() {
  auto curr = parserContext.eatExpectedToken(prev, predictiveMap);

  while (curr.has_value()) {
    PQLToken token = curr.value();

    switch (token.getType()) {
      case PQL_STMT_STMT_TOKEN:
        parserContext.transitionTo(std::make_unique<StmtStmtParserState>(
            parserContext, std::move(token.getValue()), token.getType()));
        return;
      case PQL_STMT_VAR_TOKEN:
        parserContext.transitionTo(std::make_unique<StmtVarParserState>(
            parserContext, std::move(token.getValue()), token.getType()));
        return;
      case PQL_PROC_PROC_TOKEN:
        parserContext.transitionTo(std::make_unique<ProcProcParserState>(
            parserContext, std::move(token.getValue()), token.getType()));
        return;
      default:
        break;
    }
    this->prev = token.getType();

    curr = parserContext.eatExpectedToken(prev, predictiveMap);
  }
  // should never exit in this parser
  throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCOMPLETE_QUERY);
}
