//Student Name: Dogu Can ELCI
//Student ID: 504201516
//Analysis of Algorithm-2 Homework 2 Q2
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
#include<ostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

typedef vector<int> PII;
typedef vector<PII> VPII;

int Prims_MST(int source_node, vector<VPII> & graph , vector<pair<string,int>> enumerate_vector,vector<vector<int>> city_map_up_tri_0){

    // The priority_queue stores the pair<weight, node>
    priority_queue<PII, vector<PII>, greater<PII>> q;   // The priority_queue stores the pair<weight, node2, node1 > connection is like that: node 1 ---> node 2
    vector<vector<int>> MST;   //The MST represents a MST which stores the pair <node1 , node2>
    // The cost of the source node to itself is 0
    q.push({0,source_node,0});  //It means that first node is node 0 (Mankara).
    bool added[int(graph.size())];  //it checks weither node is used as a node2 or not.(it avoids to make a circle in system.)
    memset(added, false, sizeof(bool)*int(graph.size()));
    vector<int> enemy_points;   //it stores representative numbers of enemy point nodes
    int mst_cost = 0;   //if any edge is ideal to push in MST, the cost is added in mst_cost integer variable.
    int last_node = 0;  //last_node is used for represent first iteration.
    int mo_node;    //it stores the representative node of Monstantinople.

    //This loop is used for finding Enemy spot nodes and stores enemy_points vector.
    for(int i = 0; i<int(enumerate_vector.size());i++){
        if(enumerate_vector[i].first.substr(0,1)=="E"){ //If enumerate_vector[i] starts with "E" it means that this string is "Enemy".
            enemy_points.push_back(enumerate_vector[i].second);
        }
        else if(enumerate_vector[i].first.substr(0,2)=="Mo"){   //It finds representative node of "Mo".
            mo_node = enumerate_vector[i].second;
        }
    }
    while(!q.empty()) {
       
        vector<int> element;    //it is a sub adjacency vector which has node1,node2,cost for push into priority queue.
        element = {q.top()[2],q.top()[1],q.top()[0]};
        // Select the item <cost, node> with minimum cost
        PII item;
        item = q.top(); //element vector is saved in item variable
        q.pop();    //datas of most available node is saved into item,so it is popped from priority queue for avoid to select one more for next steps.
        int node = item[1]; //node 1
        int cost = item[0];  //cost

        // If the node is node not yet added to the minimum spanning tree add it, and increment the cost.
        if(!added[node]) {  //if the node is not selected as a second node.(for avoid to make a circle) 
            if(cost!=0){    //it is for the first iteration condition that it needs to push to MST some constraints.
            MST.push_back(element); //the adjacency vector is pushed into MST.   
            }
            
        mst_cost += cost;   //mst_cost is updated by cost value of new mst element.
        added[node] = true; //the node is labeled as true for avoid select one more as a node2.
        string node_name1;
        bool cont1 = false;
        if(element[1]==mo_node){ //If node 2 is destination node,the path is completed.
            goto destination;   //it directly goes output processes
        }
        while(q.size()!=0){ //Each iteration,priority queue force to be clear,this is a kind of constraint,because
                            //node1 of current iteration must be node2 of previous iteration.
                            //For Example: iter-1 : node1->node2 iter-2 : node2->node3
            q.pop();
        }
            for(auto & pair_cost_node : graph[node]) {  //it iterates and push to priority q all edges of the node.
                for(int k = 0;k<int(enumerate_vector.size());k++){
                    if(pair_cost_node[1]==enumerate_vector[k].second){
                        node_name1 = enumerate_vector[k].first; //it stores name of place which correnponds its node number for node2
                    }
                }
                int adj_node = pair_cost_node[1];
                if(added[adj_node] == false) {
                    if(node_name1.substr(0,1)=="E"){    //Enemy Spot Constraints ,it compares node numbers,it equals to enemy spot node numbers,it continues.
                        continue;
                    }
                    else{
                        //This condition search all nodes which connect to current node for check if it is next to 5 unit or not.
                        for(int i = 0; i < int(enemy_points.size());i++){
                            for(int j = 0;j<int(graph[pair_cost_node[1]].size());j++){
                                if(graph[pair_cost_node[1]][j][1]==enemy_points[i]){
                                    if(graph[pair_cost_node[1]][j][0]<5){   //This condition is all about 5 unit constraints.
                                        cont1 = true;   //cont1 sets as true to avoid to push q(priority queue.)
                                    }    
                                }                                   
                            }
                        }
                        if(!cont1 && last_node!=0){ //If there is no any constraints to block to push,it is pushed into q.
                            q.push(pair_cost_node);            
                        }
                        else if(last_node==0){  //If it is first iteration,it directly push into q without any constraints.
                                                //Because in first iteration, "Ma" and its child nodes has to pushed into q and it can not has any constraints. 
                            q.push(pair_cost_node);
                            cont1 = false;
                        }  
                    } 
                    }
                    cont1 = false;
                }
            last_node++;    //it means that it is not first iteration anymore.
        }
    }

destination:
//This part contains Output processes.
    string node_name_1;
    string node_name_2;
    int enu_vector_size = MST.size();
    //this loop is used for finding name of places which is correspond to their representative nodes.
    for(int i =0 ; i< enu_vector_size;i++){
        for(int j = 0;j<int(enumerate_vector.size());j++){
            if(MST[i][0]==enumerate_vector[j].second){
                node_name_1 = enumerate_vector[j].first;
            }
            if(MST[i][1]==enumerate_vector[j].second){
                node_name_2 = enumerate_vector[j].first;
            }
        }
        if(i==enu_vector_size-1){
            cout<<node_name_1<<" ";
            cout<<node_name_2<<" ";
        }
        else{
        cout<<node_name_1<<" ";
        }
    }
    cout<<mst_cost<<endl;
    return mst_cost;
}

int main(){
    vector<pair<string,int>> enumerate_vector;  //it stores the pair which has place name and node number--> <PlaceName,NodeNumber>
    vector<vector<int>> city_map_up_tri;    //This is adjacency vector which includes edges considering no direction--> it includes (0,2) but not includes (2,0)
    vector<vector<int>> city_map_up_tri_0;  //This is adjacency vector which includes all edges--> it includes both (0,2) and (2,0)
    vector<int> element = {0,0,0};  //element vector is filled with input strings when current two nodes have a node number.
                        //{cost,Node_number1,Node_number2}, element vector is an adjacency vector that has cost value additionaly.
//This part of code covers enumerating process of  nodes and reading input processes.
    ifstream file;
    string input_name;  // Example format for input line: Node1 Node2 Cost
    cin>>input_name;    // Ex: city_plan_1.txt
    file.open(input_name);

    enumerate_vector.push_back(make_pair("Ma",0));  //Mankara is set as first node.
    int enume = 1;  //representative number of nodes
    string x = "";  //"Node1" of input line
    string y = "";  //"Node2" of input line
    string z = "";  //"Cost" of input line
    bool xx = false;    //it is used for check if any node(first string) has already a node number or not.
    bool yy = false;    //it is used for check if any node(second string) has already a node number or not.
    while(!file.eof()){ //it continues to get data from input file until there is no any data.
        xx = false;
        yy = false;
        getline(file,x,',');    //get first string from input line
        if(x[0]=='\n'){ //for avoid to some reading input errors
            x.erase(x.begin(),x.begin()+1);
        }
        getline(file,y,',');    //get second string from input line
        if(y[0]=='\n'){ //for avoid to some reading input errors
            y.erase(y.begin(),y.begin()+1);
        }
        getline(file,z,'\n');   //get third string from input line

        //This loop is used for define special numbers for each nodes.It checks if any node has same number or not.       
        for(int i=0;i<int(enumerate_vector.size());i++){  //all elements in enumerate_vectors are checked for get unique numbers for nodes.  
            if(x==enumerate_vector[i].first){   //if any element of the vector has the number of x place name, xx variable sets as true,
                xx = true;                      //it means that this node is already has a node number,so it do not need to get again.                          
                element[2] = enumerate_vector[i].second; //ana fonksiyonda ters tanimlandigi icin
            }

            if(y==enumerate_vector[i].first){   //if any element of the vector has the number of y place name, yy variable sets as true,
                yy = true;                      //it means that this node is already has a node number,so it do not need to get again.  
                element[1] = enumerate_vector[i].second;    //zaten buraya girdiyse diger iflere girmez.
                
            }
            }
                        
            if(!xx){    //it means that the node(first string of input) has no any node number yet. 
                enumerate_vector.push_back(make_pair(x,enume)); //the node gets current value of enume as a node number.
                element[2] = enume; //unique node number is set
                enume++;    //enume value is prepared for new node
                
            }

            if(!yy){    //it means that the node(second string of input) has no any node number yet.
                enumerate_vector.push_back(make_pair(y,enume)); //the node gets current value of enume as a node number.
                element[1] = enume; //unique node number is set
                enume++;    //enume value is prepared for new node
                
            }
            int num1 = stoi(z); //convert string to integer value for cost value
            element[0] = num1;  //cost string of current input line
            city_map_up_tri.push_back(element); //element vector({Node_number1,Node_number2,cost}) is pushed into city_map_up_tri vector.
    }

    int up_tri_size = city_map_up_tri.size();
    city_map_up_tri_0 = city_map_up_tri;
    //This loop is used to create adjacency vector which includes all edges--> it includes both (0,2) and (2,0)
    for(int i = 0; i<up_tri_size;i++){
        city_map_up_tri.push_back({city_map_up_tri[i][0],city_map_up_tri[i][2],city_map_up_tri[i][1]});
    }

    vector<VPII> graph_0;   //main graph which has all edges and vertices
    graph_0.resize(int(enumerate_vector.size()));
    //This loop is used to create main graph which has all edges and vertices.
    for(int i = 0 ;i<int(enumerate_vector.size());i++){ //adjacency which are belong to each nodes are pushed into graph
        for(int j = 0 ;j<int(city_map_up_tri.size());j++){
            if(city_map_up_tri[j][2]==i){   //if adjacency vector has node i as a first node, it is pushed into graph[i]
                graph_0[i].push_back(city_map_up_tri[j]);
            }
        }
    }
    //Example of the main graph structure:
    //if we have 3 node:
    //graph_0 [0] = { {4,1,0}, {1,2,0}, {5,3,0} };
    //graph_0 [1]   = { {4,0,1}, {2,0,1}, {3,4,1}, {3,5,1} };
    //graph_0 [2]   = { {5,0,2}, {2,0,2}, {3,1,2}, {3,1,2} };
    Prims_MST(0, graph_0,enumerate_vector,city_map_up_tri_0);
    return 0;
}