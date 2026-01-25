{
    inputs = {
        nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.05";
    };

    outputs = inputs@{ self, nixpkgs, flake-parts }: flake-parts.lib.mkFlake { inherit inputs; } {
        systems = [
            "x86_64-linux"
        ];

        perSystem = { config, self', inputs',  pkgs, pkgsCross, system, ... }: rec {
            devShells.default = pkgs.mkShell {
                nativeBuildInputs = [
                    pkgs.pkgsCross.avr.buildPackages.gcc
                    pkgs.avrdude
                ];
            };
        };
    };
}
