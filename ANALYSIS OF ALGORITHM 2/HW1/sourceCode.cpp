#include <iostream>
#include <list>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <math.h>
#include <queue>
#include <algorithm>
#include <stack>
#include <time.h>
using namespace std;
//@Student Name: Dogu Can ELCI
//@Student Number: 504201516
//Analysis of Algorithms 2 HW-1

struct node{    //structure of vertices(nodes) of tree
    node *child[10];        //child nodes of per node
    int level=0;            //tree depth of node
    int data;               //hold data 0 to 9
    vector<int> matrix;     //hold previous node's datas
    void create_tree(int ,int ,node*);  
    vector<int> BFS(vector <int>,node *,vector <vector<int>>,node*);
    bool control_mechanism(vector <vector<int>> , vector <int>);
    void create_matrix(int);
    vector<int> DFS(vector <int>,node *,vector <vector<int>>,stack <node*>,node *,node *);
};
//**************************start of tree_func***
    void node::create_tree(int counter,int a,node* newnode){ //tree building function

    for(int i=0;i<10;i++){
    child[i] = new node;
    newnode->data++;
    child[i]->create_matrix(a);                 //this function is used to prepare matrix structure of each node
    for(int k=0;k<a;k++){   
        child[i]->matrix[k] = matrix[k];        //child gets previous node's information into own matrix
    }   
    child[i]->level = counter;                  //child saves depth of tree information into its level argument
    child[i]->data = i;                         //child gets its own data information into the data argument
    child[i]->matrix[child[i]->level-1] = i;    //child gets its own data information into the matrix
    if(child[i]->level==a){         //if this depth is last level of tree
        for(int j=0;j<10;j++){
            child[i]->child[j]=NULL; //all children of last nodes must be NULL  
        }
    }
    if(child[i]!=NULL && child[i]->data!=data){ 
        int x = 0;                              //this loop is used to eliminate tree nodes because of some distinction between nodes.
        for(int k= 0;k<child[i]->level;k++){    //this loop is control whether and child or grand child of node carray same data value.
        for(int t=0;t<child[i]->level;t++){     //limit is chosen as level value, because other depths are not reached yet.
            if(child[i]->matrix[k]==child[i]->matrix[t]){   
                x++;        //it can enter this loop just one time,because it compare with itself.
            }
            if(x>1){        //if there is another node from child's parents of grandparents which is equal its data value,               
                goto go;    //it is obviously not a result,so it goes to go loop for labeled as NULL.
            }
        }
                x=0;
    }
        
    if(child[i]->level<a){          //if child node is not in last depth level of tree,it recurses,until nodes are in last depth level.
        counter++;                  //counter is used to determine current level of any nodes.
        child[i]->create_tree(counter,a ,newnode); //it recurses and its arguments are current node's children nodes.
        counter--;                  //when recursive function is finished,previous level is described.
    }
    }
    else{
    go:
       child[i]=NULL;               //it is obviously not a result,so this node is labeled as NULL,so it cant allocate useless memory.
       
    }
    }
    return;
    }

//**************************finish of create_tree**************************


//******************************BFS******************************
    vector<int> node::BFS(vector <int> general_array,node *firstnode,vector <vector<int>> opnums,node* newnode1){
        
        queue<node *> q;    //the queue holds nodes which are not visited yet according to BFS Algorithm.
        q.push(firstnode);  //First step,first node(0) is pushed into thw queue.
        newnode1->data++;   //it stores total visited nodes number.
        while(!q.empty()){  //In this loop, every child node of first node are searched by BFS Algorithm.
            node *n = q.front(); //it saves information of node which will be removed from queue.
            q.pop();            //node is removed from queue.
            bool cont5=true;    //it is used to control whether general_array has any dublicates.
            if(n->level!=0){    //it is used to pass first node iteration.
                for(int k=0;k<general_array.size();k++) //this for loop update elements of general_array which carry numbers correspond to any letter.
                    general_array[k] = n->matrix[k];   
            }
            bool result=false; //if result bool value is true,it means that true result is found and operation is finished.
            int x=0;
               for(int k= 0;k<general_array.size();k++){ //this loop is used to determine if any element of general_array has any dublicate numbers.
                   for(int t=0;t<general_array.size();t++){
                       if(general_array[k]==general_array[t]){
                           x++;
                       }
                       if(x>1){     //if any dublication is determined, cont5 is false.
                           cont5=false;
                           goto jump;
                       }
                           }
                           x=0;
                       }
           jump:
           if(cont5){
            result = control_mechanism(opnums,general_array); //if cont5 is not false,general_array can be true solution,so it should be controlled by this function.
           } 
            if(result){ //if result value change as true value by control_mechanism function, tru solution is found.
                return general_array;   //general_array is returned.
            }

            for(int i=0; i<10; i++)
                if(n->child[i]==NULL){  //if any null node is determined,it can be passed.
                    continue;
                }
                else{
                    newnode1->data++;       //it stores total visited nodes number.(for child nodes).
                    q.push(n->child[i]);    //all child nodes except NULL ones are pushed into queue for searching.
                }
                
        }
        return general_array;   //general_array is returned.
    }
//******************************BFS******************************


//******************************DFS******************************

vector<int> node::DFS(vector <int> general_array,node *firstnode,vector <vector<int>> opnums,stack <node*> st,node *finisher,node *newnode){
try{
    for(int i=0;i<10;i++){
        if(st.size()==0){
            st.push(firstnode);
        }
        if(level<general_array.size()-1){
            node *n = new node;
            n=child[i];
            st.push(n);
            n=st.top();
            if(n!=NULL){
                newnode->data++;
            n->DFS(general_array,firstnode,opnums,st,finisher,newnode);
            st.pop();
            }
        }
    else{
        if(child[i]!=NULL){
        if(level!=0){
        
        for(int k=0;k<general_array.size();k++)
            if(child[i]!=NULL && finisher->data==0){
                general_array[k] = child[i]->matrix[k];
            }     
    }
    bool cont5=true;
    bool result=false; //bunlar rakam degil index
    int x=0;
        for(int k= 0;k<general_array.size();k++){
            for(int t=0;t<general_array.size();t++){
                if(general_array[k]==general_array[t]){
                    x++;
                }
                if(x>1){
                    cont5=false;
                    goto jump;
                }
                    }
                    x=0;
                }
    jump:
    if(cont5){
    result = control_mechanism(opnums,general_array); 
    }     
    if(result && finisher->data==0){
        int x=0;
    finisher->data=-11;
        for (auto i = general_array.begin(); i != general_array.end(); ++i){
        newnode->matrix.push_back(*i);
    }

//    for(int i=0;i<general_array.size();i++){
//        newnode->data = general_array[i];
//        newnode->matrix.push_back(newnode->data);
//    }
    throw newnode->matrix;

    }
    }
    }
    }
    return newnode->matrix;
    }
    catch(vector<int> general_array1){
            return general_array1;
    }
    }
    
//******************************DFS******************************
    
//******************************CONTROL_MECHANISM******************************
bool node::control_mechanism(vector <vector<int>> opnums,vector <int> general_array){
    int op1_number=0;   //this value corresponds an integer value according to current node information which has operand2 order(arg2). 
    int op2_number=0;   //this value corresponds an integer value according to current node information which has operand3 order(arg3).
    int op3_number=0;   //this value corresponds an integer value according to current node information which has operand4 order(arg4).
    int op1_size = opnums[0].size();    //size of operand2 order(arg2)    
    int op2_size = opnums[1].size();    //size of operand3 order(arg3)
    int op3_size = opnums[2].size();    //size of operand4 order(arg4)

    vector <int> op_digit_numbers={0,0,0};

    for(int z=0;z<3;z++){   //this for loop create 3 integer value according to order of letters of arguments and current node's location.
    for(int i = 0;i<opnums[z].size();i++){
        op1_number+=pow(10,(opnums[z].size()-i-1))*general_array[opnums[z][i]]; 
    }
        op_digit_numbers[z] = op1_number;
        op1_number=0;
    }
    
    op1_number=op_digit_numbers[0];
    op2_number=op_digit_numbers[1];
    op3_number=op_digit_numbers[2];

    bool cont1 = op_digit_numbers[0]+op_digit_numbers[1]==op_digit_numbers[2];
    //cont2, cont3 and cont4 controls whether it has true number of digits.
    bool cont2= floor(op1_number/(pow(10,op1_size-1)))!=0;
    bool cont3= floor(op2_number/(pow(10,op2_size-1)))!=0;
    bool cont4= floor(op3_number/(pow(10,op3_size-1)))!=0;
    //cout<<op1_number<<" + "<<op2_number<<" = "<<op3_number<<endl;
   
    if(cont1 && cont2 && cont3 && cont4){   //if all constraints are true, so true solution is found.
        return true;
    }
    return false;
}
//******************************CONTROL_MECHANISM****************************** 


void node::create_matrix(int set_array_size){   //function is used to create empty matrix vectors which has set_array size.
    for(int i=0;i<set_array_size;i++){
        matrix.push_back(0);
    }

    return;
}


int main(int argc, char** argv1){
    clock_t start = clock();
 //arguman baslangici *************************************************************************    

//Argument reading part
    string s;
    string operation;       
    operation = argv1[1];   //it decided that function select as BFS or DFS.
vector<char> o1;        //char vector of argument1(operant1)
    s=argv1[2];
    std::copy(s.begin(), s.end(), std::back_inserter(o1));
    vector<char> o2;    //char vector of argument2(operant2)
    s=argv1[3];
    std::copy(s.begin(), s.end(), std::back_inserter(o2));
    vector<char> o3;    //char vector of argument3(operant3)
    s=argv1[4];
    std::copy(s.begin(), s.end(), std::back_inserter(o3));
    vector<char> o4;    
//Argument reading part 

//create sorted-non dublicates vector include all letters of previous 3 letter vector.
    for (auto i = o1.begin(); i != o1.end(); ++i){
        o4.push_back(*i);
    }

    for (auto i = o2.begin(); i != o2.end(); ++i){
    o4.push_back(*i);
    }

    for (auto i = o3.begin(); i != o3.end(); ++i){
    o4.push_back(*i);
    }
    
sort( o4.begin(), o4.end() );
o4.erase( unique( o4.begin(), o4.end() ), o4.end() );
//create sorted-non dublicates vector include all letters of previous 3 letter vector.

 //arguman bitisi************************************************************************


    vector <int> opnum1;            
    vector <int> opnum2;
    vector <int> opnum3;
    vector <vector<char>> ops = {o1,o2,o3}; 
    vector <vector<int>> opnums = {opnum1,opnum2,opnum3};   //store index information for per operands
    vector <char> set_array= o4;    //argument icin
    //vector <int> set_array={'t','w','o','f','u','r'}; // t:0 w:1 o:2 f:3 u:4 r:5 setlenmis array
    //op1 , op2 indexlerini set_arraye gore bulup kaydediyor. asil array, general_array
    
    //In this for loop,all letters which char vectors(o1,o2,o3) has,compare to letters of set_array(non-dublicates vector)
    //and find where is the letters which equal to letters of char vectors
    //Then pushed into operation number integer vectors.
    //Actually every level of the node tree correspond a letter and order of this level directly connected to order of set_array
    //and each node has matrix which has set_array size.
    //In any algorithm search process, arg2+arg3 must be equal arg4,so we have to know index of arg2 and arg3 for update their digits for control. 
    for(int z=0;z<3;z++){   //3 operants
    for(int i=0;i<ops[z].size();i++){   //n-variable(n different letters)
        for(int j=0;j<set_array.size();j++){
            if(ops[z][i]==set_array[j]){
                opnums[z].push_back(j);
            }
        }
    }
}

    
    int element_numb = set_array.size(); //number of distinct letters
    vector <int> general_array;         //every iteration general_array is updated by new node's matrix information.(location)
    for(int i=0;i<element_numb;i++)     //set_array size general array is created with 0 values.
        general_array.push_back(0);

    node *firstnode = new node;
    firstnode->data = -1;
    firstnode->level = 0;
    int allocnode;  //it records total node of tree which are allocated by RAM.
    allocnode=0;
    firstnode->create_matrix(set_array.size());
    node *newnode = new node;
    newnode->data = 0;  //this node is used for record allocnode memory in create_tree function.
    firstnode->create_tree(1,element_numb,newnode);   //creation of tree node
    allocnode =newnode->data; //allocnode value is found.
    vector<int> general_array1; //it is defined for return values.
    if(operation=="bfs"){       //if arg[1] is "bfs"
        node *newnode1=new node;
        newnode1->data = 0;
        general_array1=firstnode->BFS(general_array,firstnode,opnums,newnode1);

        cout<<"Algorithm: "<<operation<<endl;
        cout<<"Number of visited nodes: "<<newnode1->data<<endl;
        cout<<"Maximum number of nodes kept in the memory: "<<allocnode<<endl;
        cout << "Running time: " << (double)(clock() - start) / (double)CLOCKS_PER_SEC << std::endl;
    }
    else if(operation=="dfs"){  //if arg[1] is "dfs"
        stack <node*> st;   //this stack is used for store unvisited nodes.
        node *finisher = new node;
        finisher->data=0;
        node *newnode = new node;   //this node is used to store genaral_array values.
        general_array1=firstnode->DFS(general_array,firstnode,opnums,st,finisher,newnode);
        cout<<"Algorithm: "<<operation<<endl;
        cout<<"Number of visited nodes: "<<newnode->data<<endl;
        cout<<"Maximum number of nodes kept in the memory: "<<allocnode<<endl;
        cout << "Running time: " << (double)(clock() - start) / (double)CLOCKS_PER_SEC << std::endl; 
        
    }
 
//write to file part
    s=argv1[5];
    ofstream myfile;
    myfile.open (s);
    for(int i=0 ;i<general_array1.size()+1;i++){
        if(i!=0){
            myfile<<o4[i];
        }
        for(int j=0;j<10;j++){
            if(i==0){
                myfile<<"\t"<<j;
            }
            else{    
                if(general_array1[i-1]==j){
                myfile<<"\t"<<'1';
                }
                else{
                    myfile<<"\t"<<'.';
                }
                
            }

        }
        myfile<<"\n"<<endl;
    }
//write to file part

    getchar();
    return 0;
}