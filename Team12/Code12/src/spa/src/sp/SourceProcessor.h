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

class SourceProcessor : public ISourceProcessor {
public:
    void process(const std::string &fileName) override;
};