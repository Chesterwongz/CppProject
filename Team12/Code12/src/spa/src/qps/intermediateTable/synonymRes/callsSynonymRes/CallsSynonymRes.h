#pragma once

#include "qps/intermediateTable/synonymRes/stmtSynonymRes/StmtSynonymRes.h"

class CallSynonymRes : public StmtSynonymRes {
 public:
  explicit CallSynonymRes(string& stmtNumber, string& procName);
  [[nodiscard]] unique_ptr<SynonymRes> clone() const override;
};
