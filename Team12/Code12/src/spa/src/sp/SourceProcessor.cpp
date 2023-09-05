#include "SourceProcessor.h"
#include "sp/tokenizer/handlers/NameTokenizer.h"

void SourceProcessor::process(std::string &filePath) {
    try {
        std::string fileContent = FileReaderUtils::readFile(filePath);
        // Set language specifications here
        std::unique_ptr<ITokenizer> nameTokenizer = std::make_unique<NameTokenizer>();
        std::unique_ptr<ITokenizer> integerTokenizer = std::make_unique<IntegerTokenizer>();
        // Construct pipeline
        std::shared_ptr<TokenStream> tokenStream
                = std::make_shared<TokenStream>(fileContent, std::move(nameTokenizer));
        std::unique_ptr<IParser> parser = std::make_unique<ProgramParser>(std::move(tokenStream));
        std::unique_ptr<TNode> abstractSyntaxTree = parser->parse();
        // TODO: DesignExtractor
    } catch (const SpException &e) {
        return;
    }
}
