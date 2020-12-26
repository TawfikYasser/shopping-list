#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include<bits/stdc++.h>
using namespace std;

class Item{
public:
    char name[15],category[15],quanity[15];
};
struct PrimaryIndex{
    int RRN;
    char name[15];
    bool operator<(const PrimaryIndex &pIndex){
        return strcmp(name,pIndex.name) < 0;
    }
};
struct SecondaryIndex{
    char category[15];
    char name[15];
    bool operator<(const SecondaryIndex &sIndex){
        if(strcmp(category,sIndex.category) == 0)
            return strcmp(name,sIndex.name) < 0;
        return strcmp(category,sIndex.category) <0;
    }
};
/*int getRecordRRN(PrimaryIndex primaryIndexArray[],int numberOfRecords, string name){
    int RRN = -1;
    int left = 0 , middle, right = numberOfRecords - 1;
    while(left <= right){
        middle = (left+right) / 2;
        if(strcmp(name,primaryIndexArray[middle].name) < 0){
            right = middle-1;
        }else if(strcmp(name,primaryIndexArray[middle].name) > 0){
            left = middle+1;
        }else{
            RRN = primaryIndexArray[middle].RRN;
            break;
        }
    }
    return RRN;
}*/
void writePrimaryIndexToFile(PrimaryIndex primaryIndexArray[], int numberOfRecords, fstream &primaryIndexFile){
    for(int i =0 ;i< numberOfRecords;i++)
        primaryIndexFile.write((char*) &primaryIndexArray[i],sizeof(primaryIndexArray[i]));
}
void writeSecondaryIndexToFile(SecondaryIndex secondaryIndexArray[], int numberOfRecords, fstream &secondaryIndexFile){
    for(int i =0 ; i<numberOfRecords;i++)
        secondaryIndexFile.write((char*) &secondaryIndexArray[i],sizeof(secondaryIndexArray[i]));
}
void readPrimaryIndexFromFile(PrimaryIndex primaryIndexArray[], int numberOfRecords, fstream &primaryIndexFile){
    for(int i =0 ;i<numberOfRecords;i++)
        primaryIndexFile.read((char*) &primaryIndexArray[i],sizeof(primaryIndexArray[i]));
}
void addItem(int numberOfRecords){

    fstream dataFile,primaryIndexFile,secondaryIndexFile;
    dataFile.open("Items.txt",ios::out);
    primaryIndexFile.open("primaryIndexFile.txt",ios::out);
    secondaryIndexFile.open("secondaryIndexFile.txt",ios::out);

    PrimaryIndex *primaryIndexArray = new PrimaryIndex[numberOfRecords];
    SecondaryIndex *secondaryIndexArray = new SecondaryIndex[numberOfRecords];
    Item *itemsArray = new Item[numberOfRecords];
    for(int i = 0 ; i < numberOfRecords ; i++ ){
        Item tempItem;
        cout<<"Enter Item "<<(i+1)<<" name (Maximum 15 chars): ";
        cin>>tempItem.name;
        cout<<"Enter Item "<<(i+1)<<" category (Maximum 15 chars): ";
        cin>>tempItem.category;
        cout<<"Enter Item "<<(i+1)<<" quantity (Maximum 10 chars): ";
        cin>>tempItem.quanity;
        itemsArray[i] = tempItem;
        primaryIndexArray[i].RRN = i ;
        strcpy(primaryIndexArray[i].name,tempItem.name);
        strcpy(secondaryIndexArray[i].name,tempItem.name);
        strcpy(secondaryIndexArray[i].category,tempItem.category);
        dataFile.write((char*) &(itemsArray[i]),sizeof(itemsArray[i]));
    }
    sort(primaryIndexArray,primaryIndexArray+numberOfRecords);
    sort(secondaryIndexArray,secondaryIndexArray+numberOfRecords);

    writePrimaryIndexToFile(primaryIndexArray,numberOfRecords,primaryIndexFile);
    writeSecondaryIndexToFile(secondaryIndexArray,numberOfRecords,secondaryIndexFile);

    dataFile.close();
    primaryIndexFile.close();
    secondaryIndexFile.close();
}
void printAllNames(int numberOfRecords){
    fstream dataFile;
    dataFile.open("Items.txt",ios::in);
    Item item;
    for(int i = 0 ;i<numberOfRecords;i++){
            dataFile.seekg(i * sizeof(item),ios::beg);
            dataFile.read((char*) &item,sizeof(item));
            cout<<"Item #"<<(i+1)<<" name: "<<item.name<<endl;
    }

}
void printAllCategories(int numberOfRecords){
    fstream dataFile;
    dataFile.open("Items.txt",ios::in);
    Item item;
    for(int i = 0 ;i<numberOfRecords;i++){
            dataFile.seekg(i * sizeof(item),ios::beg);
            dataFile.read((char*) &item,sizeof(item));
            cout<<"Item #"<<(i+1)<<" category: "<<item.category<<endl;
    }

}
void searchByName(int numberOfRecords){
    fstream dataFile,primaryIndexFile;
    dataFile.open("Items.txt",ios::in);
    primaryIndexFile.open("primaryIndexFile.txt",ios::in);

    PrimaryIndex *primaryIndexArray = new PrimaryIndex[numberOfRecords];
    Item *itemsArray = new Item[numberOfRecords];

    char Name[15];
    Item item;
    int RRN;
    cout<<"Enter the item name: ";
    cin>>Name;
    //RRN = getRecordRRN(primaryIndexArray,numberOfRecords,Name);
}
void countItemsNames(int numberOfRecords){
    fstream dataFile;
    dataFile.open("Items.txt",ios::in);
    Item item;
    Item *itemsList = new Item[numberOfRecords];
    set<string> distinctListNames;
    int counter = 0;
    for(int i = 0 ;i<numberOfRecords;i++){
            dataFile.seekg(i * sizeof(item),ios::beg);
            dataFile.read((char*) &itemsList[i],sizeof(item));
            distinctListNames.insert(itemsList[i].name);
    }
    cout<<"Number of items in the shopping list = "<<distinctListNames.size()<<endl;

}
void countItemsCategories(int numberOfRecords){
    fstream dataFile;
    dataFile.open("Items.txt",ios::in);
    Item item;
    Item *itemsList = new Item[numberOfRecords];
    set<string> distinctListCategories;
    int counter = 0;
    for(int i = 0 ;i<numberOfRecords;i++){
            dataFile.seekg(i * sizeof(item),ios::beg);
            dataFile.read((char*) &itemsList[i],sizeof(item));
            distinctListCategories.insert(itemsList[i].category);
    }
    cout<<"Number of categories in the shopping list = "<<distinctListCategories.size()<<endl;

}
int main()
{
    //Starting of the program
    int numberOfRecords;
    cout<<"Please enter number of records you want to add: ";
    cin>>numberOfRecords;
    //Function to add new item to the data file if items.
    addItem(numberOfRecords);
    //printAllNames(numberOfRecords);
    //printAllCategories(numberOfRecords);
    //countItemsNames(numberOfRecords);
    //countItemsCategories(numberOfRecords);
    //searchByName(numberOfRecords);
    return 0;
}
