#include <stdexcept>
#include "ArgParser.h"


namespace ArgumentParser{

ArgParser::ArgParser(std::string program_name)
    : program_name_(program_name), help_requested_(false) {
}

ArgParser::ArgParser(char short_name, const std::string name)
    : program_name_(name), help_requested_(false) {
}

ArgParser::ArgParser()
    : help_requested_(false) {
}

ArgParser::~ArgParser() {
}


ArgParser& ArgParser::AddStringArgument(const std::string& long_name, const std::string& description) {
  Argument arg;
  arg.long_name = long_name;
  arg.short_name = '\0'; // Отсутствие короткого имени
  arg.description = description;
  arg.is_flag = false;
  arg.is_set = false;

  arguments_.push_back(arg);

  return *this;
}

ArgParser& ArgParser::AddStringArgument(char short_name, const std::string& long_name, const std::string& description) {
  Argument arg;
  arg.long_name = long_name;
  arg.short_name = short_name;
  arg.description = description;
  arg.is_flag = false;
  arg.is_set = false;

  arguments_.push_back(arg);

  return *this;
}

ArgParser& ArgParser::AddIntArgument(const std::string& long_name, const std::string& description) {
  Argument arg;
  arg.long_name = long_name;
  arg.short_name = '\0'; // Отсутствие короткого имени
  arg.description = description;
  arg.is_flag = false;
  arg.is_set = false;

  arguments_.push_back(arg);

  return *this;
}

ArgParser& ArgParser::AddIntArgument(char short_name, const std::string& long_name, const std::string& description) {
  Argument arg;
  arg.long_name = long_name;
  arg.short_name = short_name;
  arg.description = description;
  arg.is_flag = false;
  arg.is_set = false;

  arguments_.push_back(arg);

  return *this;
}

ArgParser& ArgParser::AddFlag(char short_name, const std::string& long_name, const std::string& description) {
  Argument arg;
  arg.long_name = long_name;
  arg.short_name = short_name;
  arg.description = description;
  arg.is_flag = true;
  arg.is_set = false;

  arguments_.push_back(arg);

  return *this;
}

ArgParser& ArgParser::StoreValue(std::string& value) {
  for (auto& arg : arguments_) {
    if (!arg.is_flag && arg.value_str == nullptr) {
      arg.value_str = &value;
      return *this;
    }
  }
  throw std::logic_error("No string argument to store value in.");
}

ArgParser& ArgParser::StoreValues(std::vector<int>& values) {
  for (auto& arg : arguments_) {
    if (!arg.is_flag && arg.value_int == nullptr) {
      arg.value_int = &values;
      return *this;
    }
  }
  throw std::logic_error("No integer argument to store values in.");
}

ArgParser& ArgParser::StoreValue(bool& flag) {
  for (auto& arg : arguments_) {
    if (arg.is_flag && arg.value_bool == nullptr) {
      arg.value_bool = &flag;
      return *this;
    }
  }
  throw std::logic_error("No flag argument to store value in.");
}

// Указание, что аргумент может принимать несколько значений
ArgParser& ArgParser::MultiValue(int min_values) {
  if (!arguments_.empty()) {
    arguments_.back().min_values = min_values;
    return *this;
  } else {
    throw std::logic_error("No argument to set multi-value for.");
  }
}

// Установка аргумента как позиционного
ArgParser& ArgParser::Positional() {
  if (!arguments_.empty()) {
    arguments_.back().is_positional = true;
    return *this;
  } else {
    throw std::logic_error("No argument to set as positional.");
  }
}

// Установка значения по умолчанию для строкового аргумента
ArgParser& ArgParser::Default(const std::string& default_value) {
  if (!arguments_.empty() && !arguments_.back().is_flag) {
    arguments_.back().default_value_str = default_value;
    return *this;
  } else {
    throw std::logic_error("No string argument to set default value for.");
  }
}

// Установка булевого значения по умолчанию для флага
ArgParser& ArgParser::Default(bool default_flag) {
  if (!arguments_.empty() && arguments_.back().is_flag) {
    arguments_.back().default_value_bool = default_flag;
    return *this;
  } else {
    throw std::logic_error("No flag argument to set default value for.");
  }
}


}