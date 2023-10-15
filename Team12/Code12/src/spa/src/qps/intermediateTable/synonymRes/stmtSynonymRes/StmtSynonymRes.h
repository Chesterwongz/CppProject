#pragma once

#include "qps/intermediateTable/synonymRes/SynonymRes.h"

class StmtSynonymRes : public SynonymRes {
 public:
  explicit StmtSynonymRes(const string& defaultSynonymValue);
  [[nodiscard]] unique_ptr<SynonymRes> clone() const override;
};
