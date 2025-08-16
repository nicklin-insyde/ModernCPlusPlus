#!/bin/bash
echo "Cross compile ?? 1) yes 2) no"
select answer in "yes" "no"; do
	case ${answer} in
		yes )
			NEED_CROSS_COMPILE=cross_compile
			# cross compie toolchain path
			PATH=/home/nicklin/bitbucket/toolchain/tools-master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin:${PATH}
			break;;
		no )
			NEED_CROSS_COMPILE=no_cross_compile
			break;;
		* )
			echo "oops!"
			exit 1;
			;;
	esac
done
#NEED_CROSS_COMPILE=no_cross_compile
make clean;make OPTION=${NEED_CROSS_COMPILE}
#./app
