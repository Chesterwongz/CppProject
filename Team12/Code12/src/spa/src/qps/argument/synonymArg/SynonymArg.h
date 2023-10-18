#pragma once

#include <string>
#include <utility>

#include "qps/argument/AbstractArgument.h"
#include "qps/common/Keywords.h"

using std::string;

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
  bool isSynonym() override;
  bool operator==(const AbstractArgument& other) const override;
};
