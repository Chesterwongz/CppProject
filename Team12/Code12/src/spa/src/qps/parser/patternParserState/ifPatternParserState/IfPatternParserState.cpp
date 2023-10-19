#include "IfPatternParserState.h"

PredictiveMap IfPatternParserState::predictiveMap = {
    {PQL_IF_PATTERN_TOKEN, {PQL_OPEN_BRACKET_TOKEN}},
    {PQL_OPEN_BRACKET_TOKEN,
     {PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN, PQL_LITERAL_REF_TOKEN}},
    {PQL_SYNONYM_TOKEN, {PQL_COMMA_TOKEN}},
    {PQL_LITERAL_REF_TOKEN, {PQL_COMMA_TOKEN}},
    {PQL_WILDCARD_TOKEN, {PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_COMMA_TOKEN, {PQL_WILDCARD_TOKEN}},
};

IfPatternParserState::IfPatternParserState(PQLParserContext &parserContext,
                                           PQLTokenType prev,
                                           unique_ptr<SynonymArg> synIf)
    : BaseParserState(parserContext, prev), synIf(std::move(synIf)) {}

void IfPatternParserState::processSynonymToken(PQLToken &curr) {
  string synType = parserContext.getValidSynonymType(curr.getValue());

  if (patternArg.size() != FIRST_ARG) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT);
  }

  if (synType == VARIABLE_ENTITY) {
    patternArg.push_back(std::make_unique<SynonymArg>(curr.getValue()));
  } else {
    throw QPSSemanticError(QPS_SEMANTIC_ERR_NOT_VAR_SYN);
  }
}

bool IfPatternParserState::checkSafeExit() {
  assert(synIf);
  if (patternArg.size() != expectedNumberOfArgs ||
      nonFirstArgWildcardCount != expectedNonFirstArgWildcardCount) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT);
  }
  return true;
}

void IfPatternParserState::handleToken() {
  auto curr = parserContext.eatExpectedToken(prev, predictiveMap);

  while (curr.has_value()) {
    PQLToken token = curr.value();

    switch (token.getType()) {
      case PQL_SYNONYM_TOKEN:
        processSynonymToken(token);
        break;
      case PQL_CLOSE_BRACKET_TOKEN:
        checkSafeExit();
        parserContext.addClause(std::make_unique<IfPatternClause>(
            std::move(synIf), std::move(patternArg[0])));
        ClauseTransitionParserState::setClauseTransitionState(parserContext);
        return;
      case PQL_WILDCARD_TOKEN:
        if (patternArg.size() == FIRST_ARG) {
          patternArg.push_back(std::make_unique<Wildcard>());
        } else {
          nonFirstArgWildcardCount++;
        }
        break;
      case PQL_LITERAL_REF_TOKEN:
        patternArg.push_back(std::make_unique<Ident>(token.getValue()));
        break;
      default:
        break;
    }
    this->prev = token.getType();

    curr = parserContext.eatExpectedToken(prev, predictiveMap);
  }
  throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCOMPLETE_QUERY);
}
