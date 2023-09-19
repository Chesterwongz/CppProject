#include "SourceProcessor.h"

void SourceProcessor::process(const std::string &filePath, PKBWriter *pkbWriter) {
    std::string fileContent = FileReaderUtils::readFile(filePath);
    std::optional<std::unique_ptr<TNode>> abstractSyntaxTree =
            ProgramParser(std::move(std::make_shared<ParserContext>(std::move(fileContent)))).parse();

    if (!abstractSyntaxTree.has_value()) {
        throw SpException("Failed to parse input");
    }
    TNode& root = *abstractSyntaxTree.value();
    SemanticValidator semanticValidator;
    semanticValidator.validate(root);
    DesignExtractor designExtractor(pkbWriter);
    designExtractor.extract(root);
}
