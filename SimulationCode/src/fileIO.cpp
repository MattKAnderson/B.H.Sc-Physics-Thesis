/* Source file for file I/O functions */
#include <iostream>
#include "fileIO.h"

#define oFormat std::setw(10)

void conformation_to_file(std::vector<Vector3D> positions, std::string filelocation)
{
	//getting number of atom positions to output
	int num_atoms = positions.size();

	//opening output file
	std::ofstream out_file;
	out_file.open(filelocation);
	if (!out_file.is_open()) { std::cout << "unable to open output file\n"; }
	else { std::cout << "output file successfully opened\n"; }
	//outputting to file
	out_file << num_atoms << std::endl << std::endl;
	for (int i = 0; i < num_atoms; i++)
	{
		out_file << "C\t" << std::right << std::fixed << std::setprecision(7) << oFormat << positions[i].x << "\t" << oFormat << positions[i].y << "\t" << oFormat << positions[i].z << std::endl;
	}
	out_file.close();
}

