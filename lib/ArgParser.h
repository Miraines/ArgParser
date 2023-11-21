#pragma once
#include <string>
#include <vector>

namespace ArgumentParser {

class ArgParser {
 private:

  struct Argument {
    std::string long_name;
    char short_name;
    std::string description;
    std::string* value_str; // Указатель на внешнюю строковую переменную
    std::vector<int>* value_int; // Указатель на внешний вектор целых чисел
    bool* value_bool; // Указатель на внешнюю булеву переменную
    bool is_set;
    bool is_flag;
    bool is_positional; // Показывает, является ли аргумент позиционным
    int min_values; // Минимальное количество значений для аргумента
    std::string default_value_str; // Значение по умолчанию для строкового аргумента
    bool default_value_bool; // Для флагов
    bool is_help;

    // Конструктор по умолчанию для инициализации указателей как nullptr
    Argument() : value_str(nullptr),
                 value_int(nullptr),
                 value_bool(nullptr),
                 is_set(false),
                 is_flag(false),
                 is_positional(false),
                 min_values(0),
                 default_value_bool(false),
                 default_value_str(""), is_help(false) {}
  };

  std::string program_name_;
  std::vector<Argument> arguments_;
  bool help_requested_ = false;
  std::string help_description_;

  Argument* FindArgumentByShortKey(char short_key) {
    for (auto& argument : arguments_) {
      if (argument.short_name == short_key) {
        return &argument;
      }
    }
    return nullptr;
  }

 public:
  ArgParser(std::string name);
  ArgParser(char short_name, std::string name);
  ArgParser();
  ~ArgParser();

  ArgParser& AddStringArgument(const std::string& long_name);
  ArgParser& AddStringArgument(char short_name, const std::string& long_name);
  ArgParser& AddStringArgument(char short_name, const std::string& long_name, const std::string& description);

  ArgParser& AddIntArgument(const std::string& long_name);
  ArgParser& AddIntArgument(char short_name, const std::string& long_name);
  ArgParser& AddIntArgument(const std::string& long_name, const std::string& help_description_);

  ArgParser& AddFlag(char short_name, const std::string& long_name);
  ArgParser& AddFlag(char short_name_second, const std::string& long_name, const std::string& description);
  ArgParser& AddFlag(const std::string long_name_third, const std::string& long_name_);

  //Парсинг аргументов командной строки
  bool Parse(const std::vector<std::string>& args);

  // Установка значения по умолчанию для аргумента
  ArgParser& Default(const char* default_value);
  ArgParser& Default(bool default_flag);

  // Указание, что аргумент может принимать несколько значений
  ArgParser& MultiValue(size_t min_values = 1);

  // Установка аргумента как позиционного
  ArgParser& Positional();

  // Сохранение значения аргумента во внешней переменной
  ArgParser& StoreValue(std::string& value);
  ArgParser& StoreValues(std::vector<int>& values);
  ArgParser& StoreValue(bool& flag);

  // Получение значений аргументов
  std::string GetStringValue(const std::string& arg_name, const std::string& default_value = "") const;
  int GetIntValue(const std::string& arg_name, int default_value = 0) const;
  bool GetFlag(const std::string& arg_name) const;

  ArgParser& AddHelp(char short_name, const std::string& long_name, const std::string& description);
  bool Help() const;
  std::string HelpDescription() const;

  bool CheckArgumentsAfterParsing();
  bool ProcessPositionalArgument(const std::string& arg, size_t& positional_arg_index);
  bool ProcessShortArgument(const std::string& arg);
  bool ProcessLongArgument(const std::string& arg);


  };
}