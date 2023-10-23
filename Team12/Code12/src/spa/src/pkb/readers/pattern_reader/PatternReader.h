#pragma once

#include <set>
#include <string>
#include <utility>
#include <vector>

#include "common/StmtTypes.h"
#include "pkb/interfaces/readers/IPatternReader.h"
#include "pkb/storage/pattern_storage/PatternStorage.h"

class PatternReader : public IPatternReader {
 private:
  PatternStorage& pattern_storage_;

 protected:
  explicit PatternReader(PatternStorage& storage) : pattern_storage_(storage) {}

 public:
  std::vector<std::pair<std::string, std::string>> getExactAssignPattern(
      const std::string& variableName, const std::string& rpn) override;

  std::vector<std::pair<std::string, std::string>> getPartialAssignPattern(
      const std::string& variableName, const std::string& rpn) override;

  std::vector<std::pair<std::string, std::string>> getWhilePattern(
      const std::string& variableName) override;

  std::vector<std::pair<std::string, std::string>> getIfPattern(
      const std::string& variableName) override;
};
