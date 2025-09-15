// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "trie.h"
#include <cassert>


int main(){

    std::string commandString{};
    std::string commandValue1{};

    TrieClass Trie;

    while (true){
        std::cin >> commandString;                      // inputs for the command
        if (commandString == "load"){
            Trie.load();                                // load the values of corpus.txt into the Trie
            std::cout << "success" << std::endl;        // if loaded correctly, prints "success"
        } else if (commandString == "i"){               // command "i" inserts a value
            std::cin >> commandValue1;                  // input the value that you want to insert into the Trie
            bool result = Trie.insertWord(commandValue1);           // function returns true or false depending on if the string in inputted
            if (result == true){                                
                std::cout << "success" << std::endl;
            } else {
                // assert(result == false);
                std::cout << "failure" << std::endl;
            }
        } else if (commandString == "c"){                   // command "c" runs the prefix function on the Trie
            std::cin >> commandValue1;                      // input value of prefix that you want to check all other words
            Trie.prefixWords(commandValue1);   
        } else if (commandString == "e"){                   // command "e" erases word from the Trie
            std::cin >> commandValue1;                      // Function returns true or false depending on if the word gets deleted or not
            bool result = Trie.eraseWord(commandValue1);
            if (result == true){                            // if returned true, "success" gets printed and if returned false "failure" is printed
                std::cout << "success" << std::endl;
            } else {
                std::cout << "failure" << std::endl;
            }
        } else if (commandString == "p"){                   // command "p" prints out all of the words in the Trie
            Trie.printAlphabetical();
        } else if (commandString == "spellcheck"){          // runs the spellcheck command on the word you want to check in the Trie
            std::cin >> commandValue1;                      // takes in a command value for the function
            Trie.spellcheck(commandValue1);
            std::cout << "\n";
        } else if (commandString == "empty"){               // checks if the Trie is empty or not and the function returns true or false
            bool emptyResult = Trie.empty();
            if (emptyResult == true){                       // based on return value, if the return is true, Trie is empty, if return is false, Trie is not empty
                std::cout << "empty 1" << std::endl;
            } else {
                // assert(emptyResult == false);
                std::cout << "empty 0" << std::endl;
            }
        } else if (commandString == "clear"){               // clears all of the values in the Trie besides the root node
            Trie.clear();
        } else if (commandString == "size"){                // prints the size of the Trie (number of words)
            Trie.size();
        } else if (commandString == "exit"){                // exits the code when called
            break;
        }
    }

}