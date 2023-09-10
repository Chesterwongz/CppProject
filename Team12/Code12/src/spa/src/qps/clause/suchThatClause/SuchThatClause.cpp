#include "SuchThatClause.h"
#include "qps/token/suchThatToken/SuchThatToken.h"

#include <utility>
#include <set>

SuchThatClause::SuchThatClause (
        Abstraction relationship,
        Reference first,
        Reference second) :
        relationship(std::move(relationship)),
        firstArg(first),
        secondArg(second) {}

std::set<int> evaluate(
        Context context,
        PKBReader pkb) {

}



