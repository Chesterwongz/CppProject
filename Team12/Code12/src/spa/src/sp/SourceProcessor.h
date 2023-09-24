#pragma once

#include <optional>
#include <string>
#include "ISourceProcessor.h"
#include "SourceProcessor.h"
#include "sp/exceptions/SpException.h"
#include "sp/utils/FileReaderUtils.h"
#include "sp/parser/IParser.h"
#include "sp/parser/toplevelparsers/ProgramParser.h"
#include "sp/tokenizer/Tokenizer.h"
#include "sp/extractors/DesignExtractor.h"
#include "sp/validator/SemanticValidator.h"

class SourceProcessor : public ISourceProcessor {
public:
    explicit SourceProcessor() = default;;
    void process(const std::string &fileName, PKBWriter &pkbWriter) override;
    void processContent(const std::string& fileContent, PKBWriter &pkbWriter);
};