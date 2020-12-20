//Copyright 2020 xaxaxaxa232@mail.ru

#include "header.hpp"

string getName(const json& object){
  return object.get<string>();
}

any getGroup(const json& object){
  if (object.is_string())
    return object.get<string>();
  else
    return object.get<int>();
}

any getAvg(const json& object){
  if (object.is_string())
    return object.get<string>();
  else if (object.is_number_integer())
    return object.get<int>();
  else
    return object.get<double>();
}

any getDebt(const json& object){
  if (object.is_null())
    return nullptr;
  else if (object.is_string())
    return object.get<string>();
  else
    return object.get<vector<string>>();
}

string getString(any object){
  if (object.type() == typeid(nullptr_t))
    return "null";
  else if (object.type() == typeid(string))
    return any_cast<string>(object);
  else if (object.type() == typeid(int)) {
    stringstream convector;
    convector << any_cast<int>(object);
    return convector.str();
  }
  else if (object.type() == typeid(double )) {
    stringstream convector;
    convector << any_cast<double>(object);
    return convector.str();
  }
  else {
    stringstream convector;
    convector << any_cast<vector<string>>(object).size() << "items";
    return convector.str();
  }
}

vector<Student> Student::ParseF(const string& jsonObject){
  ifstream  fileJson(jsonObject);

  if (!fileJson){
    throw runtime_error{"File can't be open."};
  }

  json youFile;
  fileJson >> youFile;
  fileJson.close();

  if (!(youFile["items"].is_array())){
    throw runtime_error{R"("File items is not array!)"};
  }
  if (youFile["items"].size() != (youFile["_meta"])["count"]){
    throw runtime_error{R"(File items is incorrect, check _meta)"};
  }

  vector<Student> vectorStud;

  for (const auto& student : youFile["items"]){
    string name_ = getName(student["name"]);
    any group_ = getGroup(student["group"]);
    any avg_ = getAvg(student["avg"]);
    any debt_ = getDebt(student["debt"]);

    vectorStud.emplace_back(name_, group_, avg_, debt_);
  }
  return vectorStud;
}

vector<Student> Student::ParseS(string jsonString){
  json youString = json::parse(jsonString);

  if (!(youString["items"].is_array())){
    throw runtime_error{R"("File items is not array!)"};
  }
  if (youString["items"].size() != (youString["_meta"])["count"]){
    throw runtime_error{R"(File items is incorrect, check _meta)"};
  }

  vector<Student> vectorStud;

  for (const auto& student : youString["items"]){
    string name_ = getName(student["name"]);
    any group_ = getGroup(student["group"]);
    any avg_ = getAvg(student["avg"]);
    any debt_ = getDebt(student["debt"]);

    vectorStud.emplace_back(name_, group_, avg_, debt_);
  }
  return vectorStud;
}

void Student::Print(const vector<Student>& students, ostream& ss) {
  vector<size_t>length (4, 0);

  for (const auto& student : students){
    if (student.name.length() > length[0])
    length[0] = student.name.length();
    if (getString(student.group).length() > length[1])
      length[1] = getString(student.group).length();
    if (getString(student.avg).length() > length[2])
      length[2] = getString(student.avg).length();
    if (getString(student.debt).length() > length[3])
      length[3] = getString(student.debt).length();
  }

  string symbol;
  for (size_t i : length){
    symbol += "|-";
    for (size_t j = 0; j < i; ++j){
      symbol += "-";
    }
  }
  symbol += "|";

  ss << "| " << left << setw(length[0]) << "name";
  ss << "| " << left << setw(length[1]) << "group";
  ss << "| " << left << setw(length[2]) << "avg";
  ss << "| " << left << setw(length[3]) << "debt" << "|" << endl;
  ss << right << symbol <<endl;

  for (const auto &student:students){
    ss << "| " << left << setw(length[0]) << student.name;
    ss << "| " << left << setw(length[1]) << getString(student.group);
    ss << "| " << left << setw(length[2]) << getString(student.avg);
    ss << "| " << left << setw(length[3]) << getString(student.debt)
    << "|" << endl;
    ss << right << symbol <<endl;
  }
  }
