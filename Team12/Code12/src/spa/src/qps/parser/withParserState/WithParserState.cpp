#include "WithParserState.h"

#include "qps/parser/clauseTransitionParserState/ClauseTransitionParserState.h"

PredictiveMap WithParserState::predictiveMap = {
    {PQL_WITH_TOKEN,
     {PQL_NOT_TOKEN, PQL_SYNONYM_TOKEN, PQL_LITERAL_REF_TOKEN,
      PQL_INTEGER_TOKEN}},
    {PQL_NOT_TOKEN,
     {PQL_SYNONYM_TOKEN, PQL_LITERAL_REF_TOKEN, PQL_INTEGER_TOKEN}},
    {PQL_SYNONYM_TOKEN, {PQL_EQUALS_TOKEN}},
    {PQL_INTEGER_TOKEN, {PQL_EQUALS_TOKEN}},
    {PQL_LITERAL_REF_TOKEN, {PQL_EQUALS_TOKEN}},
    {PQL_EQUALS_TOKEN,
     {PQL_SYNONYM_TOKEN, PQL_LITERAL_REF_TOKEN, PQL_INTEGER_TOKEN}},
};

WithParserState::WithParserState(PQLParserContext& parserContext,
                                 PQLTokenType prev)
    : BaseParserState(parserContext, prev), isNegated(false) {
  prevClauseType = WITH_CLAUSE;
}

void WithParserState::checkSameTypeComparison() {
  assert(argumentTypes.size() == expectedNumberOfArgs);
  if (argumentTypes[FIRST_ARG] != argumentTypes[SECOND_ARG]) {
    throw QPSSemanticError(QPS_SEMANTIC_ERR_INVALID_WITH);
  }
}

void WithParserState::handleToken() {
  auto curr = parserContext.eatExpectedToken(prev, predictiveMap);

  while (curr.has_value()) {
    PQLToken token = curr.value();
    unique_ptr<SynonymArg> syn;

    switch (token.getType()) {
      case PQL_NOT_TOKEN:
        isNegated = true;
        break;
      case PQL_SYNONYM_TOKEN:
        syn = std::make_unique<SynonymArg>(
            token.getValue(),
            parserContext.getValidSynonymType(token.getValue()));
        processAttrRef(syn);
        argumentTypes.emplace_back(
            PQLParserUtils::attrRefToType.at(syn->getAttrRef()));
        arguments.emplace_back(std::move(syn));
        break;
      case PQL_LITERAL_REF_TOKEN:
        argumentTypes.emplace_back(ArgumentType::NAME_TYPE);
        arguments.emplace_back(std::make_unique<Ident>(token.getValue()));
        break;
      case PQL_INTEGER_TOKEN:
        argumentTypes.emplace_back(ArgumentType::INTEGER_TYPE);
        arguments.emplace_back(std::make_unique<Integer>(token.getValue()));
        break;
      default:
        break;
    }
    if (arguments.size() == expectedNumberOfArgs) {
      // TODO(Houten): add With Clause here
      checkSameTypeComparison();
      ClauseTransitionParserState::setClauseTransitionState(parserContext);
      return;
    }
    this->prev = token.getType();

    curr = parserContext.eatExpectedToken(prev, predictiveMap);
  }
  throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCOMPLETE_QUERY);
}
