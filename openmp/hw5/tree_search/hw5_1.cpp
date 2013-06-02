//CORY BEKKER
#include<iostream>
#include<vector>
#include "tour.h"
using namespace std;

int main(){
  
  Tour hometown;
  Tour tour;
  Tour best_tour(1000000);
  vector<Tour>stack; //The stack is the tree and its nodes!
  unsigned int city = 0;
  
  stack.push_back(hometown); //Tour that visits only the hometown
  
  while(!stack.empty()) {
    tour.set_tour(stack.back());
    stack.pop_back();
    //if the current tour is the best, then change it to best_tour
    if(tour.get_num_cities() == num_cities) { 
      if(tour.better_than(best_tour))
	best_tour.set_tour(tour);
    } 
    else {
      for(city = 1; city < num_cities; city++){ //cycles through each city
	if(tour.add_city(city, best_tour)){	//adds a city to the current tour if it isnt bigger than the best tour
	  stack.push_back(tour);//adds the tour to the stack aka adds a new leaf node to the tree
	  tour.remove_last();//removes added leaf node so that way we can go back up to the tree and try the next leaf node
	}
      }
    }
  }
  best_tour.print_best();
  return 0;
}
