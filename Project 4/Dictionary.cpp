// Dictionary.cpp

// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <utility>  // for swap
using namespace std;

void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);

const int SIZE = 47701; //Container size is prime number so that the value can spread out more evenly
const int MAX_LETTERS = 26;

// This class does the real work of the implementation.

struct Node     //Builds a linked list in each bucket, open hash table implementation
{
    Node(string word, int ID, unsigned long trueID)  //Contains a word, ID and a null next ptr
    : m_word(word), ID(ID), next(nullptr), trueID(trueID)
    {}
    string m_word;
    int ID;
    Node* next;
    unsigned long trueID;
};

class DictionaryImpl
{
public:
    DictionaryImpl(); //Creates empty hash table
    ~DictionaryImpl(); //Destroys Nodes of hash table
    void insert(string word);
    void lookup(string letters, void callback(string));
private:
    Node* hash_table[SIZE]; //Hash table of array of nodes
    int hashFunc(string &word); //Hash function
    unsigned long trueID; //ID represented by function
};

DictionaryImpl::DictionaryImpl()
:trueID(1)
{
    for (int i = 0; i < SIZE; i++)
        hash_table[i] = nullptr;
}

DictionaryImpl::~DictionaryImpl()
{
    for (int i = 0; i < SIZE; i++)
    {
        Node* temp = hash_table[i];
        if (temp != nullptr) //Deletes node at hash_table[i]
        {
            Node* prev = temp;
            temp = temp->next;
            delete prev;
        }
    }
}
int DictionaryImpl::hashFunc(string &word) {
    removeNonLetters(word);
    int prime[MAX_LETTERS] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101}; //Maps each letter to a prime number so that each letter can be has a distinct ID
    trueID = 1;
    for (int i = 0; i < word.length(); i++) {
        int x = word[i] - 'a'; //Maps letter to a prime number in the array
        trueID *= prime[x]; //Creates an uniqueID by multiplying numbers
    }
    return trueID % SIZE; //Returns the array ID of the hashFunc
}

void DictionaryImpl::insert(string word)
{
    int ID = hashFunc(word);
    if(hash_table[ID] == nullptr) { //If hash_table is empty, inserts new node in that slot
        hash_table[ID] = new Node(word, ID, trueID);
    }
    else { //Traverses down hash table until an empty slot is found
        Node* temp = new Node(word, ID, trueID);
        Node* curr = hash_table[ID];
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = temp;
    }
}
void DictionaryImpl::lookup(string letters, void callback(string))
{
    if (callback == nullptr)
        return;
    removeNonLetters(letters);
    if (letters.empty())
        return;
    int ID = hashFunc(letters);
    Node* call = hash_table[ID];
    while(call != nullptr) {
        if(call->trueID == trueID) //Each anagram has a unique ID
        {
            callback(call->m_word);
            call = call->next;
        }
        else {
            call = call->next;
        }
    }
}

void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}

// Each successive call to this function generates the next permutation of the
// characters in the parameter.  For example,
//    string s = "eel";
//    generateNextPermutation(s);  // now s == "ele"
//    generateNextPermutation(s);  // now s == "lee"
//    generateNextPermutation(s);  // now s == "eel"
// You don't have to understand this function's implementation.
void generateNextPermutation(string& permutation)
{
    string::iterator last = permutation.end() - 1;
    string::iterator p;
    
    for (p = last; p != permutation.begin()  &&  *p <= *(p-1); p--)
        ;
    if (p != permutation.begin())
    {
        string::iterator q;
        for (q = p+1; q <= last  &&  *q > *(p-1); q++)
            ;
        swap(*(p-1), *(q-1));
    }
    for ( ; p < last; p++, last--)
        swap(*p, *last);
}

//******************** Dictionary functions ********************************

// These functions simply delegate to DictionaryImpl's functions.
// You probably don't want to change any of this code

Dictionary::Dictionary()
{
    m_impl = new DictionaryImpl;
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters,callback);
}
