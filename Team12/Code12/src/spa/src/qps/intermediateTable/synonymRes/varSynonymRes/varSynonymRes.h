#pragma once

#include "qps/intermediateTable/synonymRes/SynonymRes.h"

class VarSynonymRes : public SynonymRes {
 public:
  explicit VarSynonymRes(const string& defaultSynonymValue);
  [[nodiscard]] unique_ptr<SynonymRes> clone() const override;
};
