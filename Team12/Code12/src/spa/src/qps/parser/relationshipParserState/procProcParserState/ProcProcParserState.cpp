#include "ProcProcParserState.h"

unordered_map<string, Abstraction>
    ProcProcParserState::procProcKeywordToAbstraction = {
        {CALLS_ABSTRACTION, CALLS_ENUM},
        {CALLS_STAR_ABSTRACTION, CALLS_STAR_ENUM}
};

PredictiveMap ProcProcParserState::predictiveMap = {
    {PQL_PROC_PROC_TOKEN, {PQL_OPEN_BRACKET_TOKEN}},
    {PQL_OPEN_BRACKET_TOKEN,
     {PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN, PQL_LITERAL_REF_TOKEN}},
    {PQL_SYNONYM_TOKEN, {PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_WILDCARD_TOKEN, {PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_LITERAL_REF_TOKEN, {PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN}},
    {PQL_COMMA_TOKEN,
     {PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN, PQL_LITERAL_REF_TOKEN}},
    {PQL_CLOSE_BRACKET_TOKEN, startTokensOfAvailClauses}};

ProcProcParserState::ProcProcParserState(PQLParserContext &parserContext,
                                         std::string abstraction,
                                         PQLTokenType prev)
    : RelationshipParserState(parserContext, false, abstraction, prev),
      isSuccess(false) {}

void ProcProcParserState::checkIsProcSynonym(const std::string &synonym) {
  auto synType = parserContext.getValidSynonymType(synonym);
  if (synType != PROCEDURE_ENTITY) {

  }
}
