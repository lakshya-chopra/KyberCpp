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

  ## Ring:
  A ring is a set R that is equipped with 2 binary operations: (+) & (•) that satisfy the following 3 axioms:
    1. R is an abelian group under addition (commutative, identity, inverse , associative)
    2. R is monoid under multiplication, i.e. multiplication is associative & multiplicative identity is satisfied.
    3. Multiplication is distributive w.r.t to addition.

  Rings generalize fields, and the RING elements may consist of scalars, functions, matrices, etc.
  An example: 
  ![image](https://github.com/lakshya-chopra/KyberCpp/assets/77010972/b18f3b9d-5918-4a69-a34e-dffd05397a4b)

  An important example is **Z<sub>n</sub>**, which is the set of integers mod (n): the quotient group & the polynomial ring.
  
  ![image](https://github.com/lakshya-chopra/KyberCpp/assets/77010972/15d63dee-e1cc-4e9c-98d4-a855ebf697e5)
  ![image](https://github.com/lakshya-chopra/KyberCpp/assets/77010972/15852b69-ee2c-4aec-a414-b4cff30a7565)


  ## Lattices:
  
  - An **integral LATTICE** is defined as a Z-linear combination (integral scalar values) of n independent vectors, b<sub>i</sub> belonging to Z<sup>n</sup>.
  - ![image](https://github.com/lakshya-chopra/KyberCpp/assets/77010972/00d6ef32-2e1c-46e7-9fec-838d9505d015)
  - ![image](https://github.com/lakshya-chopra/KyberCpp/assets/77010972/c74d0ce4-e228-4d98-b60a-a90305b16560)
  - Reason why lattices are used? because they pose af few mathematical optimization problems which are considered to be quite hard to solve, i.e. The shortest vector problem, GapSVP & the CVP.
  - In SVP, the goal is to find the shortest non-zero vector in an integral lattice, i.e. given a vector space V and a norm N (generally the Euclidean norm) for a lattice L, one must find the shortest vector, |v|<sub>n</sub> = λ(L),where λ(L) denotes the length of the shortest non-zero vector in L.
  - In GapSVP, we are concerned with finding whether the length of such a vector is greater than or below a certain threshold (2 parameters: alpha & beta).
  - This problem can be solved (with quite ease) in lower dimensional spaces with a **good** basis (which are nearly orthogonal to each other), if however, a basis which is **bad** (vectors nearly collinear to each other) & the dimension is high, it becomes terribly hard to solve, even for QCs.
  - [LLL](https://en.wikipedia.org/wiki/Lenstra%E2%80%93Lenstra%E2%80%93Lov%C3%A1sz_lattice_basis_reduction_algorithm) is one such algorithm which can solve such problems in polynomial time

  ## LWE:
  - In LWE, given a linear system, A.s = t, where A is the coefficient / public matrix and s is the solution vector to this equation, we purposely introduce some noise in the system, that is sampled from a Gaussian Distribution (usually discrete) or a cyclotomic ring, this noise is kept secret & makes it really hard to find the solution to this problem.
  - ![image](https://github.com/lakshya-chopra/KyberCpp/assets/77010972/da569458-d4d3-4461-9ae7-9b6805537583)
  - ![image](https://github.com/lakshya-chopra/KyberCpp/assets/77010972/19723259-2615-4933-ba14-de9389d17f97)
  - ![image](https://github.com/lakshya-chopra/KyberCpp/assets/77010972/3d00dab7-a639-4a29-888d-e367491a630d)


  - In total,
    ![image](https://github.com/lakshya-chopra/KyberCpp/assets/77010972/d788125d-7735-413f-b60e-6b592165270e)

  - LWE can too be viewed as a Lattice Problem (like SIS), like the set of all integer vectors that are congruent to A*s<sup>T</sup>
  - ![image](https://github.com/lakshya-chopra/KyberCpp/assets/77010972/b392369c-6c18-40f1-8d23-eb3033ecc145)
  - This is basically like a BDD problem, where we are given a point b (the point with noise added), and from that we have to find the vector v = s<sup>t</sup>A, which allows us to find the secret (devoid of all the noise).
  - SIS vs LWE
  - ![image](https://github.com/lakshya-chopra/KyberCpp/assets/77010972/7c0372eb-378f-4ff9-89bf-bc2257c3d045)
  - The public key, A is uniformly chosen from a set of integer m*n matrices modulo q.
  - ![image](https://github.com/lakshya-chopra/KyberCpp/assets/77010972/46d205e6-4f3d-4f4e-bfaf-764c951158bb)



  
  
  ## Rings in LWE:
  
  In this, a secret polynomial from a ring is concealed with the noisy data sampled from a structured ring.

## References:
1. [crypto school croatia](https://summerschool-croatia.cs.ru.nl/2015/Lattice-based%20crypto.pdf)
2. [LWE & its relation to Lattices](https://web.stanford.edu/class/cs354/scribe/lecture14.pdf)
3. [LLL algo](https://en.wikipedia.org/wiki/Lenstra%E2%80%93Lenstra%E2%80%93Lov%C3%A1sz_lattice_basis_reduction_algorithm)
4. [Ring LWE](https://www.cse.iitk.ac.in/users/angshuman/assets/pdf/RINGLWE_SPACE_2016.pdf)
5. [PQC](https://summerschool-croatia.cs.ru.nl/2018/slides/Introduction%20to%20post-quantum%20cryptography%20and%20learning%20with%20errors.pdf)
