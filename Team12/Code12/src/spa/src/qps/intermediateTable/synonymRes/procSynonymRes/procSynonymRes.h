#pragma once

#include "qps/intermediateTable/synonymRes/SynonymRes.h"

class ProcSynonymRes : public SynonymRes {
 public:
  explicit ProcSynonymRes(const string& defaultSynonymValue);
};
