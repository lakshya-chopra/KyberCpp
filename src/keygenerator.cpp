#include "keygenerator.hpp"

void KeyGenerator::fill_seeds(){
        prng.read(seed1);
        prng.read(seed2);

        }

	KeyGenerator::KeyGenerator(std::string kyberVersion,prng::prng_t prng){
		
		this->kyberVersion = kyberVersion;
this->prng = prng;			
		switch(stoi(kyberVersion)){
			case 512:
				
				pkey.resize(kyber512_kem::PKEY_LEN,0);
				skey.resize(kyber512_kem::SKEY_LEN,0);
			       	//pkey_len = kyber512_kem::PKEY_LEN;
				//skey_len = kyber512_kem::SKEY_LEN;
				break;	
			case 768:
				pkey.resize(kyber768_kem::PKEY_LEN,0);
				skey.resize(kyber768_kem::SKEY_LEN,0);
				// pkey_len = kyber768_kem::PKEY_LEN;
                                //skey_len = kyber768_kem::SKEY_LEN;

				break;
			case 1024:
				pkey.resize(kyber1024_kem::PKEY_LEN,0);
				skey.resize(kyber1024_kem::SKEY_LEN,0);
				// pkey_len = kyber1024_kem::PKEY_LEN;
                                //skey_len = kyber1024_kem::SKEY_LEN;
				break;
		 }
	}

        void KeyGenerator::generateKeys(){
        fill_seeds();

	if(kyberVersion == "512"){
		  auto _pkey = std::span<uint8_t, kyber512_kem::PKEY_LEN>(pkey);
  auto _skey = std::span<uint8_t, kyber512_kem::SKEY_LEN>(skey);
       		 kyber512_kem::keygen(seed1, seed2 , _pkey,_skey);
        	}
	else if(kyberVersion == "768") {
		
		  auto _pkey = std::span<uint8_t, kyber768_kem::PKEY_LEN>(pkey);  
		auto _skey = std::span<uint8_t, kyber768_kem::SKEY_LEN>(skey);
	
		kyber768_kem::keygen(seed1,seed2,_pkey,_skey);
		}
	else{
	
		  auto _pkey = std::span<uint8_t, kyber1024_kem::PKEY_LEN>(pkey);
  auto _skey = std::span<uint8_t, kyber1024_kem::SKEY_LEN>(skey);
	
		kyber1024_kem::keygen(seed1,seed2,_pkey,_skey);	
	}
	}

        std::vector<uint8_t> KeyGenerator::getPK(){

                /* sha256 hash of the public key */
        	/*pkey has also been changed, despite us passing _pkey, because _pkey is sort of a pointer*/       
	       
		return pkey;
        }
        std::vector<uint8_t> KeyGenerator::getSK(){

                return skey;
	}



