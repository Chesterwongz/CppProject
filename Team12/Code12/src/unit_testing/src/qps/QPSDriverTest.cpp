// #include <string>
// #include <unordered_set>
//
// // TEMP_CATCH_INCLUDE
//
// #include "pkb/facade/PKBReader.h"
// #include "qps/QPS.h"
//
// TEST_CASE("Test QPS Driver") {
//    std::string query = "assign n;\nSelect n";
//    PKBReader pkb = PKBReader();
//    QPS driver = QPS(&pkb);
//
//    std::unordered_set<int> res = driver.processQueryString(query);
//
//    std::unordered_set<int> ans = {1,2,3};
//    bool check = res.size() == ans.size();
//
//    for (const auto& elem : res) {
//        if (ans.find(elem) == ans.end()) {
//            check = false;
//            break;
//        }
//    }
//
//    REQUIRE(check);
//}
