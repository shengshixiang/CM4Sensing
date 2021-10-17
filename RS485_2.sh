#/bin/bash 
#
# Created by andy sheng in Nov 2020
#
#RS485 test
#先打开接收，然后再进行发送，看是否收到数据和发送一致。
receive_date_dir="/home/pi/work/RS4852/RS485_txt_receive"
send_date_dir="/home/pi/work/RS4852/RS485_txt_send"
receive_command_dir="/home/pi/work/RS4852/RS485_receive"
send_command_dir="/home/pi/work/RS4852/RS485_send"

function test_rs485()
{
	
	
	ls  /home/pi/work/RS4852/RS485_receive >/dev/null 2>&1  
	if [ $?  -ne 0 ]; then  
     sudo bash /home/pi/work/RS4852/build.sh     
	fi
	
	
	
    rm $send_date_dir  >/dev/null 2>&1
	rm $receive_date_dir >/dev/null 2>&1
	
	$receive_command_dir &
	sleep 0.1
	$send_command_dir 
	sleep 0.5	
	diff $receive_date_dir $send_date_dir   >/dev/null 2>&1
	if [ $?  -eq 0 ]; then  
		cd ..	
		return 0     
	else  
		cd ..
		return 1
	fi
	
}
test_rs485
if [ $?  -eq 0 ]; then 	
#	echo "pass"
	exit 0	
else 	
	#echo "fail"
	exit 1
fi









