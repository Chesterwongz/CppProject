#include "SourceProcessor.h"

void SourceProcessor::process(std::string &filePath) {
    try {
        std::string fileContent = FileReaderUtils::readFile(filePath);
        std::unique_ptr<TNode> abstractSyntaxTree = parser.parse(fileContent);
    } catch (const SpException &e) {
        return;
    }
}
