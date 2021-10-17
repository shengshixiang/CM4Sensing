#/bin/bash 
#
# Created by andy sheng in Nov 2020
#

date_str="2020-11-30 16:10:10"
#写入的时间和读出的时间做比较
function rtc()
{
  
	#sudo date -s "2020-11-30 16:00:00"  >/dev/null 2>&1 
	sudo hwclock -w  >/dev/null 2>&1 
	[ "$?" -eq "0" ] || return 1
	sudo hwclock -s >/dev/null 2>&1
	[ "$?" -eq "0" ] || return 	1
		
	return 0

}
rtc   
if [ $? -eq 0 ]; then                 
	exit 0
else
	exit 1
fi




