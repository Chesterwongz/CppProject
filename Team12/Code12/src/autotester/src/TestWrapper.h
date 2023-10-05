#ifndef TESTWRAPPER_H
#define TESTWRAPPER_H

#include <algorithm>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <unordered_set>

// include your other headers here
#include "AbstractWrapper.h"
#include "pkb/facade/PKB.h"
#include "qps/QPS.h"
#include "sp/SourceProcessor.h"

class TestWrapper : public AbstractWrapper {
 private:
  std::unique_ptr<QPS> qps;
  std::unique_ptr<SourceProcessor> sourceProcessor;
  std::unique_ptr<PKB> pkb;

 public:
  // default constructor
  TestWrapper();

  // destructor
  ~TestWrapper();

  // method for parsing the SIMPLE source
  virtual void parse(std::string filename);

  // method for evaluating a query
  virtual void evaluate(std::string query, std::list<std::string>& results);
};

#endif
