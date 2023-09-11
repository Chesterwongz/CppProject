#include "Tokenizer.h"
#include "sp/tokenizer/handlers/RelOpTokenizer.h"
#include "sp/tokenizer/handlers/CondOpTokenizer.h"

std::unique_ptr<TokenStream> Tokenizer::tokenize(std::string fileContent) {
    // Set language specifications here
    std::unique_ptr<ITokenHandler> nameTokenizer = std::make_unique<NameTokenizer>();
    std::unique_ptr<ITokenHandler> integerTokenizer = std::make_unique<IntegerTokenizer>();
    std::unique_ptr<ITokenHandler> termOpTokenizer = std::make_unique<TermOpTokenizer>();
    std::unique_ptr<ITokenHandler> exprOpTokenizer = std::make_unique<ExprOpTokenizer>();
    std::unique_ptr<ITokenHandler> relOpTokenizer = std::make_unique<RelOpTokenizer>(); // must be above cond and delim because of '!='
    std::unique_ptr<ITokenHandler> condOpTokenizer = std::make_unique<CondOpTokenizer>();
    // ORDER MATTERS
    std::unique_ptr<ITokenHandler> delimTokenizer = std::make_unique<DelimiterTokenizer>();

    // Construct pipeline
    nameTokenizer
        ->setNext(std::move(integerTokenizer))
        ->setNext(std::move(termOpTokenizer))
        ->setNext(std::move(exprOpTokenizer))
        ->setNext(std::move(relOpTokenizer))
        ->setNext(std::move(condOpTokenizer))
        ->setNext(std::move(delimTokenizer));
    return std::make_unique<TokenStream>(std::move(fileContent), std::move(nameTokenizer));
}
