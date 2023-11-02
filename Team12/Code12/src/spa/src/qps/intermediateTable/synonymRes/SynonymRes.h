#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "qps/common/Keywords.h"

using std::string, std::unordered_map, std::unique_ptr;

class SynonymRes {
 private:
  /**
   * ATTR_REF_DEFAULT is the default value to return
   * when a synonym is referenced without any attrRef:
   * - Stmt      -> Stmt#
   * - Constants -> value
   * - Procedure -> procName
   * - Variable  -> varName
   */
  unordered_map<AttrRef, string> attributeMap = {};
  explicit SynonymRes(unordered_map<AttrRef, string> attributeMap);
  friend class SynonymResFactory;

 public:
  explicit SynonymRes(const string& defaultSynonymValue);

  [[nodiscard]] string toString() const;

  [[nodiscard]] string getAttribute(const AttrRef& attrRef) const;

  SynonymRes& operator=(const SynonymRes& other) = default;

  [[nodiscard]] bool isAttrExists(const AttrRef& attrRef) const;

  bool operator==(const SynonymRes& other) const;
  bool operator!=(const SynonymRes& other) const;
};
