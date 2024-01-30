#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstring>
#include <iterator>
#include <fstream>
#include <cstdlib>
#include <memory>
#include <math.h> //needed for fabs
#include <cmath>
#include <bits/stdc++.h>
#include <iomanip>
#include <algorithm>

template <typename T,typename U>
class Boruvka{
public:
Boruvka(std::map<T,U>& received){
graph = received;
}

std::vector<T> remove_duplicates(std::vector<T> vector_with_duplicates){
    std::vector<T> unique_vector;
    std::cout<<"Inside remove_duplicates function"<<std::endl;
    for(auto i= 0; i< vector_with_duplicates.size();i++){
        T unique= 0;
        for(auto j = i;j<vector_with_duplicates.size() && unique <2; j++){
           if(vector_with_duplicates.at(i)==vector_with_duplicates.at(j)){
            unique++;//only allows to find itself
            std::cout<<"Unique component found"<<vector_with_duplicates.at(i)<<std::endl;
           }
        }
           if(unique == 1){
            unique_vector.push_back(vector_with_duplicates.at(i));
           }
    
    }
    return unique_vector;
}
std::pair<T,U> find_smallest(std::map<T,U> comparison){
    U smallest_value = comparison.begin()->second;
    T smallest_key = comparison.begin()->first;
    for(const auto& [key,value]: comparison){
        if(value<smallest_value){
            smallest_value = value;
            smallest_key = key;
        }
    }
    return std::make_pair(smallest_key,smallest_value);
}

void process_nonadjacent_wedges(std::map<T,U> min_wedge){
    std::map<T,U> graph_copy = graph;

    std::vector<std::vector<T>> new_component;
    //should be std::vector<std::vector<T>> new_component;
    U map_iterator = 0;
    U layer_index = 0;
    U wedge_index = 0;
    std::vector<T> wedge_row;
    auto it = min_wedge.begin();
    while(true){
        
        U found_for_wedge = 0;
        bool go_to_next_layer_of_components = false;
        std::map<T,U> comparison;
        T current_wedge = it->first;
        std::cout<<"current_wedge is: "<<current_wedge<<std::endl;
        wedge_row.push_back(current_wedge);
        
        std::advance(it,1);
        T next_wedge = it->first;
        std::cout<<"next_wedge is: "<<next_wedge<<std::endl;
        
        T first_string = T(1,current_wedge[0]) + next_wedge[0];
        T second_string = T(1,current_wedge[0]) + next_wedge[1];
        T third_string = T(1,current_wedge[1]) + next_wedge[0];
        T fourth_string = T(1,current_wedge[1]) + next_wedge[1];
        
        for(const auto&[key_graph, value_graph]: graph_copy){
            U found = 0;
            if(first_string == key_graph){
                found++;
                std::cout<<"Just inserted "<<key_graph<<" in comparison map"<<std::endl;
                comparison.insert(std::pair{key_graph,value_graph});
            }
            if(second_string == key_graph){
                found++;
                std::cout<<"Just inserted "<<key_graph<<" in comparison map"<<std::endl;
                comparison.insert(std::pair{key_graph,value_graph});
            }
            if(third_string == key_graph){
                found++;
                std::cout<<"Just inserted "<<key_graph<<" in comparison map"<<std::endl;
                comparison.insert(std::pair{key_graph,value_graph});
            }
           
            if(fourth_string == key_graph){
                found++;
                std::cout<<"Just inserted "<<key_graph<<" in comparison map"<<std::endl;
                comparison.insert(std::pair{key_graph,value_graph});
            }
            
            
            // std::cout<<"Found: "<<found<<" matches for "<<key_graph<<std::endl;
            
            std::reverse(first_string.begin(),first_string.end());
            std::reverse(second_string.begin(),second_string.end());
            std::reverse(third_string.begin(),third_string.end());
            std::reverse(fourth_string.begin(),fourth_string.end());
        if(first_string == key_graph){
                found++;
                std::cout<<"Just inserted "<<key_graph<<" in comparison map"<<std::endl;
                comparison.insert(std::pair{key_graph,value_graph});
            }
            if(second_string == key_graph){
                found++;
                std::cout<<"Just inserted "<<key_graph<<" in comparison map"<<std::endl;
                comparison.insert(std::pair{key_graph,value_graph});
            }
            if(third_string == key_graph){
                found++;
                std::cout<<"Just inserted "<<key_graph<<" in comparison map"<<std::endl;
                comparison.insert(std::pair{key_graph,value_graph});
            }
           
            if(fourth_string == key_graph){
                found++;
                std::cout<<"Just inserted "<<key_graph<<" in comparison map"<<std::endl;
                comparison.insert(std::pair{key_graph,value_graph});
            }
            
            found_for_wedge = found_for_wedge + found;
             std::cout<<"Found: "<<found<<" matches for "<<key_graph<<" in forward & reverse"<<std::endl;
            
            //put a check above for 0 found and more than one. In case of 0 found switch to new_component
            //In case for one found just put it in new_component
            //In case of more than one found, invoke find_smallest, and put its return value into new_component  
        }
        map_iterator++;
        std::cout<<"We have iterated over min_wedge "<<map_iterator<<" times"<<std::endl;
        std::cout<<"Total founds for this iteration were: "<<found_for_wedge<<std::endl;
        if(found_for_wedge <2){
            layer_index++;
            std::cout<<"Time for new component.Pushing back previous wedge's row"<<std::endl;
            new_component.push_back(wedge_row);
            wedge_row.clear();
                //go_to_next_layer_of_components = true;
                
        }
    
        else{
            std::pair<T,U> p = find_smallest(comparison);
            std::cout<<"Inserted "<<p.first<<" into wedge_row"<<std::endl;

            wedge_row.push_back(p.first);
        }
        wedge_index++;
        if(map_iterator == min_wedge.size()-1){
            std::cout<<"Reached end of min_wedge, so dumping to new_component before we exit"<<std::endl;
            //before every insertion check for duplicates in a function
            wedge_row.push_back(next_wedge);
            new_component.push_back(wedge_row);
            break;
        }
    }
    std::cout<<"Removing duplicate components"<<std::endl;
for(auto k= 0; k< new_component.size();k++){
        std::vector<T> unique_components;
    for(auto i = 0; i< new_component[k].size();i++){
        unique= 0;
        for(auto j = i;j<new_component[k].size() && unique <2; j++){
          if(new_component[k].at(i)==new_component[k].at(j)){
            unique++;//only allows to find itself
          }
        }
          if(unique == 1){
            unique_components.push_back(new_component[k].at(i));
          }
    
    }
    new_component[k] = unique_components;
}
    
    std::cout<<"New components are: "<<std::endl;
    for(auto i=0;i< new_component.size();i++){
        for(auto j = 0; j< new_component[i].size();j++){
            std::cout<<new_component[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<"Finding links between the newly created components"<<std::endl;
    std::vector<T> links_between_components;
    std::map<T,U> links;
     for(auto i=0;i< new_component.size();i++){
        U next_index = i+1;
        if(next_index <new_component.size()){
             auto j = 0;
             auto k = 0;
             for(j = 0,k = 0 ; j< new_component[i].size() && k< new_component[next_index].size();j++,k++){
                T first_check = T(1,new_component[i][j][0]) + new_component[next_index][k][1];
                T second_check = T(1,new_component[i][j][1]) + new_component[next_index][k][0];
                T third_check = T(1,new_component[i][j][0]) + new_component[next_index][k][0];
                T fourth_check = T(1,new_component[i][j][1]) + new_component[next_index][k][1];
                std::cout<<"Checking components "<<first_check<<" and "<<second_check<<" and "<<third_check<<" and "<<fourth_check<<std::endl;
                for(const auto& [key,value]:graph_copy){
                    if(first_check==key){
                        links_between_components.push_back(key);
                        links.insert(std::pair{key,value});
                    }
                    if(second_check==key){
                        links_between_components.push_back(key);
                        links.insert(std::pair{key,value});
                    }
                    if(third_check==key){
                        links_between_components.push_back(key);
                        links.insert(std::pair{key,value});
                    }
                    if(fourth_check==key){
                        links_between_components.push_back(key);
                        links.insert(std::pair{key,value});
                    }
                }
            }         
        }
       
        
    }
    std::cout<<"Found links:"<<std::endl;
    //std::map<T,U> comparison;
    for(auto k:links_between_components){
        std::cout<<k<<" ";
        
    }
    std::cout<<std::endl;
    std::pair<T,U> p = find_smallest(links);
    std::vector<T> insert_link;
    //std::cout<<p.first<<std::endl;
    insert_link.push_back(p.first);
    new_component.push_back(insert_link);
    std::cout<<"The solution: "<<std::endl;
    for(auto i=0;i< new_component.size();i++){
        for(auto j = 0; j< new_component[i].size();j++){
            std::cout<<new_component[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

}

void forest(std::map<std::string,int> graph){
    std::vector<char> key_first_char;
    std::vector<char> key_second_char;
    std::vector<char> initial_components;
    std::map<T,U> graph_copy = graph;
    std::vector<T> unique_separate_component;
    for(const auto& [key,value]: graph){
        //std::cout<<key[0]<<" : "<<value<<std::endl;
    key_first_char.push_back(key[0]);
    key_second_char.push_back(key[1]);
    }
    for(auto i: key_second_char){
        key_first_char.push_back(i);
  
    for(auto i= 0; i< key_first_char.size();i++){
        unique= 0;
        for(auto j = i;j<key_first_char.size() && unique <2; j++){
          if(key_first_char.at(i)==key_first_char.at(j)){
            unique++;//only allows to find itself
          }
        }
          if(unique == 1){
            initial_components.push_back(key_first_char.at(i));
          }
    
    }

    std::map<T,U> comparison;
    for(auto i = 0; i< initial_components.size(); i++){
        
        for(const auto& [key,value]: graph){
            
            if(initial_components[i]==key[0] || initial_components[i]==key[1]){
               
                {
                comparison.insert(std::pair{key,value});
                }
                //std::cout<<"Value just pushed back: "<<values<<std::endl;
            }
            
        }
        {
        std::pair<T,U> p = find_smallest(comparison);
        min_wedge.insert(std::pair{p.first,p.second});
        }
       
        comparison.clear();
    }
    std::vector<T> keys;
    std::vector<char> characters;
    for(const auto& [key,value]: min_wedge){
        std::cout<<key<<": "<<value<<" ";
        keys.push_back(key);
        characters.push_back(key[0]);
        characters.push_back(key[1]);
    }
    std::vector<char> unique_components;
   
    for(auto i= 0; i< characters.size();i++){
        unique= 0;
        for(auto j = i;j<characters.size() && unique <2; j++){
          if(characters.at(i)==characters.at(j)){
            unique++;//only allows to find itself
          }
        }
          if(unique == 1){
            unique_components.push_back(characters.at(i));
          }
    
    }
  
U map_iterator1 = 0;
U layer_index1 = 0;
U wedge_iterator1 = 0;
U index_of_next_wedge = 0;
U index_of_another_components_start=0;
std::vector<T> wedge_row1;
std::vector<std::vector<T>> new_component1;
auto it1 = min_wedge.begin();
T current_wedge1 = it1->first;
bool go_to_next_layer_of_components1 = false;
bool found_head_of_next_component = false;
U map_iterations=0;
bool non_adjacent_wedges_processed = false;


while(true){
 	if(map_iterator1 >= min_wedge.size()-1){
		std::cout<<"Finished adding a component"<<std::endl;
		go_to_next_layer_of_components1=true;
		map_iterator1=index_of_another_components_start;
		map_iterations++;
		new_component1.push_back(wedge_row1);
		U found_wedges = 0;
		for(auto i=0;i< new_component1.size();i++){
        	for(auto j = 0; j< new_component1[i].size();j++){
            	//std::cout<<new_component[i][j]<<" ";
		for(const auto&[key_wedge, value_wedge]: min_wedge){
		if(key_wedge==new_component1[i][j]){
		found_wedges++;
		}
        	}
       
   		}
		}
	
		
		if(found_wedges==min_wedge.size()){
		std::cout<<"Reached end of map"<<std::endl;
		break;
		}
	}
	if(go_to_next_layer_of_components1== true){
	go_to_next_layer_of_components1=false;
	wedge_row1.clear();
	auto it2=std::next(it1,index_of_another_components_start);
	map_iterator1=index_of_another_components_start;
	current_wedge1=it2->first;
        std::cout<<"current_wedge is: "<<current_wedge1<<std::endl;
        wedge_row1.push_back(current_wedge1);
        
        std::advance(it2,1);
        T next_wedge1 = it2->first;
        std::cout<<"next_wedge is: "<<next_wedge1<<std::endl;
	std::cout<<"Map iterator is: "<<map_iterator1<<std::endl;

	std::cout<<"Added "<<current_wedge1<<" to wedge_row"<<std::endl;
	map_iterator1=map_iterator1+2;
	wedge_iterator1=0;
	while(wedge_iterator1 < min_wedge.size()-1){
	wedge_iterator1++;
	std::advance(it2,1);
	T next_next_wedge = it2->first;
	std::cout<<"Entered while loop of second component with next_next_wedge "<<next_next_wedge<<std::endl;

	if((next_next_wedge[0]==current_wedge1[0])||(next_next_wedge[0]==current_wedge1[1])||(next_next_wedge[1]==current_wedge1[0])||(next_next_wedge[1]==current_wedge1[1])){
	wedge_row1.push_back(next_next_wedge);
	index_of_next_wedge = std::distance(min_wedge.begin(),min_wedge.find(next_next_wedge));
	std::cout<<"Moving forward, added "<<next_next_wedge<<" with index "<<index_of_next_wedge<<" to wedge_row"<<std::endl;

	break;
	}
	}	
	}
	else{
	std::map<T,U> comparison1;
	auto it2=std::next(it1,index_of_next_wedge);
	current_wedge1=it2->first;
        std::cout<<"current_wedge is: "<<current_wedge1<<std::endl;
        //wedge_row.push_back(current_wedge);
        
        std::advance(it2,1);
        T next_wedge1 = it2->first;
        std::cout<<"next_wedge is: "<<next_wedge1<<std::endl;
	std::cout<<"Map iterator is: "<<map_iterator1<<std::endl;
if(map_iterator1==0){
	//First iteration
	if((current_wedge1[0]==next_wedge1[0])||(current_wedge1[0]==next_wedge1[1])||(current_wedge1[1]==next_wedge1[0])||(current_wedge1[1]==next_wedge1[1])){
	wedge_row1.push_back(current_wedge1);
	wedge_row1.push_back(next_wedge1);
	std::cout<<"Added "<<current_wedge1<<" and "<<next_wedge1<<" to wedge_row"<<std::endl;
	map_iterator1=map_iterator1+2;
	while(wedge_iterator1 < min_wedge.size()-1){
	wedge_iterator1++;
	std::advance(it2,1);
	T next_next_wedge = it2->first;
	if((next_next_wedge[0]==next_wedge1[0])||(next_next_wedge[0]==next_wedge1[1])||(next_next_wedge[1]==next_wedge1[0])||(next_next_wedge[1]==next_wedge1[1])){
	wedge_row1.push_back(next_next_wedge);
	index_of_next_wedge = std::distance(min_wedge.begin(),min_wedge.find(next_next_wedge));
	std::cout<<"Moving forward, added "<<next_next_wedge<<" with index "<<index_of_next_wedge<<" to wedge_row"<<std::endl;
	break;
	}
	else if(found_head_of_next_component == false){//Catch start of next component
	found_head_of_next_component = true;
	index_of_another_components_start=std::distance(min_wedge.begin(),min_wedge.find(next_next_wedge));
	std::cout<<"But "<<next_next_wedge<<" with index "<<index_of_another_components_start<<" is in another component"<<std::endl;
		
	}
	}	
	}
	else{
	//First and next wedges weren't part of same component. But we move on with first wedge to seek its component-partners

	process_nonadjacent_wedges(min_wedge);
	non_adjacent_wedges_processed = true;
	break;
	}
	}
	else{
	std::cout<<"Moved on from first two nodes"<<std::endl;
	if((current_wedge1[0]==next_wedge1[0])||(current_wedge1[0]==next_wedge1[1])||(current_wedge1[1]==next_wedge1[0])||(current_wedge1[1]==next_wedge1[1])){
	
	wedge_row1.push_back(next_wedge1);
	std::cout<<"Added "<<next_wedge1<<" to wedge_row"<<std::endl;
	map_iterator1=map_iterator1+1;
	while(wedge_iterator1 < min_wedge.size()-1){
	wedge_iterator1++;
	std::advance(it2,1);
	T next_next_wedge = it2->first;
	if((next_next_wedge[0]==next_wedge1[0])||(next_next_wedge[0]==next_wedge1[1])||(next_next_wedge[1]==next_wedge1[0])||(next_next_wedge[1]==next_wedge1[1])){
	wedge_row1.push_back(next_next_wedge);
	index_of_next_wedge = std::distance(min_wedge.begin(),min_wedge.find(next_next_wedge));
	std::cout<<"Moving forward, added "<<next_next_wedge<<" with index "<<index_of_next_wedge<<" to wedge_row"<<std::endl;
	break;
	}
	}	
	}
	else{
		std::cout<<"No further matches in this component"<<std::endl;
		map_iterator1++;
		map_iterator1++;
	}

	}
		
        		
	}

	}
if(non_adjacent_wedges_processed==false){
   std::cout<<"New components are: "<<std::endl;
    for(auto i=0;i< new_component1.size();i++){
        for(auto j = 0; j< new_component1[i].size();j++){
            std::cout<<new_component1[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
std::cout<<"Finding links between the newly created components"<<std::endl;
    std::vector<T> links_between_components1;
    std::map<T,U> links1;
     for(auto i=0;i< new_component1.size();i++){
        U next_index1 = i+1;
        if(next_index1 <new_component1.size()){
             auto j = 0;
             auto k = 0;
             for(j = 0,k = 0 ; j< new_component1[i].size() && k< new_component1[next_index1].size();j++,k++){
                T first_check = T(1,new_component1[i][j][0]) + new_component1[next_index1][k][1];
                T second_check = T(1,new_component1[i][j][1]) + new_component1[next_index1][k][0];
                T third_check = T(1,new_component1[i][j][0]) + new_component1[next_index1][k][0];
                T fourth_check = T(1,new_component1[i][j][1]) + new_component1[next_index1][k][1];
                std::cout<<"Checking components "<<first_check<<" and "<<second_check<<" and "<<third_check<<" and "<<fourth_check<<std::endl;
                for(const auto& [key,value]:graph_copy){
                    if(first_check==key){
                        links_between_components1.push_back(key);
                        links1.insert(std::pair{key,value});
                    }
                    if(second_check==key){
                        links_between_components1.push_back(key);
                        links1.insert(std::pair{key,value});
                    }
                    if(third_check==key){
                        links_between_components1.push_back(key);
                        links1.insert(std::pair{key,value});
                    }
                    if(fourth_check==key){
                        links_between_components1.push_back(key);
                        links1.insert(std::pair{key,value});
                    }
                }
            }         
        }
       
        
    }
    std::cout<<"Found links:"<<std::endl;
    //std::map<T,U> comparison;
    for(auto k:links_between_components1){
        std::cout<<k<<" ";
        
    }
    std::cout<<std::endl;
    std::pair<T,U> p1 = find_smallest(links1);
    std::vector<T> insert_link1;
    //std::cout<<p.first<<std::endl;
    insert_link1.push_back(p1.first);
    new_component1.push_back(insert_link1);
    std::cout<<"The solution: "<<std::endl;
    for(auto i=0;i< new_component1.size();i++){
        for(auto j = 0; j< new_component1[i].size();j++){
            std::cout<<new_component1[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

    
   
}
private:
U unique = 0;

std::map<T,U> min_wedge;
std::map<T,U> graph;
};

int main(){
    std::map<std::string,int> undirected_graph = {
    {"AB",7},
    {"AD",4},
    {"BC",11},
    {"BD",9},
    {"BE",10},
    {"CE",5},
    {"DE",15},
    {"DF",6},
    {"EF",12},
    {"EG",8},
    {"FG",13}
    };
    std::map<std::string,int> undirected_graph2 = {
        {"AB",13},
        {"AC",6},
        {"BC",7},
        {"BD",1},
        {"CD",14},
        {"CE",8},
        {"CH",20},
        {"DE",9},
        {"DF",3},
        {"EF",2},
        {"EJ",18},
        {"GH",15},
        {"GI",5},
        {"GJ",19},
        {"GK",10},
        {"HJ",17},
        {"IK",11},
        {"JK",16},
        {"JL",4},
        {"KL",12}
    };
    std::unique_ptr<Boruvka<std::string,int>> b1(new Boruvka(undirected_graph));
    b1->forest(undirected_graph);
   //std::unique_ptr<Boruvka<std::string,int>> b2(new Boruvka(undirected_graph2));
   //b2->forest(undirected_graph2);
    return 0;
}
