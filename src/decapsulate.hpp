#ifndef DECAPSULATE_HPP
#define DECAPSULATE_HPP

#include<iostream>
#include<array>
#include<algorithm>
#include <vector>

#include "kyber512_kem.hpp"
#include "kyber768_kem.hpp"
#include "kyber1024_kem.hpp"


class DecapsulateKey{

	constexpr static size_t KEY_LEN = 32;
	private:
               std::vector<uint8_t> skey;
            std::vector<uint8_t> cipher;

		
	public:

		std::array<uint8_t,32> shrd_key1{};
		DecapsulateKey(std::vector<uint8_t> skey, std::vector<uint8_t> cipher);
		void decapsulate();
		std::array<uint8_t,32> getSharedKey();
};

#endif
