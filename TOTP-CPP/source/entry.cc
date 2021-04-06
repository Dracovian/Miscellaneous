#include <sys/stat.h>
#include <fstream>
#include <cstdlib>
#include <cstdio>

#include "token.h"
#include "pcg.h"

void keygen(const std::string& filename, TOTP::algo_method method) {
    if (method < 0 || method > 2) throw std::runtime_error("Invalid algorithm.");

    std::string data_upper, data_lower;
    std::ofstream stream;

    if (method == 0) { data_upper =   gen_sha1_key(); data_lower =   gen_sha1_key(); }
    if (method == 1) { data_upper = gen_sha256_key(); data_lower = gen_sha256_key(); }
    if (method == 2) { data_upper = gen_sha512_key(); data_lower = gen_sha512_key(); }

    stream.open(filename);
    stream << data_upper;
    stream << data_lower;
    stream.close();
}

std::string getkey(const std::string& filename) {
    std::ifstream stream;
    std::string data;

    stream.open(filename);
    stream >> data;
    stream.close();

    return data;
}

void help() {
    std::fprintf(stdout, "Usage: program keyfile {token length} {token expiration}\n");
}

int main(int argc, char **argv) {
    if (argc < 2 || argc > 4) { help(); return 0; }
    struct stat buffer;

    if(stat(argv[1], &buffer) != 0)
        keygen(std::string(argv[1]), TOTP::SHA1);

    auto key = getkey(std::string(argv[1]));
    for (auto &c : key)
        c = toupper(c);

    TOTP::Token *token;
    if (argc == 2) token = new TOTP::Token(key);
    if (argc == 3) token = new TOTP::Token(key, std::strtol(argv[2], 0, 10));
    if (argc == 4) token = new TOTP::Token(key, std::strtol(argv[2], 0, 10), std::strtol(argv[3], 0, 10));
    
    try {
        TOTP::algo_method method = TOTP::SHA1;
        std::string timestamp = token->timestamp();
        std::string hash = token->hmac(key, timestamp, method);
        std::string otp = token->truncate(hash, method);

        std::fprintf(stdout, "Token: %s\nLeft: %ld seconds\nCode: %s\n", token->getToken(), token->timeleft(timestamp), otp.c_str());

        std::string tok;
        std::fprintf(stdout, "Enter the token: ");
        std::cin >> tok;

        bool verified = token->verify(key, tok, method);
        std::fprintf(stdout, "Verified: %s\n", verified ? "True" : "False");
    } catch(std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}