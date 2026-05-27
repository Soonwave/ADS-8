// Copyright 2021 NNTU-CS
#include "bst.h"

#include <cctype>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);

  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }

  std::string current_word;
  int count = 0;

  while (!file.eof()) {
    int ch = file.get();

    if (ch == std::char_traits<char>::eof()) {
      break;
    }

    count++;

    if (std::isalpha(static_cast<unsigned char>(ch))) {
      current_word += static_cast<char>(
          std::tolower(static_cast<unsigned char>(ch)));
    } else {
      if (!current_word.empty()) {
        tree.insert(current_word);
        current_word.clear();
      }
    }
  }

  if (!current_word.empty()) {
    tree.insert(current_word);
  }

  file.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> freq;
  tree.extractAll(&freq);

  std::sort(freq.begin(), freq.end(),
            [](const std::pair<std::string, int>& a,
               const std::pair<std::string, int>& b) {
              if (a.second != b.second) {
                return a.second > b.second;
              }
              return a.first < b.first;
            });

  std::ofstream out_file("result/freq.txt");
  if (!out_file) {
    std::cout << "File error!" << std::endl;
  }

  for (const auto& item : freq) {
    std::cout << item.first << " : " << item.second << "\n";
    if (out_file.is_open()) {
      out_file << item.first << " : " << item.second << "\n";
    }
  }

  if (out_file.is_open()) {
    out_file.close();
  }
}
