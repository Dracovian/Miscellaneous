#pragma once

#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <exception>
#include "base32.h"
#include <ctime>

#ifndef SHA1_DIGEST_LENGTH
#define SHA1_DIGEST_LENGTH 20
#endif

namespace TOTP {
    enum algo_method { SHA1, SHA256, SHA512 };
    
    template <typename type>
    type pow(type a, type b) {
        type output = 1;

        for (type d = 0; d < b; ++d)
            output *= a;

        return output;
    }

    class Token : public Base32 {
    public:
        Token(const std::string& key) : tokenLength(6), tokenExpiration(30) {
            tokenPrivateKey = encode(key);
        }

        Token(const std::string& key, long length) : tokenLength(length), tokenExpiration(30) {
            tokenPrivateKey = encode(key);
        }

        Token(const std::string& key, long length, long expires) : tokenLength(length), tokenExpiration(expires) {
            tokenPrivateKey = encode(key);
        }

        ~Token() {
            tokenLength = tokenExpiration = 0;
            tokenPrivateKey = std::string();
        };

        std::string timestamp() {
            return toString<long>(std::time(0) / tokenExpiration);
        }

        long timeleft(const std::string& timestamp) {
            long ts = std::strtol(timestamp.c_str(), 0, 10);
            ts *= tokenExpiration;

            return tokenExpiration - (std::time(0) - ts);
        }

        const char *getToken() {
            return tokenPrivateKey.c_str();
        }

        std::string _hmac(const std::string& key, const std::string& msg, const EVP_MD *algo, unsigned char hash[], unsigned int len) {
            HMAC_CTX *hmac = HMAC_CTX_new();
            HMAC_Init_ex(hmac, &key[0], key.length(), algo, 0);
            HMAC_Update(hmac, (unsigned char *) &msg[0], msg.length());
            HMAC_Final(hmac, hash, &len);
            HMAC_CTX_free(hmac);

            std::string strhash = toString<unsigned char *>(hash);
            if (strhash.length() < len)
                strhash.insert(strhash.end(), len - strhash.length(), '0');

            return strhash;
        }

        std::string hmac(const std::string& key, const std::string& msg, enum algo_method method) {
            if (method == 0) { unsigned char hash[  SHA1_DIGEST_LENGTH]; return _hmac(key, msg, EVP_sha1(),   hash,   SHA1_DIGEST_LENGTH); }
            if (method == 1) { unsigned char hash[SHA256_DIGEST_LENGTH]; return _hmac(key, msg, EVP_sha256(), hash, SHA256_DIGEST_LENGTH); }
            if (method == 2) { unsigned char hash[SHA512_DIGEST_LENGTH]; return _hmac(key, msg, EVP_sha512(), hash, SHA512_DIGEST_LENGTH); }

            throw std::runtime_error("Invalid algorithm.");
        }

        std::string truncate(const std::string& hash, enum algo_method method) {
            if (method < 0 || method > 2) throw std::runtime_error("Invalid algorithm.");
            if (method == 0 && hash.length() <   SHA1_DIGEST_LENGTH) throw std::runtime_error("Invalid SHA1_HMAC hash.  ");
            if (method == 1 && hash.length() < SHA256_DIGEST_LENGTH) throw std::runtime_error("Invalid SHA256_HMAC hash.");
            if (method == 2 && hash.length() < SHA512_DIGEST_LENGTH) throw std::runtime_error("Invalid SHA512_HMAC hash.");
            int offset;

            if (method == 0) { offset = hash[19] & 0xF; }
            if (method == 1) { offset = hash[31] & 0xF; }
            if (method == 2) { offset = hash[63] & 0xF; }

            int binary = (
                ((hash.at(offset    ) & 0x7F) << 24) |
                ((hash.at(offset + 1) & 0xFF) << 16) |
                ((hash.at(offset + 2) & 0xFF) <<  8) |
                 (hash.at(offset + 3) & 0xFF)
            );

            std::stringstream result;
            result << binary % pow<long>(10, tokenLength);
            
            std::string res = result.str();
            res.insert(res.end(), tokenLength - res.length(), '0');
            
            return res;
        }

        bool verify(const std::string& key, const std::string& token, enum algo_method method) {
            std::string tsp = timestamp();
            std::string hmc = hmac(key, tsp, method);
            std::string otp = truncate(hmc, method);

            return otp.compare(token) == 0;
        }

    private:
        long tokenLength, tokenExpiration;
        std::string tokenPrivateKey;
    };
};
