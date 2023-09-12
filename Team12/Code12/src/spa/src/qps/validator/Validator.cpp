#include "Validator.h"
#include "qps/token/declarativeToken/declarativeToken.h"

bool Validator::validateTokens(TokenStream& queryTokenVector) {
//    for (int i = 0; i < queryTokenVector.size(); i++) {
//        QueryToken* queryToken = (queryTokenVector[i]).get();
//
//        if (DeclarativeToken* declarativeToken = dynamic_cast<DeclarativeToken*>(queryToken)) {
//            string synonym = declarativeToken->getSynonym();
//            if (declarativeTokensMap.find(synonym) == declarativeTokensMap.end()) {
//                declarativeTokensMap.insert({synonym, declarativeToken});
//            } else {
//                throw std::runtime_error("Cannot reuse synonyms");
//            }
//        } else {
//
//        }
//    }
    return true;
}
