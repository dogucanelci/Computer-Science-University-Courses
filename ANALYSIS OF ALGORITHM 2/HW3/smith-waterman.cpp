//@Student_Name: Dogu Can ELCI
//@Student_ID: 504201516
//Anaysis of Algorithm-2 Homework-3

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

int main(int argc, char* argv1[]){

//    std::ofstream outfile ("output_e2-1_sln.txt");
    std::ofstream outfile (argv1[2]);
    std::ifstream file(argv1[1]);
    vector<vector<string>> all_inputs;
    vector<pair<string,string>> all_pair_inputs;
    if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
        all_inputs.push_back({line,"0"});
    }
    file.close();
}
    std::sort(all_inputs.begin(), all_inputs.end()); 
    for(int i = 0 ;i<signed(all_inputs.size());i++){
        all_inputs[i][1]="1";
        for(int j = 0 ;j<signed(all_inputs.size());j++){
            if(i!=j){
                if(all_inputs[j][1]=="0"){
            all_pair_inputs.push_back({all_inputs[i][0],all_inputs[j][0]});
                }
            }
        }
    }
    std::sort(all_pair_inputs.begin(), all_pair_inputs.end());
    all_pair_inputs.erase(std::unique(all_pair_inputs.begin(), all_pair_inputs.end()), all_pair_inputs.end());
while(all_pair_inputs.size()!=0){

    string str1 = all_pair_inputs[0].first;
    string str2 = all_pair_inputs[0].second;
    int x = str1.length();
    int y = str2.length();
    int match = 1;
    int dismatch = -2;
    int gap = -4;
    int gap_val1;
    int gap_val2;
    int ismatched;
    int bigger;
    int biggest = 0;
    int main_array[x+1][y+1];
    vector<int> current_value_vector;
    vector<string> strings;
    vector<pair<int,int>> index_vector;
    for(int i = 0;i<x+1;i++){
        main_array[i][0] = 0;
    }
    for(int i = 0;i<y+1;i++){
        main_array[0][i] = 0;
    }

    for(int i = 1;i<x+1;i++){
        for(int j = 1 ;j<y+1;j++){
            gap_val1 = main_array[i-1][j] + gap;
            current_value_vector.push_back(gap_val1);
            gap_val2 = main_array[i][j-1] + gap;
            current_value_vector.push_back(gap_val2);
            if(str1[i-1]==str2[j-1]){
                ismatched = main_array[i-1][j-1] + match ;
                current_value_vector.push_back(ismatched);
                if(ismatched>biggest){
                    biggest = ismatched;
                }
            }
            else{
                ismatched = main_array[i-1][j-1] + dismatch;
                current_value_vector.push_back(ismatched);
            }
            bigger = 0;
            for(int k = 0 ; k<3;k++){
                if(current_value_vector[k]>bigger){
                    bigger = current_value_vector[k];
                }
            }
            if(bigger<0){
                bigger = 0;
            }
            main_array[i][j] = bigger ;
            current_value_vector = {};

        }
    }

    for(int i = 0 ; i < x+1;i++ ){
        for(int j = 0;j< y+1;j++){
            if(main_array[i][j]==biggest && biggest!=0){
                index_vector.push_back({i,j});
            }
        }
    }
    
    while(index_vector.size()!=0){
        string str = "";
        
        int i = index_vector[index_vector.size()-1].first;
        int j = index_vector[index_vector.size()-1].second;
        while(main_array[i][j]!=0){
            str = str2[j-1] + str;
            i--;
            j--;
            
        }
        index_vector.pop_back();
        strings.push_back(str);
    }
    std::sort(strings.begin(), strings.end());
    strings.erase(std::unique(strings.begin(), strings.end()), strings.end());
    std::reverse(strings.begin(), strings.end());
    
    outfile<<str1<<" "<<"-"<<" "<<str2<<endl;
    outfile<<"Score:"<<" "<<biggest<<" "<<"Sequence(s):";
    if(strings.size()!=0){       
    while(strings.size()!=0){
        string str_last = strings[strings.size()-1];
        outfile<<" "<<'"'<<str_last<<'"';
        strings.pop_back();
    }
        outfile<<"\n";    
    }
    all_pair_inputs.erase(all_pair_inputs.begin());
}
outfile.close();
    return 0;
}
