#include "TestWrapper.h"

#include "qps/exceptions/QPSException.h"

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
  if (wrapper == 0) wrapper = new TestWrapper;
  return wrapper;
}
// Do not modify the following line
volatile bool AbstractWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() {
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
  sourceProcessor = std::make_unique<SourceProcessor>();
  //  pkbWriter = std::make_unique<PKBWriter>();
  pkb = std::make_unique<PKB>();
  qps = std::make_unique<QPS>(pkb->getReader());
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
  // call your parser to do the parsing
  // ...rest of your code...
  try {
    sourceProcessor->process(filename, pkb->getWriter());
  } catch (SpException& error) {
    std::cout << error.what() << std::endl;
    exit(1);
  } catch (...) {
    exit(1);
  }
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results) {
  // call your evaluator to evaluate the query here
  // ...code to evaluate query..
  try {
    auto result = qps->processQueryString(query);

    // store the answers to the query in the results list (it is initially
    // empty) each result must be a string.
    for (const auto& r : result) {
      results.push_back(r);
    }
  } catch (const QPSException& error) {
    results.emplace_back(error.what());
    return;
  } catch (const Exception& error) {
    results.emplace_back(error.what());
    return;
  } catch (const std::runtime_error& error) {
    results.emplace_back(error.what());
    return;
  } catch (...) {
    results.emplace_back("Something went very wrong");
    return;
  }
}
