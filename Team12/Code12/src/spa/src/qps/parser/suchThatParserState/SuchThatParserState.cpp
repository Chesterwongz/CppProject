#include "SuchThatParserState.h"

#include "qps/parser/relationshipParserState/stmtStmtParserState/StmtStmtParserState.h"
#include "qps/parser/relationshipParserState/stmtVarParserState/StmtVarParserState.h"

PredictiveMap SuchThatParserState::predictiveMap = {
        { PQL_NULL_TOKEN, { PQL_SUCH_TOKEN } },
        { PQL_SUCH_TOKEN, { PQL_THAT_TOKEN } },
        { PQL_THAT_TOKEN, { PQL_STMT_STMT_TOKEN,
                            PQL_STMT_VAR_TOKEN } }
};

SuchThatParserState::SuchThatParserState(PQLParserContext &parserContext) :
        BaseParserState(parserContext) {};

void SuchThatParserState::processNameToken(PQLToken &curr) {
    auto tokenType = PQLParserUtils::getTokenTypeFromKeyword(curr.getValue());
    curr.updateTokenType(tokenType);
}

void SuchThatParserState::handleToken() {
    while (!this->tokenStream.isTokenStreamEnd()) {
        auto& curr = tokenStream.getCurrentToken();

        if (curr.getType() == PQL_NAME_TOKEN) {
            processNameToken(curr);
        }

        if (!PQLParserUtils::isExpectedToken(predictiveMap, prev, curr.getType())) {
            throw QPSSyntaxError(QPS_TOKENIZATION_ERR + curr.getValue());
        }
        switch (curr.getType()) {
            case PQL_SUCH_TOKEN:
            case PQL_THAT_TOKEN:
                break;
            case PQL_STMT_STMT_TOKEN:
                parserContext.transitionTo(make_unique<StmtStmtParserState>(parserContext));
                return;
            case PQL_STMT_VAR_TOKEN:
                parserContext.transitionTo(make_unique<StmtVarParserState>(parserContext));
                return;
            default:
                throw QPSSyntaxError(QPS_TOKENIZATION_ERR + curr.getValue());
        }
        this->prev = curr.getType();
        tokenStream.next();
    }
    // should never exit in this parser
    throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT);
}


