//#include "QueryTokenLL.h"
//
//QueryTokenLL::QueryTokenLL(TokenList *tokens) {
//    this->tokens = tokens;
//    currIndex = 0;
//    linkedListSize = tokens->size();
//}
//
//const bool QueryTokenLL::isEndOfLL() {
//    return currIndex >= linkedListSize;
//}
//
//const QueryToken *QueryTokenLL::getCurrentToken() {
//    if (isEndOfLL()) {
//        return nullptr;
//    }
//
//    return &tokens->at(currIndex);
//}
//
//const void QueryTokenLL::next() {
//    if (!isEndOfLL()) {
//        currIndex++;
//    }
//}
