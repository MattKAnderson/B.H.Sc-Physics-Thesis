#pragma once

#define _USE_MATH_DEFINES

#include "HRing.h"
#include <random>
#include <chrono>
#include <cmath>


typedef std::vector<double> row;
typedef std::vector<row> matrix;
typedef std::chrono::high_resolution_clock clk;

class MCsim
{
public:
	//public member data
	//none

	//public member functions
	MCsim();
	MCsim(double a, double temperature, int size, double max_angle_change);
	~MCsim();
	
	void simulate(int warm, int Nstep, int Nmeas);
	std::vector<Vector3D> returnAtomPositions();
	double EE_avg();
	double E_avg();
	double pass_ratio();
	row final_angles();
	matrix gyration_tensor();


private:
	//private member data
	double oldAngle;
	double Energy;
	double newEnergy;
	double T;
	double alpha;
	double successRatio;
	int anglePos;
	int total_measurements;
	int measure_num;
	int SweepSize;
	int successfulPasses;
	int fails;
	row EE_measurements;
	row E_measurements;
	row Angles;
	std::vector<HRing> Chain;
	std::mt19937_64 rng;
	std::uniform_real_distribution <double> angle_dis;
	std::uniform_real_distribution <double> dis0to1{ 0.0, 1.0 };
	std::uniform_real_distribution <double> angle_adjust;
	std::uniform_int_distribution <int> pick_atom{ 0, 5 };
	std::uniform_int_distribution <int> pick_angle;
	
	//starting coordinates
	Vector3D initial0{ 0.0, 0.0, 0.0 };
	Vector3D initial1{ 1.0, 0.0, 0.0 };
	Vector3D initialP{ 0.0, 1.0, 0.0 };
	
	//HChain avg_structure; add later

	//private memberfunctions
	void MCSweeps(int N);       //perform N number of Monte Carlo Sweeps
	void measure();
	void calculate_avgs();
	void statistical_error();
	void update_conformation();
	double change_angle();
	double chain_energy();
	double EE_distance();
};

