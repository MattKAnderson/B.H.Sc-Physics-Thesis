/* Main file for MC simulation of helicene */

#include <iostream>
#include <string>
#include "MCsim.h"
#include "fileIO.h"

using namespace std;

int main()
{
	//simulation parameters
	int chainSize = 8;
	double temp = 1.0;
	double alpha = 3.5;
	double max_angle_change = 0.30;  //in radians
	//sampling parameters
	int Nwarm = 10000;
	int Nstep = 10;
	int Nmeas = 100;

	//atom positions
	vector<Vector3D> atomPositions(6 * chainSize);

	//file output name
	string positionfile = "C:/Users/matta/Documents/sim_files/atomPositions.txt";

	//simulation
	MCsim sim(alpha, temp, chainSize, max_angle_change);
	sim.simulate(Nwarm, Nstep, Nmeas);
	atomPositions = sim.returnAtomPositions();

	cout << "Average End to End distance was: \t" << sim.EE_avg() << endl;
	cout << "Average Energy was: \t\t\t" << sim.E_avg() << endl;
	cout << "Pass ratio was: " << sim.pass_ratio() << endl;
	for (int i = 0; i < chainSize - 1; i++)
	{
		cout << "Angle " << i << " : " << sim.final_angles()[i] << std::endl;
	}
	cin.get();
	//output to file
	conformation_to_file(atomPositions, positionfile);
}