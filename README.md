#Simple Json

[![Build Status](https://travis-ci.org/darkdukey/simple-json.svg?branch=master)](https://travis-ci.org/darkdukey/simple-json)

Simple Json is a json library to parse and manipulate json. The goal of this library is to make it super easy to use.

##Usage

### Parse Json

```cpp
const string json_string = R"({"name":"Nice Guy", "age":42})";

Json json = Json::parse(json_string);
```

### Access value
```cpp
json["name"].string_value();
json["age"].int_value();
```

### Create Json
```cpp
Json json;
json["name"] = "Nice Guy";
json.dump();
```

###

Check out the [test cases](https://github.com/darkdukey/simple-json/blob/master/test.cpp) for more samples.

##Links
Simple Json is heavily inspired by [json11](https://github.com/dropbox/json11)