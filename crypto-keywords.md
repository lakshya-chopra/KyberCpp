Here's a concise division of all the commonly used cryptographic primitives & constructions:

  ## Hashing:
  - SHA family:
    - SHA1
    - SHA2 (SHA2-256, SHA2-512)
    - SHA3 (subset of Keccak) - SHA3-256, SHA3-512, SHAKE256, SHAKE512 (two xofs)
  - Keccak (for variable length hashes)
    ![image](https://github.com/lakshya-chopra/KyberCpp/assets/77010972/3009bafe-6233-4a2b-96dd-9dbc46e24b46)
  - [Ref](https://crypto.stackexchange.com/a/68314)
    
## Ciphers:
  - Block Ciphers - AES (128/256/512), modes - CTR, CBC, GCM. 3DES
     ![image](https://github.com/lakshya-chopra/KyberCpp/assets/77010972/9ec0a3ea-2151-4f1f-aa87-c833f9e2eb0e)
  - Stream Cipher: ChaCha20, Salsa20
     ChaCha20-Poly1305 is equivalent to AES-GCM (ciphering with authentication), such algorithms are known as "authenticated encryption with associated data" (AEAD).
## MACs:
  - Hash Based - HMAC-SHA256, HMAC-SHA512
  - Poly1305, UMAC, VMAC
  - Checksums (not really used now, vulnerable to forgery)
    ![image](https://github.com/lakshya-chopra/KyberCpp/assets/77010972/f39f9a78-bf04-4318-bc0d-b06f198f650d)

## Public Key Cryptography:
  - PKC is utilised to safely transfer a symmetric key (used for encryption of critical data), from one end to the other, by making use of asymmetric algorithms, or Key exchanges like Diffie Hellman (or ECDH). The main crux of PKC is that, we are using a publicly available key for encrypting some data, and only the corresponding priv key can be used to decrypt it back (reason why it's asymmetric: keys for enc and dec are different).
    
    - Cryptographic protocols, primitives & constructions used:
      
      - **Diffie Hellman KEX, following protocols are the extensions of this: ECDH, El Gamal, X3DH, PQXDHE.**
      - Elliptic Curve Crypt - based on the ECDLP problem, the PKC techniques utilising this are:
          - ECDH(E)
          - ECDSA
          - EdDSA
            ECC is a cryptographic primitive over which the above mentioned techniques/protocols are built upon.
      - RSA:
          - RSA PKCS#1-15 (from 1 to 15) : a set of standards, techniques that use the RSA crypt primitive.
            - RSA PKCS#1.5 (incorporates RSA-OAEP)
          - can be used for KEM, KEX, & DSA, [RSA KEM](https://datatracker.ietf.org/doc/html/rfc5990)
            [Read More here](https://www.spiceworks.com/it-security/network-security/articles/what-is-pkcs/#:~:text=PKCS%20%231%20%E2%80%93%20RSA%20cryptography%20standard,format%20of%20the%20digital%20certificate.)
      - **Encryption Schemes - ECIES, DHIES, DH Ratchet, Signal Protocol, RSA-KEM** <br/>

      RSA-OAEP is used for making the RSA Key Exchange **IND-CPA & IND-CCA secure.** Plain Old RSA has been deprecated.
      ![image](https://github.com/lakshya-chopra/KyberCpp/assets/77010972/46927e56-adce-47c7-a808-33bdb321d840)

 ## Digital Signature Algorithms:
   - RSA
   - ECDSA (can be used with a variety of curves)
   - EdDSA - Ed25519, Ed448
   - ![image](https://github.com/lakshya-chopra/KyberCpp/assets/77010972/55f97ba2-8da3-45b9-9af5-b78c2cfe8be1)
   - (EdDSA is distinct from ECDSA, despite the fact that they both may use Curve25519).

## Public Key Infra (PKI):
  - This is a combination of DSA and PKC, done to ensure that the asymmetric keys & cipher texts are from the authenticated user/server only, this is used to avoid MITM attacks. Here, an external trusted agency, known as the "Root CA" is utilized to prove the authenticity of the server/user, this is done using digital certificates signed using some DS algorithm. This practice is utilized in TLS/SSL. TLS is used to securely distribute symmetric keys between the client and the server, as well provide the proof that both the client & the server are authentic.
  - There are various cipher suites that TLS makes use of, for key exchanges: RSA (now discarded in v1.3), ECHDE, PSK (pre-shared key, useful for local networks), DHE may be used. 
  - For DSA, usually RSA is used, but EdDSA or ECDSA may be also be used.
  - For symmetric key, AES_128/256 may be used in any of the supported modes. ChaCha20 is also supported.
  - For hashing (or MAC), SHA256/SHA384 are commonly used.
  - ![image](https://github.com/lakshya-chopra/KyberCpp/assets/77010972/0b23f7f4-87b0-4639-b158-1f4d4befa5c5)
  - The reason why RSA was discarded as KEX, is because of it's slowness in generation of keys, and lack of forward secrecy as compared to ECDHE, note ECDHE is distinct from ECDH (ECHDE = Ephemeral ECDH), DHE is another PFS KEX (Ephemeral DH).
  - HTTPS = HTTP + TLS/SSL.
  - [imp, diff b/w static dh, ecdhe](https://security.stackexchange.com/a/33240)
  - [how ssl/tls works?](https://security.stackexchange.com/a/20847)
  - [SSL/TLS PKI](https://security.stackexchange.com/questions/87564/how-does-ssl-tls-pki-work/89072#89072)
      


[Book](https://cryptobook.nakov.com/)
[Overview of Cryptography](https://medium.com/@sinister/overview-of-cryptography-c7349b92a72b)

    
