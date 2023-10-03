class IParentWriter {
 public:
  virtual ~IParentWriter() = default;
  virtual void setParentRelationship(int statementNumber,
                                     int childStatement) = 0;
  virtual void setParentStarRelationship(int statementNumber,
                                         int childStatement) = 0;
};