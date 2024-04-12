## Program Flow:

  - Firstly, with the help of a Hardware/Secure RNG, 3 seeds : d, z & m are generated. Seeds 'd' and 'z' are used to create a random array of 32 bytes which is used in the generation of the keypair: pk & sk. Seed m is used for encapsulation, we'll come to that later.
  - After keygen, the public key which is transmitted across a public & insecure channel by the sender (here, Alice) to the receiver (refer to them as Bob). The Secret key is kept secure by Alice and never shared with anyone.
  - Bob uses the public key of Alice to generate a shared secret and a cipher, out of which only the cipher is sent back to Alice.
  - Alice decapsulates the cipher using her secret key and obtains the shared secret.
  - The Shared Secret, used by Kyber, as specified in it's submission round 2, is a key derived from SHAKE256 (a combination of SHA256 i.e. SHA2 and Keccak256/SHA3), and has a fixed length of **32 bytes**. Since this shared secret is of 32 bytes, one could directly use it as key for **symmetric encryption**, [interesting question here] (https://crypto.stackexchange.com/questions/89795/can-a-kem-shared-secret-be-used-directly-as-a-symmetric-key)
    Do not that using SHAKE256 has not been made mandatory by NIST, and thus, in general, a fixed keylength of 32 bytes using hashing functions from either the SHA2 or SHA3 family is generated.
  -  ><br/>As a modification in round-2, we decided to derive the final key using SHAKE-256 instead of SHA3-256.
    >This is an advantage for protocols that need keys of more than 256 bits.
    >Instead of first requesting a 256-bit key from Kyber and then expanding it, they can pass an additional key-length parameter to Kyber and obtain a key of the desired length. This feature is not supported by the NIST API, so in our implementations we set the keylength to a fixed length of 32 bytes in api.h.
     > <cite> [read more here](https://pq-crystals.org/kyber/data/kyber-specification-round3-20210131.pdf)
  - ![image](https://miro.medium.com/v2/resize:fit:1100/format:webp/0*-q0OB65GCekDIm-6.png)
  - ![image](https://github.com/lakshya-chopra/KyberCpp/assets/77010972/7d6a5a54-233e-45c9-b967-1a941a169bff)

  - For sharing b/w both the sides, this procedure can be followed:
  - ![image](https://github.com/lakshya-chopra/KyberCpp/assets/77010972/87511884-15d6-4d99-874e-f4c1c2fbb43d)

  - First Standardized PQC algorithms:
    ![image](https://github.com/lakshya-chopra/KyberCpp/assets/77010972/23e3e968-a16c-4f75-97f6-a77cbbf0d493)

## A bit of mathematical background:

  - An **integral LATTICE** is defined as a Z-linear combination (integral scalar values) of n independent vectors, b<sub>i</sub> belonging to Z<sup>n</sup>.
  - ![image](https://github.com/lakshya-chopra/KyberCpp/assets/77010972/c74d0ce4-e228-4d98-b60a-a90305b16560)
  - Reason why lattices are used? because they pose one such optimization problem which is considered to be quite hard to solve, i.e. The shortest vector problem



