{
    inputs = {
        nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    };

    outputs = inputs@{ self, nixpkgs, flake-parts }: flake-parts.lib.mkFlake { inherit inputs; } {
        systems = [
            "x86_64-linux"
        ];

        perSystem = { config, self', inputs',  pkgs, pkgsCross, system, ... }: {
            devShells.default = pkgs.mkShell {
                nativeBuildInputs = [
                    pkgs.pkgsCross.avr.buildPackages.gcc
                ];
            };
        };
    };
}
