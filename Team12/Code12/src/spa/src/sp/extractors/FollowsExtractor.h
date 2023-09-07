#pragma once

#include "Extractor.h"

class FollowsExtractor : public Extractor {

public:
    explicit FollowsExtractor(PkbWriter *pkbWriter);
};
