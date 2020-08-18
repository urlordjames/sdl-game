{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    buildInputs = with pkgs; [
      SDL2
      SDL2.dev
      gcc
      cmake
      gnumake
    ];
  }
