#include "SpTokenizer.h"

std::unique_ptr<TokenStream<SpToken>> SpTokenizer::tokenize(std::string fileContents) {
    // Set language specifications here
    std::unique_ptr<ITokenHandler<SpToken>> nameTokenizer = std::make_unique<SpNameTokenizer>();
    std::unique_ptr<ITokenHandler<SpToken>> integerTokenizer = std::make_unique<SpIntegerTokenizer>();
    std::unique_ptr<ITokenHandler<SpToken>> termOpTokenizer = std::make_unique<SpTermOpTokenizer>();
    std::unique_ptr<ITokenHandler<SpToken>> exprOpTokenizer = std::make_unique<SpExprOpTokenizer>();
    std::unique_ptr<ITokenHandler<SpToken>> relOpTokenizer = std::make_unique<SpRelOpTokenizer>(); // must be above cond and delim because of '!='
    std::unique_ptr<ITokenHandler<SpToken>> condOpTokenizer = std::make_unique<SpCondOpTokenizer>();
    // ORDER MATTERS
    std::unique_ptr<ITokenHandler<SpToken>> delimTokenizer = std::make_unique<SpDelimiterTokenizer>();

    // Construct pipeline
    nameTokenizer->setNext(std::move(integerTokenizer))
            .setNext(std::move(termOpTokenizer))
            .setNext(std::move(exprOpTokenizer))
            .setNext(std::move(relOpTokenizer))
            .setNext(std::move(condOpTokenizer))
            .setNext(std::move(delimTokenizer));
    InputStream inputStream = InputStream(std::move(fileContents));
    return TokenStream<SpToken>::initialize(inputStream, *nameTokenizer);
}
