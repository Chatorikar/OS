#The 'grep' command stands for "global regular expression print"

Create_Address_Book()
{
	if [ -f $1 ] 
		then
			echo "File is Already Exit "
	else
		touch $1.txt
		echo "File $filename is Successfully Created "
	fi
}


Show_Content_of_File()
{
	if [ -f $1 ]
		then 
			echo "File Content : "
			cat $1
	else 
		echo "File Doesn't Content : "
	fi
}

Insert_Record()
{	
	re='^[0-9]+$'
	while [ -z $name ]; do #Avoid NuLL
		echo -ne "Enter Name : "
		read name
	done


	while [ -z $phone ]; do
		echo -ne "\nEnter Phone : "
		read phone

		if [ ${#phone} -ne 3 ] || ! [[ $phone =~ $re ]]; then
			echo -ne "\nPhone Not Valid"
			unset phone
		fi

		if [ -n $phone ]; then
			
			(grep -r -w $phone "2.txt") && unset phone

			if [ -z $phone ]; then
				echo "Error: Already Present : "
				unset phone
			fi
		fi
	done





	printf "\n%10s %10s %9s %8s %14s %10s %6s" $name $phone >> 2.txt

	unset name
	unset phone


}	

Search()
{
	(grep -r -w $1 "2.txt" && echo "Found" ) || echo "Not Found"
}

Delete()
{
	if grep -r -w $1 "2.txt"; then
		sed -i "/$1/d" "2.txt"
		echo "Successfully Deleted"
	else
		echo Invalid Key Value
	fi
}



choice=0
while (( choice != 6 ))
do
	echo 
	echo -ne "Enter Your Choice "
	read choice

	case $choice in

		1)  echo
			echo -ne "Enter File Name to be Create : "
			read filename
			Create_Address_Book $filename.txt;;
			
		2) 	echo 
			Show_Content_of_File 2.txt;;
			# Show_Content_of_File $filename.txt;;

		3)  echo 
			echo -ne "How Many Record do you want to Insert : "
			read count
			while (( $count > 0 ))
			do 
				Insert_Record
				(( count-- ))
			done;;
			
		4) echo 
		   echo "Enter Search Record : "
		   read key
		   Search $key
		   ;;

		5) echo 
		   echo "Enter Delete Record : "
		   read key
		   Delete $key
		   ;;
		


		*) 	echo 
			echo -ne "Please Correct Choice ";;

	esac 

done
