#include "SourceProcessor.h"

void SourceProcessor::process(const std::string &filePath, PKBWriter &pkbWriter) {
    std::string fileContent = FileReaderUtils::readFile(filePath);
    processContent(fileContent, pkbWriter);
}

void SourceProcessor::processContent(const std::string& fileContent, PKBWriter &pkbWriter) {
    std::optional<std::unique_ptr<TNode>> abstractSyntaxTree =
        ProgramParser(std::move(std::make_shared<ParserContext>(fileContent))).parse();

    if (!abstractSyntaxTree.has_value()) {
        throw SpException("Failed to parse input");
    }
    TNode& root = *abstractSyntaxTree.value();
    SemanticValidator semanticValidator;
    semanticValidator.validate(root);
    DesignExtractor designExtractor(pkbWriter);
    designExtractor.extract(root);
}
