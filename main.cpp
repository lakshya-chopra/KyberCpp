#include "kyber512_kem.hpp"

#include <algorithm>
#include <array>
#include<iostream>

/*One could also ponder about the fact that we're creating these variables at runtime and not in the global area */

int main(){

//first, we'll create two 32 byte seeds, reason why uint_8 is being used. Initialize each element to 0 (values will be filled later)
  std::array<uint8_t, 32> d{}; 
  std::array<uint8_t, 32> z{}; 

  // initialize a pair of public and private key.
  std::array<uint8_t, kyber512_kem::PKEY_LEN> pkey{};
  std::array<uint8_t, kyber512_kem::SKEY_LEN> skey{};
  
  std::array<uint8_t, 32> m{}; 
  std::array<uint8_t, kyber512_kem::CIPHER_LEN> cipher{};

  // here, we are using a prng, in future, one could replace it with a qrng for true and most secure form of randomness.
  prng::prng_t prng;

  prng.read(d);
  prng.read(z);
  prng.read(m);

  /*call the keygen method & then encapsulate it using the random seed, this gives a SHAKE256 KDF and a ciphertext.
 
    [Note that: Encapsulation is done by the recipient (Bob) using the public key of Alice (sender), Bob then sends the KDF (shared secret) and ciphertext to Alice, who decrypts the cipher using her private key, and also obtains the KDF, this is decapsulation]
    
  */
   
  kyber512_kem::keygen(d, z, pkey, skey);
  auto skdf = kyber512_kem::encapsulate(m, pkey, cipher);
  auto rkdf = kyber512_kem::decapsulate(skey, cipher);

  std::array<uint8_t, 32> sender_key{};
  skdf.squeeze(sender_key);

  std::array<uint8_t, 32> receiver_key{};
  rkdf.squeeze(receiver_key);

  //check if both are equal or not.
  
  try{
  	if(std::ranges::equal(sender_key, receiver_key)){
	  std::cout<<"Perfect Transmission"<<std::endl;
	}
	else{
		throw std::runtime_error("Issues with this system, should be aborted!");
	}
  }
catch(std::runtime_error& e){
	std::cerr<<e.what()<<std::endl;

}
  
  return 0;
}
