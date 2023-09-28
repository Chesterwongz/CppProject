#pragma once

#include <string>

#include "qps/argument/IArgument.h"
#include "common/utils/StringUtils.h"
#include "qps/common/Keywords.h"

using std::string;

class Wildcard : public IArgument {
private:
	const QPSStringUtils::ArgumentType argumentType = QPSStringUtils::WILDCARD;
	string wildcardValue = WILDCARD_KEYWORD;

public:
	explicit Wildcard() = default;
	string getValue() override;
	QPSStringUtils::ArgumentType getArgumentType() override;
	bool isWildcard() override;
    bool operator==(const IArgument& other) const override;
};
