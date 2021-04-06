with import <nixpkgs> {}; {
    tributeEnv = gcc8Stdenv.mkDerivation {
        name = "tribute-env";
        buildInputs = [ stdenv
                        gcc
                        gdb
                        SDL2
                        pkgconfig
                        cmake
                      ];
    };
}