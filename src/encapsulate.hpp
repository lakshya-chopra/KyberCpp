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


                void initSeed();                        
		public:
		                std::vector<uint8_t> shrd_key0;
			EncapsulateKey(std::vector<uint8_t> pkey,std::string kyberVersion);
			void encapsulate();
			auto getCipher() -> std::vector <uint8_t>;
			std::vector<uint8_t> getSharedKey();

};

#endif
