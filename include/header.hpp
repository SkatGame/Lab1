//Copyright 2020 xaxaxaxa232@mail.ru

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <any>
#include <utility>
#include <vector>
#include <ostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::any;
using std::cin;
using std::ifstream;
using std::ostream;
using std::stringstream;
using std::any_cast;
using std::setw;
using std::left;
using std::right;
using std::runtime_error;
using std::move;
using std::ofstream;
using std::ios;
using std::nullptr_t;
using json = nlohmann::json;

struct Student {
 public:
  Student(string name_, any group_, any avg_, any debt_){
    name = move(name_);
    group = move(group_);
    avg = move(avg_);
    debt = move(debt_);
  }
  static vector<Student> ParseF(const string& jsonObject);
  static vector<Student> ParseS(string jsonString);
  static void Print(const vector<Student>& students, ostream& info);

 private:
  string name;
  any group;
  any avg;
  any debt;
};

string getName(const json& object);
any getGroup(const json& object);
any getAvg(const json& object);
any getDebt(const json& object);
string getString(any object);

#endif // INCLUDE_HEADER_HPP_
