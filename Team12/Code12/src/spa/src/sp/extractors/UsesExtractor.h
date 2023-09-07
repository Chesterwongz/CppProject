#pragma once

#include "Extractor.h"

class UsesExtractor : public Extractor {
public:
    explicit UsesExtractor(PkbWriter *pkbWriter);
};
