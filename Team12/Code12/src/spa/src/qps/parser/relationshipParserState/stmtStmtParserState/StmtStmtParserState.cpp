#include "StmtStmtParserState.h"

unordered_map<string, Abstraction> StmtStmtParserState::stmtStmtKeywordToAbstraction = {
        { FOLLOWS_ABSTRACTION, FOLLOWS_ENUM },
        { FOLLOWS_STAR_ABSTRACTION, FOLLOWS_STAR_ENUM },
        { PARENTS_ABSTRACTION, PARENTS_ENUM },
        { PARENTS_STAR_ABSTRACTION, PARENTS_STAR_ENUM }
};

PredictiveMap StmtStmtParserState::predictiveMap = {
        { PQL_NULL_TOKEN, { PQL_STMT_STMT_TOKEN } },
        { PQL_STMT_STMT_TOKEN, { PQL_OPEN_BRACKET_TOKEN } },
        { PQL_OPEN_BRACKET_TOKEN, { PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN, PQL_INTEGER_TOKEN } },
        { PQL_SYNONYM_TOKEN, { PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN } },
        { PQL_WILDCARD_TOKEN, { PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN } },
        { PQL_INTEGER_TOKEN, { PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN } },
        { PQL_COMMA_TOKEN, { PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN, PQL_INTEGER_TOKEN } },
        { PQL_CLOSE_BRACKET_TOKEN, { PQL_PATTERN_TOKEN } }
};

StmtStmtParserState::StmtStmtParserState(PQLParserContext &parserContext) :
RelationshipParserState(parserContext, false),
isSuccess(false) {}

void StmtStmtParserState::checkIsStmtSynonym(const std::string &synonym) {
    auto synType = parserContext.checkValidSynonym(synonym);
    if (stmtEntities.find(synType) != stmtEntities.end()) {
        throw QPSSemanticError(QPS_SEMANTIC_ERR_NOT_STMT_SYN);
    }
}

void StmtStmtParserState::handleToken() {
    while (!this->tokenStream.isTokenStreamEnd()) {
        auto& curr = tokenStream.getCurrentToken();

        if (curr.getType() == PQL_NAME_TOKEN) {
            RelationshipParserState::processNameToken(curr);
        }

        if (!PQLParserUtils::isExpectedToken(predictiveMap, prev, curr.getType())) {
            throw QPSSyntaxError(QPS_TOKENIZATION_ERR + curr.getValue());
        }

        switch (curr.getType()) {
            case PQL_STMT_STMT_TOKEN:
                relationship = curr.getValue();
            case PQL_COMMA_TOKEN:
                break;
            case PQL_OPEN_BRACKET_TOKEN:
                isInBracket = true;
                break;
            case PQL_CLOSE_BRACKET_TOKEN:
                isInBracket = false;
                isSuccess = checkSafeExit(arguments);
                parserContext.addClause(make_unique<SuchThatClause>(
                        getAbstractionType(relationship, stmtStmtKeywordToAbstraction),
                        std::move(arguments.at(0)),
                        std::move(arguments.at(1))
                ));
                break;
            case PQL_SYNONYM_TOKEN:
                checkIsStmtSynonym(curr.getValue());
                arguments.push_back(std::move(std::make_unique<SynonymArg>(curr.getValue())));
                break;
            case PQL_INTEGER_TOKEN:
                arguments.push_back(std::move(std::make_unique<Integer>(curr.getValue())));
                break;
            case PQL_WILDCARD_TOKEN:
                arguments.push_back(std::move(std::make_unique<Wildcard>()));
                break;
            case PQL_PATTERN_TOKEN:
                this->parserContext.transitionTo(make_unique<PatternParserState>(parserContext));
                return;
            default:
                throw QPSSyntaxError(QPS_TOKENIZATION_ERR + curr.getValue());
        }
        this->prev = curr.getType();
        tokenStream.next();
    }
    if (!isSuccess) {
        throw QPSSyntaxError(QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT);
    }
}
