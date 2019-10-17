#include "MCsim.h"
#include <iostream>

MCsim::MCsim()
{
}

MCsim::MCsim(double a, double temperature, int size, double max_angle_change)
{
	SweepSize = 36 * size;          //total number of atoms
	alpha = a;
	T = temperature;
	//seeding random generator and setting bounds for rand_ring distribution
	clk::time_point time = clk::now();
	clk::duration dtime = time.time_since_epoch();
	long long unsigned seed = std::chrono::duration_cast<std::chrono::nanoseconds>(dtime).count();
	std::cout << "The seed is: " << seed << std::endl;
	rng.seed(seed);
	std::uniform_int_distribution <int> temp(0, (size - 2));
	pick_angle.param(temp.param());
	std::uniform_real_distribution <double> temp2(-max_angle_change, max_angle_change);
	angle_adjust.param(temp2.param());
	std::uniform_real_distribution <double> temp3(-M_PI, M_PI);
	angle_dis.param(temp3.param());
	//initializing chain conformation
	Chain.resize(size);
	Angles.resize(size - 1);
	for (int i = 0; i < size - 1; i++)
	{
		Angles[i] = angle_dis(rng);
	}
	Energy = chain_energy();

}


MCsim::~MCsim()
{
}

void MCsim::simulate(int warm, int Nstep, int Nmeas)
{
	measure_num = 0;
	EE_measurements.resize(Nmeas);
	E_measurements.resize(Nmeas);
	//doing warm-up sweeps
	MCSweeps(warm);
	successfulPasses = 0;
	fails = 0;
	//doing simulation experiment
	for (int i = 0; i < Nmeas; i++)
	{
		MCSweeps(Nstep);
		measure();
	}
	successRatio = double(successfulPasses) / double(successfulPasses + fails);
}

std::vector<Vector3D> MCsim::returnAtomPositions()
{
	update_conformation();
	std::vector<Vector3D> positions(6 * Chain.size());
	for (int i = 0; i < Chain.size(); i++)
	{
		for (int j = 0; j < 6; j++)
		{
			positions[i * 6 + j] = Chain[i].atoms[j];
		}
	}
	return positions;
}

double MCsim::EE_avg()
{
	double avg = 0.0;
	for (int i = 0; i < measure_num; i++)
	{
		avg += EE_measurements[i];
	}
	avg /= measure_num;
	return avg;
}

double MCsim::E_avg()
{
	double avg = 0.0;
	for (int i = 0; i < measure_num; i++)
	{
		avg += E_measurements[i];
	}
	avg /= measure_num;
	return avg;
}

double MCsim::pass_ratio()
{
	return successRatio;
}

row MCsim::final_angles()
{
	return Angles;
}

matrix MCsim::gyration_tensor()
{
	return matrix();
}

void MCsim::MCSweeps(int N)
{
	int iter = N * SweepSize;
	for (int i = 0; i < iter; i++)
	{
		anglePos = pick_angle(rng);
		oldAngle = Angles[anglePos];
		Angles[anglePos] = change_angle();
		newEnergy = chain_energy();
		if (newEnergy < Energy)
		{
			Energy = newEnergy;
			successfulPasses += 1;
		}
		else if (exp(-(newEnergy - Energy) / T) > dis0to1(rng))
		{
			Energy = newEnergy;
			successfulPasses += 1;
		}
		else
		{
			Angles[anglePos] = oldAngle;
			fails += 1;
		}
	}
}

void MCsim::measure()
{
	EE_measurements[measure_num] = EE_distance();
	E_measurements[measure_num] = Energy;
	measure_num += 1;
}

void MCsim::calculate_avgs()
{
}

void MCsim::statistical_error()
{
}

void MCsim::update_conformation()
{
	Chain[0].update(initial0, initial1, initialP, 0.0);
	for (int i = 0; i < (Chain.size() - 1); i++)
	{
		Chain[i + 1].update(Chain[i].pass_new_pos1(), Chain[i].pass_new_pos2(), Chain[i].pass_perp(), Angles[i]);
	}
}

double MCsim::chain_energy()
{
	double sum = 0.0;
	for (int i = 0; i < (Chain.size() - 1); i++)
	{
		sum += alpha * (Angles[i]) * (Angles[i]);
		//std::cout << "sum: " << sum << "\t";
	}
	//std::cout << std::endl;
	//std::cin.get();
	return sum;
}

double MCsim::EE_distance()
{
    update_conformation();
	Vector3D EE = Chain[0].atoms[5] - Chain[Chain.size() - 1].atoms[5];
	return EE.Vlen();
}

double MCsim::change_angle()
{
	double angle_change = angle_adjust(rng);
	if ((Angles[anglePos] + angle_change) > M_PI)
	{
		return (-2*M_PI + Angles[anglePos] + angle_change);
	}
	else if ((Angles[anglePos] + angle_change) <= -M_PI)
	{
		return (2*M_PI + Angles[anglePos] + angle_change);
	}
	return (Angles[anglePos] + angle_change);
}
