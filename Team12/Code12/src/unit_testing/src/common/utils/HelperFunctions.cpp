#include "HelperFunctions.h"

unordered_set<string> convertStringVectorToUnorderedSet(
    const vector<string>& stringVector) {
  return {stringVector.begin(), stringVector.end()};
}
