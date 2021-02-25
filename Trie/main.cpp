#include <iostream>
#include <vector>
// src https://www.geeksforgeeks.org/trie-insert-and-search/

const int ALPHABET_SIZE = 26;

// trie node
struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];

    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord = false;

    TrieNode() {
        for(int i = 0;i < ALPHABET_SIZE; i++){
            children[i] = nullptr;
        }
    }
};

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(TrieNode* root, std::string key) {
    TrieNode* pCrawl = root;

    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = new TrieNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}

// Returns true if key presents in trie, else
// false
bool search(TrieNode* root, std::string key) {
    TrieNode* pCrawl = root;

    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != nullptr && pCrawl->isEndOfWord);
}

// Driver
int main() {

    std::vector<std::string> keys = {"the", "a", "there",
                     "answer", "any", "by",
                     "bye", "their" };

    TrieNode* root = new TrieNode();

    // Construct trie
    for (int i = 0; i < keys.size(); i++)
        insert(root, keys[i]);

    // Search for different keys
    search(root, "the")? std::cout << "Yes\n" : std::cout << "No\n";
    search(root, "these")? std::cout << "Yes\n" :  std::cout << "No\n";
    return 0;
}