#include "TokenizerFactory.h"

unique_ptr<PQLTokenizer> TokenizerFactory::makeTokenizer(const string& query) {
    return make_unique<PQLTokenizer>(query);
}
