#include <iostream>
#include <vector>

using namespace std;

class node{
public:
    node(int val){
        this->value = val;
        //initializing the height by the help of tossing coin
        height = pickHeight();
        next = vector<node*>(height + 1);
        nextLength = vector<int>(height + 1);
        isDuplicated = false;
    }
    node(){}
    int value;
    int height;
    bool isDuplicated;
    vector<node*> next;
    vector<int> nextLength;

private:
    //from ODS book
    int pickHeight() {
        int z = rand();
        int k = 0;
        int m = 1;
        while ((z & m) != 0) {
            k++;
            m <<= 1;
        }
        return k;
    }
};


class skipList{
public:
    skipList(){
        dummy = new node;
    }

    bool isEmpty(){
        if(dummy->next.size() == 0)
            return true;
        else
            return false;
    }

    void add(int x){
        //Making the node
        node* newNode = new node(x);
        cout << "Search path for adding element <" << x << ">:\n";
        if(!isEmpty()){
            int i = dummy->next.size()-1;
            heightCounter = 0;
            lengthCounter = 0;
            addNode(newNode, i , dummy);
            if(newNode->height > dummy->next.size() - 1){
                for(int i = dummy->next.size() - 1; i < newNode->height; i++){
                    dummy->next.push_back(newNode);
                    if(heightCounter <= newNode->height){
                        dummy->nextLength.push_back(lengthCounter + 1);
                    }
                }
            }
        }
        else{
            cout << "The list was empty, so there is no search path for first insertion\n\n";
            for(int i = 0; i <= newNode->height; i++){
                dummy->next.push_back(newNode);
                dummy->nextLength.push_back(1);
                newNode->next[i] = nullptr;
            }
        }
    }

    void remove(int x){
        cout << "Search path for removing element <" << x << ">:\n";
        node* newNode = find(x);
        if(newNode == nullptr)
            cout << "This element is not within the list" << endl;
        else{
            int i = dummy->next.size()-1;
            heightCounter = 0;
            cout << "Search path for finding the predecessor of element <" << x << ">:\n";
            removeNode(newNode, i, dummy);
            delete(newNode);
        }

    }

    node* find(int x){
        node* ptr = dummy;
        cout << "Search path for finding element <" << x << ">:\n";
        int level = dummy->next.size() - 1;
        for(int i = level; i >= 0; ){
            if(ptr != dummy)
                cout << "value:\t" << ptr->value << "\tlevel:\t" << i << endl;
            else
                cout << "value:\t" << "dummy" << "\tlevel:\t" << i << endl;

            if(ptr->next[i] != nullptr && ptr->next[i]->value < x)
                ptr = ptr->next[i];
            else if(ptr->next[i] != nullptr && ptr->next[i]->value == x){
                ptr = ptr->next[i];
                if(ptr != dummy)
                    cout << "value:\t" << ptr->value << "\tlevel:\t" << i << endl;
                else
                    cout << "value:\t" << "dummy" << "\tlevel:\t" << i << endl;
                cout << "FOUND\n";
                return ptr;
            }
            else
                i--;
        }
        if(ptr != nullptr){
            if(ptr->value == x){
                cout << "FOUND\n";
                return ptr;
            }
            else{
                cout << "NOT FOUND\n";
                return nullptr;
            }
        }
        else{
            cout << "NOT FOUND\n";
            return nullptr;
        }
    }

    int find_by_rank(int index){
        node* ptr = dummy;
        int level = dummy->next.size() - 1;
        for(int i = level; i >= 0; ){
            if(ptr->nextLength[i] != 0 && ptr->nextLength[i] <= index){
                index -= ptr->nextLength[i];
                ptr = ptr->next[i];
            }
            else
                i--;
        }
        if(index == 0)
            return ptr->value;
    }

    void print_SkipList(){
        cout << "Displaying nodes' values and their heights:\n";
        node* temp = dummy->next.front();
        while(temp != nullptr){
            cout << "value: " << temp->value << "\t" << "height: " << temp->height << endl;
            temp = temp->next[0];
        }
        cout << endl;
    }

    skipList truncate(int index){
        int value = find_by_rank(index);
        int i = dummy->next.size() - 1;
        skipList newSl;
        for(int i = 0; i < this->dummy->next.size(); i++){
            newSl.dummy->next.push_back(nullptr);
            newSl.dummy->nextLength.push_back(0);
        }

        truncateHelper(value, i, dummy, newSl.dummy);
        return newSl;
    }

    void absorb(skipList sl){
        int dummySize1 = this->dummy->next.size();
        int dummySize2 = sl.dummy->next.size();
        int d = abs(dummySize1 - dummySize2);
        if(dummySize2 > dummySize1){
            for(int i = dummySize1; i < d; i++){
                this->dummy->next.push_back(nullptr);
                this->dummy->nextLength.push_back(0);
            }
            node* ptr = this->dummy;
            int i = this->dummy->next.size() - 1;
            absorbHelper(i, ptr, sl.dummy);
        }
        else{
            node* ptr = this->dummy;
            int i = sl.dummy->next.size() - 1;
            absorbHelper(i, ptr, sl.dummy);
        }

    }

    node* dummy; //sentinel

private:
    int heightCounter = 0; //used for updating "next" pointers
    int lengthCounter = 0; //used for updating "nextLength" values

    //man hameye function haye asli ro be komake in helper ha be soorate bazgashti piadesazi kardam
    //ta betunam node haye ghabli ro update konam
    //bejaye estefade az stack ta hafeze behine tar bashe

    void addNode(node* u, int i, node* ptr){
        if(ptr != dummy)
            cout << "value:\t" << ptr->value << "\tlevel:\t" << i << endl;
        else
            cout << "value:\t" << "dummy" << "\tlevel:\t" << i << endl;

        //base case
        if(i == 0) {
            if(ptr->next[0] != nullptr){
                if(ptr->next[0]->value > u->value){
                    //check if it is duplicated or not
                    //man inja element haye tekrari ro be listam ezafe nemikonam ta baraye methode truncate be moshkel nakhoram
                    u->nextLength[0] = 1; //because it is not at the end of the list
                    ptr->nextLength[0] = 1;
                    u->next[0] = ptr->next[0];
                    ptr->next[0] = u;
                    cout << "ADDED\n" << endl;
                    return;
                }
                //check if it is duplicated or not
                //man inja element haye tekrari ro be listam ezafe nemikonam ta baraye methode truncate be moshkel nakhoram
                else if(ptr->next[0]->value == u->value){
                    u->isDuplicated = true;
                    cout << "The element <" << u->value << "> already exists.\n\n";
                    return;
                }
            }
            else{
                u->next[0] = ptr->next[0];
                ptr->next[0] = u;
                u->nextLength[0] = 0;
                ptr->nextLength[0] = 1;
                cout << "ADDED\n" << endl;
                return;
            }
        }

        //going to the right
        if(ptr->next[i] != nullptr && ptr->next[i]->value < u->value){
            lengthCounter += ptr->nextLength[i];
            ptr = ptr->next[i];
            addNode(u, i, ptr);
        }
        //going downward
        else{
            i--;
            addNode(u, i , ptr);
            //updating previous nodes
            heightCounter++;
            if(heightCounter <= u->height && !u->isDuplicated){
                u->next[heightCounter] = ptr->next[heightCounter];
                ptr->next[heightCounter] = u;
                ptr->nextLength[heightCounter] = lengthCounter;
                u->nextLength[heightCounter] = 0;
            }
        }
    }

    void removeNode(node* u, int i, node* ptr){
        if(ptr != dummy)
            cout << "value:\t" << ptr->value << "\tlevel:\t" << i << endl;
        else
            cout << "value:\t" << "dummy" << "\tlevel:\t" << i << endl;

        //base case
        if(i == 0){
            if(ptr->next[0]->value == u->value){ //it means that we have found the predecessor
                ptr->next[0] = u->next[0];
                ptr->nextLength[0] += u->nextLength[0];
                ptr->nextLength[0] -= 1;
                cout << "DELETED\n" << endl;
                return;
            }
        }

        if(ptr->next[i] != nullptr && ptr->next[i]->value < u->value){
            ptr = ptr->next[i];
            removeNode(u, i, ptr);
        }
        else{
            i--;
            removeNode(u, i, ptr);
            //updating previous nodes
            heightCounter++;
            if(heightCounter <= u->height){
                ptr->next[heightCounter] = u->next[heightCounter];
                if(u->nextLength[heightCounter] != 0){
                    ptr->nextLength[heightCounter] += u->nextLength[heightCounter];
                    ptr->nextLength[heightCounter] -= 1;
                }
                else
                    ptr->nextLength[heightCounter] = 0;
            }
        }

    }

    void truncateHelper(int value, int i, node* ptr, node* newDummy){
        //base case
        if(i == 0){
            if(ptr->value == value){ //it means that we have found the predecessor
                newDummy->next[0] = ptr->next[0];
                newDummy->nextLength[0] = ptr->nextLength[0];
                ptr->next[0] = nullptr;
                ptr->nextLength[0] = 0;
                return;
            }
        }

        if(ptr->next[i] != nullptr && ptr->next[i]->value <= value){
            ptr = ptr->next[i];
            truncateHelper(value, i, ptr, newDummy);
        }
        else{
            i--;
            truncateHelper(value, i, ptr, newDummy);
            //updating previous nodes
            heightCounter++;
            if(heightCounter <= newDummy->height){
                newDummy->next[heightCounter] = ptr->next[heightCounter];
                newDummy->nextLength[heightCounter] = ptr->nextLength[heightCounter];
            }
        }

    }

    void absorbHelper(int i, node* ptr, node* newDummy){
        //base case
        if(i == 0 && ptr->next[0] == nullptr){
            ptr->next[0] = newDummy->next[0];
            ptr->nextLength[0] += newDummy->nextLength[0];
            return;
        }

        //going to the right
        if(ptr->next[i] != nullptr){
            lengthCounter += ptr->nextLength[i];
            ptr = ptr->next[i];
            absorbHelper(i, ptr, newDummy);
        }
        //going downward
        else{
            i--;
            absorbHelper(i, ptr, newDummy);
            //updating previous nodes
            ptr->next[i] = newDummy->next[i];
            ptr->nextLength[i] = lengthCounter + newDummy->nextLength[i];
        }

    }


};
int main(){
    //An example containing all possible operators
    skipList SL;
    SL.add(1);
    SL.add(2);
    SL.add(2);
    SL.add(5);
    SL.add(4);
    SL.add(3);
    SL.add(6);


    SL.print_SkipList();

    SL.remove(2);

    SL.print_SkipList();

    cout << SL.find_by_rank(2) << endl;

    SL.print_SkipList();

    skipList newSL = SL.truncate(3);
    newSL.print_SkipList();
    SL.print_SkipList();

    SL.add(2);
    newSL.add(8);
    SL.absorb(newSL);
    SL.print_SkipList();
}