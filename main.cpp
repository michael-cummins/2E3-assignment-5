#include <iostream>
#include <string>
#include "node.hpp"
#include <fstream>

using namespace std;

bool process_node(string new_node, node*& tree);
void find_word(node* tree, string word);
void print_tree(node* tree);
void build_tree(int& wordcount, int& individual_word_count, node*& tree, string& filename);

int main() {
  node* root = nullptr;
  int wordcount = 0;
  int individual_word_count = 0;
  string filename;
  cout << "Please enter the name of the book file:" << endl;
  cin >> filename;

  build_tree(wordcount, individual_word_count, root, filename);

  cout << "The file " << "\"" << filename << "\"" << " contains " << wordcount << " words of which " << individual_word_count << " are distinct." << endl;
  
  string s;
  cout << "Please enter the word you wish to check:" << endl;
  cin >> s;
  while (cin.eof() == false) {
    find_word(root, s);
    cout << "Please enter the word you wish to check:" << endl;
    cin >> s;
  }
  
  cout << "Goodbye" << endl;

 return 0;
}

void build_tree(int& wordcount, int& individual_word_count, node*& tree, string& filename){
  ifstream xfile;
  xfile.exceptions(std::iostream::failbit);
  try{
    xfile.open(filename);
    string t_word;
    string line;
    while (xfile.eof() == false) {
      xfile >> t_word;
      if (xfile.fail() == false) {
        wordcount++;
        if (process_node(t_word, tree)) {
          individual_word_count++;
        }
      }
    }
    xfile.close();
  }
  catch(...){
    cout << "An error occurred attempting to open the file " << "\"" << filename << "\"" << "." << endl;
    cout << "Please enter the name of the book file:" << endl;
    cin >> filename;
    build_tree(wordcount, individual_word_count, tree, filename);
  }
}

void print_tree(node *tree) {
  if (tree != nullptr) {
    print_tree(tree->before);
    cout << "\"" << *tree <<"\" " << tree->count << endl;
    print_tree(tree->after);
  }
}

// returns true if the node is new, false otherwise
bool process_node(string new_node, node*& tree) {
	bool response;
  //covers trivial base case
	if (tree == nullptr) {
		tree = new node();
    tree->assign(new_node);
		response = true; // it is a new node
	} else {
    //base case that we're already pointing to the new word
		if (new_node == *tree) {
			tree->count++;
			response = false; // it is not a new node
		} else {
			if (new_node < *tree) {
				response = process_node(new_node, tree->before);
			} else {
				response = process_node(new_node, tree->after);
			}
		}
	}
	return response;
}

void find_word(node* tree, string word){
  try {
    //found the word
    if(word == *tree) {
      if (tree->count == 1) {
        cout << "The word " << "\"" << word << "\"" 
        << " was found once." << endl;
      }
      else if (tree->count == 2) {
        cout << "The word " << "\"" << word << "\"" 
        << " was found twice." << endl;
      }
      else { 
      cout << "The word " << "\"" << word << "\"" 
      << " was found " << tree->count << " times." << endl;
      }
    }
    //havent found the word
    //check for dead end
    else if ((tree->before == nullptr) && (tree->after == nullptr)) {
      throw (word_not_found);
    }
    if (*tree > word) {
      //check before subtree
      find_word(tree->before, word);
    }
    if (*tree < word) {
      //check after subtree
      find_word(tree->after, word);
    }
  }
  catch (...){
    cout << "The word " << "\"" << word << "\"" 
    << " was not found." << endl;
  }
}