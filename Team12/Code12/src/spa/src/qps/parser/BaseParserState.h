#pragma once

#include <optional>
#include <unordered_set>

#include "PQLParserContext.h"
#include "qps/clause/Clause.h"

class BaseParserState : public IParserState {
 protected:
  static constexpr int FIRST_ARG = 0;
  static constexpr int SECOND_ARG = 1;
  PQLParserContext& parserContext;
  PQLTokenType prev;
  void processNameToken(PQLToken& curr) override;
  void processAttrRef(unique_ptr<SynonymArg>& synArg);
  string checkValidAttrRef(const string& synonym, string attrRef);

  explicit BaseParserState(PQLParserContext& parserContext, PQLTokenType prev);
  ~BaseParserState() override = default;
};
