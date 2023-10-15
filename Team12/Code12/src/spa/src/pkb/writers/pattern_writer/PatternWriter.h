#pragma once

#include "pkb/interfaces/writers/IPatternWriter.h"
#include "pkb/storage/pattern_storage/PatternStorage.h"

class PatternWriter : public IPatternWriter {
 private:
  IPatternStorage& patternStorage;

 protected:
  explicit PatternWriter(IPatternStorage& patternStorage)
      : patternStorage(patternStorage) {}

 public:
  void addAssignPattern(const std::string& varName, const std::string& rpn,
                        int stmtNum) override;

  void addWhilePattern(int stmtNum, const std::string& varName) override;
  void addIfPattern(int stmtNum, const std::string& varName) override;
};
