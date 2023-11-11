#include "StmtStmtParserState.h"

#include <utility>

#include "qps/clause/clauseDecorator/notDecorator/NotDecorator.h"

unordered_map<string, Abstraction>
    StmtStmtParserState::stmtStmtKeywordToAbstraction = {
        {FOLLOWS_ABSTRACTION, FOLLOWS_ENUM},
        {FOLLOWS_STAR_ABSTRACTION, FOLLOWS_STAR_ENUM},
        {PARENTS_ABSTRACTION, PARENTS_ENUM},
        {PARENTS_STAR_ABSTRACTION, PARENTS_STAR_ENUM},
        {NEXT_ABSTRACTION, NEXT_ENUM},
        {NEXT_STAR_ABSTRACTION, NEXT_STAR_ENUM},
        {AFFECTS_ABSTRACTION, AFFECTS_ENUM}};

PredictiveMap StmtStmtParserState::predictiveMap = {
    {PQL_STMT_STMT_TOKEN, {PQL_OPEN_BRACKET_TOKEN}},
    {PQL_OPEN_BRACKET_TOKEN,
     {PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN, PQL_INTEGER_TOKEN}},
    {PQL_SYNONYM_TOKEN, {PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_WILDCARD_TOKEN, {PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_INTEGER_TOKEN, {PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_COMMA_TOKEN,
     {PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN, PQL_INTEGER_TOKEN}}};

StmtStmtParserState::StmtStmtParserState(PQLParserContext &parserContext,
                                         string abstraction, PQLTokenType prev,
                                         bool isNegated)
    : RelationshipParserState(parserContext, false, std::move(abstraction),
                              prev, isNegated) {}

string StmtStmtParserState::getStmtSynonym(const std::string &synonym) {
  auto synType = parserContext.getValidSynonymType(synonym);
  if (!PQLParserUtils::isStmtSynonym(synType)) {
    parserContext.setSemanticallyInvalid();
  }
  return synType;
}

void StmtStmtParserState::handleToken() {
  auto curr = parserContext.eatExpectedToken(prev, predictiveMap);

  unique_ptr<Clause> suchThatClause;

  while (curr.has_value()) {
    PQLToken token = curr.value();

    switch (token.getType()) {
      case PQL_OPEN_BRACKET_TOKEN:
        isInBracket = true;
        break;
      case PQL_CLOSE_BRACKET_TOKEN:
        isInBracket = false;

        suchThatClause = createSuchThatClause(
            getAbstractionType(abstraction, stmtStmtKeywordToAbstraction));

        BaseParserState::addEvaluableClause(std::move(suchThatClause),
                                            isNegated);

        ClauseTransitionParserState::setClauseTransitionState(parserContext);
        return;
      case PQL_SYNONYM_TOKEN:
        arguments.push_back(std::make_unique<SynonymArg>(
            token.getValue(), getStmtSynonym(token.getValue())));
        break;
      case PQL_INTEGER_TOKEN:
        arguments.push_back(std::make_unique<Integer>(token.getValue()));
        break;
      case PQL_WILDCARD_TOKEN:
        arguments.push_back(std::make_unique<Wildcard>());
        break;
      default:
        break;
    }
    this->prev = token.getType();

    curr = parserContext.eatExpectedToken(prev, predictiveMap);
  }
  throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCOMPLETE_QUERY);
}
