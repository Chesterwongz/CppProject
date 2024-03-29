#include "StmtVarParserState.h"

#include <utility>

#include "qps/clause/clauseDecorator/notDecorator/NotDecorator.h"

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
    {PQL_WILDCARD_TOKEN, {PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_LITERAL_REF_TOKEN, {PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_INTEGER_TOKEN, {PQL_COMMA_TOKEN}}};

StmtVarParserState::StmtVarParserState(PQLParserContext& parserContext,
                                       string abstraction, PQLTokenType prev,
                                       bool isNegated)
    : RelationshipParserState(parserContext, false, std::move(abstraction),
                              prev, isNegated) {}

string StmtVarParserState::getValidSynonym(const string& synonym,
                                           size_t argumentNumber) {
  auto synType = parserContext.getValidSynonymType(synonym);
  bool isValidFirstSyn =
      argumentNumber == FIRST_ARG &&
      (synType != VARIABLE_ENTITY && synType != CONSTANT_ENTITY);
  bool isValidSecondSyn =
      argumentNumber == SECOND_ARG && synType == VARIABLE_ENTITY;

  if (!isValidFirstSyn && !isValidSecondSyn) {
    parserContext.setSemanticallyInvalid();
  }
  return synType;
}

void StmtVarParserState::checkIsValidWildcard() {
  if (arguments.size() == FIRST_ARG) {
    parserContext.setSemanticallyInvalid();
  }
}

void StmtVarParserState::handleToken() {
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
            getAbstractionType(abstraction, stmtVarKeywordToAbstraction));
        BaseParserState::addEvaluableClause(std::move(suchThatClause),
                                            isNegated);

        ClauseTransitionParserState::setClauseTransitionState(parserContext);

        return;
      case PQL_SYNONYM_TOKEN:
        arguments.push_back(std::make_unique<SynonymArg>(
            token.getValue(),
            getValidSynonym(token.getValue(), arguments.size())));
        break;
      case PQL_WILDCARD_TOKEN:
        checkIsValidWildcard();
        arguments.push_back(std::make_unique<Wildcard>());
        break;
      case PQL_LITERAL_REF_TOKEN:
        arguments.push_back(std::make_unique<Ident>(token.getValue()));
        break;
      case PQL_INTEGER_TOKEN:
        arguments.push_back(std::make_unique<Integer>(token.getValue()));
        break;
      default:
        break;
    }
    this->prev = token.getType();

    curr = parserContext.eatExpectedToken(prev, predictiveMap);
  }
  throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCOMPLETE_QUERY);
}
