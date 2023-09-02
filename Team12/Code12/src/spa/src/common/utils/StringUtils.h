#include <algorithm>
#include <cctype>
#include <regex>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <utility>

using std::string;
using std::stringstream;

class StringUtils {
public:
    static const char CHAR_NEWLINE;
    static const char CHAR_SPACE;
    static const char CHAR_ZERO;
    static const string STRING_NEWLINE;

    static bool isNumeric(const string &str);
    static bool isName(const string &str);
    static bool isInteger(const string &str);

private:
    StringUtils() = default;
};
