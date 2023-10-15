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
  // TODO(qps): Remove this constructor
  explicit SynonymArg(string argumentValue)
      : synonymValue(std::move(argumentValue)) {}

  explicit SynonymArg(string argumentValue, Entity entityType)
      : synonymValue(std::move(argumentValue)),
        entityType(std::move(entityType)) {}

  explicit SynonymArg(string argumentValue, Entity entityType, AttrRef ref)
      : synonymValue(std::move(argumentValue)),
        entityType(std::move(entityType)),
        attrRef(std::move(ref)) {}

  string getValue() override;
  void setAttrRef(AttrRef ref);
  QPSStringUtils::ArgumentType getArgumentType() override;
  bool isSynonym() override;
  bool operator==(const AbstractArgument& other) const override;
};
