#include "StmtVarParserState.h"

unordered_map<string, Abstraction>
    StmtVarParserState::stmtVarKeywordToAbstraction = {
        { USES_ABSTRACTION, USES_ENUM },
        { MODIFIES_ABSTRACTION, MODIFIES_ENUM }
};

PredictiveMap StmtVarParserState::predictiveMap = {
        { PQL_NULL_TOKEN, { PQL_STMT_VAR_TOKEN } },
        { PQL_STMT_VAR_TOKEN, { PQL_OPEN_BRACKET_TOKEN } },
        { PQL_OPEN_BRACKET_TOKEN, { PQL_SYNONYM_TOKEN,
                                    PQL_LITERAL_REF_TOKEN,
                                    PQL_INTEGER_TOKEN,
                                    PQL_WILDCARD_TOKEN} },
        { PQL_COMMA_TOKEN, { PQL_SYNONYM_TOKEN, PQL_WILDCARD_TOKEN,
                             PQL_LITERAL_REF_TOKEN } },
        { PQL_SYNONYM_TOKEN, { PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN } },
        { PQL_WILDCARD_TOKEN, { PQL_CLOSE_BRACKET_TOKEN } },
        { PQL_LITERAL_REF_TOKEN, { PQL_COMMA_TOKEN, PQL_CLOSE_BRACKET_TOKEN } },
        { PQL_INTEGER_TOKEN, { PQL_COMMA_TOKEN } },
        { PQL_CLOSE_BRACKET_TOKEN, { PQL_PATTERN_TOKEN } }
};

StmtVarParserState::StmtVarParserState(PQLParserContext &parserContext) :
        RelationshipParserState(parserContext, false),
        isSuccess(false) {}

void StmtVarParserState::checkIsValidSynonym(
    const std::string &synonym, int argumentNumber) {
    auto synType = parserContext.checkValidSynonym(synonym);
    if (argumentNumber == SECOND_ARG && synType != VARIABLE_ENTITY) {
        throw QPSSemanticError(QPS_SEMANTIC_ERR_NOT_VAR_SYN);
    }
}

void StmtVarParserState::checkIsValidWildcard() {
    if (arguments.size() == FIRST_ARG) {
        throw QPSSemanticError(QPS_SEMANTIC_ERR_WILDCARD_FIRSTARG);
    }
}

void StmtVarParserState::checkIsValidIdent(const string& ref) {
    if (!QPSStringUtils::isIdentValue(ref)) {
        throw QPSSyntaxError(QPS_TOKENIZATION_ERR_IDENT);
    }
}

void StmtVarParserState::handleToken() {
    while (!this->tokenStream.isTokenStreamEnd()) {
        auto& curr = tokenStream.getCurrentToken();

        if (curr.getType() == PQL_NAME_TOKEN) {
            processNameToken(curr);
        }

        if (!PQLParserUtils::isExpectedToken(
                predictiveMap, prev, curr.getType())) {
            throw QPSSyntaxError(QPS_TOKENIZATION_ERR + curr.getValue());
        }

        switch (curr.getType()) {
            case PQL_STMT_VAR_TOKEN:
                relationship = curr.getValue();
            case PQL_COMMA_TOKEN:
                break;
            case PQL_OPEN_BRACKET_TOKEN:
                isInBracket = true;
                break;
            case PQL_CLOSE_BRACKET_TOKEN:
                isInBracket = false;
                isSuccess = checkSafeExit(arguments);
                parserContext.addClause(std::make_unique<SuchThatClause>(
                        getAbstractionType(relationship,
                                       stmtVarKeywordToAbstraction),
                        std::move(arguments.at(0)),
                        std::move(arguments.at(1))
                ));
                break;
            case PQL_SYNONYM_TOKEN:
                checkIsValidSynonym(curr.getValue(), arguments.size());
                arguments.push_back(
                    std::move(std::make_unique<SynonymArg>(curr.getValue())));
                break;
            case PQL_WILDCARD_TOKEN:
                checkIsValidWildcard();
                arguments.push_back(
                    std::move(std::make_unique<Wildcard>()));
                break;
            case PQL_LITERAL_REF_TOKEN:
                checkIsValidIdent(curr.getValue());
                arguments.push_back(
                    std::move(std::make_unique<Ident>(curr.getValue())));
                break;
            case PQL_INTEGER_TOKEN:
                arguments.push_back(
                    std::move(std::make_unique<Integer>(curr.getValue())));
                break;
            case PQL_PATTERN_TOKEN:
                this->parserContext.transitionTo(
                    std::make_unique<PatternParserState>(parserContext));
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
