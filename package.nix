{ lib, stdenv, pkgsCross, cmake }:

stdenv.mkDerivation {
    name = "blinkenrocket-firmware";

    src = lib.sourceByRegex ./. [
        "^src.*"
        "CMakeLists.txt"
    ];

    nativeBuildInputs = [
        cmake
        pkgsCross.avr.buildPackages.gpp
    ];
}
