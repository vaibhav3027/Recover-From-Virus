#include <stdio.h>
#include <windows.h>//imported to use the methods like RegOpenKey() and... and variables(type deff(ed) data types) like HKEY,LONG,..
#include <stdlib.h>//imported just to set the title of the program using system(_char_squence__) function
#include <conio.h>
HKEY hkey; //Stores the open key handler(key that was opened by RegOpenKey())
LONG open; //Stores the Result/Value passed by the function.Type "net helpmsg returned_value" in cmd followed by enter to see the problem
void enable_taskMgr(HKEY hkey);
void enable_regTools(HKEY hkey);
void enable_gpedit();
void enable_cmd();
main() {
	system("title Recover from virus attack");//system() method/function is used to call windows commands and title(inside the quotes) is a windows' command.
	printf("What do you want to Enable?\n1. Task Manager\n2. Registry Tools\n3. Group Policy Editor\n4. Command prompt\n5. ALL OF THE ABOVE\n");
	int choice;
	scanf("%d",&choice);
	blog_it://marker
	open=RegOpenKey(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",&hkey);/*Tries to open the quoted key,if it's there it returns
	0(or ERROR_SUCCESS) which is then gets stored in open. hkey is used to store handler to opened key*/
	if(open!=ERROR_SUCCESS)//Runs when open is not equal to zero i.e. there is an error opening the key,which usually happens when that key is missing or admin privilege is not granted to the program
	{
		open=RegOpenKey(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies",&hkey);//tries to open the root of previous key to check whether it's there or not.
		if(open!=ERROR_SUCCESS)//gets executed when even this key is not present
		{
			RegCreateKey(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies",&hkey);//In that case it creates the key and stores the handler of opened key in hkey
		}
		open=RegCreateKey(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",&hkey);//creates the key and stores the handler in hkey
		if(open==5)/*when open equals to 5 it signifies that key cannot be created due to administrator privilege issue.i checked this here because it decrease the execution time if used here.
		if i had used this on above "if" block, it would'nt run when Policies key is present and if had used it on both block i'll decreasing the execution time and increasing the size of compiled exe
		Oh how can i forget,job of granting admin privilege can only be done when you restart the program,so no matter where you are, you have to just close the program and restart it
		and admin privelage is required only to create/modify the keys(and it's values),Simply opening it doesn't needs admin privilege
		TIP:You can use "net helpmsg {no.}" to see the system error messages. for instance you can use "net helpmsg 5" in command prompt*/
		{
			printf("\aPROCESS HALTED!!\nRe-run the program as an ADMINISTRATOR.");//prints the  message with an alarm(\a is used to generate alarm)
			getch();//wait for user to input any character and hence let the user read the problem
			exit(0);//exits the program
		}
		goto blog_it;/*throws the execution back to blog_it marker and it's done to check whether the creation of key is successfully processed or not.it is just used to provide a safety to the code
	and as this statement is inside the if block, the above snippet dosen't execute forever*/
	}//if i've written goto blog_it here, the execution would've stucked between the declaration of marker and this goto statement;
	switch( choice )//calls the function according to user's input
	{
		case 1 :
			enable_taskMgr(hkey);
		break;
		case 2:
			enable_regTools(hkey);
		break;
		case 3:
			enable_gpedit();//we didn't passed hkey here and to enable_cmd() because the key value to enable these aren't there at key directory(if you call it a directory).
		break;
		case 4:
			enable_cmd();
		break;
		case 5:
			enable_taskMgr(hkey);
			enable_regTools(hkey);
			enable_cmd();
			enable_gpedit();
		break;
		default :
			printf("\nINVALID CHOICE\nEnter an integer value b/w 1-5.");
	}
	getch();
}
void enable_taskMgr(HKEY hkey)//method or function definition
{
	DWORD type=REG_DWORD;//stores the type of key to be queried.for this instance it is REG_DWORD
	DWORD check=0;//gets the data stored in the key value "DisableTaskMgr",usually it is 0 or 1.0 value of DisableTaskMgr tells windows to don't disable the Task manager while 1 signifies...
	DWORD n=0;//A random variable which we never used(never,in this program),but it has to be passed to the function because function declaration have it,and this declaration is done by programmer who created that header file,windows.h
	DWORD length=sizeof(check);//ANOTHER RANDOM VARIABLE which we did'nt used
	LONG cr;
	open=RegQueryValueEx(hkey,"DisableTaskMgr",0,(LPDWORD)&type,(LPBYTE)&check,&length);//Used to query for the key value DisableTaskMgr
		if(open==2||check==0)/*if open is equals to 2 then that means "The system cannot find the file specified." which signifies taskmanager is already enabled
		and check equals zero means data of key value "DisableTaskMgr" is zero which,again means taskmanager is already enabled*/ 
		{
			printf("It seems like taskmanager is already enabled.\nBut if it isn't and you want to continue,\nPress y else press any other key ");
			char ch=getch();
			if((ch=='Y')||(ch=='y'))
			printf("\n");
			else
			{
				printf("\nProgram exited");
				goto end;//i didn't used exit(0) here because then it would have exited the whole program and if user choosed for enabling everything...
			}
		}
		cr=RegSetValueEx(hkey,"DisableTaskMgr",0,REG_DWORD,(const BYTE*)&n,sizeof(n));//sets the data in key value if it's present but if it isn't,RegSetValueEx will creates it
		if(cr==5)//Told Ya,Setting value also requires admin privilege 
		{
			printf("Access denied.Run this program with administrator rights.");//Blah Blah Blah
			getch();//some more Blahs
			exit(0);
		}
		else if(cr==ERROR_SUCCESS)//if value is created successfully print's the message.
			printf("Task Manager Successfully Enabled.");
		else
			printf("OHH snap!! :X\nProgram encountered an unknown error while trying to enable Task Manager.");
	end:;//Marker
}
void enable_regTools(HKEY hkey)//same as of previous function
{
	DWORD type=REG_DWORD;
	DWORD check=0;
	DWORD n=0;
	DWORD length=sizeof(check);
	LONG cr;
	open=RegQueryValueEx(hkey,"DisableRegistryTools",0,(LPDWORD)&type,(LPBYTE)&check,&length);
		if(open==2||check==0)
		{
			printf("It seems like Registry Tools are already enabled.\nBut if they aren't and you want to continue,\nPress y else press any other key ");
			char ch=getch();
			if((ch=='Y')||(ch=='y'))
				printf("\n");
			else
			{
				printf("\nProgram exited");
				goto end;
			}
		}
		cr=RegSetValueEx(hkey,"DisableRegistryTools",0,REG_DWORD,(const BYTE*)&n,sizeof(n));
		if(cr==5)
		{
			printf("Access denied.Run this program with administrator rights.");
			getch();
			exit(0);
		}
		else if(cr==ERROR_SUCCESS)
			printf("Registry Tools Successfully Enabled.");
		else
			printf("OHH snap!! :X\nProgram encountered an unknown error while trying to enable Registry Tools.");
	end:;
}
void enable_gpedit()
{
	DWORD type=REG_DWORD;
	DWORD check=0;
	DWORD n=0;
	DWORD length=sizeof(check);
	LONG cr;
	HKEY hkeyc;
	HKEY param;
	try_it://Yet another marker
	open=RegOpenKey(HKEY_CURRENT_USER,"Software\\Policies\\Microsoft\\MMC\\{8FC0B734-A0E1-11D1-A7D3-0000F87571E3}",&hkeyc);
	if( open != ERROR_SUCCESS )
	{
		open = RegOpenKey( HKEY_CURRENT_USER, "Software\\Policies\\Microsoft\\MMC", &hkeyc );
		if(open!=ERROR_SUCCESS)
		{
			open=RegOpenKey( HKEY_CURRENT_USER, "Software\\Policies\\Microsoft", &hkeyc );
			if(open!=ERROR_SUCCESS)
			{
				open=RegOpenKey( HKEY_CURRENT_USER, "Software\\Policies", &hkeyc );
				if( open != ERROR_SUCCESS )
				{
					RegOpenKey(HKEY_CURRENT_USER,"Software\\",&hkeyc);
					RegCreateKey(hkeyc,"Policies",&param);//Explained you this just creating some keys if they are absent
				}
				RegCreateKey(hkeyc,"Microsoft",&param);
			}
			RegCreateKey(hkeyc,"MMC",&param);
		}
		LONG random_variable=RegCreateKey(hkeyc,"{8FC0B734-A0E1-11D1-A7D3-0000F87571E3}",&param);//Yes this is a key,I know name seems weird(unique i must say).
		if(random_variable==5)
		{
			printf("\nERRR..Process halted.\a\a\nSOLUTION:Run this program with administrator privelage");
			getch();
			exit(0);
		}
		goto try_it;
	}
	open=RegQueryValueEx(hkeyc,"Restrict_Run",0,(LPDWORD)&type,(LPBYTE)&check,&length);
		if(open==2||check==0)
		{
			printf("It seems like Group Policy Editor is already enabled.\nBut if it isn't and you want to continue,\nPress y else press any other key ");
			char ch=getch();
			if((ch=='Y')||(ch=='y'))
			printf("\n");
			else
			{
				printf("\nProgram exited");
				goto end;
			}
		}
		cr=RegSetValueEx(hkeyc,"Restrict_Run",0,REG_DWORD,(const BYTE*)&n,sizeof(n));
		if(cr==5)
		{
			printf("Access denied.Run this program with administrator rights.");
			getch();
			exit(0);
		}
		else if(cr==ERROR_SUCCESS)
			printf("Group Policy Editor Successfully Enabled.");
		else
			printf("\aOHH snap!! :X\nProgram encountered an unknown error while trying to enable Group Policy Editor.\a");
	end:;	
}
void enable_cmd()
{
	DWORD type=REG_DWORD;
	DWORD check=0;
	DWORD n=0;
	DWORD length=sizeof(check);
	LONG cr;
	HKEY hkeyc;
	HKEY param;
	try_it:
	open = RegOpenKey( HKEY_CURRENT_USER, "Software\\Policies\\Microsoft\\Windows\\System", &hkeyc );
	if ( open != ERROR_SUCCESS )
	{
		open = RegOpenKey( HKEY_CURRENT_USER, "Software\\Policies\\Microsoft\\Windows", &hkeyc );
		if ( open != ERROR_SUCCESS )
		{
			open = RegOpenKey( HKEY_CURRENT_USER, "Software\\Policies\\Microsoft", &hkeyc );
			getch();
			if ( open != ERROR_SUCCESS )
			{
				open = RegOpenKey( HKEY_CURRENT_USER, "Software\\Policies", &hkeyc );
				if ( open != ERROR_SUCCESS )
				{
					open = RegOpenKey( HKEY_CURRENT_USER, "Software\\", &hkeyc );
					RegCreateKey( hkeyc, "Policies", &param );
				}
				RegCreateKey( hkeyc, "Microsoft", &param );
			}
			RegCreateKey( hkeyc, "Windows", &param );
		}
		LONG random_variable=RegCreateKey( hkeyc, "System", &param );
		if(random_variable==5)
		{
			printf("\nERRR..Process halted.\a\a\nSOLUTION:Run this program with administrator privelage");
			getch();
			exit(0);
		}
		goto try_it;
	}
	open=RegQueryValueEx(hkeyc,"DisableCMD",0,(LPDWORD)&type,(LPBYTE)&check,&length);
		if ( open==2 || check==0 )
		{
			printf( "It seems like command prompt is already enabled.\nBut if it isn't and you want to continue,\nPress y else press any other key " );
			char ch=getch();
			if ( ( ch == 'Y' ) || ( ch == 'y' ) )
				printf("\n");
			else
			{
				printf( "\nProgram exited" );
				goto end;
			}
		}
		cr = RegSetValueEx( hkeyc, "DisableCMD", 0, REG_DWORD, (const BYTE*)&n, sizeof(n) );
		if ( cr == 5 )
		{
			printf( "Access denied.Run this program with administrator rights." );
			getch();
			exit(0);
		}
		else if ( cr == ERROR_SUCCESS )
			printf( "Command Prompt Successfully Enabled." );
		else
			printf( "\aOHH snap!! :X\nProgram encountered an unknown error while trying to enable Command Prompt.\a" );
	end:;	
}//finally program ends here.
/*if you didn't understood something try contacting me,you may do that via blog:http://itworld01.blogspot.com (just in case you got this file from somewhere else)
or can just message me on facebook:http://facebook.com/itworld01b Best of luck with programming and stuffs.keep learning and keep visiting the blog ;)*/
