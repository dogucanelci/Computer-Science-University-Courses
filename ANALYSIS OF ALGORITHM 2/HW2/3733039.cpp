//Student Name: Dogu Can ELCI
//Student ID: 504201516
//Analysis of Algorithm-2 Homework 2
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

    
    priority_queue<PII, vector<PII>, greater<PII>> q;   // The priority_queue stores the pair<weight, node2, node1 > connection is like that: node 1 ---> node 2
    vector<vector<int>> MST;   //The MST represents a MST which stores the pair <node1 , node2>
    bool opposite_check = false;    //Sometimes some nodes represent opposite positions in output conditions unlike positions in input files like (node2,node1) 
                                    //And it is used to check it.
                                    
    q.push({0,source_node,0});      // The cost of the source node to itself is 0          
    bool added[int(graph.size())];  //it checks weither node is used as a node2 or not.(it avoids to make a circle in system.)
    memset(added, false, sizeof(bool)*int(graph.size()));   //it is used to make location and create enough default items in the bool added array.

    int mst_cost = 0;               //if any edge is ideal to push in MST, the cost is added in mst_cost integer variable.

    while(!q.empty()) {
        vector<int> element;    //it is a sub adjacency vector which has node1,node2,cost for push into priority queue.
        element = {q.top()[2],q.top()[1],q.top()[0]};
        // Select the item <cost, node> with minimum cost
        PII item;
        item = q.top(); //element vector is saved in item variable
        q.pop();    //datas of most available node is saved into item,so it is popped from priority queue for avoid to select one more for next steps.

        int node = item[1]; //presentative number of node2
        int cost = item[0];  //cost of edge

        // If the node is node not yet added to the minimum spanning tree add it, and increment the cost.
        if(!added[node]) {  //if the node is not selected as a second node.(for avoid to make a circle) 
            int a = element[0];
            int b = element[1];
            if(cost!=0){    //If the iteration is not first iteration (in first iteration, the node has to push directly)
            //This loop finds some anormality about location of nodes in adjacency vector and fix it according to input location of strings.
            //For example: Adjacency vector is pushed into MST as Hipp,GP but it has to be GP,Hipp sequence.
            for(int i = 0;i<int(city_map_up_tri_0.size());i++){
                if(element[0]==city_map_up_tri_0[i][2]){
                    if(element[1]==city_map_up_tri_0[i][1]){    //If there is perfect match between nodes,opposite_check variable sets as true.
                        opposite_check = true;  
                    }        
                }
            }
            if(opposite_check){ //It means that there is no anormality in location of nodes.
                MST.push_back(element); //The most available adjency vector(<node1,node2,cost>) is pushed into MST.
                opposite_check = false;                
                }
            else{   //It means that nodes have to change places between each other.
                element[0] = b;
                element[1] = a;
                MST.push_back(element);
                opposite_check = false;    
                }
        }
            mst_cost += cost;   //mst_cost is updated by cost value of new mst element.
            added[node] = true; //the node is labeled as true for avoid select one more as a node2.

        vector<int> ideal_church;   //ideal_church stores the representative numbers of all churches of the plan.
        vector<int> ideal_church1;  //it stores the pairs which includes first node(GP) and ideal church(Ch n) <GP,Ch n>
        vector<int> hipp_const;     //it stores the pair which includes first node(GP) and Hipp <GP,Hipp>
        int hipp_node;              //it stores representative number of Hipp node.
        if(cost==0){                //it is for the first iteration condition that it needs to push to MST some constraints.
            //Church Constraint  
            for(int i = 0;i<int(enumerate_vector.size());i++){
                string area_name = enumerate_vector[i].first;
                char a = area_name[0];
                if(a=='C'){    //Check is it church or not
                    ideal_church.push_back(enumerate_vector[i].second); 
                }
                else if(area_name=="Hipp"){    //it determines what is the representation number of Hipp node
                    hipp_node = enumerate_vector[i].second;
                }
            }
//this for loop is used for "Church constraint" and "Hipp constraint" in the plan.            
            for(int i=0;i<int(ideal_church.size());i++){
                for(int j=0;j<int(graph[0].size());j++){
                    if(ideal_church[i]==graph[0][j][1]){
                        if(i==0){           // if it is church that it can be seen first,it is chosen as an ideal church.
                            ideal_church1 = graph[0][j];
                        }
                        else if(ideal_church1[0]>graph[0][j][0]){   //if edge cost of previous church is more than new one,new one is selected as an ideal church.
                            ideal_church1 = graph[0][j];            //it is the pair which includes first node(GP) and ideal church(Ch n) <GP,Ch n>
                        }
                    }
                    else if(hipp_node==graph[0][j][1]){ //if the node in current iteration condition is "Hipp", it is chosen.
                        hipp_const = graph[0][j];
                    }
                }
            }
        }
            string node_name1;
            string node_name2;
            vector<vector<int>> constraints = {{0,0,0} , hipp_const , ideal_church1};
        // Iterate through all the nodes adjacent to the node taken out of priority queue.
        // Push only those nodes (weight,node1,node2) that are not yet present in the minumum spanning tree.

            //This condition accept just first iteration which have to include some constraints in first time like:
                // *Church constraint
                // *Hipp constraint
            //It also check some constraints which is for not just first iteration such as:
                // *Hipp-Bas constraint
                // *Hp-Hp constraint
            //Except this constraints, any adjacency vector is pushed into priority queue.
            if(cost==0){
                for(int i =0;i<int(constraints.size());i++){
                    node = constraints[i][1];
                    for(auto & pair_cost_node : graph[node]) {  //it iterates and push to priority q all edges of the node.
                    for(int k = 0;k<int(enumerate_vector.size());k++){
                            if(pair_cost_node[1]==enumerate_vector[k].second){  //node_1
                                node_name1 = enumerate_vector[k].first; //it stores name of place which correnponds its node number for node2
                            }
                            if(pair_cost_node[2]==enumerate_vector[k].second){  //it stores name of place which correnponds its node number for node1  
                                node_name2 = enumerate_vector[k].first;
                            }
                        }
                        int adj_node = pair_cost_node[1]; //it is the second node (node 2)
                        if(added[adj_node] == false) {  //if the node is not selected as a second node.(for avoid to make a circle)
                            string node1subs = node_name1.substr(0,4);
                            string node2subs = node_name2.substr(0,3);
                            //This condition is used for Hipp-Bas constraint.
                            if((node_name1.substr(0,4)=="Hipp" && node_name2.substr(0,3)=="Bas") || (node_name1.substr(0,3)=="Bas" && node_name2.substr(0,4)=="Hipp")){
                                continue;
                            }
                            //This condition is used for Hp-Hp constraint.
                            else if(node_name1.substr(0,2)=="Hp" && node_name2.substr(0,2)=="Hp"){
                                continue;
                            }
                            else{
                                //if this element covers both nodes which are first node(GP) and ideal Church,it is pushed into MST directly without pushed into queue first.
                                if(pair_cost_node[2]==0 && pair_cost_node[1]==ideal_church1[1]){
                                    element = {pair_cost_node[2],pair_cost_node[1],pair_cost_node[0]};
                                    MST.push_back(element);
                                    mst_cost += pair_cost_node[0];
                                }
                            //This condition is used for Hipp-GP constraint.
                                if(((node_name1.substr(0,4)=="Hipp" && node_name2.substr(0,2)=="GP") || (node_name2.substr(0,4)=="Hipp" && node_name1.substr(0,2)=="GP"))){
                                    element = {pair_cost_node[2],pair_cost_node[1],pair_cost_node[0]};
                                    MST.push_back(element);
                                    mst_cost += pair_cost_node[0];
                                }
                            //if there is no any constraint block in condition
                                else{
                                    q.push(pair_cost_node); //Adjacency vector is pushed into priority queue.
                                }  
                            } 
                        }
                    }
                        added[node] = true; //this is just for nodes which are in constraints.                                        
                }
            }
            //After Church constraint and Hipp constraint is controlled in first iteration,
            //some constraints which is for not just first iteration such as:
                // *Hipp-Bas constraint
                // *Hp-Hp constraint
            //are continue to checking for other iteration steps.
            //Except this constraints, any adjacency vector is pushed into priority queue.
            else{
            for(auto & pair_cost_node : graph[node]) {                  
                for(int k = 0;k<int(enumerate_vector.size());k++){      //it iterates and push to priority q all edges of the node.
                    if(pair_cost_node[1]==enumerate_vector[k].second){  //it stores name of place which correnponds its node number for node2
                        node_name1 = enumerate_vector[k].first;
                    }
                    if(pair_cost_node[2]==enumerate_vector[k].second){  //it stores name of place which correnponds its node number for node1
                        node_name2 = enumerate_vector[k].first;
                    }
                }
                int adj_node = pair_cost_node[1];
                if(added[adj_node] == false) {  //if the node is not selected as a second node.(for avoid to make a circle)
                    //This condition is used for Hipp-Bas constraint.
                    if((node_name1.substr(0,4)=="Hipp" && node_name2.substr(0,3)=="Bas") || (node_name1.substr(0,3)=="Bas" && node_name2.substr(0,4)=="Hipp")){   //if it is hipodrome
                        continue;
                    }
                    //This condition is used for Hp-Hp constraint.
                    else if(node_name1.substr(0,2)=="Hp" && node_name2.substr(0,2)=="Hp"){
                        continue;
                    }
                    else{
                        q.push(pair_cost_node);
                    }         
                }
            }
        }
    }
}

//This part contains Output processes.
    std::sort(MST.begin(), MST.end(),[](const std::vector<int>& a, const std::vector<int>& b) {return a[2] < b[2];});   //sorting process as their costs.
    string node_name_1;
    string node_name_2;
    //this loop is used for finding name of places which is correspond to their representative nodes.
    for(int i =0 ; i< int(MST.size());i++){
        for(int j = 0;j<int(enumerate_vector.size());j++){
            if(MST[i][0]==enumerate_vector[j].second){
                node_name_1 = enumerate_vector[j].first;
            }
            if(MST[i][1]==enumerate_vector[j].second){
                node_name_2 = enumerate_vector[j].first;
            }
        }
        cout<<node_name_1<<" "<<node_name_2<<" "<<MST[i][2]<<endl;
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

    enumerate_vector.push_back(make_pair("GP",0));  //Great Palace is set as first node.
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
//    getchar();
    return 0;
}