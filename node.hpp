#pragma once
#include <string>

enum word_check {word_not_found, file_not_found};

class node : public std::string {
  public:
  node();
  int count; 
  node *before;
  node *after;
};
