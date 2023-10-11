#include "StmtStmtParserState.h"

#include <utility>

unordered_map<string, Abstraction>
    StmtStmtParserState::stmtStmtKeywordToAbstraction = {
        {FOLLOWS_ABSTRACTION, FOLLOWS_ENUM},
        {FOLLOWS_STAR_ABSTRACTION, FOLLOWS_STAR_ENUM},
        {PARENTS_ABSTRACTION, PARENTS_ENUM},
        {PARENTS_STAR_ABSTRACTION, PARENTS_STAR_ENUM},
        {NEXT_ABSTRACTION, NEXT_ENUM},
        {NEXT_STAR_ABSTRACTION, NEXT_STAR_ENUM}};

PredictiveMap StmtStmtParserState::predictiveMap = {
    {PQL_STMT_STMT_TOKEN, {PQL_OPEN_BRACKET_TOKEN}},
    {PQL_OPEN_BRACKET_TOKEN,
     {PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN, PQL_INTEGER_TOKEN}},
    {PQL_SYNONYM_TOKEN, {PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_WILDCARD_TOKEN, {PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_INTEGER_TOKEN, {PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_COMMA_TOKEN,
     {PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN, PQL_INTEGER_TOKEN}},
    {PQL_CLOSE_BRACKET_TOKEN, startTokensOfAvailClauses}};

StmtStmtParserState::StmtStmtParserState(PQLParserContext &parserContext,
                                         string abstraction, PQLTokenType prev)
    : RelationshipParserState(parserContext, false, std::move(abstraction),
                              prev),
      isSuccess(false) {}

void StmtStmtParserState::checkIsStmtSynonym(const std::string &synonym) {
  auto synType = parserContext.getValidSynonymType(synonym);
  if (stmtEntities.find(synType) == stmtEntities.end()) {
    throw QPSSemanticError(QPS_SEMANTIC_ERR_NOT_STMT_SYN);
  }
}

void StmtStmtParserState::handleToken() {
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
            getAbstractionType(abstraction, stmtStmtKeywordToAbstraction),
            std::move(arguments.at(FIRST_ARG)),
            std::move(arguments.at(SECOND_ARG))));
        break;
      case PQL_SYNONYM_TOKEN:
        checkIsStmtSynonym(token.getValue());
        arguments.push_back(
            std::move(std::make_unique<SynonymArg>(token.getValue())));
        break;
      case PQL_INTEGER_TOKEN:
        arguments.push_back(
            std::move(std::make_unique<Integer>(token.getValue())));
        break;
      case PQL_WILDCARD_TOKEN:
        arguments.push_back(std::move(std::make_unique<Wildcard>()));
        break;
      case PQL_PATTERN_TOKEN:
        this->parserContext.transitionTo(std::make_unique<PatternParserState>(
            parserContext, token.getType()));
        return;
      case PQL_SUCH_TOKEN:
        this->parserContext.transitionTo(std::make_unique<SuchThatParserState>(
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
