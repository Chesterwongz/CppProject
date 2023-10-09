#include <string>

class ICallsWriter {
 public:
  virtual ~ICallsWriter() = default;
  virtual void setCallsRelationship(const std::string& callerProc,
                                    const std::string& calleeProc) = 0;
  virtual void setCallsStarRelationship(const std::string& callerProc,
                                        const std::string& calleeProc) = 0;
};
