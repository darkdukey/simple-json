#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <cassert>
#include <list>
#include <set>
#include <unordered_map>

#include "json98.h"

using namespace json98;
using namespace std;

// Check that Json has the properties we want.
#include <type_traits>
#define CHECK_TRAIT(x) static_assert(std::x::value, #x)
CHECK_TRAIT(is_nothrow_constructible<Json>);
CHECK_TRAIT(is_nothrow_default_constructible<Json>);
CHECK_TRAIT(is_copy_constructible<Json>);
// CHECK_TRAIT(is_nothrow_move_constructible<Json>);
CHECK_TRAIT(is_copy_assignable<Json>);
// CHECK_TRAIT(is_nothrow_move_assignable<Json>);
CHECK_TRAIT(is_nothrow_destructible<Json>);

void log(const string& msg) {
    cout << msg << endl;
}

void parse_from_stdin() {
    string buf;
    string line;
    while (std::getline(std::cin, line)) {
        buf += line + "\n";
    }

    auto json = Json::parse(buf);
    if (json.is_valid()) {
        printf("Result: %s\n", json.dump().c_str());
    } else {
        printf("Invalid json\n");
    }
}

int main(int argc, char **argv) {
    if (argc == 2 && argv[1] == string("--stdin")) {
        parse_from_stdin();
        return 0;
    }

    log("===== Test Parsing =====");

    const string simple_test =
        R"({"k1":"v1", "k2":42, "k3":3.14159, "k4":["a",123,true,false,null]})";

    auto json = Json::parse(simple_test);

    std::cout << "k1: " << json["k1"].string_value() << "\n";
    std::cout << "k2: " << json["k2"].int_value() << "\n";
    std::cout << "k3: " << json["k3"].float_value() << "\n";
    std::cout << "k4: " << json["k4"].dump() << "\n";

    for (auto &k : json["k3"].array_items()) {
        std::cout << "    - " << k.dump() << "\n";
    }

    log("===== Test New line =====");

// Line break test
    const string json_with_newline = 
        R"({"k1":"This is line 1 \n this is line 2"})";

    auto new_line = Json::parse(json_with_newline);

    if (new_line.is_valid()) {
        std::cout << new_line.dump() << std::endl;
        std::cout << new_line["k1"].string_value() << std::endl;
    } else {
        std::cout << "Invalid json" << std::endl;
    }


    std::cout << "===== Test Unicode =====" << std::endl;

// Unicode test
    const string unicode_escape_test =
        R"([ "blah\ud83d\udca9blah\ud83dblah\udca9blah\u0000blah\u1234" ])";

    const char utf8[] = "blah" "\xf0\x9f\x92\xa9" "blah" "\xed\xa0\xbd" "blah"
                        "\xed\xb2\xa9" "blah" "\0" "blah" "\xe1\x88\xb4";

    Json uni = Json::parse(unicode_escape_test);
    assert(uni[0].string_value().size() == (sizeof utf8) - 1);
    assert(std::memcmp(uni[0].string_value().data(), utf8, sizeof utf8) == 0);

// Test create json

    log("===== Test Json creation =====");
    Json create_json;
    create_json["string_value"] = "this is a string value \n and a new line";
    create_json["float_value"] = 3.1415926;
    create_json["int_value"] = 123456;
    create_json["bool_value"] = true;
    // create_json["array_value"] = {1, 2, 3, 4};

    log(create_json.dump());

// Comment support

// Array support
    // std::list<int> l1 { 1, 2, 3 };
    // std::vector<int> l2 { 1, 2, 3 };
    // std::set<int> l3 { 1, 2, 3 };
    // assert(Json(l1) == Json(l2));
    // assert(Json(l2) == Json(l3));

// Compare support
    // std::map<string, string> m1 { { "k1", "v1" }, { "k2", "v2" } };
    // std::map<string, string> m2 { { "k1", "v1" }, { "k2", "v2" } };
    // assert(Json(m1) == Json(m2));

// Serialization
    // class Point {
    // public:
    //     int x;
    //     int y;
    //     Point (int x, int y) : x(x), y(y) {}
    //     Json to_json() const { return Json::array { x, y }; }
    // };

    // std::vector<Point> points = { { 1, 2 }, { 10, 20 }, { 100, 200 } };
    // std::string points_json = Json(points).dump();
    // printf("%s\n", points_json.c_str());
}
