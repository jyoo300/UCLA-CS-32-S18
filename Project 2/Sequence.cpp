#include "Sequence.h"



Sequence::Sequence()
: head(nullptr), items(0), tail(nullptr)
{}

Sequence::~Sequence() {
    Node *p = head;
    while (p != nullptr) {
        Node *n = p->next; //Points n to the next node in the sequence
        delete p; //Deletes current node
        p = n; //Points p to the next node
    }
}

Sequence::Sequence(const Sequence& other)
: items(0)
{
    head = nullptr;
    Node *p = head;
    tail = p; //Sets tail and head to be nullptr
    Node *s = other.head;
    int pos = 0; //Keeps track of Sequence position
    ItemType x;
    while(s != nullptr) {
        other.get(pos, x); //Gets value from other Sequence at pos
        insert(pos, x); //Inserts value it into main the main sequence
        s = s->next;
        pos++;
    }
}

Sequence& Sequence::operator=(const Sequence& src) {
    if(this != &src)
    {
        Sequence temp(src); //Creates a temporary Sequence holding all of src's node
        swap(temp); //Swaps pointers with the temp Sequence
    }
    return *this;
}
bool Sequence::empty() const {
    return head == nullptr;
}

int Sequence::size() const {
    return items;
}

bool Sequence::insert(int pos, const ItemType& value) {
    bool inserted = false; //Keeps track of whether the value has been inserted or not
    if (pos >= 0 && pos<= size())
    {
        if (head == nullptr) //Seq is empty
        {
            Node *p;
            p = new Node;
            p->value = value;
            p->next = head; //Sets the p->next's address to be head
            p->prev = nullptr;
            head = p; //Sets the new head address to be at p
            tail = p;
            items++;
            inserted = true;
        }
        else if(pos == 0) //Beginning of the pos when the seq isn't empty
        {
            Node *p;
            p = new Node;
            head->prev = p; //Sets head's prev address to be p
            p->value = value;
            p->next = head;
            p->prev = nullptr;
            head = p;
            items++;
            inserted = true;
        }
        else if(pos == size()) //Value is inserted at the end of the Sequence
        {
            Node *p;
            p = new Node;
            tail->next = p;
            p->value = value;
            p->next = nullptr;
            p->prev = tail; //Sets p's prev address to be tail
            tail = p; //Replaces tail's current address with p's address
            items++;
            inserted = true;
        }
        else //Value is inserted in the middle of the sequence
        {
            Node *p = head;
            int pos2 = 0; //Keeps track of Sequence's current position
            while (p!=nullptr) {
                if(pos2 == pos) //If the current position equals the passed position, the loop will break and bool inserted will equal true
                {
                    inserted = true;
                    break;
                }
                p = p->next;
                pos2++;
            }
            if (inserted == true) {
                Node *latest;
                latest = new Node;
                latest->value = value;
                //Links latest to other nodes to ensure that latest follows the current p-prev address and precedes p's address
                latest->prev = p->prev; //Links latest with the node preceding p
                latest->next = p; //Links latest with p so that p follows latest
                p->prev->next = latest; //Links p-prev with latest so that latest follows p-prev
                p->prev = latest; //Links p with latest so that latest preceded p
                items++;
            }
        }
    }
    
    return inserted;
}

int Sequence::insert(const ItemType& value) {
    int count = 0;
    if(head == nullptr) {
        Node *p;
        p = new Node;
        p->value = value;
        p->next = head;
        p->prev = nullptr;
        head = p;
        tail = p;
        items++;
    }
    else if(value <= head->value) //inserts at pos 0 when Sequence is not empty
    {
        Node *p;
        p = new Node;
        head->prev = p;
        p->value = value;
        p->next = head;
        p->prev = nullptr;
        head = p;
        items++;
    }
    else {
        Node *p = head;
        bool insertMiddle = false;
        while (p->next != nullptr) //While p doesn't equal Tail
        {
            if(value <= p->value) {
                insertMiddle = true;
                break;
            }
            p = p->next;
            count++;
            if(p->next == nullptr && value < p->value) {
                insertMiddle = true;
                break;
            }
        }
        if(p->next == nullptr && insertMiddle == false)
        {
            Node *p;
            p = new Node;
            tail->next = p; //Links tail to p so that p follows tail
            p->value = value;
            p->next = nullptr;
            p->prev = tail; //Links p to tail so that tail precedes p
            tail = p; //Sets the tail's address to be p's address
            items++;
        }
        else if (insertMiddle == true) //Inserted in the middle of the sequence
        {
            Node *latest;
            latest = new Node;
            latest->value = value;
            latest->prev = p->prev;
            latest->next = p;
            p->prev->next = latest;
            p->prev = latest;
            items++;
        }
    }
    return count;
}



bool Sequence::erase(int pos) {
    if(head == nullptr || pos > size()-1) {
        return false;
    }
    Node* p = head;
    int count = 0;
    bool erased = false;
    while(head != nullptr) {
        if(pos == count && count == 0) //The node is in the beginning of the sequence
        {
            Node *killMe = head;
            head = killMe->next;
            delete killMe;
            erased = true;
            items--;
            break;
        }
        else if(pos == count && pos == size()-1)//The node is at the end of the sequence
        {
            Node* killMe = tail;
            tail = killMe->prev;
            p->prev->next = nullptr;
            items--;
            erased = true;
            break;
        }
        else if(pos == count && count !=0 && count != size()-1) //The node is in the middle of the sequence
        {
            Node *killMe = p;
            p->prev->next = killMe->next; //Links the previous node to the next node
            p->next->prev = killMe->prev; //Links the next node to the previous node
            delete killMe;
            erased = true;
            items--;
            break;
        }
        p = p->next;
        count++;
    }
    return erased;
}

int Sequence::remove(const ItemType& value) {
    int erased = 0; //Keeps track of how many times the passed value is erased
    int pos = 0; //Keeps track of the current position
    Node *p = head;
    while(p != nullptr) {
        if(p->value == value) //If the node value equals the passed value the node value will be erased
        {
            erase(pos);
            pos--;
            erased++;
        }
        p = p->next;
        pos++;
    }
    return erased;
}

bool Sequence::get(int pos, ItemType& value) const {
    Node *p = head;
    int pos2 = 0; //Keeps track of the current position
    bool inserted = false; //Return value
    while (p!=nullptr) {
        if (pos == pos2) { //If the value equals the node value that is being pointed to, the loop will break and the passed value will be set to the node value,
            inserted = true;
            value = p->value;
            break;
        }
        p = p->next;
        pos2++;
    }
    return inserted;
}

bool Sequence::set(int pos, const ItemType& value) {
    Node *p = head;
    int count = 0;
    bool inserted = false;
    while (p!=nullptr) {
        if(pos==count)//If the value equals the node value that is being pointed to, the loop will break and the node value will be set to the passed value
        {
            inserted = true;
            p->value = value;
            break;
        }
        p = p->next;
        count++;
    }
    return inserted;
}

int Sequence::find(const ItemType& value) const {
    Node *p = head;
    int count = 0;
    bool present = false;
    while (p != nullptr) {
        if(value == p->value) //If the value equals the node that is being pointed to, the loop will break
        {
            present = true;
            break;
        }
        p = p->next;
        count++;
    }
    if(present == false) {
        count = -1;
    }
    return count;
}

void Sequence::swap(Sequence &other) {
    //Create temporary pointers that hold head's and tails's initial addresses
    Node *tempHead = head;
    Node *tempTail = tail;
    
    //Gives head and tail the address of the other Sequence's head and tail respectively
    head = other.head;
    tail = other.tail;
    
    //Gives other.head and other.tail the initial addresses of head and tail respectively
    other.head = tempHead;
    other.tail = tempTail;
    
    //Swaps sizes of the two sequences
    int temp = other.items;
    other.items = items;
    items = temp;
}



int subsequence (const Sequence& seq1, const Sequence& seq2) {
    int count = -1; //Return value
    int seq1pos = 0; //Keeps track of Seq 1's pos
    int seq2pos= 0; //Keeps track of Seq 2's pos
    int temp1 = 0; //Copies seq1pos
    int temp2 = 0; //Copies
    bool activated = false; //Keeps track if a seq2 is a subsequence of Seq1
    ItemType x;
    ItemType y;
    while(seq1pos < seq1.size())
    {
        seq1.get(seq1pos, x);
        seq2.get(seq2pos, y);
        if(x == y) //If the value at seq1 at pos seq1pos == the value at seq2 at pos 0
        {
            count = seq1pos;
            activated = true;
        }
        if (activated == true) //Checks if seq2 is a subseq of seq1
        {
            temp1 = seq1pos; //Copies current pos of seq1
            temp2 = seq2pos; //Copies current pos of seq2
            while(temp2 < seq2.size()) //Runs through all nodes of seq2
            {
                seq1.get(temp1, x);
                seq2.get(temp2, y);
                if(x == y && temp2 == seq2.size()-1) //If all the values of seq2 are found in seq1 in the same order
                {
                    break;
                }
                else if (x == y) {
                }
                else if (x != y) //If the value at seq1 doesn't equal the value at seq2
                {
                    activated = false;
                    seq2pos = 0;
                    count = -1;
                    break;
                }
                temp1++;
                temp2++;
            }
        }
        if (activated == true) //if seq2 is confirmed to be a subseq of seq1 the while loop breaks
        {
            break;
        }
        seq1pos++;
    }
    return count;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
    //Creates temporary copies of seq1 and seq2
    Sequence temp1(seq1);
    Sequence temp2(seq2);
    int size = temp1.size() + temp2.size();
    //Keeps track of pos of seq1 and seq1 and resultpos
    int seq1pos = 0;
    int seq2pos = 0;
    int resultpos = 0;
    ItemType x;
    ItemType y;
    while(resultpos < size) //While the pos of result is less than the combined sizes of seq1 and seq2
    {
        if(seq1pos < seq1.size()) //Inserts the values of seq1
        {
            temp1.get(seq1pos, x);
            result.insert(resultpos, x);
            seq1pos++;
            resultpos++;
        }
        if(seq2pos < seq2.size()) //Inserts the values of seq2
        {
            temp2.get(seq2pos, y);
            result.insert(resultpos, y);
            seq2pos++;
            resultpos++;
        }
    }
    if(size < result.size()) //erases excess values that were not inserted into the sequence
    {
        int copy = result.size();
        while (size < result.size()) {
            result.erase(copy);
            copy--;
        }
    }
}
