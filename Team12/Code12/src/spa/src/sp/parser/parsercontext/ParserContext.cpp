#include "ParserContext.h"

ParserContext::ParserContext(const std::string &input) {
    tokenStream = Tokenizer::tokenize(input);
}

bool ParserContext::addProcName(const std::string &newName) {
    if (this->seenProcNames.count(newName)) {
        throw DuplicateProcNameException(newName);
    }
    this->seenProcNames.insert(newName);
    return true;
}

bool ParserContext::addVarName(const std::string &newName) {
    if (this->seenVarNames.count(newName)) {
        throw DuplicateProcNameException(newName);
    }
    this->seenVarNames.insert(newName);
    return true;
}

bool ParserContext::isExpected(TokenType expectedType) {
    std::optional<Token> tokenOpt = tokenStream->peek();
    return tokenOpt.has_value() && tokenOpt.value().getType() == expectedType;
}

bool ParserContext::isExpected(TokenType expectedType, const std::string &expectedValue) {
    return isExpected(expectedType) && tokenStream->peek()->getValue() == expectedValue;
}

std::optional<std::string> ParserContext::tryEatExpected(TokenType expectedType) {
    if (!isExpected(expectedType)) return std::nullopt;
    return tokenStream->eat()->getValue();
}

std::optional<std::string> ParserContext::tryEatExpected(TokenType expectedType, const std::string &expectedValue) {
    if (!isExpected(expectedType, expectedValue)) return std::nullopt;
    return tokenStream->eat()->getValue();
}

std::string ParserContext::forceEatExpected(TokenType expectedType) {
    if (!isExpected(expectedType))
        throw UnexpectedTokenException(TokenTypeUtils::toString(expectedType), lineNum);
    return tokenStream->eat().value().getValue();
}

std::string ParserContext::forceEatExpected(TokenType expectedType, const std::string &expectedValue) {
    if (!isExpected(expectedType, expectedValue)) throw UnexpectedTokenException(expectedValue, lineNum);
    return tokenStream->eat().value().getValue();
}

int ParserContext::getLineNum() const {
    return lineNum;
}

void ParserContext::incrementLineNum() {
    lineNum++;
}
