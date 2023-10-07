// TEMP_CATCH_INCLUDE

void require(bool b) { REQUIRE(b); }

TEST_CASE("1st Test") { require(1 == 1); }
