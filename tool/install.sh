#!/usr/bin/env bash
if [ $UID = 0 ];then
	if [ x$1 = x ];then
		a=install
	else
		a=$1
	fi
	case $a in
	install)
		mkdir build
		cd build
		cmake -DCMAKE_BUILD_TYPE=Release ..
		make
		make install 
		cp install_manifest.txt ..
		cd ..
		rm -rf build
		;;
	uninstall)
		cat install_manifest.txt | sudo xargs rm -f
		rm -f install_manifest.txt
		;;
	*)
		echo 未知选项
	esac
else
	echo 没有root权限
fi

