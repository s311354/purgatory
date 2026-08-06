#!/bin/sh
# This script installs binary packages needed to build purgatory

set -e
. /etc/os-release

set -x

case "$ID" in
	ubuntu | pop | linuxmint | debian | raspbian | neon | zorin)
		apt-get update
		apt-get install -y cmake gcc g++ clang gdb linux-tools-common linux-tools-generic linux-tools-$(uname -r) || {
			# Fallback if kernel-specific tools aren't available
			apt-get install -y cmake gcc g++ clang gdb linux-tools-common linux-tools-generic || true
		}
		;;
	fedora | amzn | rhel | centos)
		dnf install -y gcc-g++ cmake glibc-static libstdc++-static diffutils util-linux tar perf
		;;
	arch | archarm | artix | endeavouros | manjaro | cachyos)
		pacman -Sy --needed --noconfirm base-devel cmake util-linux perf
		;;
	alpine)
		apk update
		apk add bash make linux-headers cmake gcc g++ perf
		;;
	clear-linux-os)
		swupd update
		swupd bundle-add c-basic diffutils performance-tools
		;;
	freebsd)
		pkg update
		pkg install -y cmake bash binutils gcc
		# Note: perf is Linux-specific, not available on FreeBSD
		;;
	*)
		echo "Error: don't know anything about build dependencies on $ID-$VERSION_ID"
		exit 1
esac

