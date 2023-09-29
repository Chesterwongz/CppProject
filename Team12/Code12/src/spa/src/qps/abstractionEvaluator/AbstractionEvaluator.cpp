#include "AbstractionEvaluator.h"

IntermediateTable AbstractionEvaluator::evaluate(BaseAbstraction &abstraction) {
    switch (abstraction.getAbstractionPermutation()) {
        case (ArgumentPermutation::SYNONYM_SYNONYM):
            return abstraction.evaluateSynonymSynonym();

        case (ArgumentPermutation::SYNONYM_INTEGER):
            return abstraction.evaluateSynonymInteger();

        case (ArgumentPermutation::SYNONYM_IDENT):
            return abstraction.evaluateSynonymIdent();

        case (ArgumentPermutation::SYNONYM_WILDCARD):
            return abstraction.evaluateSynonymWildcard();

        case (ArgumentPermutation::INTEGER_SYNONYM):
            return abstraction.evaluateIntegerSynonym();

        case (ArgumentPermutation::INTEGER_INTEGER):
            return abstraction.evaluateIntegerInteger();

        case (ArgumentPermutation::INTEGER_IDENT):
            return abstraction.evaluateIntegerIdent();

        case (ArgumentPermutation::INTEGER_WILDCARD):
            return abstraction.evaluateIntegerWildcard();

        case (ArgumentPermutation::IDENT_SYNONYM):
            return abstraction.evaluateIdentSynonym();

        case (ArgumentPermutation::IDENT_INTEGER):
            return abstraction.evaluateIdentInteger();

        case (ArgumentPermutation::IDENT_IDENT):
            return abstraction.evaluateIdentIdent();

        case (ArgumentPermutation::IDENT_WILDCARD):
            return abstraction.evaluateIdentWildcard();

        case (ArgumentPermutation::WILDCARD_SYNONYM):
            return abstraction.evaluateWildcardSynonym();

        case (ArgumentPermutation::WILDCARD_INTEGER):
            return abstraction.evaluateWildcardInteger();

        case (ArgumentPermutation::WILDCARD_IDENT):
            return abstraction.evaluateWildcardIdent();

        case (ArgumentPermutation::WILDCARD_WILDCARD):
            return abstraction.evaluateWildcardWildcard();
    }
};
