/***
 * @file Color_Generator.cpp
 * Color factory
 */
// Copyright 2019 by Julio Albornoz <gatalegath@protonmail.com>
// The License.txt file describes the conditions under which this
// software may be distributed.

#include "Generators.h"
#include <algorithm>
#include <fstream>
#include <sstream>

Color_Generator::Color_Generator(Config* config){
	/***
	* Class responsible of creating the color palette used by the program
	* 
	* @param config: Configuration parameters
	* 
	* @field size: Ruleset length
	* @field base: Number of colors used to generate the colors
	* @field interp: Color interpolation method
	* @field shuffle: Determines if the generated colors are shuffled after generation
	* @field save: Determines if generated data is saved after the simulation
	* @field palette: List of colors values for each tile (0-255)
	*/
	
	size = config->length;
	base = config->base;
	interp = config->interp;
	shuffle = config->shuffle;
	write = config->Csave;
	
	scheme = config->scheme;
	
	if (scheme == "RANDOM"){
		random_palette(base);
		}
	else if (scheme == "LOAD"){
		load();
		}
	
	generate_colors();
	}

Color_Generator::~Color_Generator(){
	delete palette;
	}
	
void Color_Generator::load(std::string path){
	/***
	* Loads a palette from a txt file
	* 	
	* @param path: Path of the ant source file
	*/
	std::ifstream file(path);
	std::string line;
	
	std::vector<glm::vec3>* colors = new std::vector<glm::vec3>;
	
	while (std::getline(file, line)){
		std::stringstream linestream(line);
		std::string val;
		
		glm::vec3 col;
		for (int i = 0; i < 3; i++){
			getline(linestream, val, '\t');
			col[i] = std::stoi(val);
			}
		colors->push_back(col);
		}
		
	palette = colors;
	file.close();
	}
	
void Color_Generator::save(std::string path){
	/***
	* Saves the current palette into a file
	* 
	* @param path: Path of the backup file
	*/
	std::ofstream file(path);
	std::vector<glm::vec3> colors = *palette;
	for (unsigned int i = 0; i < size; i++){
		glm::vec3 color = colors[i];
		file << (int)color[0] << '\t' << (int)color[1] << '\t' << (int)color[2] << '\n';
		}
		
	file.close();
	}
	
void Color_Generator::random_palette(unsigned int n){
	/***
	* Generates a random color palette 
	* 
	* @param n: Number of colors to generate
	*/
	std::vector<glm::vec3>* colors = new std::vector<glm::vec3>;
	
	for (unsigned int i = 0; i < n; i++){
		colors->push_back(glm::vec3(rand() % 256, rand() % 256, rand() % 256));
		}
	palette = colors;
	}
	
std::vector<glm::vec3>* Color_Generator::fill_palette(){
	/***
	* This method extends the existing palette to a target number of colors.
	* 
	* @return Numpy array with the new colorset
	*/
	unsigned int n = palette->size();
	
	std::vector<glm::vec3>* colors = new std::vector<glm::vec3>; 
	
	if (interp == "RGB"){
		int req = size - n ;
		int gaps[n-1];
		std::fill(&gaps[0], &gaps[n-1], (req/(n-1)));
		
		for (unsigned int i = 0; i < (req % (n-1)); i++){		//Adds remainder
			gaps[i]++;
			}
		
		std::vector<glm::vec3> pal = *palette;
		for (unsigned int j = 0; j < n-1; j++){
			linspace(pal[j], pal[j+1], gaps[j], colors);
			}
		
		colors->push_back(pal[n-1]);
		}
	
	else{
		std::vector<glm::vec3> pal = *palette;
		for (unsigned int i = 0; i < size; i++){
			colors->push_back(pal[i%n]);
			}
		}
		
	if (shuffle){
		std::random_shuffle(colors->begin(), colors->end());
		}

	return colors;
	}

void Color_Generator::linspace(glm::vec3 A, glm::vec3 B, int num, std::vector<glm::vec3>* vector){
	/***
	* Generates num-1 colors between colors A and B, returns a vector including A and the generated colors
	*
	*/
	glm::vec3 steps = (B - A)/(float)(num + 1);
	
	for (int i = 0; i < num+1; i++){
		vector->push_back(A + steps * (float)i);
		}
	}	

void Color_Generator::generate_colors(){
	/***
	* Generates a color palette based on the given parameters and saves it 
	* inside the object self.palette field
	*/
	unsigned int n = palette->size();
	
	if (n < (size)-1){
		palette = fill_palette();
		}
	}