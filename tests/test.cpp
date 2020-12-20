//Copyright 2020 xaxaxaxa232@mail.ru

#include <gtest/gtest.h>
#include "header.hpp"

const char inside[] =R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})";
const char error1[] =R"({
   "items": {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
  },
  "_meta": {
    "count": 3
  }
})";

const char error2[] =R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 5
  }
})";

const char table[] = R"(| name         | group | avg | debt  |
|--------------|-------|-----|-------|
| Ivanov Petr  | 1     | 4.25| null  |
|--------------|-------|-----|-------|
| Sidorov Ivan | 31    | 4   | C++   |
|--------------|-------|-----|-------|
| Pertov Nikita| IU8-31| 3.33| 3items|
|--------------|-------|-----|-------|
)";

TEST(Cout, Test1) {
  stringstream stest;
 stest << Student::ParseS(inside);
 EXPECT_EQ(stest.str(), table);
}

TEST(Cout, Test2) {
ofstream jFile;
jFile.open("testFile.json", ios::out);
jFile << inside;
jFile.close();
  stringstream stest;
  stest << Student::ParseF("testFile.json");
  EXPECT_EQ(stest.str(), table);
}

TEST(Error, Test1){
  EXPECT_THROW((Student::ParseS(error1)), runtime_error);
}


TEST(Error, Test2){
  EXPECT_THROW((Student::ParseS(error2)), runtime_error);
}

TEST(Error, Test3) {
  ofstream jFile;
  jFile.open("testFile.json", ios::out);
  jFile << error1;
  jFile.close();
  EXPECT_THROW((Student::ParseF("testFile.json")), runtime_error);
}

TEST(Error, Test4) {
  ofstream jFile;
  jFile.open("testFile.json", ios::out);
  jFile << error2;
  jFile.close();
  EXPECT_THROW((Student::ParseF("testFile.json")), runtime_error);
}

TEST(Error, Test6) {
  EXPECT_THROW((Student::ParseF("fail.json")), runtime_error);
}
