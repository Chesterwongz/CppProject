#pragma once

#include "Extractor.h"

class ModifiesExtractor : public Extractor {
public:
    explicit ModifiesExtractor(PkbWriter *pkbWriter);
};
