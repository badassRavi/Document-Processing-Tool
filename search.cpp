// Do NOT add any other includes
#include "search.h"

void mylove(string pat, int M, int* laluu) {
    int len = 0;
    laluu[0] = 0;
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) laluu[i++] = ++len;
        else if (len) len = laluu[len - 1];
        else laluu[i++] = 0;
    }
}

string to__lowerr(string s){
    string d="";
    for (char i:s){
        int k=i-'A';
        if (k>=0 && k<=25) i=i+32;
        d+=i;
    }
    return d;
}

void bassON(string pat, sentencenode* root,int &count,Node* &node,Node* &ptr) {
    int M = pat.length(), N = root->sentence.length();
    int laluu[M];
    mylove(pat, M, laluu);
    int i = 0, j = 0;
    while (N - i >= M - j) {
        if (pat[j] == root->sentence[i]) j++, i++;
        if (j == M) {
        
            if (node==nullptr) {
                node= new Node(root->book_code,root->page,root->paragraph,root->sentence_no,i-j);
                ptr=node;
                count++;
            }
            else {
                Node* t=new Node(root->book_code,root->page,root->paragraph,root->sentence_no,i-j);
                ptr->right=t;
                t->left=ptr;
                ptr=t;
                count++;
            }
            // cout << "Found at index " << i - j << " ";
            j = laluu[j - 1];
        } else if (i < N && pat[j] != root->sentence[i]) {
            j ? j = laluu[j - 1] : i++;
        }
    }
    return ;
}

sentencenode::sentencenode() {
    book_code=page=paragraph=sentence_no=0;
    sentence="we are terminals";
}

sentencenode::sentencenode(int b_code, int pg, int para, int s_no, string sen){
    book_code = b_code;
    page = pg;
    paragraph = para;
    sentence_no = s_no;
    sentence=sen;
}


SearchEngine::SearchEngine(){
    // Implement your function here  
    head=new sentencenode();
    tail=new sentencenode();
    head->next=tail;
    tail->prev=head;
}

SearchEngine::~SearchEngine(){
    // Implement your function here 
    sentencenode* temp=head;
    temp=temp->next;
    while (temp!=tail){
        sentencenode* delnode=temp;
        temp=temp->next;
        delete delnode;
    } 
    delete head;
    delete tail;
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here 
    sentence=to__lowerr(sentence);
    sentencenode* node=new sentencenode(book_code,page,paragraph,sentence_no,sentence);
    node->prev=tail->prev;
    node->next=tail;
    tail->prev->next=node;
    tail->prev=node;
    return;
}

Node* SearchEngine::search(string pattern, int& n_matches){
    // Implement your function here
    pattern=to__lowerr(pattern);
    Node* node=nullptr;
    Node* ptr=nullptr;
    int count=0;
    sentencenode* temp=head->next;
    while (temp!=tail){
        bassON(pattern,temp,count,node,ptr);
        temp=temp->next;
    }
    n_matches=count;
    return node;
}

// int main(){
//     SearchEngine s;
//     s.insert_sentence(1,1,1,1,"I am ravi");
//     string r="ravi";
//     int num=0;
//     s.search(r,num);
//     cout<<num<<endl;
//     return 0;
// }