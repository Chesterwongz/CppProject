#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "qps/argument/AbstractArgument.h"
#include "qps/common/Keywords.h"

using std::string, std::vector, std::unique_ptr;

class SynonymArg : public AbstractArgument {
 private:
  const QPSStringUtils::ArgumentType argumentType = QPSStringUtils::SYNONYM;
  string synonymValue;
  Entity entityType;
  AttrRef attrRef;

 public:
  explicit SynonymArg(string argumentValue, Entity entityType)
      : synonymValue(std::move(argumentValue)),
        entityType(std::move(entityType)) {}

  explicit SynonymArg(string argumentValue, Entity entityType, AttrRef ref)
      : synonymValue(std::move(argumentValue)),
        entityType(std::move(entityType)),
        attrRef(std::move(ref)) {}

  const string& getValue() override;
  const Entity& getEntityType();
  void setAttrRef(AttrRef ref);
  const AttrRef& getAttrRef();
  QPSStringUtils::ArgumentType getArgumentType() override;
  bool isSynonym() const override;
  bool isStmtSynonym() override;
  bool isVarSynonym() override;
  bool isProcSynonym() override;
  bool operator==(const AbstractArgument& other) const override;
  string getArgSignature() override;
};

typedef vector<unique_ptr<SynonymArg>> SynonymsToSelect;
