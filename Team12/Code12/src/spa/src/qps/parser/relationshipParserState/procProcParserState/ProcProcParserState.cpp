#include "ProcProcParserState.h"

#include <utility>

#include "qps/clause/clauseDecorator/notDecorator/NotDecorator.h"

unordered_map<string, Abstraction>
    ProcProcParserState::procProcKeywordToAbstraction = {
        {CALLS_ABSTRACTION, CALLS_ENUM},
        {CALLS_STAR_ABSTRACTION, CALLS_STAR_ENUM}};

PredictiveMap ProcProcParserState::predictiveMap = {
    {PQL_PROC_PROC_TOKEN, {PQL_OPEN_BRACKET_TOKEN}},
    {PQL_OPEN_BRACKET_TOKEN,
     {PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN, PQL_LITERAL_REF_TOKEN}},
    {PQL_SYNONYM_TOKEN, {PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_WILDCARD_TOKEN, {PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_LITERAL_REF_TOKEN, {PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_COMMA_TOKEN,
     {PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN, PQL_LITERAL_REF_TOKEN}}};

ProcProcParserState::ProcProcParserState(PQLParserContext &parserContext,
                                         std::string abstraction,
                                         PQLTokenType prev, bool isNegated)
    : RelationshipParserState(parserContext, false, std::move(abstraction),
                              prev, isNegated) {}

void ProcProcParserState::checkIsProcSynonym(const std::string &synonym) {
  auto synType = parserContext.getValidSynonymType(synonym);
  if (synType != PROCEDURE_ENTITY) {
    parserContext.setSemanticallyInvalid();
  }
}

void ProcProcParserState::handleToken() {
  auto curr = parserContext.eatExpectedToken(prev, predictiveMap);

  while (curr.has_value()) {
    PQLToken token = curr.value();

    unique_ptr<Clause> suchThatClause;

    switch (token.getType()) {
      case PQL_OPEN_BRACKET_TOKEN:
        isInBracket = true;
        break;
      case PQL_CLOSE_BRACKET_TOKEN:
        isInBracket = false;
        suchThatClause = createSuchThatClause(
            getAbstractionType(abstraction, procProcKeywordToAbstraction));

        BaseParserState::addEvaluableClause(std::move(suchThatClause),
                                            isNegated);

        ClauseTransitionParserState::setClauseTransitionState(parserContext);
        return;
      case PQL_SYNONYM_TOKEN:
        checkIsProcSynonym(token.getValue());
        arguments.push_back(
            std::make_unique<SynonymArg>(token.getValue(), PROCEDURE_ENTITY));
        break;
      case PQL_LITERAL_REF_TOKEN:
        arguments.push_back(std::make_unique<Ident>(token.getValue()));
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
