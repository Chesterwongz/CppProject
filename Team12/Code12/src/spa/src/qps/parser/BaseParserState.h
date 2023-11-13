#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_set>
#include <utility>

#include "PQLParserContext.h"
#include "qps/clause/Clause.h"

class BaseParserState : public IParserState {
 private:
  string getValidAttrRef(const string& synonym, const string& attrRef);

 protected:
  static constexpr int FIRST_ARG = 0;
  static constexpr int SECOND_ARG = 1;
  PQLParserContext& parserContext;
  PQLTokenType prev;
  void processNameToken(PQLToken& curr) override;
  void processAttrRef(unique_ptr<SynonymArg>& synArg);
  void addEvaluableClause(unique_ptr<Clause> clause, bool isNegated);

  explicit BaseParserState(PQLParserContext& parserContext, PQLTokenType prev);
  ~BaseParserState() override = default;

 public:
  bool isTerminable() override;
};
