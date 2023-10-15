#pragma once

#include "qps/intermediateTable/synonymRes/SynonymRes.h"

class ProcSynonymRes : public SynonymRes {
 public:
  explicit ProcSynonymRes(const string& defaultSynonymValue);
  [[nodiscard]] unique_ptr<SynonymRes> clone() const override;
};
