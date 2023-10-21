#include "SourceProcessor.h"

void SourceProcessor::process(const std::string &filePath,
                              PKBWriter &pkbWriter) {
  std::string fileContent = FileReaderUtils::readFile(filePath);
  processContent(fileContent, pkbWriter);
}

void SourceProcessor::processContent(const std::string &fileContent,
                                     PKBWriter &pkbWriter) {
  std::shared_ptr<ParserContext> parserContext =
      std::make_shared<ParserContext>(fileContent);
  std::optional<std::unique_ptr<TNode>> abstractSyntaxTree =
      ProgramParser(parserContext)
          .parse();

  if (!parserContext->isEnd() || !abstractSyntaxTree.has_value()) {
    throw SpParsingFailedException();
  }

  TNode &root = *abstractSyntaxTree.value();
  semanticValidator.validate(root);
  DesignExtractor designExtractor(pkbWriter);
  designExtractor.extract(root);
}
