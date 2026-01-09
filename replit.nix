{ pkgs }: {
  deps = [
    pkgs.gcc
    pkgs.gnumake
    pkgs.SDL2
    pkgs.SDL2_image
    pkgs.SDL2_ttf
    pkgs.SDL2_mixer
  ];
}