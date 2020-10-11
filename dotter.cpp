#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <locale>
#include <cstdlib>

std::map<wchar_t, std::vector<wchar_t>> substitution_map {
  {'a', {L'a', L'á'}},
  {'e', {L'e', L'é'}},
  {'i', {L'i', L'í'}},
  {'o', {L'o', L'ó' ,L'ö', L'ő'}},
  {'u', {L'u', L'ú', L'ü', L'ű'}},
  {'A', {L'A', L'Á'}},
  {'E', {L'E', L'É'}},
  {'I', {L'I', L'Í'}},
  {'O', {L'O', L'Ó', L'Ö', L'Ő'}},
  {'U', {L'U', L'Ú', L'Ü', L'Ű'}},
};

void process_line(const std::wstring &line, wchar_t &character, const int pointer)
{
    std::system("clear");
    if(character=='a' || character=='e' || character=='i' || character=='o' || character=='u' ||
      character=='A' || character=='E' || character=='I' || character=='O' || character=='U')
    {
      std::wcout << line << std::endl;
      for(int i = 0; i < pointer; ++i)
        std::wcout << " ";
      std::wcout << "^" << std::endl;

      auto options = substitution_map.at(character);
      for(int i = 0; i < options.size(); ++i)
        std::wcout << i + 1 << " ==> " << options[i] << std::endl;
      bool valid = false;
      std::wstring choice;

      do {
        std::getline(std::wcin, choice);
        try {
          int int_choice = std::stoi(choice);
          if(int_choice <= options.size()) {
            character = options[int_choice - 1];
            valid = true;
          }
        } catch (const std::invalid_argument&) {
          if(choice.empty())
            valid = true;
        }
      } while (!valid);
    }
}

void dotter(std::wstring &line)
{
  int i = 0;
  std::for_each(line.begin(), line.end(), [&line, &i](wchar_t &character){ process_line(line, character, i); ++i; });
}

int main()
{
  std::vector<std::wstring> text;
  std::locale::global(std::locale("hu_HU.UTF-8"));
  std::wcout.imbue(std::locale());

  for (std::wstring line; std::getline(std::wcin, line) && line != std::wstring{L"STOP"}; ) {
    text.push_back(line);
  }

  std::for_each(text.begin(), text.end(), dotter);

  std::system("clear");
  auto print = [](const std::wstring& line) { std::wcout << line << std::endl;};
  std::for_each(text.cbegin(), text.cend(), print);
}
