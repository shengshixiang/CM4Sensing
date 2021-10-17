
#/bin/bash 
#
# Created by andy sheng in Nov 2020
#


dev="/dev/sda3"



	
function uhost2.0()
{
    sudo umount /mnt >/dev/null 2>&1;	
	f_found=1
	for name in $dev
	do
		if sudo mount  $name /mnt >/dev/null 2>&1; then
			f_found=0
			break	
		fi
	done
	
	[ "$f_found" -eq "0" ] || return 1
	touch udisk.txt

	sudo echo "cm4industrial_uhost2.0_test" > udisk.txt
	sudo cp udisk.txt /mnt/
	[ "$?" -eq "0" ] || return 	1
	date1=$(cat /mnt/udisk.txt)
	sudo rm /mnt/udisk.txt
	sudo umount /mnt >/dev/null 2>&1;
	
	if [ "$date1" == "cm4industrial_uhost2.0_test" ];then	
		return 0
	else	
		return 1
	fi	
}
uhost2.0
if [ $? -eq 0 ]; then

	exit 0
else

	exit 1
fi



