#! /bin/bash
. ./task_7.sh
. ./exeption.sh

boldface='\033[1m'
red='\033[31m'
norm='\033[0m'

function check_args {
	if [[ $# < 3 ]]
	then
		echo -1

	elif ! [[ $2 =~ ^-?[[:digit:]]+$ && $3 =~ ^-?[[:digit:]]+$ ]]
	then
		echo -2

	elif [[ $1 == 'div' && $3 -eq 0 ]]
	then
		echo -3
	else
		echo 0
	fi
}

function sum {
	echo $[$1 + $2]
}
function sub {
	echo $[$1 - $2]
}
function mul {
	echo $[$1 * $2]
}
function div {
	echo $[$1 / $2]
}

function select_case {
	case $1 in
		'sum')
			sum $2 $3
			;;
		'sub')
			sub $2 $3
			;;
		'mul')
		        mul $2 $3
			;;
		'div') 
			div $2 $3
			;;
		*)
			echo "bad"
		
	esac
}

function calc {
	check=$(check_args $1 $2 $3)
	if [[ $check -ne 0 ]] 
	then
		ans=$(print_error $check)
		echo $ans
		return
	fi

	ans=$(select_case $1 $2 $3)
	
	if [[ $ans == "bad" ]]
	then
		ans=$(print_error -6)
		echo $ans
		return
	fi
	echo $ans
} 

