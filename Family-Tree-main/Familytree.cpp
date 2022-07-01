/*Author: Anjali Marwaha
  Roll No: 2020UIT3119
*/
#include<stdio.h>
class tnode{
    int value,generation;
    class tnode *parent;
    class LinkedList *child_list;
    tnode(int q);
friend class LinkedList;
friend class Node;
friend class FamilyTree;
};

tnode::tnode(int q){
    value=q;
    generation=0;
    parent=NULL;
    child_list=NULL;
}

class Node{
    class tnode *ele;
    class Node *nxt;
    friend class FamilyTree;
friend class LinkedList;
};

class LinkedList{
public:
    class Node *head;
    class Node *tail;
    int length;
    LinkedList();//{head=NULL;tail=NULL;length=0;}
    void addback(class tnode *n);
    int len();
    class Node* top();
};
LinkedList::LinkedList(){
    head=NULL;
    tail=NULL;
    length=0;
}

void LinkedList::addback(class tnode *n){
    if (tail==NULL)
    {
        tail = new Node;
        tail->ele=n;
        tail->nxt=NULL;
        head=tail;
        length++;
    }
    else
    {
        class Node *temp=tail;
        tail = new Node;
        tail->ele=n;
        temp->nxt=tail;
        tail->nxt=NULL;
        length++;
    }
}

int LinkedList::len(){
    return length;
}

class Node* LinkedList::top(){
    return head;
}
//This is Familiy Tree class
class FamilyTree{
private:
    class tnode *root;
public:
    FamilyTree(int q);
    ~FamilyTree();
    class tnode* search(int x);
    class tnode* find(int x,class tnode *tr);
    class tnode* remove(class tnode *tr);
    void insertChild(int x,int y);
    int ischild(int x,int y);
    int isgrandparent(int x,int y);
    int isgrandchild(int x,int y);
    bool inchildlist(tnode* dummy,tnode* check);
    int isNephew(class tnode* temp,class tnode* temp_1);
    int isUncle(class tnode* temp,class tnode* temp_1);
    void print(int x,const char arr[],int i,int j);
    int isCousin(class tnode *temp,class tnode *temp_1 );
    void relationship(int x,int y);
};

FamilyTree::FamilyTree(int q){
    root = new tnode(q);
}

FamilyTree::~FamilyTree(){
    remove(root);
}

class tnode* FamilyTree::search(int x){
    return find(x,root);
}

class tnode* FamilyTree::find(int x,class tnode *tr){
    class tnode* found;
    if (tr->value==x)  return tr;
    if (tr->child_list==NULL) return NULL;
    class Node *temp = tr->child_list->top();
    for(int i=0;i<(tr->child_list->len());i++){
        found= find(x,temp->ele);
        if(found!=NULL) return found;
        temp=temp->nxt;
    }
    return NULL;
}

class tnode* FamilyTree::remove(class tnode *tr){
    class tnode* found;
    if (tr->child_list==NULL) { delete tr; return NULL;}
    class Node *temp = tr->child_list->head;
    while(temp!=NULL){
        found=remove(temp->ele);
        temp=temp->nxt;
    }
    delete tr;
    return NULL;
}

void FamilyTree::insertChild(int x,int y){
    class tnode* temp = search(x);
    if (temp==NULL) {
        printf("No parent found\n");
        return;
    }
    tnode *node = new tnode(y);
    node->parent=temp;
    node->generation=temp->generation+1;
    if(temp->child_list==NULL)
        temp->child_list= new LinkedList();
    temp->child_list->addback(node);
}

int FamilyTree::ischild(int x,int y){
    class tnode *temp =find(x,root);
    if( temp==root) return 0;
    Node* temp_1=temp->parent->child_list->head;
    while(temp_1!=NULL){
        if (temp_1->ele->value==y){
            printf("%d and %d are siblings\n",x,y);
            return 1;
        }
        temp_1=temp_1->nxt;
    }
    return 0;
}

int FamilyTree::isgrandparent(int x,int y){
    class tnode* temp= find(y,root);
    int count=0;
    while(temp!=NULL){
        if (temp->value==x){
            print(count,"Parent",x,y);
            return 1;
        }
        count++;
        temp=temp->parent;
    }
    return 0;
}

int FamilyTree::isgrandchild(int x,int y){
    class tnode* temp= find(x,root);
    int count=0;
    while(temp!=NULL){
        if (temp->value==y){
            print(count,"Child",x,y);
            return 1;
        }
        count++;
        temp=temp->parent;
    }
    return 0;
}

bool FamilyTree::inchildlist(tnode* dummy,tnode* check){
    if(dummy->parent==NULL) return false;
    Node* temp= dummy->parent->child_list->head;
    while(temp!=NULL){
        if (temp->ele->value==check->value)
            return true;
        temp=temp->nxt;
    }
    return false;
}

int FamilyTree::isNephew(class tnode* temp,class tnode* temp_1){
    class tnode *iter= temp;
    int count=1;
    while(iter->parent!=NULL){
        iter=iter->parent;
        if (inchildlist(temp_1,iter)==true) {
            print(count,"Nephew/Niece",temp->value,temp_1->value);
            return 1;
        }
        count++;
    }
    return count;
}

int FamilyTree::isUncle(class tnode* temp,class tnode* temp_1){
    class tnode *iter= temp_1;
    int count=1,k=0;
    while (iter->parent!=NULL)
    {
        iter=iter->parent;
        if (inchildlist(temp,iter)==true) {
            print(count,"Uncle/Aunt",temp->value,temp_1->value);
            k=1;
            return 1;
        }
        count++;
    }
    return count;
}

void FamilyTree::print(int x,const char arr[],int i,int j){
    char plus[4][18]={"","Grand","Great Grand","Great Great Grand"};
    if (arr[0]=='C'|| arr[0]=='P'||arr[0]=='U'||arr[0]=='N'){
        if(x<5)
            printf("%d is %s %s of %d\n",i,plus[x-1],arr,j);
        else
            if(x==5)
                printf("%d is %drd %s %s of %d\n",i,x-2,plus[2],arr,j);
            else
                printf("%d is %dth %s %s of %d\n",i,x-2,plus[2],arr,j);
    }
}

int FamilyTree::isCousin(class tnode *temp,class tnode *temp_1 ){
    tnode *iter= temp;
    tnode *iter_1= temp_1;
    char lls[4][3]={"st","nd","rd","th"};
    char lln[4][7]={"once","twice","thrice","times"};
    if(temp->generation<temp_1->generation){
        int count=0,gen1,gen2;
        gen1=temp_1->generation;
        gen2=temp->generation;
        for(int i=0;i<gen1-gen2;i++){
            temp_1=temp_1->parent;
        }
        while(temp!=temp_1){
            temp=temp->parent;
            temp_1=temp_1->parent;
            count++;
        }
        if (temp==temp_1)
        {	int k=count-1;
            if(k<3)
                printf("%d is %d%s cousin %d times removed of %d\n",iter->value,count-1,lls[k-1],gen1-gen2,iter_1->value);
            else
                printf("%d is %d%s cousin %d times removed of %d\n",iter->value,count-1,lls[3],gen1-gen2,iter_1->value);
            return 1;
        }
    }
    else if(temp->generation>temp_1->generation){
        int count=0,gen1,gen2;
        gen2=temp_1->generation;
        gen1=temp->generation;
        for(int i=0;i<gen1-gen2;i++){
            temp=temp->parent;
        }
        while(temp!=temp_1){
            temp=temp->parent;
            temp_1=temp_1->parent;
            count++;
        }
        if (temp==temp_1)
        {	int k=count-1;
            if(k<3)
                printf("%d is %d%s cousin %d times removed of %d\n",iter->value,count-1,lls[k-1],gen1-gen2,iter_1->value);
            else
                printf("%d is %d%s cousin %d times removed of %d\n",iter->value,count-1,lls[3],gen1-gen2,iter_1->value);
            return 1;
        }
    }
    else {
        int count=0;
        int gen1=temp->generation;
        int gen2=temp_1->generation;
        int k=gen1-(gen1-gen2)-1;
        while(temp!=NULL){
            temp=temp->parent;
            temp_1=temp_1->parent;
            if(temp==temp_1) {printf("%d is %d%s cousin of %d\n",iter->value,count,lls[count-1],iter_1->value); return 1;}
            count++;
        }
    }
    return 0;
}

void FamilyTree::relationship(int x,int y){
    tnode* temp= find(x,root);
    tnode* temp_1= find(y,root);
    if( x==y ) {printf("Both are same menbers\n"); return;}
    if(temp==NULL || temp_1==NULL){
        printf("%d and %d are unrelated\n",x,y);
        return;
    }

    if (ischild(x,y)==1) return;
    if(temp->generation<=temp_1->generation){
            if(isgrandparent(x,y)==1) return;
            if(isUncle(temp,temp_1)==1 ) return;
            if(isCousin(temp,temp_1)==1) return;
    }
    else{
        if (isgrandchild(x,y)) return;
        if (isNephew(temp,temp_1)==1) return;
        if (isCousin(temp,temp_1)==1) return;
    }
}
int main(){
   class FamilyTree ft(30);
	ft.insertChild(30,20);
	ft.insertChild(20,15);
	ft.insertChild(15,3);
	ft.insertChild(15,16);
	ft.insertChild(16,17);
	ft.insertChild(17,18);
	ft.insertChild(3,8);
	ft.insertChild(8,10);
	ft.insertChild(3,4);
	ft.insertChild(3,11);
	ft.insertChild(3,12);
	ft.insertChild(4,5);
	ft.insertChild(4,6);
	ft.insertChild(6,7);
	ft.insertChild(10,13);
	ft.insertChild(4,100);
    ft.insertChild(100,101);
    ft.insertChild(101,102);
    ft.insertChild(102,103);
    ft.insertChild(103,104);
    ft.insertChild(104,105);
	ft.relationship(4,5);
	ft.relationship(10,7);
	ft.relationship(18,13);
	ft.relationship(4,6);
	ft.relationship(8,4);
	ft.relationship(8,17);
	ft.relationship(10,5);
	ft.relationship(16,10);
	ft.relationship(3,10);
	ft.relationship(3,13);
	ft.relationship(16,13);
	ft.relationship(15,13);
	ft.relationship(30,13);
	ft.relationship(40,13);
	ft.relationship(20,30);
	ft.relationship(5,4);
	ft.relationship(7,10);
	ft.relationship(13,18);
	ft.relationship(6,4);
	ft.relationship(4,8);
	ft.relationship(17,8);
	ft.relationship(5,10);
	ft.relationship(10,16);
	ft.relationship(10,3);
	ft.relationship(13,3);
	ft.relationship(13,16);
	ft.relationship(13,15);
	ft.relationship(13,30);
	ft.relationship(13,40);
	ft.relationship(30,20);
    ft.relationship(105,7);
    ft.relationship(105,5);
}
