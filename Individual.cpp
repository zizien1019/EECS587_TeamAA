#include <random>
// #include "Individual.h"

#include <vector>




// This struct defines the chance for an individual to get infected as well as,
// the infection period in epochs
struct IndividualParameters {
	float Infectiosity = 0.13;
	std::uint8_t DiseaseDuration = 7;
};





class Individual {
public:
	Individual() : infected_(false), hit_(false), recovered_(), epochs_infected_(0), location_(0) { } // Default constructor
	Individual(bool infected, bool hit, bool recovered, std::uint8_t days_infected, int location) // Full constructor
		: infected_(infected), hit_(hit), recovered_(recovered), epochs_infected_(days_infected), location_(location) { }
	void infect();
	void recover();
	void advance_epoch();
	void try_infect();
	void move(std::vector<int>& new_locations);
	void set_location(int location);
	int get_location() const;
	bool is_infected() const;
	bool is_hit() const;
	bool is_recovered() const;
private:
	bool infected_;
	bool hit_; // Indicates if individual was infected as some point
	bool recovered_;
	std::uint8_t epochs_infected_;
	int location_; // Refers to the graph node that represents the current location of the individual
	IndividualParameters parameters_;
	static float get_random_infect_chance();
	static int get_random_location(size_t neighbours_size);
};

// Infect the individual
inline void Individual::infect() {
	infected_ = true;
	hit_ = true;
}

// Recover the individual
inline void Individual::recover() {
	if (infected_) {
		infected_ = false;
		recovered_ = true;
	}
}

// Advanced the time for the current individual. Also check if the individual gets healed
inline void Individual::advance_epoch() {
	if (infected_) {
		if (epochs_infected_ >= parameters_.DiseaseDuration)
			recover();
		else
			++epochs_infected_;
	}
}

// Set the location
inline void Individual::set_location(int location) {
	location_ = location;
}

// Get the location
inline int Individual::get_location() const {
	return location_;
}

// Check if individual is currently infected
inline bool Individual::is_infected() const {
	return infected_;
}

// Check if individual was infected in the past
inline bool Individual::is_hit() const {
	return hit_;
}

// Check if individual is recovered
inline bool Individual::is_recovered() const {
	return recovered_;
}






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

int Individual::get_random_location(size_t neighbours_size) {
	std::random_device random_device;
	std::mt19937 mersenne_twister_engine(random_device());
	std::uniform_int_distribution<> uniform_int_distribution(0, static_cast<int>(neighbours_size)); // Since we added the current location, no need to decarase the max int

	return uniform_int_distribution(mersenne_twister_engine);
}

// Randomly move the individual to another location or stay at the same location
void Individual::move(std::vector<int>& node_neighbours) {

	node_neighbours.push_back(location_); // Add current location in the new locations vector
	location_ = node_neighbours[get_random_location(node_neighbours.size())]; // Assign the random location
}