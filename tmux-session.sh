#!/usr/bin/env bash
# tmux-session.sh - Development environment
set -e

REPO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SESSION="purgatory"
MODE="${1:-dev}"

# Helper functions
txt() { tmux send-keys -t "$1" "$2" C-m; }
cmd() { tmux send-keys -t "$1" "$2" C-m; }

# Check if session already exists
if tmux has-session -t "$SESSION" 2>/dev/null; then
    echo "✓ Session '$SESSION' already exists. Attaching..."
    tmux attach -t "$SESSION"
    exit 0
fi

# Mode-specific setup
case "$MODE" in
    dev)
        # 3-window: editor, build/test, git
        tmux new-session -d -s "$SESSION" -n editor -c "$REPO_DIR"
	sleep 0.5
        txt "$SESSION:0" "# Edit code here - AI Assistant"
        txt "$SESSION:0" "# === Kiro CLI - AI Assistant ==="
        txt "$SESSION:0" "# Start: kiro-cli chat"
        txt "$SESSION:0" "# "
        txt "$SESSION:0" "# Try: \"implement quicksort in src/array.cc\""
        txt "$SESSION:0" "#      \"add tests for function X\""
        txt "$SESSION:0" "#      \"fix the error in window 1\""

        tmux new-window -t "$SESSION:1" -n build -c "$REPO_DIR"
	sleep 0.5
        txt "$SESSION:1" "# Build commands:"
        txt "$SESSION:1" "#   cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=c++ -DBUILD_TESTING=ON -B build"
        txt "$SESSION:1" "#   cmake --build build -j\$(nproc)"
        txt "$SESSION:1" "# "    
        txt "$SESSION:1" "# Test commands:"
	txt "$SESSION:1" "#   ctest --test-dir build --output-on-failure -j\$(nproc)"

        tmux new-window -t "$SESSION:2" -n git -c "$REPO_DIR"
	sleep 0.5
        cmd "$SESSION:2" "git status"
        ;;

    quick)
        # 2-pane: editor, terminal
        tmux new-session -d -s "$SESSION" -n workspace -c "$REPO_DIR"
        txt "$SESSION:0" "# Edit code here"

        tmux split-window -h -t "$SESSION:0" -c "$REPO_DIR" -p 40
        txt "$SESSION:0.1" "# Terminal ready"
        ;;

    *)
        echo "Unknown mode: $MODE"
        echo "Usage: $0 [dev|quick]"
        exit 1
        ;;
esac

# Set status bar
tmux set-option -t "$SESSION" status-right "#[fg=green]${MODE} #[fg=cyan]%H:%M"
tmux set-option -t "$SESSION" status-left "#[fg=blue][#S] "

# Select first window and attach
tmux select-window -t "$SESSION:0"
echo "✓ Session '$SESSION' created (mode: $MODE)"
tmux attach -t "$SESSION"
