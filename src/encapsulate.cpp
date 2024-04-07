#include "encapsulate.hpp"

void EncapsulateKey::initSeed(){
                        prng::prng_t prng;
                        prng.read(m);

                }
                 EncapsulateKey::EncapsulateKey(std::vector<uint8_t> pkey,std::string kyberVersion){
	
                         this->pkey = pkey;
                         this->kyberVersion = kyberVersion;

                 }
	
        	void EncapsulateKey::encapsulate(){

                         cipher.clear();
                         cipher.resize(kyber512_kem::CIPHER_LEN);
                         initSeed(); //fill the values

                         if (kyberVersion == "512"){

                                /*we have to create a cipher & pkey std::span, because that's what these functions accept (not a vector)*/
                                std::cout<<"am here"<<std::endl;
                                auto _cipher = std::span<uint8_t,kyber512_kem::CIPHER_LEN>(cipher);
                                 auto _pkey = std::span<uint8_t, kyber512_kem::PKEY_LEN>(pkey);

                         	auto skdf = kyber512_kem::encapsulate(m,_pkey,_cipher);
                                skdf.squeeze(shrd_key0);
				
//write this to a file.
                         }
                        return;

                }

                 std::vector<uint8_t> EncapsulateKey::getCipher(){
                        return cipher;
                 }

std::array<uint8_t,32> EncapsulateKey::getSharedKey(){

	return shrd_key0;

}
