#pragma once

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

namespace TOTP {
    template <typename type>
    std::string toString(type a) {
        std::stringstream ss;
        ss << a;

        return ss.str();
    }

    class Base32 {
    public:
        Base32() = default;
        ~Base32() = default;

        std::string encode(const std::string& input) {
            std::string encoded;

            size_t length = input.length();
            unsigned buffer = 0, buffersize = 0;

            for (size_t i = 0; i < length; ++i) {
                char ch = input.at(i);

                buffer <<= 8;
                buffer |= ch;
                buffersize += 8;

                while (buffersize > 4) {
                    buffersize -= 5;

                    unsigned ord = buffer & (0x1F << buffersize);
                    ord >>= buffersize;

                    encoded.append(toString<char>(charset.at(ord)));
                }
            }

            if (buffersize > 0) {
                buffer <<= 5 - buffersize;
                unsigned ord = buffer & 0x1F;

                encoded.append(toString<char>(charset.at(ord)));
            }

            if (encoded.length() % 8 != 0)
                encoded.append(padding.substr(encoded.length() % 8));

            return encoded;
        }

        std::string Decode(const std::string& input) {
            std::string decoded;

            size_t length = input.length();
            unsigned buffer = 0, buffersize = 0;

            for (size_t i = 0; i < length; ++i) {
                char ch = input.at(i);

                if (charset.find(ch) == -1) {
                    if (ch == ' ' || ch == '\r' || ch == '\n' || ch == '\t')
                        continue;
                }

                unsigned ord = charset.find(ch);
                buffer <<= 5;
                buffer |= ord;
                buffersize += 5;

                if (buffersize > 7) {
                    buffersize -= 8;
                    ord = (buffer & (0xFF << buffersize)) >> buffersize;

                    if (ord <= 0x7F)
                        decoded.append((char *) &ord);
                }
            }

            return decoded;
        }

    private:
        const std::string padding = std::string("========");
        const std::string charset = std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZ234567");
    };
}