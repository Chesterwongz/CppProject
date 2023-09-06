#include "ProgramParser.h"

ProgramParser::ProgramParser(std::string &filePath) {
    std::string fileContent = FileReaderUtils::readFile(filePath);
    // Set language specifications here
    std::unique_ptr<ITokenizer> nameTokenizer = std::make_unique<NameTokenizer>();
    std::unique_ptr<ITokenizer> integerTokenizer = std::make_unique<IntegerTokenizer>();
    // Construct pipeline
    nameTokenizer->setNext(std::move(integerTokenizer));
    tokenStream = std::make_shared<TokenStream>(fileContent, std::move(nameTokenizer));
};

std::unique_ptr<TNode> ProgramParser::parse() {
    // TODO
    return std::make_unique<TNode>(TNodeType::TNODE_PROGRAM);
}
