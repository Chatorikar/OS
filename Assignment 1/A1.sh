header(){

	echo -n -e "\n\n\t\t      Name        \tAddress        \tPincode	      \tCity      \tState   "
	echo ""
}

Create(){

	echo -n -e "Enter Filename  :  "
	read filename
	touch $filename.txt
	echo -n -e "\n\n Files $filename.txt is Sucessfully Created  \n\n\n"

}

View_All_Record(){

	choice=5

	# while [ $choice -ge  5 ]
	# 	do
	# 		echo  -e " \n\n\t\t-------- Views Record According to : --------"
	# 		echo  -e "\n\t\t\t\t 1) Name  "
	# 		echo  -e " \t\t\t\t 2) Pincode : "
	# 		echo  -e " \t\t\t\t 3)City  "
	# 		echo  -e " \t\t\t\t 4)State  "
	# 		echo -n -e "\n\t\t----------- Select your Choice-----------  :  "
	#
	# 		read choice
	#
	# 	done

	echo -e "\t\t All Record are as follows :   \n\n\n"
	header
	cat Record.txt
	echo -n -e "\n\n\n"

}


Insert_Record(){


	echo -n -e " Hello , Please nter your Name : "
	read name

	echo -n -e  "\n\n Hey ! $name ,  Enter Your Address  : "
	read address

	while [ $OK -lt 2  ]
		do
			echo -n -e  "\n Please Enter PinCode : "
			read pincode
			if ! [[ "$pincode" =~ ^[0-9]+$ ]]
		    then
		        echo "Sorry integers only"
			else
					OK = 1
			fi
	done

	echo -n -e  "\n Please Enter City    : "
	read city

	echo -n -e  "\n Please Enter State    : "
	read state

	#printf '|%4.4s|' Record Successfully Added
	#echo -n -e "\n\n\t\t\t\t\t\t\t Record Successfully Added \n\n"
	#printf "\ns%-20s\t|%20s$name|%-6s$date_journy|%-15s$source_AP|%-15s$Desti_AP|" >>  Record.txt
	#echo -n -e "\n\n\t\t\t $name        \t$date_journy June       \t$source_AP	      \t$Desti_AP   " >> Record.txt
	#echo -n -e "\n\n\t\t\t $name        \t$date_journy June       \t$source_AP	      \t$Desti_AP   " >> Record.txt
	header
	#cat 'Record.txt' | column -t -s '| '
	echo -n -e " \n\t\t\t$name\t\t$address\t\t$pincode\t\t$city\t\t$state   " >> Record.txt
	View_All_Record
	#printf  "\n%-20s|%-30s|%-5s$date_journy June|%-10s$source_AP|%-10s$Desti_AP|">>  Record.txt
	#printf   "\n |%-20s $name %-20s|$date_journy June  %20s|$source_AP %20s|$Desti_AP %20s| ">> Record.txt
#	sed $'s/#/\001#/' input-record.txt | column -ets $'\001'

}

Delete_Record(){
			echo "Enter The Roll Number You Want To Search Record For -"
			read name_delt
			echo
			echo
			header
			grep -w -h "$name_delt" Record.txt
			if [ $? -eq 0 ]
			then
				echo
				echo " Record Found."
				# echo " Enter Passanger Name : "
				# read name_delt
				sed -i "/$name_delt/d" Record.txt
			else
				echo
				echo "Record Not Found."
			fi


}


modify(){

	echo " Enter Passanger Name : "
	read name_delt
	header
	if grep -i "$name_delt" Record.txt;
		then
			sed -i "/$name_delt/d" Record.txt
	fi

	Insert_Record





}




while true
	do
		echo -n -e "
			    1) Create Address Book.
			    2) View all Passangers Record.
			    3) Insert New Record.
			    4) Delete a record.
			    5) Modify a record.
			    6) Exit.
			    Enter Your Choice "
		read choice
		case $choice in

		 1)	Create;;

	 	 2) View_All_Record;;

		 3) Insert_Record;;

		 4) Delete_Record;;

		 5) modify;;

		esac
done
