#include <string>
#include "SynonymArg.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

string SynonymArg::getValue() {
	return synonymValue;
}

QPSStringUtils::ArgumentType SynonymArg::getArgumentType() {
	return argumentType;
}

bool SynonymArg::isSynonym() {
	return true;
}

bool SynonymArg::operator==(const IArgument& other) const {
    const auto* otherSynonym = dynamic_cast<const SynonymArg*>(&other);
    if (!otherSynonym) return false;

    return this->synonymValue == otherSynonym->synonymValue;
}
