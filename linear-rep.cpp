#include<iostream>
#include <iomanip>
#include <ios>
#include<utility>
using namespace std;

const int SIZE = 10;
// hashTable values are stored in this format:
// {value,chain}

void print(pair<int,int> hashTable[],int size){
    cout<<endl;
    cout<<"Value"<<setw(5)<<"|"<<setw(7)<<"Chain"<<endl;
    for (int i=0;i<size;i++){
        cout<<setw(4)<<hashTable[i].first;
        cout<<setw(6)<<"|"<<setw(6)<<hashTable[i].second<<endl;
    }
    cout<<"\n....................................\n";
}

void clear(pair<int,int> hashTable[],int size){
    for (int i=0;i<size;i++){
        hashTable[i].first = -1;
        hashTable[i].second = -1;
    }
}

void updateChain(pair<int,int> rep,pair<int,int> hashTable[],int size){
    // rep is the pair of value replaced which is causing chainUpdate
    int loc = rep.first % size;
    int i = loc;
    int chainEnd = loc;
    while (hashTable[i].second != -1 && hashTable[i].second != rep.second){
        int next = hashTable[i].second;
        // if next value has a different hash then break because original 
        // value has been replaced from that location
        if (hashTable[next].first%SIZE != loc) break;
        i = next;
        chainEnd = i;
    }
        // when we reach the value which was replaced chain skips the next 
        // value after that and we break the loop
    hashTable[chainEnd].second = rep.second;
    return;
}

void insert(int val,pair<int,int> hashTable[],int size){
    cout<<"Value to insert: "<<val<<endl;
    int loc = val%size;
    // case 1 there is no value at loc
    if (hashTable[loc].first==-1){
        cout<<"CASE 1"<<endl;
        cout<<"Inserted "<<" at index "<<loc<<endl;
        hashTable[loc].first = val;
        hashTable[loc].second = -1;
        return;
    }
    // case 2 there is a value at loc and hash (last digit) matches
    if (hashTable[loc].first!=-1 &&hashTable[loc].first%size==loc){
        cout<<"CASE 2"<<endl;
        int i = loc;
        int chainEnd = loc;
        // if chain exists then follow it till it ends and store the index 
        // where it ends
        while (hashTable[i].second != -1){
            i = hashTable[i].second;
            chainEnd = i;
        }
        // find the first empty location after chain ends and insert value 
        // at that location also update chain end to store location where 
        // value was inserted
        do {
            if (hashTable[i].first==-1 || hashTable[i].first==-2){
                cout<<"Inserted "<<" at index "<<i<<endl;
                hashTable[i].first = val;
                // updating the end of the chain
                if (chainEnd!=-1) hashTable[chainEnd].second = i;
                return;
            }
            i = i+1;
            if (i==size) i = 0;
        } while (i!=loc);
        cout<<"Table full. Could not insert value "<<val<<endl;
        return;
    }
    // case 3 there is a value at loc and hash (last digit) does not match
    // in this case replacement will be done
    if (hashTable[loc].first!=-1 && hashTable[loc].first%size!=loc){
        pair<int,int> replaced = hashTable[loc];
        // the value which will be replaced
        // insert the value
        hashTable[loc].first = val;
        hashTable[loc].second = -1;
        cout<<"Inserted  at index "<<loc<<endl;
        cout<<"...................................."<<endl;
        updateChain(replaced,hashTable,SIZE);
        print(hashTable,SIZE);
        insert(replaced.first,hashTable,SIZE);
        return;
    }
}

int search(int key,pair<int,int> hashTable[],int size){
    int loc = key%SIZE;
    // case 1 if loc is empty we can say that value does not exist in hashTable
    if (hashTable[loc].first==-1){
        cout<<"CASE 1"<<endl;
        cout<<"Value not found in hash table"<<endl;
        return -1;
    }
    // case 2 loc is not empty, last digit matches
    if (hashTable[loc].first!=-1 &&hashTable[loc].first%size==loc){
        cout<<"CASE 2"<<endl;
        int i = loc;
        int chainEnd = loc;
        // follow the chain if it exists till end or till value is found
        do{
            if (hashTable[i].first==key) {
                cout<<"Value "<<key<< " found at index: "<<i<<endl;
                return i;
            }
            i = hashTable[i].second;
        }while (hashTable[i].second != -1);
        // if the chain ends and value is not found then it is not in hash table
        cout<<"Value "<<key<<" was not found in the table"<<endl;
        return -1;
    }
    // case 3 loc is not empty, last digit does not match
    // in this case also the value does not exist in our hashTable
    return -1;
}

void remove(int key,pair<int,int> hashTable[],int size){
    int index = search(key,hashTable,size);
    if (index==-1) cout<<key<<" does not exist in the hash table"<<endl;
    else{
        pair<int,int> removed = hashTable[index];
        hashTable[index].first = -2;
        hashTable[index].second = -1;
        cout<<"Deleted "<<key<<" from hash table"<<endl;
        updateChain(removed,hashTable,SIZE);
    }
}

int main(){
    pair<int,int> hashTable[SIZE];
    clear(hashTable,SIZE);

    insert(22,hashTable,SIZE);
    print(hashTable,SIZE);

    insert(12,hashTable,SIZE);
    print(hashTable,SIZE);
    
    insert(33,hashTable,SIZE);
    print(hashTable,SIZE);

    insert(44,hashTable,SIZE);
    print(hashTable,SIZE);

    insert(66,hashTable,SIZE);
    print(hashTable,SIZE);

    insert(55,hashTable,SIZE);
    print(hashTable,SIZE);

    insert(13,hashTable,SIZE);
    print(hashTable,SIZE);

    insert(43,hashTable,SIZE);
    print(hashTable,SIZE);

    // search(33,hashTable,SIZE);
    // search(52,hashTable,SIZE);

    // remove(77,hashTable,SIZE);
    // remove(72,hashTable,SIZE);
    // print(hashTable,SIZE);
}