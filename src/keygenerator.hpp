#ifndef KEYGENERATOR_HPP
#define KEYGENERATOR_HPP

#include "kyber512_kem.hpp"
#include "kyber768_kem.hpp"
#include "kyber1024_kem.hpp"

#include <algorithm>
#include <array>
#include<iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <fstream>

class KeyGenerator{

        private:
        /*seeds must be kept  private*/

        /* Using vector because it can be resized. */
	
        std::vector<uint8_t> pkey; //depending on the version, we'll resize.
        std::vector<uint8_t> skey;
	
	prng::prng_t prng;

        std::array<uint8_t,32> seed1{};
        std::array<uint8_t,32> seed2{};
	
	std::string kyberVersion;

	void fill_seeds();
	
public:
	KeyGenerator(std::string kyberVersion,prng::prng_t prng);
	
	void generateKeys();
	auto getSK() -> std::vector<uint8_t>;
	auto getPK() -> std::vector<uint8_t> ;

};

#endif

