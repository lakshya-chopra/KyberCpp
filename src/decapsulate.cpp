#include "decapsulate.hpp"


DecapsulateKey::DecapsulateKey(std::vector<uint8_t> skey, std::vector<uint8_t> cipher){ 
                       this->skey = skey;
                        this->cipher = cipher;
}

void DecapsulateKey::decapsulate(){

                        auto _cipher = std::span<uint8_t,kyber512_kem::CIPHER_LEN>(cipher);
                        auto _skey = std::span<uint8_t, kyber512_kem::SKEY_LEN>(skey);
	
			auto rkdf = kyber512_kem::decapsulate(_skey, _cipher);
			rkdf.squeeze(shrd_key1);

			return ;

                }

std::array<uint8_t,32> DecapsulateKey::getSharedKey(){

	return shrd_key1;
	

}



