{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    { nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            qmk
            # Python と uv を追加（Serena MCP のため）
            python311
            uv
          ];
          shellHook = ''
            echo "Entering custom Nix shell..."

            # Serena MCP のインストール/更新
            echo "Setting up Serena MCP server..."
            export SERENA_DIR="$HOME/.local/share/serena"
            mkdir -p "$SERENA_DIR"

            # PATH に serena を追加
            export PATH="$HOME/.local/bin:$PATH"

            # Serena がインストールされていない、または古い場合は更新
            if ! command -v serena-mcp-server &> /dev/null; then
              echo "Installing Serena MCP server..."
              uv tool install --python python3.11 git+https://github.com/oraios/serena
            else
              echo "Serena MCP server is already installed"
              # 必要に応じて更新
              # uv tool upgrade serena
            fi
          '';
        };
      }
    );
}
