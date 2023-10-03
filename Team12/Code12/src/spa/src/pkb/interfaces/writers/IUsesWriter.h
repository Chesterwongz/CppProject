class IUsesWriter {
 public:
  virtual ~IUsesWriter() = default;
  virtual void setUsesRelationship(const std::string& variableName,
                                   int statementNumber) = 0;
};
