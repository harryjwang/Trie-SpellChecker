#include "trie.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

// implement classes' member functions here...

TrieClass::TrieNode::TrieNode(){            // creates the potential children for each node and set them to nullptr
    for (int i{0}; i < 26; i++){
        children[i] = nullptr;
    }
    endOfWord = false;
}

TrieClass::TrieNode::~TrieNode(){}

TrieClass::TrieClass(){            // creates a root node and sets the num of words in the Trie to 0
    root = new TrieNode();
    numWords = 0;
}

TrieClass::~TrieClass(){            // Erases the entire Trie starting at the root (including it)
    clearTrieRecurse(root);
}

void::TrieClass::load(){            // load the words in the Corpus.txt file into the Trie with help from the insert function
    std::ifstream fileToRead("corpus.txt");         // reads corpus.txt
    std::string wordToAdd;                          
    while (!fileToRead.eof()){                 // Reads the file and then using the insert function it inserts the words
        fileToRead >> wordToAdd;             
        insertWord(wordToAdd);               
    }
}

bool::TrieClass::insertWord(std::string &word){             // takes in a string value and recursively insert the word into the Trie
    TrieNode *testNode = root;
    int wordLength = word.length();
    for (int i{0}; i < wordLength; i++){                    
        int letterIndex = word[i] - 'A';
        if (testNode -> children[letterIndex] == nullptr){              // if there is no node on the node of the letter of the word
            testNode -> children[letterIndex] = new TrieNode();
            testNode = testNode -> children[letterIndex];
        } else {                                                        // if there is a node already, the move to the next node
            testNode = testNode -> children[letterIndex];
        }
    }
    
    if (testNode -> endOfWord == false){                            // if it is not the end of the word, set it to the end of the word and increment the num of words
        testNode -> endOfWord = true; 
        numWords++;
        return true;
    } else {                                                // return false if it's not true and so the main function with print failure
        return false;
    }
}

void::TrieClass::prefixWords(std::string &prefix){           // Command c (prefix)
    TrieNode *prefixNode = root;
    int count = 0;
    int prefixLength = prefix.length();   

    for (int index{0}; index < prefixLength; index++){          // iterate through the lenght of the prefix to get to the node after the prefix
        int letterIndex = prefix[index] - 'A';

        // Debugging Code //
        // std::cout << "reaches this point" << std::endl;

        if (prefixNode -> children[letterIndex] == nullptr){
            std::cout << "not found" << std::endl;
            return;
        }
        prefixNode = prefixNode -> children[letterIndex];
    }

    // Debugging Code //
    // std::cout << "reaches this point (1)" << std::endl;

    prefixRecurse(prefixNode, prefix, count);       // run the prefix recursion function

    // Debugging Code //
    // std::cout << "reaches this point (4)" << std::endl;


    if (count == 0){                            // if, after you iterate there are no values then prints not found as there are no values there
        std::cout << "not found" << std::endl;
    } else {                                    // if there are values, print the number of values
        // assert(count > 0);
        std::cout << "count is " << count << std::endl;
    }
}

void::TrieClass::prefixRecurse(TrieNode *startingNode, std::string &prefixString, int &count){          // prefix recursion function
    
    if (startingNode == nullptr){               // if the node that you start at is null, return and don't do anything
        return;
    }

    if (startingNode -> endOfWord == true){         // increment if you get to the end of a word
        count++;
    } 

    // Debugging Code //
    // std::cout << "reaches this point (2)" << std::endl;

    for (int index{0}; index < 26; index++){                    //iterate through the children of the node and add letters to the prefix where the 
                                                                // next node isn't null
        
        TrieNode *newNode = startingNode -> children[index];
        char addLetter = 'A' + index;
        prefixString.push_back(addLetter);

        // Debugging Code
        // std::cout << "reaches this point (3)" << std::endl;
        
        if (newNode != nullptr){                                // repeat the prefix recursion function if the next node is not null
            prefixRecurse(newNode, prefixString, count);
        }
        prefixString.pop_back(); 
    }
}

bool::TrieClass::eraseWord(std::string &word){               // Command e (word)        
    int depthOfWord = 0;
    return deleteWordRecurse(word, root, depthOfWord);      // return whether the word is deleted or not
}

bool::TrieClass::deleteWordRecurse(std::string &wordToDelete, TrieNode *&startingNode, int &wordLetterIndex){
    if (startingNode == nullptr) {              // if the node is null then you return false and you can't delete the word
        return false;               
    }

    int lengthOfWordToDelete = wordToDelete.length();
    if (wordLetterIndex == lengthOfWordToDelete) {          // if the number of letters in the word is the same as the one you iterate in the Trie
        if (startingNode->endOfWord == true) {              // if you get to the end of the word, set the boolean of it being the end of the word to flase and 
                                                            // decrement by 1
            startingNode->endOfWord = false;
            numWords--;

            if (isNextLevelEmpty(startingNode) == true)  {           // if the Trie is empty starting from the node after the prefix is iterated down the Trie,
                                                            // delete that node and set it to null
                delete startingNode;
                startingNode = nullptr;
            }

            return true;                                // if it works, then you have deleted the word and return true to print sucess as in the word is deleted
        } else {
            // assert(wordLetterIndex != lengthOfWordToDelete);
            return false;                       // if the word you want to delete and the word iterated in the Trie isn't the same then failure should be printed
                                                // because it returns false
        }
    }

    int letterIndex = wordToDelete[wordLetterIndex] - 'A';          // Find the letter index of the word
    TrieNode *&nextNode = startingNode->children[letterIndex];        // Make a node that is the array of the next letter in the word
    ++wordLetterIndex;                                              // increment the index of the letters in the word you want to delete

    if (deleteWordRecurse(wordToDelete, nextNode, wordLetterIndex)) {       // if you can delete the node
        if (isNextLevelEmpty(startingNode) && !(startingNode->endOfWord)) {     // if all nodes after the starting node is null and it's the end of the word,
                                                                                // delete the node and set it to null
            delete startingNode;
            startingNode = nullptr;
        }  
        return true;                                                          // if you can delete it thne return true
    } else {                                                        
        // assert(startingNode == nullptr);
        return false;                                                           // if you can't delete it then return false
    }
}

bool::TrieClass::isNextLevelEmpty(TrieNode *startingNode){                      // given a starting node, checks if all the node after that node is null
    for (int index{0}; index < 26; index++){                                // iterates each index from the initial node and keeps going into the children
                                                                            // if there's one node that has a value, then return false as in the levels after the node is not empty
        if (startingNode -> children[index] != nullptr){
            return false;
        }
    }
    return true;            // return true if there are no values after the given node
}

void::TrieClass::printAlphabetical() {          // prints all of the nodes that are in the Trie
    std::string startingWord = "";
    alphabeticalPrintingRecurse(root, startingWord); // calls recusion function starting at a given Node
    std::cout << "\n";
}

void::TrieClass::alphabeticalPrintingRecurse(TrieNode* temp, std::string &wordToPrint) {
    if (numWords == 0){             // if there's no value in the Trie then return the code and do nothing
        return;
    } else if (temp -> endOfWord == true) {         // if you get to the end of the word, print it out
        std::cout << wordToPrint << " ";
    }

    std::string nextWord = wordToPrint;
    int index = 0;
    while (index < 26){         // recurse for all for all of children of a node (0 to 25 -> 26 letters in the alphabet)
        if (temp -> children[index] != nullptr) {               // if the children node isn't null, the run the if statement
            char currentChar = index + 'A';                     // create  cahracter that corresponds to the letter you iterated to
            nextWord.push_back(currentChar);                    // push to the back of the string to avoid O(N)
            alphabeticalPrintingRecurse(temp -> children[index], nextWord);         // recurse to the next letter of Trie
            nextWord.pop_back();            // once you're done recusing to the end of the word, pop all the stuff you pushed to the back of the initial string
        }
        index++;                     // increment to the next letter once recursion is done
        }
}

void::TrieClass::spellcheck(std::string &word){         // spellcheck command
    std::string wordString;
    checkSpellCheckWordRecurse(word, wordString, root);     // run recursion function of the spellcheck command
}

void::TrieClass::checkSpellCheckWordRecurse(std::string &word, std::string &checkedWord, TrieNode *startingNode){       // recursion for spellcheck command
    // bool stringMatch = true;
    if (startingNode == nullptr){       // if the initial node is null, do nothing and return back
        return;
    } else {                                                // if the next node has a value, go through all of the value in the children
        for (int index{0}; index < 26; index++){
            int letterIndex = word[index] - 'A';
            if (startingNode -> children[letterIndex] == nullptr){          // if the child is null break out of that if statement
                // stringMatch = false;
                break;
            } else {                    // if the child is not null then you add 
                checkedWord += word[index];                                     // add the letter to the word to check, if you do this...
                startingNode = startingNode -> children[letterIndex];           // update the node you are to to indicate the end of where the word you are checking 
            }
        }
    }

    if ((word == checkedWord) && (startingNode -> endOfWord == true)){          // if the word you want to spellcheck is the same as the one you iterated to get,
                                                                                // and you get to the end of the word, print "correct"
        // assert(stringMatch == true);
        std::cout << "correct";
    } else if (startingNode == root){                   // if the first letter of the word you want to spellcheck doesn't exist
        
    } else {                                                                    // if it's not, run the recursion of printing all of the words in the Trie below a
                                                                                // given node (in this case the node where you get to the point that you get the most
                                                                                // letters from spellcheck word as possible)
        // assert(stringMatch == false);
        alphabeticalPrintingRecurse(startingNode, checkedWord);
    }
}

bool::TrieClass::empty(){           // checks if the Trie is empty
    if (numWords == 0){             // if there are zero words in the Trie, return true (empty Trie)
        return true;
    } else {                        // if the number of words in the Trie is not 0, return false (Trie is not empty)
        return false;
    }
}

void::TrieClass::clear(){               // deletes all of the nodes in the Trie besides the root
    clearTrieRecurse(root);             // run clear recursion function starting at the root
    root = new TrieNode();              // since the recursion clear function deletes ALL nodes, make a new root node
    std::cout << "success" << std::endl;            // print success once this is done
}

void::TrieClass::clearTrieRecurse(TrieNode *startingNode){          // Deletes the entire Trie including the root node
    if (startingNode == nullptr){                                   // if the node you want to start with is null, return and don't do anything
        return;
    } else {                                                        // if the starting node isn't null, iterate through all possible children and their children (recursion)
        for (int index{0}; index < 26; index++){                    // for each child of every single node iterate to those nodes
            if (startingNode -> children[index] != nullptr){            // as long as the child node of all the nodes you iterate to has a value,
                                                                        // run the clear recursion function that recurses through the children again until it gets to
                                                                        // end of the Trie
                clearTrieRecurse(startingNode -> children[index]);
                startingNode -> children[index] = nullptr;              // set the child node to be null
                }
        }
        delete startingNode;                                            // delete the node if you get to the bottom of a branch of the Trie
        numWords = 0;
    }
}

void::TrieClass::size(){
    std::cout << "number of words is " << numWords << std::endl;            // Prints the number of words in the Trie
}
