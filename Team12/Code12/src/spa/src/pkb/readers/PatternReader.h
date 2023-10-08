#pragma once

#include <set>
#include <string>
#include <utility>
#include <vector>

#include "common/StmtTypes.h"
#include "pkb/interfaces/readers/IPatternReader.h"
#include "pkb/storage/patternstorage/PatternStorage.h"

class PatternReader : public virtual IPatternReader {
 private:
  PatternStorage& pattern_storage_;

 protected:
  explicit PatternReader(PatternStorage& storage) : pattern_storage_(storage) {}

 public:
  std::vector<std::string> getExactAssignPattern(
      const std::string& variableName, const std::string& rpn,
      bool isSynonym) override;

  std::vector<std::string> getPartialAssignPattern(
      const std::string& variableName, const std::string& rpn,
      bool isSynonym) override;
};
