#! /bin/bash
<<Doc
Name: Sd .abdul khadar
Date: 30/4/2023
Description:command line test 
Sample Input:
Sample Output:
Doc

RED='\033[0;31m'	# Red color
GREEN='\033[0;32m'	# Green color
PURPLE='\033[0;35m'	# Purple color
NC='\033[0m'		# No color


function signup 
{
	user_array=( $(cat $1))
while [ true ]
do

	read -p "enter user name to sign up: " user_name
    flag=0
	for i in ${user_array[@]} 
	do
		if [ $user_name = $i ]
		then
			echo "user name already exist please enter new username"
			
			flag=1
			break
		fi	
	done
    if [ $flag -eq 0 ]
	then
         echo "$user_name" >> "$1"
    read -s -p "ENTER THE PASSWORD: " password
    echo "$password">>password.csv
	echo "-------signup successful-------------------"
	break
	fi
done
}

function evaluate_test
{
	echo "----------------evaluating the test -----------------"
	echo -e " "
	count=0
	myans_array=( $(cat my_answers.csv) )
	echo "${myans_array[@]}"
	correct_array=( $(cat correct_ans.csv))
	i=0
	for(( k=5; k<= 20; k=k+5 ))
	do
		
		echo "$(head -n $k questions.csv |tail -n 5 )"
	#	if [ "${myans_array[i]}" = "${correct_array[i]}" ]  due trailing space it may show not equal so dng this
		if [ "$(echo -e "${myans_array[i]}" | tr -d '[:space:]')" = "$(echo -e "${correct_array[i]}" | tr -d '[:space:]')" ]
     	then
			echo -e "RESULT:${GREEN}you entered correct answer :: ${myans_array[i]}  ${NC}"
	    	count=$(expr $count + 1 )
	    elif [ "${myans_array[i]}" = "e" ]
		then
			echo -e "RESULT:${PURPLE}Timeout!${NC}" 
		else
			echo -e "RESULT:${RED}you entered wrong answer: ${myans_array[i]} ${NC} "
		    echo -e "${GREEN} correct answer is : ${correct_array[i]} ${NC}"

    	fi
		i=$((i+1)) 
    done
	echo "----------final result  : no of correct answers  :  $count / 4 ----------"
	sed -i '1,5d' my_answers.csv 
}
function conduct_test
{
	read -p  "enter your choice  1.take test 2.exit: " ch
	echo  "--------------------concuting the test --------------"
    c=5
	flag=0
	count=0
	case $ch in
		1)
			while [ $c -le 20 ]
			do
				flag=0
				echo "$(head -n $c questions.csv |tail -n 5 )"
             for i in `seq 15 -1 1`
             do
            	echo -n -e "\r enter the option before the time limit $i "
				
	         	read -t 1 ans
		    	
             	if [ -n "$ans" ]
				then
                   flag=1
					break
				fi
            done
			if [ $flag -eq 0 ]
			then
		       ans="e"	
         	fi
            echo "$ans" >> "my_answers.csv" 
			c=$(( c + 5 ))
		
    	   done
		   evaluate_test
         
			;;
		2)exit 0
			;;
	esac

}

function signin 
{
	user_array=( $(cat $1))
	password_array=( $(cat password.csv))
#	echo "${password_array[@]}"

while [ true ]
do
	echo " "

	read -p "enter user name to sign in: " user_name
    flag=0
	password_flag=0
	for i in `seq 0 $((${#user_array[@]}-1))`
	do
		if [ $user_name = ${user_array[i]} ]
		then
            echo "ENTER THE PASSWORD: " 
			read -s password
			if [ $password -eq ${password_array[i]} ]
			then
	        echo -n "signup successful"
			echo " conducting test"
			#test functioon
			conduct_test

			flag=1
			break
		    else
				password_flag=1
		
				break
			fi
		fi	
	done
	#CHECKING WHETHER USER NAEM FOUND OR NOT 
   if [ $flag -eq 1 ]
	then
	break
   elif [ $password_flag -eq 1 ]
   then
		echo "ENTERED THE WRONG PASSWORD TRY AGAIN"
   else
		echo "USER NAME NOT FOUND TRY AGAIN"
	fi
done
}




#while [ true ];do
echo "Enter the choice  "
echo "1. SIGNUP"
echo "2. SIGNIN"
echo "3. EXIT"

read -p "enter your choice" ch
user_file="user.csv"
case $ch in
	1)
		signup $user_file
		;;
	2)
		signin $user_file

		;;
	3)echo "choosen exit"
     	exit 0	
		;;
	*)
		echo "enter a valid option"
		;;
esac
#done

