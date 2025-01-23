#include<iostream>

using namespace std;

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
        cout<<hashTable[i]<<" ";
    }
    cout<<endl;
}

int main(){
    int hashTable[10];
    clear(hashTable,10);

    int ans=1;
    while (ans!=0){
        // menu
        cout<<"0. Exit\n";
        cout<<"1. Insert a value\n";
        cout<<"2. Search a value\n";
        cout<<"3. Delete a value\n";
        cout<<"4. Clear table\n";
        cin>>ans;

        if (ans==1){
            int val;
            cout<<"Enter value to insert: ";
            cin>>val;
            insert(val,hashTable,10);
            print(hashTable,10);
        }

        else if (ans==2){
            int key;
            cout<<"Enter key to search: ";
            cin>>key;
            search(key,hashTable,10);
            print(hashTable,10);
        }

        else if (ans==3){
            int key;
            cout<<"Enter key to delete: ";
            cin>>key;
            del(key,hashTable,10);
            print(hashTable,10);
        }

        else if (ans==4){
            clear(hashTable,10);
            print(hashTable,10);
        }
        cout<<"\n***************************************\n\n";
    }
}