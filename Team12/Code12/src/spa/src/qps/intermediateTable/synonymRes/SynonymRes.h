#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "qps/common/AttrRefEnum.h"
#include "qps/common/Keywords.h"

using std::string, std::unordered_map, std::unique_ptr;

class SynonymRes {
 private:
  /**
   * defaultSynonymValue is the default value to return
   * when a synonym is referenced without any attrRef:
   * - Stmt      -> Stmt#
   * - Constants -> value
   * - Procedure -> procName
   * - Variable  -> varName
   */
  unordered_map<AttrRefEnum, string> attributeMap = {};
  const unordered_map<AttrRef, AttrRefEnum> attrRefToEnumMap = {
      {ATTR_REF_PROC_NAME, AttrRefEnum::PROC_NAME_ENUM },
      {ATTR_REF_VAR_NAME, AttrRefEnum::VAR_NAME_ENUM },
      {ATTR_REF_VALUE, AttrRefEnum::VALUE_ENUM },
      {ATTR_REF_STMT_NUMBER, AttrRefEnum::STMT_NUM_ENUM },
  };
  explicit SynonymRes(unordered_map<AttrRefEnum, string> attributeMap);
  friend class SynonymResFactory;

 public:
  explicit SynonymRes(const string& defaultSynonymValue);

  [[nodiscard]] string toString() const;

  [[nodiscard]] string getAttribute(AttrRefEnum attrRef) const;
  [[nodiscard]] string getAttribute(const AttrRef& attrRef) const;

  [[nodiscard]] virtual SynonymRes clone() const;

  [[nodiscard]] bool isAttrExists(AttrRefEnum attrRef) const;
  [[nodiscard]] bool isAttrExists(const AttrRef& attrRef) const;

  bool operator==(const SynonymRes& other) const;
  bool operator!=(const SynonymRes& other) const;
};

namespace SynonymResUtils {
const unordered_map<AttrRef, AttrRefEnum> attrRefToEnumMap = {
    {ATTR_REF_PROC_NAME, AttrRefEnum::PROC_NAME_ENUM },
    {ATTR_REF_VAR_NAME, AttrRefEnum::VAR_NAME_ENUM },
    {ATTR_REF_VALUE, AttrRefEnum::VALUE_ENUM },
    {ATTR_REF_STMT_NUMBER, AttrRefEnum::STMT_NUM_ENUM },
};
}
