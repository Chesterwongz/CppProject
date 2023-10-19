#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "qps/common/AttrRefEnum.h"

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
  string defaultSynonymValue;
  unordered_map<AttrRefEnum, string> attributeMap = {};
  explicit SynonymRes(string defaultSynonymValue,
                      unordered_map<AttrRefEnum, string> attributeMap);
  friend class SynonymResFactory;

 public:
  explicit SynonymRes(string defaultSynonymValue);

  [[nodiscard]] string toString() const;

  string getAttribute(AttrRefEnum attrRef);

  [[nodiscard]] virtual SynonymRes clone() const;

  [[nodiscard]] bool isAttrExists(AttrRefEnum attrRef) const;

  bool operator==(const SynonymRes& other) const;
  bool operator!=(const SynonymRes& other) const;
};
