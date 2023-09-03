#pragma once

#include <string>
#include "BaseTokenHandler.h"
#include "common/utils/StringUtils.h"

class NameTokenHandler : public BaseTokenHandler {
public:
    Token handle(std::shared_ptr<TokenStream> tokenStream) override;
};
