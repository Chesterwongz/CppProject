import re
import sys


def extract_information(txt_content):
    # Split the content using the regex pattern
    sections = re.split(r"^======.*======$", txt_content, flags=re.MULTILINE)

    # Remove any empty sections that might result from the split
    sections = [section.strip() for section in sections if section.strip() != ""]
    number = 0
    test_cases = []
    for section in sections:
        lines = section.split("\n")
        lines[1] = lines[1].replace('\"', '\\\"')
        query_lines = lines[:2]
        results = lines[2].split(", ") if lines[2] != "none" else []
        number += 1
        test_cases.append((number, query_lines, results))
    return test_cases


def generate_cpp_test(test_cases, query_path):
    cpp_tests = []
    for test_case in test_cases:
        number, query_lines, results = test_case
        results_str = ', '.join(['"{}"'.format(res) for res in results]) if results else ""
        cpp_test = f"""TEST_CASE("SP-PKB-QPS {query_path} - {number}") {{
    string query =
        "{query_lines[0]}\\n"
        "{query_lines[1]}";
    SourceProcessor sp;
    PKB pkb;
    sp.processContent(source, pkb.getWriter());
    QPS qps(pkb.getReader());
    auto result = qps.processQueryString(query);
    set<string> expected = {{{results_str}}};
    REQUIRE(result == expected);
}}\n"""
        cpp_tests.append(cpp_test)
    return "\n".join(cpp_tests)


def process_source_file(filepath):
    source = "string source = \n"
    with open(filepath, "r") as source_file:
        for line in source_file:
            stripped_line = line.rstrip()
            quoted_line = f'    "{stripped_line}"'
            source += quoted_line + "\n"
    return source[:-1] + ";\n\n"


def process_files(source_path, query_path, dest_path):
    with open(query_path, "r") as file:
        content = file.read()
        formatted_test_cases = extract_information(content)
        formatted_cpp_tests = generate_cpp_test(formatted_test_cases, query_path)
        prefix = """#include <catch.hpp>
#include "sp/SourceProcessor.h"
#include "pkb/facade/PKB.h"
#include "qps/QPS.h"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <map>
#include <set>

using std::string, std::unordered_map,std::map, std::unordered_set, std::set, std::vector, std::pair;
        
"""
        source_code = process_source_file(source_path)
        with open(f"src/integration_testing/src/sp_pkb_qps/{dest_path}", "w") as out_file:
            out_file.write(prefix)
            out_file.write(source_code)
            out_file.write(formatted_cpp_tests)


if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("Usage: tests/convertAutotesterToIT.py <source_file> <query_file> <destination_file>\n"
              "e.g. tests/convertAutotesterToIT.py "
              "tests/Milestone1/SingleClauseTests/Follows_source.txt "
              "tests/Milestone1/SingleClauseTests/Follows_queries.txt "
              "TestFollows.cpp ")
        sys.exit(1)

    source_filename = sys.argv[1]
    query_filename = sys.argv[2]
    destination_filename = sys.argv[3]
    process_files(source_filename, query_filename, destination_filename)
