#pragma once

#include "qps/intermediateTable/synonymRes/SynonymRes.h"

class ConstantSynonymRes : public SynonymRes {
 public:
  ConstantSynonymRes(const string& defaultSynonymValue);
};
