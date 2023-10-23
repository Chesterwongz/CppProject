#include <string>

class ICallsWriter {
 public:
  virtual ~ICallsWriter() = default;
  virtual void addCalls(const std::string& callerProc,
                        const std::string& calleeProc, int stmtNum) = 0;
};
