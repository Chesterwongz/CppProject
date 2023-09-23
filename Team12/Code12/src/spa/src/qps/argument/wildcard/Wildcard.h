#pragma once

#include <string>

#include "qps/argument/IArgument.h"
#include "common/utils/StringUtils.h"
using std::string;

class Wildcard : public IArgument {
private:
	const QPSStringUtils::ArgumentType argumentType = QPSStringUtils::WILDCARD;
	string wildcardValue = StringUtils::WILDCARD;

public:
	explicit Wildcard() = default;
	string getValue() override;
	QPSStringUtils::ArgumentType getArgumentType() override;
	bool isIdent() override;
	bool isInteger() override;
	bool isSynonym() override;
	bool isWildcard() override;
    bool operator==(const IArgument& other) const override;
};
