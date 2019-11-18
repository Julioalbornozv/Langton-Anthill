#include "Parameters.h"
#include "Generators.h"
//#include <Ant.h>
//#include <Colony.h>
//#include <Engine.h>

#include <iostream>

int main(){
	//Read initial parameters
	Config Param = Config();
	
	// Initialize tiles
	Tile_Generator TGen = Tile_Generator(&Param);
	
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