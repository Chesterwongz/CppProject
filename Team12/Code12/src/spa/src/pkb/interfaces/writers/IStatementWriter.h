class IStatementWriter {
public:
    virtual ~IStatementWriter() = default;
    virtual void setStatement(int statementNumber, StmtType statementType) = 0;
};
