# KyberCPP

For this project, we'll make use of this [repository](https://github.com/itzmeanjan/kyber), here first we can install cmake and then build an executable out of it, or we can include this library directly in our header files and call out it's methods.

Note that, we could've also used `liboqs-cpp`, which is liboqs bindings for c++ projects.

### for installing cmake:
```
# first remove all traces of cmake from the system (if any)
$ sudo apt remove --purge --auto-remove cmake

# run the update command and add the software-properties-common manager alongside lsb_release (which is the version of your debian system)
$ sudo apt update && \
  sudo apt install -y software-properties-common lsb-release && \
  sudo apt clean all

# add kitware's signing key: (kitware is the organization which maintains cmake)
$ wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null

# add kitware's repo to  your apt sources list, lsb_release -cs can be Focal Fossa, Bionic, or jammy.
$ sudo apt-add-repository "deb https://apt.kitware.com/ubuntu/ $(lsb_release -cs) main"

# finally update and install cmake:
$ sudo apt update
  sudo apt install cmake
```

Test the installation using : `cmake -version`

## for directly using the header files, follow these steps:

#### edit the .bashrc file and add the header file variables (use the path of the directory where you cloned kyber,here I am using the root)
```
export KYBER_HEADERS=~/kyber/include
export SHA3_HEADERS=~/kyber/sha3/include
export SUBTLE_HEADERS=~/kyber/subtle/include
```
Logout and login again, or use `source .bashrc`.

### next, we can test out an example of kyber512, as given below:
```
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

```
[comments have been added for better understanding] <br/>

  - compile using `g++ -std=c++20 -Wall -O3 -march=native -I $KYBER_HEADERS -I $SHA3_HEADERS -I $SUBTLE_HEADERS main.cpp`.
  - give the `a.out` file the executable permissionss. `chmod +x ./a.out`
  - run : `./a.out`

