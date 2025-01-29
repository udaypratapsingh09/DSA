#include<iostream>

using namespace std;

const int SIZE = 10;

void insert(int val,int hashTable[],int size){
    int loc = val % size;
    int i = loc;
    do {
        if (hashTable[i]==-1 || hashTable[i]==-2){
            cout<<"Inserted "<<val<<" at index "<<i<<endl;
            hashTable[i] = val;
            return;
        }
        i = i+1;
        if (i==size) i = 0;
    } while (i!=loc);
    cout<<"Table full. Could not insert value "<<val<<endl;
}

void search(int key,int hashTable[],int size){
    int loc = key % size;
    int i = loc;
    do {
        if (hashTable[i]==-1){
            cout<<"Value "<<key<<" was not found in the table"<<endl;
            return;
        }
        if (hashTable[i]==key){
            cout<<"Value "<<key<<" was found at index: "<<i<<endl;
            return;
        }
        i = i+1;
        if (i==size) i = 0;
    } while (i!=loc);
    cout<<"Value "<<key<<" was not found in the table"<<endl;
}

void del(int key,int hashTable[],int size){
    int loc = key % size;
    int i = loc;
    do {
        if (hashTable[i]==-1){
            cout<<"Value "<<key<<" was not found in the table"<<endl;
            return;
        }
        if (hashTable[i]==key){
            hashTable[i] = -2;
            return;
        }
        i = i+1;
        if (i==size) i = 0;
    } while (i!=loc);
    cout<<"Value "<<key<<" was not found in the table"<<endl;
}

void clear(int hashTable[],int size){
    for (int i=0;i<size;i++){
        hashTable[i] = -1;
    }
}

void print(int hashTable[],int size){
    for (int i=0;i<size;i++){
        cout<<hashTable[i]<<endl;
    }
    cout<<endl;
}

int main(){
    int hashTable[SIZE];
    clear(hashTable,SIZE);
    insert(22,hashTable,SIZE);
    insert(12,hashTable,SIZE);
    insert(33,hashTable,SIZE);
    insert(44,hashTable,SIZE);
    insert(66,hashTable,SIZE);
    insert(55,hashTable,SIZE);
    insert(13,hashTable,SIZE);
    insert(43,hashTable,SIZE);

    print(hashTable,SIZE);
}