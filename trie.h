// define your classes here...
#include <iostream>

class TrieClass {
    public:

        TrieClass();
        ~TrieClass();

        void load();
        bool insertWord(std::string &word);
        void prefixWords(std::string &prefix);
        bool eraseWord(std::string &word);
        void printAlphabetical();
        void spellcheck(std::string &word);
        bool empty();
        void clear();
        void size();
        
    private:
    
        int numWords;

        private:

            class TrieNode {

                public:
                    TrieNode();
                    ~TrieNode();

                    TrieNode* children[26];
                    bool endOfWord;                    
            };

            TrieNode* root;
            void alphabeticalPrintingRecurse(TrieNode *temp, std::string &wordToPrint);
            void clearTrieRecurse(TrieNode *startingNode);
            void prefixRecurse(TrieNode *startingNode, std::string &prefixString, int &count);
            void checkSpellCheckWordRecurse(std::string &word, std::string &checkedWord, TrieNode *startingNode);
            bool deleteWordRecurse(std::string &wordToDelete, TrieNode *&startingNode, int &letterIndex);
            bool isNextLevelEmpty(TrieNode *startingNode);
};