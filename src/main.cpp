#include "keygenerator.hpp"

#include <iostream>
#include <sstream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>

#include "encapsulate.hpp"
#include "decapsulate.hpp"

int main(){

	std::string kyberVers;
        while(1){

                std::cout<<"Welcome to Kyber Keygenerator, specify the kyber version you would like to use: [512/768/1024]\n\n"<<std::endl;
                std::cin >> kyberVers; //this will be stored in a file, so that other programs of this implementation can access it accordingly.
                if((kyberVers != "512") && (kyberVers != "768") && (kyberVers != "1024")){
                        std::cout<<"\nPlease enter correct version names"<<std::endl;
                }else{
                        break;
                }
        }
	prng::prng_t prng;

        KeyGenerator keygen(kyberVers,prng);
        keygen.generateKeys();

        auto pkey = keygen.getPK();
        auto skey = keygen.getSK();

        std::stringstream ss;

        std::cout<<"\nPublic Key:\n "<<std::endl;
        for(auto i : pkey){

                //add hex form of this integer to the stringstream.
                ss << std::hex << static_cast<int>(i);

        }
        //finally read from the ss

        std::cout<<ss.str()<<std::endl;

        std::cout<<"\nfault here!\n"<<std::endl;

        EncapsulateKey encaps(pkey,kyberVers,prng);
        encaps.encapsulate();

        ss.str("");
        ss.clear();

        auto cipher = encaps.getCipher();

        std::cout<<"\nCipher Key:\n"<<std::endl;

        for(auto i : cipher){
                ss <<std::hex <<static_cast<int>(i);
        }
        std::cout<<ss.str()<<std::endl;

       DecapsulateKey decaps(skey,cipher);

	       auto shared_key1 = decaps.getSharedKey();
//        ss.str("");
 //       ss.clear();
  //      for (auto i : shared_key1){
//                ss << std::hex <<static_cast<int>(i);
//}

        std::cout<<"\n Here's the shared secret " <<std::endl;
 //       std::cout<<ss.str()<<std::endl;

{
	using namespace kyber_utils;
	std::cout<<to_hex(shared_key1)<<std::endl;		

}

	return 0;
}
