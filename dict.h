// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class trienode {
public:
    bool endofword;
    int count;
    trienode* arr[53];

    trienode() : endofword(false) ,count(0) {
        for (int i=0;i<53;i++){
            arr[i]=nullptr;
        }
    }
    ~trienode(){
        for (int i=0;i<53;i++){
            if (arr[i]) delete arr[i];
        }
    }
};


class trie {
public:
    trienode* root;
    trie() : root(new trienode()) {}

    int asciii(char c){
        int k=c;
        if (k>=35 && k<=38) return k-35;
        else if (k==42 || k==43) return k-38;
        else if (k>=47 && k<=57) return k-41;
        else if (k>=60 && k<=63) return k-43;
        else if (k==92) return 21;
        else if (k>=94 && k<=122) return k-72;
        else if (k==124) return 51;
        else return 52;
    }

    int num(int k){
        if (k>=0 && k<=3) return k+35;
        else if (k==4 || k==5) return k+38;
        else if (k>=6 && k<=16) return k+41;
        else if (k>=17 && k<=20) return k+43;
        else if (k==21) return 92;
        else if (k>=22 && k<=50) return k+72;
        else if (k==51) return 124;
        else return 126;

    }



    void insert(string s) {
        trienode* temp = root;
        for (int c=0;c<s.size();c++) {
            int k = asciii(s[c]);
            if (!temp->arr[k]) {
                temp->arr[k] = new trienode();
            }
            temp = temp->arr[k];
        }
        temp->endofword = true;
        temp->count++;
    }

    int search(string s) {
        trienode* temp = root;
        for (char c : s) {
            int k = asciii(c);
            if (temp==nullptr || !temp->arr[k]) return 0;
            temp = temp->arr[k];
        }
        if (!temp->endofword) return 0;
        return temp->count;
    }

    void dumphelper(trienode* root,string path,string dumname){
    ofstream dumpfile(dumname,ios::app);
    if (root->endofword==true){
        dumpfile<<path<<","<<root->count<<endl;
    }
    string pathh=path;
    for (int i=0;i<53;i++){
        if (root->arr[i]) {
            pathh+=static_cast<char>(num(i));
            dumphelper(root->arr[i],pathh,dumname);
        }
        pathh=path;
    }
}

    void dump(string dumname){
        ofstream dumpfile(dumname ,ios::app);
        dumpfile.clear();
        string path="";
        dumphelper(root,path,dumname);
        dumpfile.close();
        }

    trienode* khtm(trienode* &root){
    if (!root) return nullptr;
    for (int i=0;i<53;i++){
        root->arr[i]=khtm(root->arr[i]);
    }
    delete root;
    root=nullptr;
    return nullptr;
    }

    ~trie(){
       root=khtm(root);
    }
};

class Dict {
private:
    trie sr;
    // You can add attributes/helper functions here

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};