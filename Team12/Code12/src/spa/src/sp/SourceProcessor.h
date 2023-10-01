#pragma once

#include <optional>
#include <string>
#include "ISourceProcessor.h"
#include "SourceProcessor.h"
#include "sp/exceptions/SpException.h"
#include "sp/utils/FileReaderUtils.h"
#include "sp/parser/IParser.h"
#include "sp/parser/toplevelparsers/ProgramParser.h"
#include "sp/tokenizer/SpTokenizer.h"
#include "sp/extractors/DesignExtractor.h"
#include "sp/validator/SemanticValidator.h"

class SourceProcessor : public ISourceProcessor {
private:
    SemanticValidator semanticValidator;

public:
    SourceProcessor(): semanticValidator() {};
    void process(const std::string &fileName, PKBWriter &pkbWriter) override;
    void processContent(const std::string& fileContent, PKBWriter &pkbWriter);
};