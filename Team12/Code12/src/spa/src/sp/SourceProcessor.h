#pragma once

#include <string>
#include "ISourceProcessor.h"
#include "SourceProcessor.h"
#include "sp/exceptions/SpException.h"
#include "sp/utils/FileReaderUtils.h"

class SourceProcessor : public ISourceProcessor {
public:
    void process(std::string &fileName) override;
};