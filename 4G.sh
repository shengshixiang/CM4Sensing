#/bin/bash 
#
# Created by andy sheng in Nov 2020
#

ping www.baidu.com -I wwan0 -c 2  >/dev/null 2>&1
if [ $? -eq 0 ]; then
 #   echo -e  "\033[32m 4G PASS \033[0m"
	exit 0
else
#	echo -e  "\033[31m 4G FAIL\033[0m"
	exit 1
fi
