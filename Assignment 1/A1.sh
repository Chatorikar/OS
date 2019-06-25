header(){
	
	echo -e "\t\t\t Name     Date of Journy   Source AirPort	 Destination AirPort   \n\n"
	
}

Create(){

	echo -n -e "Enter Filename  :  "
	read filename 
	touch $filename.txt	  
	echo -n -e "\n\n Files $filename.txt is Sucessfully Created  \n\n\n"
		 	  
}

View_All_Record(){

	echo -e "\t\t All Record are as follows :   \n\n\n"
	header
	cat Record.txt
		 	  
}


Insert_Record(){
	
	echo -n -e " Enter passanger Name : "
	read name
	echo " Hello ,  $name ! "
	echo "" 
	cal 
	echo -n -e  "\n\n Please Enter Date of Journey  : "
	read date_journy  
	echo -n -e  "\n Please Enter Source : "
	read source_AP
	echo -n -e  " Please Enter Destination  : " 
	read Desti_AP
	
	#printf '|%4.4s|\n' Record Successfully Added 
	echo -n -e "\n\n\t\t\t\t\t\t\t Record Successfully Added \n\n"	     
	echo -n -e "\n\n\t\t\t $name        \t$date_journy June       \t$source_AP	      \t$Desti_AP   " >> Record.txt
	header
	echo -e "\t\t\t $name        \t$date_journy June       \t$source_AP	      \t$Desti_AP   "

}

Delete_Record(){

	echo " Enter Passanger Name : "
	read name_delt
	sed -i "/$name_delt/d" Record.txt
}



while true
	do
		echo -n -e "
			    1) Create File.
			    2) View all Passangers record.
			    3) Insert a record.
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
		 	 
		esac
done
