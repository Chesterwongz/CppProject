#ifndef TESTWRAPPER_H
#define TESTWRAPPER_H

#include <string>
#include <iostream>
#include <list>
#include <memory>

// include your other headers here
#include "AbstractWrapper.h"
#include "sp/SourceProcessor.h"

class TestWrapper : public AbstractWrapper {
private:
    std::unique_ptr<SourceProcessor> sourceProcessor;
    std::unique_ptr<PKBWriter> pkbWriter;

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
