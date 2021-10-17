#/bin/bash 
#
# Created by andy sheng in Nov 2021
#
#

ls "/dev/mmcblk2" >/dev/null 2>&1  

if [ $? -eq 0 ]; then
	exit 0
			#echo -e "\033[32m eth0 PASS \033[0m"
	else
	exit 1
			#echo -e "\033[31m eth0 FAIL \033[0m"
fi
