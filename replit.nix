{ pkgs }: {
	deps = [
    pkgs.gcc
    pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}