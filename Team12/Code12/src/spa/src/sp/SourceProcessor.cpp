#include "SourceProcessor.h"
#include "sp/tokenizer/handlers/NameTokenizer.h"

void SourceProcessor::process(std::string &filePath) {
    try {
        std::unique_ptr<TNode> abstractSyntaxTree = ProgramParser(filePath).parse();
        // TODO: DesignExtractor
    } catch (const SpException &e) {
        return;
    }
}
