#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<dos.h>
#include<fstream.h>
#include<graphics.h>

//Declaring Global Variables
union REGS in,out;
int midx=319,midy=239,propx=160,cnt=0,opt=0,i=0;
char *a,*b;

//Declaring Global Program Utilities
class utilities
{ 
	public: 
		int font,bcol,tcol,size,accgl;
}u;

struct mousepos
{ 
	int x1,y1,x2,y2,num;
}m[15];

//Declaring Account Classes and Structures
struct accdetails
{
	char accnm[20],password[15],repassword[15];
};

struct msg
{
	char text[100],nm[15],d[15],t[15];
};

class account
{
	public:
		char name[30],cntry[15],occ[15],age[2];
		accdetails accdet;
		unsigned int fno,tno,accno;
		msg fmsg[5],tmsg[5];
		account()
	    {
			fno=tno=0;
		}
		void msgbox(int typ);
		void personal();
		int accsettings();
		int changeaccsettings();
}acc[10];

//Declaring Program Functions
void start();
void intro();
void end();
int crtacc(account &log,account acc[]);
void login(account acc[10]);
int acfn(account &log,account acc[]);
int mail(account &log,account acc[]);
int send(account &from,account acc[]);
int settings();
void tcol();
void bcol();
void font();
void verify(char *a,int typ);
void cl(int x1,int y1,int x2,int y2,int p);
void inter();
void expand(int x,int y,char *a,int siz=4);
void enter(int x,int y,char *ch,int typ,int ent=0);
void show(int x,int y,char *a);
void infoent(int x,int y,int x1,int x2,int y1,char *a,char *b,int typ);
void datetime(char *d,char *t);
int sel();
void massign(int x1,int y1,int x2,int y2,int num);
void fil(int x1,int y1,int x2,int y2,int col,char *a);
void load();
void save();

//Main Function
int main()
{
	clrscr();
	load();
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"C:/TC/BGI");
	start();
	intro();
	while(1)
	{
		inter();
		expand(propx,midy-100,"1. Create an account");
		expand(propx,midy-50,"2. Login");
		expand(propx,midy,"3. Settings");
		expand(propx,midy+50,"4. Exit");
		opt=sel();
		switch(opt)
		{
			case 0:
			{
				crtacc(acc[u.accgl],acc);
				u.accgl++;
				break;
			}
			case 1:
			{
				login(acc);
				break;
			}
			case 2:
			{
				settings();
				break;
			}
			default:
			{
			    verify ("Are you sure you want to exit?",0);
			    opt=sel();
			    if(opt==0)
			    {
			       save();
			       closegraph();
			       end();
			       return 0;
			    }
			}
		}
	}
}

//Introductory Designing Functions
void start()
{
	for(int i=250;i>=0;i-=10)
	{
		settextstyle(8,0,10);
		outtextxy(midx-50,midy-140-i,"A");
		settextstyle(8,0,4);
		outtextxy(midx-52-i,midy-87,"M");
		outtextxy(midx+5+i,midy-87,"Z");
		outtextxy(midx+25+i,midy-42,"PPS");
		delay(40);
		if(i>0)
			cleardevice();
	}
	delay(200);
	settextstyle(0,0,1);
	outtextxy(midx-85,midy+20,"Programming");
	delay(500);
	outtextxy(midx+10,midy+20,"Redefined");
	getch();
	setfillstyle(1,WHITE);
	for(i=0;i<800;i+=100)
	{
		bar(getmaxx()-i,0,getmaxx(),i);
		delay(50);
	}
	delay(300);
}

void intro()
{
	setbkcolor(15);
	for(int i=150;i>50;i-=50)
	{
		setfillstyle(1,YELLOW);
		setcolor(8);
		bar(midx-70-i,midy-40-i,midx+70-i,midy+40-i);
		rectangle(midx-70-i,midy-40-i,midx+70-i,midy+40-i);
		line(midx-70-i,midy-40-i,midx-i,midy-i);
		line(midx+70-i,midy-40-i,midx-i,midy-i);
		setfillstyle(1,9);
		bar(midx-70+i,midy-40-i,midx+70+i,midy+40-i);
		setcolor(BLUE);
		for(int k=0;k<70;k+=10)
			line(midx-60+i,midy-30+k-i,midx+60+i,midy-30+k-i);
		delay(125);
		if(i!=100)
			cleardevice();
		else
			cl(midx-170,midy-140,midx-30,midy-40,0);
	}
	int tri[6]={midx-70,midy-15,midx+70,midy-15,midx,midy+30};
	setfillstyle(1,YELLOW);
	setcolor(8);
	for(int p=0;p<30;p+=5)
	{
		tri[5]-=p;
		bar(midx-70,midy-15,midx+70,midy+60);
		rectangle(midx-70,midy-15,midx+70,midy+60);
		fillpoly(3,tri);
		delay(125);
	}
	cl(midx+30,midy-140,midx+170,midy-60,0);
	i+=10;
	setfillstyle(1,9);
	bar(midx-70+i,midy-40-i,midx+70+i,midy+40-i);
	setcolor(BLUE);
	for(int k=0;k<70;k+=10)
		line(midx-60+i,midy-30+k-i,midx+60+i,midy-30+k-i);
	delay(125);
	cleardevice();
	setfillstyle(1,YELLOW);
	setcolor(8);
	bar(midx-70,midy-15,midx+70,midy+60);
	rectangle(midx-70,midy-15,midx+70,midy+60);
	fillpoly(3,tri);
	setfillstyle(1,9);
	bar(midx-70,midy-16,midx+70,midy-15);
	delay(125);
	setfillstyle(1,YELLOW);
	for(p=0;p<30;p+=5)
	{
		tri[5]+=p;
		bar(midx-70,midy-15,midx+70,midy+60);
		rectangle(midx-70,midy-15,midx+70,midy+60);
		fillpoly(3,tri);
		delay(125);
		if(p!=25)
			cl(midx-70,midy-80,midx+70,midy-15,0);
	}
	setfillstyle(1,YELLOW);
	settextstyle(8,0,6);
	delay(200);
	for(i=0;i<1000;i+=20)
	{
		setcolor(8);
		bar(midx-70-i,midy-15,midx+70-(i*25),midy+60);
		for(int k=0;k<6;k+=2)
			tri[k]-=i;
		fillpoly(3,tri);
		setcolor(5);
		outtextxy(getmaxx()-i,midy-50,"THE MAILER");
		if(i==500)
		{
			settextstyle(3,0,1);
			delay(1000);
			outtextxy(midx-200,midy+150,"Press any key to continue.");
			getch();
			cl(midx-210,midy+130,midx+200,midy+170,0);
			settextstyle(8,0,6);
		}
		delay(15);
		cleardevice();
	}
}

void end()
{
	cout<<"\n\n\n\n\n\t\tA Computer Science Project By:\n\n\t\t\t\t\tAbdul Marzouq";
	delay(1000);
	cout<<"\n\n\n\n\t\tSpecial Thanks To:\n\n\t\t\t\tMr. Himanshu Khare\n\t\t\t\tComputer Science Teacher\n\t\t\t\tK.V. No. 2,Kasaragod";
	delay(3000);
}

//Accounts Related Functions
int crtacc(account &log,account acc[])
 {
    if(u.accgl>10)
    {
	verify("Memory Full!",2);
	return 0;
    }
    inter();
    infoent(midx-200,midy-100,midx-50,midx+100,midy-70,"Name:",log.name,0);
    infoent(midx-200,midy-50,midx-50,midx-10,midy-20,"Age:",log.age,0);
    infoent(midx-200,midy,midx-50,midx+100,midy+30,"Country:",log.cntry,0);
    infoent(midx-200,midy+50,midx-50,midx+100,midy+80,"Occupation:",log.occ,0);
    verify("Succeeded",1);
    do
    {
	    inter();
	    infoent(midx-200,midy-100,midx-25,midx+125,midy-70,"User Name:",log.accdet.accnm,0);
	    infoent(midx-200,midy-50,midx-25,midx+125,midy-20,"Password:",log.accdet.password,1);
	    infoent(midx-200,midy,midx-25,midx+125,midy+30,"Re-Password:",log.accdet.repassword,1);
	    for(i=0;i<u.accgl;i++)
		{
			opt=0;
			if(strcmp(acc[i].accdet.accnm,log.accdet.accnm)==0)
			{
				opt=1;
				break;
			}
	    }
	   for(i=0;i<strlen(log.accdet.accnm);i++)
	   {
		   if(log.accdet.accnm[i]<48 || log.accdet.accnm[i]>122 || (log.accdet.accnm[i]>57 && log.accdet.accnm[i]<65))
		   {
			   opt=2;
			   break;
		   }
	   }
	   if(strlen(log.accdet.accnm)>8)
	      opt=2;
	   if(opt==1)
		  verify("Username Already Exists!",2);
	   else if(strcmp(log.accdet.password,log.accdet.repassword)!=0)
		  verify("Passwords Do Not Match!",2);
	   else if(opt==2)
	       verify("Username not valid!",2);
	   else
		   break;
	   verify("Do you want to continue?",0);
	   opt=sel();
	   if(opt==1)
		   break;
	}while(1);
    if(opt!=1)
		verify("Succeeded!",1);
    log.accno=u.accgl;
    return 0;
}

void login(account acc[])
{
	account log;
	inter();
    infoent(midx-200,midy-100,midx+25,midx+180,midy-70,"User Name:",log.accdet.accnm,0);
	infoent(midx-200,midy-50,midx+25,midx+180,midy-20,"Password:",log.accdet.password,1);
	for(int i=0;i<u.accgl;i++)
    {
		opt=0;
		if((strcmp(log.accdet.accnm,acc[i].accdet.accnm)==0) && strcmp(log.accdet.password,acc[i].accdet.password)==0)
			break;
		else
			opt=1;
	}
	if(opt!=1)
	{
		verify("Succeeded",1);
		acfn(acc[i],acc);
	}
	else
		verify("Incorrect Username / Password",2);
}

int acfn(account &log,account acc[])
{
	do
	{
		inter();
		expand(propx,midy-100,"1. Mailbox");
		expand(propx,midy-50,"2. Account Settings");
		expand(propx,midy,"3. Delete Account");
		expand(propx,midy+50,"4. Log Out");
		opt=sel();
		switch(opt)
		{
			case 0:
			{
				mail(log,acc);
			    break;
			}
		    case 1:
			{
				log.accsettings();
			    break;
			}
		    case 2:
			{
				verify("Are you sure you want to delete your account?",0);
			    opt=sel();
			    if(opt==0)
			    {
					for(i=log.accno;i<u.accgl-1;i++)
						acc[i]=acc[i+1];
					u.accgl--;
					return 0;
			    }
			}
		    default:
			{
				verify ("Are you sure you want to log out?",0);
				opt=sel();
				if(opt==0)
					return 0;
			}
		}
	}while(1);
}

int mail(account &log,account acc[])
{
	do
	{
		inter();
		expand(propx,midy-100,"1. Send a message");
		expand(propx,midy-50,"2. Inbox");
		expand(propx,midy,"3. Sent Messages");
		expand(propx,midy+50,"4. Back");
		opt=sel();
		switch(opt)
		{
			case 0:
			{
				send(log,acc);
			    break;
			}
		    case 1:
			{
				log.msgbox(0);
				break;
			}
		    case 2:
			{
				log.msgbox(1);
				break;
			}
		    default: return 0;
		}
	}while(1);
}

int send(account &from,account acc[])
{
	char name[15]="From: ";
	inter();
	strcat(name,from.accdet.accnm);
	expand(midx-200,midy-140,name,2);
	infoent(midx-200,midy-100,midx-50,midx+100,midy-70,"To:",name,0);
	for(int i=0;i<u.accgl;i++)
	{
		opt=0;
		if(strcmp(name,acc[i].accdet.accnm)==0)
			break;
		else
			opt=1;
	}
	if(opt==1)
	{
		verify("Account Does Not Exist.",2);
		return 0;
	}
	expand(midx-200,midy-55,"Text:",2);
	rectangle(midx-210,midy-20,midx+200,midy+140);
	settextstyle(0,0,1);
	outtextxy(midx-200,midy+170,"Press Esc when finished typing.");
	enter(midx-200,midy-5,from.fmsg[from.fno].text,0,1);
	strcpy(from.fmsg[from.fno].nm,acc[i].accdet.accnm);
	strcpy(acc[i].tmsg[acc[i].tno].text,from.fmsg[from.fno].text);
	strcpy(acc[i].tmsg[acc[i].tno].nm,from.accdet.accnm);
	datetime(from.fmsg[from.fno].d,from.fmsg[from.fno].t);
	datetime(acc[i].tmsg[acc[i].tno].d,acc[i].tmsg[acc[i].tno].t);
	from.fno=++acc[i].tno;
	verify("Message Sent",1);
	cnt=0;
	return 0;
}

void account::msgbox(int typ)
{
	msg m[7];
	int chk,p;
	do
	{
		chk=(typ==0)?tno:fno;
		inter();
		for(i=0;i<chk;i++)
		{
			for(p=0;p<chk;p++)
				m[p]=(typ==0)?tmsg[p]:fmsg[p];
			itoa(i+1,a,10);
			if(typ==0)
				strcat(a,". From: ");
			else
				strcat(a,". To: ");
			strcat(a,m[i].nm);
			strcat(a,"  ");
			strcat(a,m[i].d);
			expand(midx-200,midy-160+(40*i),a,2);
			settextstyle(6,0,1);
			fil(midx-140+textwidth(a),midy-160+(40*i),midx-80+textwidth(a),midy-138+(40*i),4,"Delete");
			massign(midx-140+textwidth(a),midy-160+(40*i),midx-80+textwidth(a),midy-138+(40*i),cnt);
	    }
		setcolor(u.tcol);
		strcpy(a,"Exit");
		expand(midx-180,midy+80,a);
		opt=sel();
		if(opt==(i*2))
			break;
	    else if(opt%2==0)
		{
			opt=opt/2;
			inter();
			if(typ==0)
				strcpy(a,"From:  ");
			else
				strcpy(a,"To:  ");
			strcat(a,m[opt].nm);
			expand(midx-200,midy-160,a,2);
			strcpy(a,"Date:  ");
			strcat(a,m[opt].d);
			expand(midx-200,midy-130,a,2);
			strcpy(a,"Time:  ");
			strcat(a,m[opt].t);
			expand(midx-200,midy-100,a,2);
			expand(midx-200,midy-60,"Text:  ",2);
			rectangle(midx-210,midy-25,midx+200,midy+140);
			show(midx-200,midy-10,m[opt].text);
			massign(0,0,getmaxx(),getmaxy(),0);
			opt=sel();
	     }
	    else
		{
			 opt=opt/2;
			 if(typ==0)
			 {
				 for(p=opt;p<tno-1;p++)
					 tmsg[p]=tmsg[p+1];
				 tno--;
			 }
			 else
		     {
				 for(p=opt;p<fno-1;p++)
					 fmsg[p]=fmsg[p+1];
				 fno--;
		      }
	    }
	}while(1);
}

account::accsettings()
{
	do
	{
		inter();
		expand(propx,midy-100,"1. Change Account Details");
		expand(propx,midy-50,"2. View Account Details");
		expand(propx,midy,"3. Back");
		opt=sel();
		switch(opt)
		{
			case 0:
			{  
				changeaccsettings();
		        break;      
			}
			case 1:
			{   
				personal();
				break;
			}
			default: return 0;
		}
    }while(1);
}

account::changeaccsettings()
{
	do
	{
		inter();
		expand(propx,midy-175,"1. Change Username");
		expand(propx,midy-125,"2. Change Password");
		expand(propx,midy-75,"3. Change Name");
		expand(propx,midy-25,"4. Change Age");
		expand(propx,midy+25,"5. Change Occupation");
		expand(propx,midy+75,"6. Change Country");
		expand(propx,midy+125,"7. Back");
		opt=sel();
		if(opt<6)
			inter();
		switch(opt)
		{
			case 0:
			{ 
				infoent(midx-225,midy-15,midx+25,midx+230,midy+15,"Enter Username:",accdet.accnm,0);
			    break;  
			}
	    case 1:
			{
				infoent(midx-230,midy-100,midx+30,midx+230,midy-70,"Enter Old Password:",a,1);
			    if(strcmp(accdet.password,a)!=0)
			     {
						 verify("Passwords Does Not Match",2);
						 opt=10;
					     break;
				 }
				 infoent(midx-230,midy-50,midx+30,midx+230,midy-20,"Enter New Password:",b,1);
				 infoent(midx-230,midy,midx+30,midx+230,midy+30,"Re-Enter Password:",accdet.repassword,1);
				 if(strcmp(b,accdet.repassword)!=0)
				 {
					 verify("Passwords Does Not Match",2);
					 opt=10;
				     break;
			     }
			     strcpy(accdet.password,b);
			     break;  
			}
		    case 2:
			{ 
				infoent(midx-225,midy-15,midx+25,midx+225,midy+15,"Enter Your Name:",name,0);
			     break;
			}
	        case 3:
			{
				infoent(midx-200,midy-15,midx+25,midx+65,midy+15,"Enter Your Age:",age,0);
			    break;
			}
            case 4:
			{ 
				infoent(midx-225,midy-15,midx+25,midx+225,midy+15,"Enter Occupation:",occ,0);
		        break;  
			}
	        case 5:
			{
				infoent(midx-225,midy-15,midx+25,midx+225,midy+15,"Enter Your Country:",cntry,0);
		        break;  
			}
		default: return 0;
		}
	    if(opt!=10)
			verify("Succeeded",1);
	}while(1);
}

void account::personal()
{
	inter();
	expand(propx,midy-150,accdet.accnm);
	expand(propx,midy-100,"Name:");
	expand(propx+200,midy-100,name);
	expand(propx,midy-50,"Age:");
	expand(propx+200,midy-50,age);
	expand(propx,midy,"Country:");
	expand(propx+200,midy,cntry);
	expand(propx,midy+50,"Occupation:");
	expand(propx+200,midy+50,occ);
	massign(0,0,getmaxx(),getmaxy(),0);
	opt=sel();
}

//Program Settings Related Functions
int settings()
{
	do
	{
		inter();
		expand(propx,midy-100,"1. Change Background Color");
		expand(propx,midy-50,"2. Change Text Color");
		expand(propx,midy,"3. Change Font");
		expand(propx,midy+50,"4. Back");
		opt=sel();
		switch(opt)
		{
			case 0:
			{
				bcol();
				break;
			}
			case 1:
			{
				tcol();
				break;
			}
			case 2:
			{
				font();
				break;
			}
		default: return 0;
	    }
	}while(1);
}

void bcol()
{
	inter();
	expand(midx-200,midy-175,"Select the background color:");
	for(int i=1,n=0,y=0;i<15;i++)
	{
		setfillstyle(1,i);
		if(i!=u.bcol && i!=u.tcol)
		{
			y=midy-125+(n*20);
			bar(midx-100,y,midx,y+10);
			delay(100);
			n++;
			massign(midx-100,y,midx,y+10,i);
		}
	}
	opt=sel();
	u.bcol=opt;
}

void tcol()
{
	inter();
	expand(midx-125,midy-175,"Select the text color:");
	for(int i=0,n=0,y=0;i<16;i++)
	{
		setfillstyle(1,i);
		if(i!=u.tcol && i!=u.bcol)
		{
			y=midy-125+(n*20);
			bar(midx-100,y,midx,y+10);
			delay(100);
			n++;
			massign(midx-100,y,midx,y+10,i);
		}
	}
	opt=sel();
	u.tcol=opt;
}

void font()
{
	inter();
	expand(midx-100,midy-175,"Select the font:");
	char *nam="Font";
	for(int i=1,n=0,y=0;i<9;i++)
	{
		settextstyle(i,0,2);
		if(i!=u.font)
		{
			y=midy-125+(n*35);
			outtextxy(midx-100,y,nam);
			delay(100);
			n++;
			massign(midx-100,y,midx-100+textwidth(nam),y+textheight(nam),i);
		}
	}
	opt=sel();
	u.font=opt;
}

//Program's Main Design Functions
void inter()
{
	cleardevice();
	setlinestyle(0,1,3);
	setbkcolor(u.bcol);
	if(u.bcol!=8)
		setcolor(8);
	else
		setcolor(1);
	for(int i=50;i>0;i-=5)
	{
		rectangle(midx-310+i,midy-240+i,midx+250+i,midy+185+i);
		delay(35);
	}
	setcolor(u.tcol);
	settextstyle(u.font,0,2);
}

void expand(int x,int y,char *a,int siz)
{
	for(int i=1;i<siz;i++)
	{
		setcolor(u.tcol);
		settextstyle(u.font,0,i);
		outtextxy(x-9*i,y,a);
		delay(125);
		if(i<siz-1)
			cl(x-9*i,y,x+textwidth(a),y+textheight(a),0);
    }
    massign(x-27,y+10,x-20+textwidth(a),y+textheight(a),cnt);
}

void verify (char *a,int typ)
{
	int x,y;
	if(u.bcol!=8)
		setcolor(8);
	else
		setcolor(1);
	rectangle(midx-200,midy-100,midx+200,midy+100);
	cl(midx-199,midy-99,midx+199,midy+99,0);
	rectangle(midx-190,midy-90,midx+190,midy+90);
	setcolor(u.tcol);
	settextstyle(6,0,1);
	if(typ==1)
	{
		outtextxy(midx-160,midy-60,"Verifying......");
		delay(1000);
		cl(midx-170,midy-80,midx+180,midy,0);
	}
	if(strlen(a)>35)
	  outtextxy(midx-180,midy-60,a);
	else
	  outtextxy(midx-160,midy-60,a);
	if(typ>0)
	{
		if(typ==1)
			fil(midx-50,midy+21,midx+35,midy+44,2,"Continue");
	    else
			fil(midx-49,midy+21,midx+5,midy+44,4,"Back");
		massign(midx-50,midy+20,midx+50,midy+45,0);
		opt=sel();
	}
	else
	{
		fil(midx-150,midy+20,midx-100,midy+45,2,"Yes");
		fil(midx+100,midy+20,midx+150,midy+45,4,"No");
		massign(midx-150,midy+20,midx-100,midy+45,0);
		massign(midx+100,midy+20,midx+150,midy+45,1);
	}
	setcolor(u.tcol);
	settextstyle(u.font,0,3);
}

void fil(int x1,int y1,int x2,int y2,int col,char *a)
{
	setcolor(8);
	rectangle(x1-1,y1-1,x2+1,y2+1);
	for(int p=x1;p<=x2;p++)
	{
		for(int q=y1;q<=y2;q++)
			putpixel(p,q,col);
	}
	setcolor(15);
	outtextxy(x1+10,y1-2,a);
}

void cl(int x1,int y1,int x2,int y2,int p)
{
	setviewport(x1,y1,x2,y2,p);
	clearviewport();
	setviewport(0,0,0,0,0);
}

void datetime(char *d,char *t)
{
	cnt=0;
	struct date da;
	struct time ti;
	getdate(&da);
	gettime(&ti);
	itoa(da.da_day,a,10);
	strcpy(d,a);
	strcat(d,"/");
	itoa(da.da_mon,a,10);
	strcat(d,a);
	strcat(d,"/");
	itoa(da.da_year,a,10);
	strcat(d,a);
	itoa(ti.ti_hour,a,10);strcpy(t,a);
	strcat(t,":");
	itoa(ti.ti_min,a,10);
	strcat(t,a);
	strcat(t,":");
	itoa(ti.ti_sec,a,10);
	strcat(t,a);
}

void show(int x,int y,char *a)
{
	char ch[2];
	settextstyle(0,0,1);
	for(int i=0,j=0;i<strlen(a);i++,j++)
	{
		ch[0]=a[i];
		ch[1]='\0';
		if(a[i]=='%')
		{
			j=-1;
			y+=textheight(ch);
		}
		else
			outtextxy(x+(j*textwidth(ch)),y,ch);
	}
	settextstyle(u.font,0,2);
}

//Mouse Enabling Functions
void massign(int x1,int y1,int x2,int y2,int num)
{
	m[cnt].x1=x1;
	m[cnt].y1=y1;
	m[cnt].x2=x2;
	m[cnt].y2=y2;
	m[cnt++].num=num;
}

int sel()
{
	int opt=6,x,y,chk=0;
	in.x.ax = 1;
	int86 (51,&in,&in);
	while(1)
	{
		in.x.ax=3;
		x=in.x.cx;
		y=in.x.dx;
		int86(51,&in,&in);
		for(int i=0;i<cnt;i++)
		{
			if(x>m[i].x1 && x<m[i].x2 && y>m[i].y1 && y<m[i].y2 && in.x.bx ==1)
			{
				opt=m[i].num;
				chk=1;
				in.x.ax=2;
				int86(51,&in,&out);
				break;
		}
		}
		if(chk==1)
			break;
    }
    cnt=0;
    return opt;
}

//Program's Main Input Functions
void enter(int x,int y,char *ch,int typ,int ent)
{
	char a[2];
	int k[15]={0},n=0,temp=x;
	settextstyle(0,0,1);
	for(int i=0,j=0;i>=0;i++,j++)
	{
		if(ent==0)
			j=i;
		ch[i]=getch();
		a[0]=ch[i];
		a[1]='\0';
		if(ch[i]==8)
		{
			k[n]--;
			if(ent==1 && ch[i-1]=='%')
			{
				j=k[--n];
				y-=textheight(a);
			}
			cl(x+((j-1)*textwidth(a)),y,x+(j*textwidth(a)),y+textheight(a),0);i-=2;
			if(ent==1 && j>0)
				j-=2;
		}
		else if(ch[i]==13)
		{
			if(ent==1)
			{
				ch[i]='%';
				x=temp;
				j=-1;
				k[n++]++;
				k[n]=-1;
				y+=textheight(a);
			}
			else
				break;
		}
		else if(ch[i]!=27)
		{
			if(typ==0)
				outtextxy(x+(j*textwidth(a)),y,a);
			else
				outtextxy(x+(j*textwidth(a)),y,"*");
			k[n]++;
		}
		if(ent==1 && ch[i]==27)
			break;
	}
	ch[i]='\0';
	settextstyle(u.font,0,2);
}

void infoent(int x,int y,int x1,int x2,int y1,char *a,char *b,int typ)
{
	outtextxy(x,y,a);
	rectangle(x1,y,x2,y1);
	enter(x1+5,(y+y1)/2-1,b,typ);
	if(strlen(b)==0 | (typ>0 && strlen(b)<4))
	{
		cl(midx-240,y,midx+240,y1,0);
		infoent(x,y,x1,x2,y1,a,b,typ);
	}
}

//Program's Memory Storage Related Functions
void load()
{
	ifstream ifs,ufs;
	int i=0;
	ifs.open("mails.txt",ios::in);
	ufs.open("utilities.txt",ios::in);
	ufs.read((char*)&u,sizeof(u));
	while(ifs.read((char*)&acc[i++],sizeof(acc[i])))
	ifs.close();
	ufs.close();
	if(u.bcol==0 || u.tcol==0)
	{
	     u.bcol=7;
	     u.tcol=1;
	     u.font=8;
	}
}

void save()
{
	ofstream ofs,ufs;
	ofs.open("mails.txt",ios::out);
	ufs.open("utilities.txt",ios::out);
	ufs.write((char*)&u,sizeof(u));
	for(int i=0;i<=u.accgl;i++)
	      ofs.write((char*)&acc[i],sizeof(acc[i]));
	ofs.close();
	ufs.close();
}
