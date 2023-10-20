#include "WithEvaluator.h"
#include "qps/exceptions/QPSInvalidWhileEvaluatorException.h"

IntermediateTable WithEvaluator::evaluateStmtNum(PKBReader& pkbReader) {
  throw QPSInvalidWhileEvaluatorException(QPS_INVALID_WHILE_EVALUATOR_EVALUATION);
}

IntermediateTable WithEvaluator::evaluateConstantValue(PKBReader& pkbReader) {
  throw QPSInvalidWhileEvaluatorException(
      QPS_INVALID_WHILE_EVALUATOR_EVALUATION);
}

IntermediateTable WithEvaluator::evaluateProcName(PKBReader& pkbReader) {
  throw QPSInvalidWhileEvaluatorException(
      QPS_INVALID_WHILE_EVALUATOR_EVALUATION);
}

IntermediateTable WithEvaluator::evaluateVarName(PKBReader& pkbReader) {
  throw QPSInvalidWhileEvaluatorException(
      QPS_INVALID_WHILE_EVALUATOR_EVALUATION);
}

IntermediateTable WithEvaluator::evaluateCallProcName(PKBReader& pkbReader) {
  throw QPSInvalidWhileEvaluatorException(
      QPS_INVALID_WHILE_EVALUATOR_EVALUATION);
}

IntermediateTable WithEvaluator::evaluateCallStmtNum(PKBReader& pkbReader) {
  throw QPSInvalidWhileEvaluatorException(
      QPS_INVALID_WHILE_EVALUATOR_EVALUATION);
}

IntermediateTable WithEvaluator::evaluateReadVarName(PKBReader& pkbReader) {
  throw QPSInvalidWhileEvaluatorException(
      QPS_INVALID_WHILE_EVALUATOR_EVALUATION);
}

IntermediateTable WithEvaluator::evaluateReadStmtNum(PKBReader& pkbReader) {
  throw QPSInvalidWhileEvaluatorException(
      QPS_INVALID_WHILE_EVALUATOR_EVALUATION);
}

IntermediateTable WithEvaluator::evaluatePrintVarName(PKBReader& pkbReader) {
  throw QPSInvalidWhileEvaluatorException(
      QPS_INVALID_WHILE_EVALUATOR_EVALUATION);
}

IntermediateTable WithEvaluator::evaluatePrintStmtNum(PKBReader& pkbReader) {
  throw QPSInvalidWhileEvaluatorException(
      QPS_INVALID_WHILE_EVALUATOR_EVALUATION);
}
