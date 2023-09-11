#include "SourceProcessor.h"

void SourceProcessor::process(const std::string &filePath) {
    try {
        std::string fileContent = FileReaderUtils::readFile(filePath);
        std::optional<std::unique_ptr<TNode>> abstractSyntaxTree =
                ProgramParser(std::move(std::make_shared<ParserContext>(std::move(fileContent)))).parse();
        if (abstractSyntaxTree.has_value()) {
            designExtractor.extract(abstractSyntaxTree.value().get());
        }
    } catch (const SpException &e) {
        return;
    }
}
