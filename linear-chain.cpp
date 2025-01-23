#include<iostream>
#include<utility>
using namespace std;

void insert(int val,pair<int,int> hashTable[],int size){
    cout<<"Value to insert: "<<val<<endl;
    int loc = val%size;
    // case 1 loc is empty
    if (hashTable[loc].first==-1){
        cout<<"CASE 1"<<endl;
        cout<<"Inserted "<<" at index "<<loc<<endl;
        hashTable[loc].first = val;
        return;
    }
    // case 2 loc is not empty,hash matches
    if (hashTable[loc].first!=-1 &&hashTable[loc].first%size==loc){
        cout<<"CASE 2"<<endl;
        int i = loc;
        int chainEnd = loc;
        while (hashTable[i].second != -1){
            i = hashTable[i].second;
            chainEnd = i;
        }
        
        do {
            if (hashTable[i].first==-1 || hashTable[i].first==-2){
                cout<<"Inserted "<<" at index "<<i<<endl;
                hashTable[i].first = val;
                if (chainEnd!=-1) hashTable[chainEnd].second = i;
                return;
            }
            i = i+1;
            if (i==size) i = 0;
        } while (i!=loc);
        cout<<"Table full. Could not insert value "<<val<<endl;
        return;
    }
    // case 3 loc is not empty, hash does not match
    if (hashTable[loc].first!=-1 && hashTable[loc].first%size!=loc){
        cout<<"CASE 3"<<endl;
        int i = loc;
        do {
            if (hashTable[i].first==-1 || hashTable[i].first==-2){
                cout<<"Inserted "<<" at index "<<i<<endl;
                hashTable[i].first = val;
                return;
            }
            i = i+1;
            if (i==size) i = 0;
        } while (i!=loc);
        cout<<"Table full. Could not insert value "<<val<<endl;
        return;
    }
}

int search(int key,pair<int,int> hashTable[],int size){
    int loc = key%10;
    // case 1 if loc is empty we can say that value does not exist in hashTable
    if (hashTable[loc].first==-1){
        cout<<"CASE 1"<<endl;
        cout<<"Value not found in hash table"<<endl;
        return -1;
    }
    // case 2 loc is not empty, last digit matches
    if (hashTable[loc].first!=-1 &&hashTable[loc].first%size==loc){
        // follow the chain if it exists till end or till value is found
        cout<<"CASE 2"<<endl;
        int i = loc;
        int chainEnd = loc;
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
    if (hashTable[loc].first!=-1 && hashTable[loc].first%size!=loc){
        // in this case there is no chain to follow we proceed with linear probing
        cout<<"CASE 3"<<endl;
        int i = loc;
        do {
            if (hashTable[i].first==-1){
                cout<<"Value "<<key<<" was not found in the table"<<endl;
                return -1;
            }
            if (hashTable[i].first==key){
                cout<<"Value "<<key<< " found at index: "<<i<<endl;
                return i;
            }
            i = i+1;
            if (i==size) i = 0;
        } while (i!=loc);
        cout<<"Value "<<key<<" was not found in the table"<<endl;
        return -1;
    }
}

void remove(int key,pair<int,int> hashTable[],int size){
    int index = search(key,hashTable,size);
    if (index==-1) cout<<key<<" does not exist in the hash table"<<endl;
    else{
        hashTable[index].first = -2;
        hashTable[index].second = -1;
        cout<<"Deleted "<<key<<" from hash table"<<endl;
    }
}

void print(pair<int,int> hashTable[],int size){
    for (int i=0;i<size;i++){
        cout<<hashTable[i].first<<" "<<hashTable[i].second;
        cout<<endl;
    }
    cout<<"\n....................................\n";
}

void clear(pair<int,int> hashTable[],int size){
    for (int i=0;i<size;i++){
        hashTable[i].first = -1;
        hashTable[i].second = -1;
    }
}

int main(){
    pair<int,int> hashTable[10];
    clear(hashTable,10);

    insert(55,hashTable,10);
    print(hashTable,10);

    insert(26,hashTable,10);
    print(hashTable,10);
    
    insert(15,hashTable,10);
    print(hashTable,10);

    insert(95,hashTable,10);
    print(hashTable,10);

    insert(77,hashTable,10);
    print(hashTable,10);

    insert(17,hashTable,10);
    print(hashTable,10);

    search(17,hashTable,10);
    search(15,hashTable,10);
    search(77,hashTable,10);
    remove(77,hashTable,10);
    print(hashTable,10);
}