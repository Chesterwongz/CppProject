#include "HelperFunctions.h"

unordered_set<std::pair<std::string, std::string>> convertStringVectorToUnorderedSet(
    const vector<std::pair<std::string, std::string>>& stringVector) {
  return {stringVector.begin(), stringVector.end()};
}
