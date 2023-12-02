#include <random>
#include <iostream>
#include <map>

#include "Individual.h"
using namespace std;
// Check if an individual gets infected by a predefined chance
void Individual::try_infect() {

	if (!infected_) {
		if (get_random_infect_chance() < parameters_.Infectiosity)
			infect();
	}
}

float Individual::get_random_infect_chance() {

	std::random_device random_device;
	std::mt19937 mersenne_twister_engine(random_device());
	std::uniform_real_distribution<> real_random(0, 1);

	return static_cast<float>(real_random(mersenne_twister_engine));
}
//////////////////////////##################################################
int Individual::get_random_location(map<int,int> weights,std::vector<int>& node_neighbours) {
	std::random_device random_device;
	std::mt19937 mersenne_twister_engine(random_device());

	// Create a discrete distribution based on edge weights
    std::vector<double> probabilities;

// mod by Alan ============================================================
// factors: 
// 1. population at the neighboring cells
// 2. distance to the neighboring cells
// 3. movement of the majority
#include<cmath>
    for (int neighbor : node_neighbours) {
		int n = population(neighbor); //+2 to avoid problem when population == 0 or 1
			int Total_people = 1000;
			int Locations = 100000;
		double weight1 = exp( -((n-Total/sqrt(Locations))/(Total/sqrt(Locations)/3)).^2 );
		double weight2 = exp( -(n/(Total/sqrt(Locations)/10)).^2 );
		weights.at(neighbor) = weight1+weight2;
		cout<<"neighbor: "<<neighbor<<"weights.at(neighbor): "<<weights.at(neighbor)<<endl;
        probabilities.push_back(weights.at(neighbor));
    }
// end mod by Alan ========================================================

	// Normalize probabilities to make sure they sum to 1
    double total_weight = std::accumulate(probabilities.begin(), probabilities.end(), 0.0);
    for (double& prob : probabilities) {
        prob /= total_weight;
    }

	cout<<"probabilites.size(): "<<probabilities.size()<<endl;
	std::discrete_distribution<> discrete_distribution(probabilities.begin(), probabilities.end());

	return discrete_distribution(mersenne_twister_engine);
}

// Randomly move the individual to another location or stay at the same location
void Individual::move(std::vector<int>& node_neighbours, map<int,int> weights) {
    
	
	node_neighbours.push_back(location_); // Add current location in the new locations vector
	
	weights[location_]=100;
	location_ = node_neighbours[get_random_location( weights,node_neighbours)]; // Assign the random location
}
//////////////////////////##################################################