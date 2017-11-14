#include "Glow.h"
#include "OneshotsGlowHack.h"
CHackProcess fProcess; // Object made so we can use the class functions
Glow H;
int main() // our start this code runs first.
{
	std::cout << "Merccss Private" << std::endl;
	std::cout << "F1 to toggle glow" << std::endl;
	std::cout << "Red = Enemy" << std::endl;
	std::cout << "Green = Team" << std::endl;
	fProcess.RunProcess(); // runing RunProcess() that setups everything we need to read and write memory.
	std::cout << "Game Found Injecting..." << std::endl;
	std::cout << "Succesfully injected" << std::endl;
	while (true) // a while loop that we have to run our code over and over until we shut it down.
	{
		H.Run();
		Sleep(1); // Sleep of 1ms so we dont eat to much cpu power.
	}
	
    return 0; 
}

