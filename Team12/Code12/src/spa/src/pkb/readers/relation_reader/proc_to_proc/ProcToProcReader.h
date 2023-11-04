#pragma once

#include <string>
#include <utility>
#include <vector>

#include "common/utils/CollectionUtils.h"
#include "pkb/storage/relation_storage/RelationTStore.h"
#include "pkb/utils/PredicateUtils.h"

class ProcToProcReader {
 private:
  RelationTStore<std::string>& store;

 public:
  explicit ProcToProcReader(RelationTStore<std::string>& store)
      : store(store) {}

  // Calls(p, "proc2"), returns all p
  std::vector<std::string> getDirectP1ByP2(const std::string& proc2);

  // Calls*(p, "proc2"), returns all p
  std::vector<std::string> getTransitiveP1ByP2(const std::string& proc2);

  // Calls("proc1", p), returns all p
  std::vector<std::string> getDirectP2ByP1(const std::string& proc1);

  // Calls*("proc1", p), returns all p
  std::vector<std::string> getTransitiveP2ByP1(const std::string& proc1);

  // Calls(p1, p2)
  std::vector<std::pair<std::string, std::string>> getDirectP1AndP2Pairs();

  // Calls*(p1, p2)
  std::vector<std::pair<std::string, std::string>> getTransitiveP1AndP2Pairs();

  bool hasDirectRelation(const std::string& proc1, const std::string& proc2);

  bool hasTransitiveRelation(const std::string& proc1,
                             const std::string& proc2);
};
