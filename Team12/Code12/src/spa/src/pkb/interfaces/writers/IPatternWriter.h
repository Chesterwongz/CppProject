class IPatternWriter {
public:
    virtual ~IPatternWriter() = default;
    virtual void setAssignPattern(const std::string& variableName, const std::string& rpn, int statementNumber) = 0;
};
