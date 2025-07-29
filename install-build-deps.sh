#!/bin/sh
# This script installs binary packages needed to build purgatory

set -e
. /etc/os-release

set -x

case "$ID" in
	ubuntu | pop | linuxmint | debian | raspbian | neon | zorin)
		apt-get update
		apt-get install -y cmake gcc g++ clang gdb
		;;
	fedora | amzn | rhel | centos)
		dnf install -y gcc-g++ cmake glibc-static libstdc++-static diffutils util-linux tar
		;;
	arch | archarm | artix | endeavouros | manjaro | cachyos)
		pacman -Sy --needed --noconfirm base-devel cmake util-linux
		;;
	alpine)
		apk update
		apk add bash make linux-headers cmake gcc g++
		;;
	clear-linux-os)
		swupd update
		swupd bundle-add c-basic diffutils
		;;
	freebsd)
		pkg update
		pkg install -y cmake bash binutils gcc
		;;
	*)
		echo "Error: don't know anything about build dependencies on $ID-$VERSION_ID"
		exit 1
esac

