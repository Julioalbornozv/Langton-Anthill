#include "Parameters.h"
//#include <Generators.h>
//#include <Ant.h>
//#include <Colony.h>
//#include <Engine.h>

#include <iostream>

int main(){
	//Read initial parameters
	Config Param = Config();
	std::cout << Param.DWidth << std::endl;
	std::cout << Param.DHeight << std::endl;
	std::cout << Param.base << std::endl;
	std::cout << Param.scheme << std::endl;
	std::cout << Param.interp << std::endl;
	std::cout << Param.shuffle << std::endl;
	std::cout << Param.Csave << std::endl;
	std::cout << Param.length << std::endl;
	std::cout << Param.symbols << std::endl;
	std::cout << Param.def_rule << std::endl;
	std::cout << Param.Rsave << std::endl;
	std::cout << Param.scale << std::endl;
	std::cout << Param.shape << std::endl;
	
	// Initialize tiles
	//Tile_Generator TGen = Tile_Generator(config);
	//
	//// Initialize engine class
	//Engine render = Engine(config, TGen.generic);
	//
	//// Create ants
	//Colony Anthill = Colony(config, TGen.generic);
	//Anthill.load_ants("ants.txt");
	//
	//// Generates colors
	//Color_Generator CGen = Color_Generator(config);
	//
	//// Starts render loop
	//render.run(Anthill, CGen, TGen);
	}