#pragma once

#include <memory>
#include <vector>
#include <string>

#include "qps/tokenFactory/TokenFactory.h"

using std::unique_ptr, std::vector, std::string;

class DeclarativeTokenFactory : public TokenFactory {
private:
    string entityType;

protected:
	const bool isValid(UnvalidatedTokens unvalidatedTokens) override;

public:
    DeclarativeTokenFactory() : entityType("") {}
	TokenStreamPtr createTokens(UnvalidatedTokens unvalidatedTokens) override;
    void setEntityType(const string entity);
};
