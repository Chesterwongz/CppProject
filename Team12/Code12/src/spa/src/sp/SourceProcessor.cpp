#include "SourceProcessor.h"

void SourceProcessor::process(const std::string &filePath, PKBWriter *pkbWriter) {
    std::string fileContent = FileReaderUtils::readFile(filePath);
    std::optional<std::unique_ptr<TNode>> abstractSyntaxTree =
            ProgramParser(std::move(std::make_shared<ParserContext>(std::move(fileContent)))).parse();
    DesignExtractor designExtractor(pkbWriter);
    if (abstractSyntaxTree.has_value()) {
        designExtractor.extract(abstractSyntaxTree.value().get());
    }
}
