#pragma once

#include "qps/intermediateTable/synonymRes/SynonymRes.h"

class ConstantSynonymRes : public SynonymRes {
 public:
  explicit ConstantSynonymRes(const string& defaultSynonymValue);
  [[nodiscard]] unique_ptr<SynonymRes> clone() const override;
};
