#ifndef ENCAPSULATE_HPP
#define ENCAPSULATE_HPP

#include<iostream>
#include<array>
#include<algorithm>
#include <vector>

#include "kyber512_kem.hpp"
#include "kyber768_kem.hpp"
#include "kyber1024_kem.hpp"


class EncapsulateKey{

		constexpr static size_t KEY_LEN = 32;
	        private:
                //seed for the KDF:
                 std::array<uint8_t, 32> m{};
                 std::vector<uint8_t> cipher{};

                 std::vector<uint8_t> pkey;
                 std::string kyberVersion;
			
		prng::prng_t prng;

	
                void initSeed();                        

		public:
		                std::array<uint8_t,32> shrd_key0{1,2,3,4,5,6,7};
			EncapsulateKey(std::vector<uint8_t> pkey,std::string kyberVersion,prng::prng_t prng);
			void encapsulate();
			auto getCipher() -> std::vector <uint8_t>;
			std::array<uint8_t,32> getSharedKey();

};

#endif
