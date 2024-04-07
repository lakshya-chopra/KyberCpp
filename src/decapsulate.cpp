#include "decapsulate.hpp"


DecapsulateKey::DecapsulateKey(std::vector<uint8_t> skey, std::vector<uint8_t> cipher){ 
                       this->skey = skey;
                        this->cipher = cipher;
			         shrd_key1.clear();
                                shrd_key1.resize(32);

}

void DecapsulateKey::decapsulate(){

                        auto _cipher = std::span<uint8_t,kyber512_kem::CIPHER_LEN>(cipher);
                        auto _skey = std::span<uint8_t, kyber512_kem::SKEY_LEN>(skey);
	
			auto _shrd_key1 = std::span<uint8_t,32>(shrd_key1);			

			auto rkdf = kyber512_kem::decapsulate(_skey, _cipher);
			rkdf.squeeze(_shrd_key1);

			return ;

                }

std::vector<uint8_t> DecapsulateKey::getSharedKey(){

	return shrd_key1;
	

}



