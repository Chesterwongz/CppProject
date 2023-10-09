#include "StmtVarParserState.h"

unordered_map<string, Abstraction>
    StmtVarParserState::stmtVarKeywordToAbstraction = {
        {USES_ABSTRACTION, USES_ENUM}, {MODIFIES_ABSTRACTION, MODIFIES_ENUM}};

PredictiveMap StmtVarParserState::predictiveMap = {
    {PQL_STMT_VAR_TOKEN, {PQL_OPEN_BRACKET_TOKEN}},
    {PQL_OPEN_BRACKET_TOKEN,
     {PQL_SYNONYM_TOKEN, PQL_LITERAL_REF_TOKEN, PQL_INTEGER_TOKEN,
      PQL_WILDCARD_TOKEN}},
    {PQL_COMMA_TOKEN,
     {PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN, PQL_LITERAL_REF_TOKEN}},
    {PQL_SYNONYM_TOKEN, {PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_WILDCARD_TOKEN, {PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_LITERAL_REF_TOKEN, {PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_INTEGER_TOKEN, {PQL_COMMA_TOKEN}},
    {PQL_CLOSE_BRACKET_TOKEN, startTokensOfAvailClauses}};

StmtVarParserState::StmtVarParserState(PQLParserContext& parserContext,
                                       string abstraction, PQLTokenType prev)
    : RelationshipParserState(parserContext, false, abstraction, prev),
      isSuccess(false) {}

void StmtVarParserState::checkIsValidSynonym(const std::string& synonym,
                                             int argumentNumber) {
  auto synType = parserContext.getValidSynonymType(synonym);
  if (argumentNumber == SECOND_ARG && synType != VARIABLE_ENTITY) {
    throw QPSSemanticError(QPS_SEMANTIC_ERR_NOT_VAR_SYN);
  }
}

void StmtVarParserState::checkIsValidWildcard() {
  if (arguments.size() == FIRST_ARG) {
    throw QPSSemanticError(QPS_SEMANTIC_ERR_WILDCARD_FIRSTARG);
  }
}

void StmtVarParserState::checkIsValidIdent(const string& ref) {
  if (!QPSStringUtils::isIdentValue(ref)) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR_IDENT);
  }
}

void StmtVarParserState::handleToken() {
  auto curr = parserContext.eatExpectedToken(prev, predictiveMap);

  while (curr.has_value()) {
    PQLToken token = curr.value();

    switch (token.getType()) {
      case PQL_OPEN_BRACKET_TOKEN:
        isInBracket = true;
        break;
      case PQL_CLOSE_BRACKET_TOKEN:
        isInBracket = false;
        isSuccess = checkSafeExit(arguments);
        parserContext.addClause(std::make_unique<SuchThatClause>(
            getAbstractionType(abstraction, stmtVarKeywordToAbstraction),
            std::move(arguments.at(FIRST_ARG)),
            std::move(arguments.at(SECOND_ARG))));
        break;
      case PQL_SYNONYM_TOKEN:
        checkIsValidSynonym(token.getValue(), arguments.size());
        arguments.push_back(
            std::move(std::make_unique<SynonymArg>(token.getValue())));
        break;
      case PQL_WILDCARD_TOKEN:
        checkIsValidWildcard();
        arguments.push_back(std::make_unique<Wildcard>());
        break;
      case PQL_LITERAL_REF_TOKEN:
        checkIsValidIdent(token.getValue());
        arguments.push_back(
            std::move(std::make_unique<Ident>(token.getValue())));
        break;
      case PQL_INTEGER_TOKEN:
        arguments.push_back(
            std::move(std::make_unique<Integer>(token.getValue())));
        break;
      case PQL_PATTERN_TOKEN:
        this->parserContext.transitionTo(std::make_unique<PatternParserState>(
            parserContext, token.getType()));
        return;
      default:
        break;
    }
    this->prev = token.getType();

    curr = parserContext.eatExpectedToken(prev, predictiveMap);
  }
  if (!isSuccess) {
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT);
  }
}
