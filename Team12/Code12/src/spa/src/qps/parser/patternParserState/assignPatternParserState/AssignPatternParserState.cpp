#include "AssignPatternParserState.h"

PredictiveMap AssignPatternParserState::predictiveMap = {
    {PQL_ASSIGN_PATTERN_TOKEN, {PQL_OPEN_BRACKET_TOKEN}},
    {PQL_OPEN_BRACKET_TOKEN,
     {PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN, PQL_LITERAL_REF_TOKEN}},
    {PQL_SYNONYM_TOKEN, {PQL_COMMA_TOKEN}},
    {PQL_WILDCARD_TOKEN,
     {PQL_COMMA_TOKEN, PQL_LITERAL_REF_TOKEN, PQL_LITERAL_EXPRESSION_TOKEN,
      PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_LITERAL_REF_TOKEN,
     {PQL_COMMA_TOKEN, PQL_WILDCARD_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_LITERAL_EXPRESSION_TOKEN,
     {PQL_WILDCARD_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_COMMA_TOKEN,
     {PQL_WILDCARD_TOKEN, PQL_LITERAL_REF_TOKEN,
      PQL_LITERAL_EXPRESSION_TOKEN}}};

AssignPatternParserState::AssignPatternParserState(
    PQLParserContext& parserContext, PQLTokenType prev,
    unique_ptr<SynonymArg> synAssign)
    : BaseParserState(parserContext, prev),
      isPartialMatch(false),
      synAssign(std::move(synAssign)),
      secondArgWildcardCount(0) {}

void AssignPatternParserState::processSynonymToken(PQLToken& curr) {
  string synType = parserContext.getValidSynonymType(curr.getValue());

  if (patternArg.size() != FIRST_ARG) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT);
  }

  if (synType == VARIABLE_ENTITY) {
    patternArg.push_back(
        std::move(std::make_unique<SynonymArg>(curr.getValue())));
  } else {
    throw QPSSemanticError(QPS_SEMANTIC_ERR_NOT_VAR_SYN);
  }
}

void AssignPatternParserState::processLastArgument() {
  bool isWildcardMatch = patternArg.size() == SECOND_ARG &&
                         secondArgWildcardCount == WILDCARD_MATCH_COUNT;
  bool isExactMatch = patternArg.size() == expectedNumberOfArgs &&
                      secondArgWildcardCount == EXACT_MATCH_COUNT;
  isPartialMatch = secondArgWildcardCount == PARTIAL_MATCH_COUNT &&
                   patternArg.size() == expectedNumberOfArgs;

  if (isWildcardMatch) {
    patternArg.push_back(std::move(std::make_unique<Wildcard>()));
  } else if (isPartialMatch || isExactMatch) {
    return;
  } else {
    throw QPSSyntaxError(QPS_SYNTAX_ERR_INVALID_PATTERN_MATCH);
  }
}

bool AssignPatternParserState::checkSafeExit() {
  assert(synAssign);
  if (patternArg.size() != expectedNumberOfArgs) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT);
  }
  return true;
}

void AssignPatternParserState::processLiteralRefToken(PQLToken& curr) {
  if (patternArg.size() == SECOND_ARG) {
    curr.updateTokenType(PQL_LITERAL_EXPRESSION_TOKEN);
  }
}

void AssignPatternParserState::checkIsValidExpr(const std::string& ref) {
  if (!ExpressionValidator::isValidExpression(ref)) {
    throw QPSSyntaxError(QPS_SYNTAX_ERR_INVALID_PATTERN_MATCH);
  }
}

// TODO(Hwee): Review and remove redundant logic
void AssignPatternParserState::handleToken() {
  auto curr = parserContext.eatExpectedToken(prev, predictiveMap);

  while (curr.has_value()) {
    PQLToken token = curr.value();
    if (token.getType() == PQL_LITERAL_REF_TOKEN) processLiteralRefToken(token);

    switch (token.getType()) {
      case PQL_SYNONYM_TOKEN:
        processSynonymToken(token);
        break;
      case PQL_CLOSE_BRACKET_TOKEN:
        processLastArgument();
        checkSafeExit();
        parserContext.addClause(std::make_unique<PatternClause>(
            std::move(synAssign), std::move(patternArg), isPartialMatch));
        ClauseTransitionParserState::setClauseTransitionState(parserContext);
        return;
      case PQL_WILDCARD_TOKEN:
        if (patternArg.size() >= SECOND_ARG) {
          secondArgWildcardCount++;
        } else {
          patternArg.push_back(std::make_unique<Wildcard>());
        }
        break;
      case PQL_LITERAL_REF_TOKEN:
        patternArg.push_back(std::make_unique<Ident>(token.getValue()));
        break;
      case PQL_LITERAL_EXPRESSION_TOKEN:
        checkIsValidExpr(token.getValue());
        patternArg.push_back(
            std::move(std::make_unique<PatternExp>(token.getValue())));
        break;
      default:
        break;
    }
    this->prev = token.getType();

    curr = parserContext.eatExpectedToken(prev, predictiveMap);
  }
  throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCOMPLETE_QUERY);
}
