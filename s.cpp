#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")

#define FILENAME1 "buyers.txt"
#define FILENAME2 "seats.txt"
using namespace std;

void initialization();
class buyer
{
	public:
		int m_id;
		string m_name;
		int m_seat;
		int m_starting;
		int m_terminal;
		//int m_price;
		
	public:
		buyer(int id,string name,int starting,int terminal,int seat)
		{
			m_id=id;
			m_name=name;
			m_starting=starting;
			m_terminal=terminal;
			m_seat=seat;
			//m_price=price;
		}
};

void save(int num_buyer,buyer* arr_buyer[],bool arr_seat[10][9])
{
	ofstream ofs1,ofs2;
	ofs1.open(FILENAME1,ios::out);

	for(int i=0;i<num_buyer;i++)
	{

		if(arr_buyer[i]==NULL)continue;
		ofs1<<arr_buyer[i]->m_id<<" "
		    <<arr_buyer[i]->m_name<<" "
	 	    <<arr_buyer[i]->m_starting<<" "
		    <<arr_buyer[i]->m_terminal<<" "
		    <<arr_buyer[i]->m_seat<<endl;
		    //<<arr_buyer[i]->m_price<<endl;
	    
	}

	ofs2.open(FILENAME2,ios::out);
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<9;j++)
		{
			ofs2<<arr_seat[i][j]<<" ";
		}
	}
	ofs1.close();
	ofs2.close();
}
int count()
{
	ifstream ifs1;
	ifs1.open(FILENAME1,ios::in);
	int id;string name;int stts;int tmns;int seat;
	int index=0;
	while(ifs1>>id&&ifs1>>name&&ifs1>>stts&&ifs1>>tmns&&ifs1>>seat)
	{
		index++;
	}
	return index;
}
int load(buyer** arr_buyer,bool arr_seat[10][9])
{
	ifstream ifs1;
	ifs1.open(FILENAME1,ios::in);
	int id;string name;int stts;int tmns;int seat;
	int index=0;
	while(ifs1>>id&&ifs1>>name&&ifs1>>stts&&ifs1>>tmns&&ifs1>>seat)
	{
		buyer * buyerinfile=nullptr;
		buyerinfile=new buyer(id,name,stts,tmns,seat);
		arr_buyer[index]=buyerinfile;
		index++;
	}
	ifstream ifs2;
	ifs2.open(FILENAME2,ios::in);
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<9;j++)
		{
			ifs2>>arr_seat[i][j];
		}
	}
	return index;
}
int cal(int n)
{
	int num=1;
	n--;

	while(1)
	{
		if(n<1) break;
		num*=10;
		n--;
	}
	return num;
}



int main()
{
	//定义长度变量
	int send_len = 0;
	int recv_len = 0;
	int len = 0;
	//定义发送缓冲区和接受缓冲区
	char send_buf0[100];char send_buf1[100];char send_buf2[100];char send_buf3[100];
	char recv_buf0[100];char recv_buf1[100];char recv_buf2[100];char recv_buf3[100];
	//定义服务端套接字，接受请求套接字
	SOCKET s_server;
	SOCKET s_accept;
	//服务端地址客户端地址
	SOCKADDR_IN server_addr;
	SOCKADDR_IN accept_addr;
	initialization();
	//填充服务端信息
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(9999);
	//创建套接字
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (bind(s_server, (SOCKADDR *)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "套接字绑定失败！" << endl;
		WSACleanup();
	}
	else {
		cout << "套接字绑定成功！" << endl;
	}
	//设置套接字为监听状态
	if (listen(s_server, SOMAXCONN) < 0) {
		cout << "设置监听状态失败！" << endl;
		WSACleanup();
	}
	else {
		cout << "设置监听状态成功！" << endl;
	}
	cout << "服务端正在监听连接，请稍候...." << endl;
	//接受连接请求
	len = sizeof(SOCKADDR);
	s_accept = accept(s_server, (SOCKADDR *)&accept_addr, &len);
	if (s_accept == SOCKET_ERROR) {
		cout << "连接失败！" << endl;
		WSACleanup();
		return 0;
	}
	cout << "连接建立，准备接受数据" << endl;
	//接收数据
	
	

	buyer** arr_buyer=nullptr;
	bool arr_seat[10][9]={0};
	int buyernow;

	buyernow=count();
	arr_buyer=new buyer*[buyernow];
	buyernow=load(arr_buyer,arr_seat);

cout<<arr_buyer[buyernow-1]<<' '<<buyernow<<endl;
for(int i=0;i<10;i++)
{
	for(int j=0;j<9;j++)
	{
		cout<<arr_seat[i][j]<<' ';
	}
	cout<<endl;
}
	int the_stts=0;int the_tmns=0;int the_seat=0;
	int choice1=0;
	
	int numa=0,numb=0,numb0=0;
	while(1)
	{
		cout<<"begin!"<<endl;
		//recv 0
		recv_len = recv(s_accept, recv_buf0, 100, 0);
		//
		cout<<"client's choice is";
		cout<<recv_buf0[0]<<"!!"<<endl; /////////////////////
		choice1=recv_buf0[0]-48;
		cout<<"choice1 "<<choice1<<endl;
		if(choice1==0)
		{
			cout<<recv_buf0<<endl; 
			break;//quit    branch0
		}
		if(choice1==1)  //branch1
		{
			
			while(1)
			{
				//recv 1,2
				recv_len = recv(s_accept, recv_buf1, 100, 0);
				recv_len = recv(s_accept, recv_buf2, 100, 0);
				//
				cout<<"the starting and terminal station are";
				cout<<recv_buf1<<endl<<recv_buf2<<endl;//////////////////////
				
				if(recv_buf2[0]=='0')//recv2.0='0'表示末站为10 
				{
					the_tmns=10;
				}
				else
				{
					the_tmns=recv_buf2[0]-48;
				}
				send_buf0[0]='1';
				for(int j=0;j<10;j++)
				{
					send_buf0[j+1]='1';
					for(int i=recv_buf1[0]-48-1;i<the_tmns-1;i++)
					{
						if(arr_seat[j][i]==1)
						{
							send_buf0[j+1]='0';
							break;
						}
					}
					
				}
				for(int i=1;i<11;i++)
				{
					if(send_buf0[i]=='1')
					{
						break;
					}
					if(i==10&&send_buf0[i]=='0')
					{
						send_buf0[0]='0';
						break;
					}
				}
				
				cout<<send_buf0<<endl;////////////////////////////////////////
				//send 0
				send_len = send(s_accept, send_buf0, 100, 0);
				//
				
				if(send_buf0[0]=='0')
				{
					continue;
				}
				else
				{
					the_stts=recv_buf1[0]-48;
					break;
				}
			}
			
			//recv 3
			recv_len = recv(s_accept, recv_buf3, 100, 0);
			//
			cout<<"seat choosed is"<<' ';
			cout<<recv_buf3<<endl;/////////////////////
			
			if(recv_buf3[0]=='1'&&recv_buf3[1]=='0')
			{
				the_seat=10;
			}
			else the_seat=recv_buf3[0]-48;
			for(int i=the_stts-1;i<the_tmns-1;i++)
			{
				arr_seat[the_seat-1][i]=1;
			}
			for(int i=the_stts-1;i<the_tmns-1;i++)////////////arr_seat 
			{
				cout<<arr_seat[the_seat-1][i]<<' ';
			}
			cout<<endl;
			cout<<"the_seat "<<the_seat<<endl;
			//recv 1
			recv_len = recv(s_accept, recv_buf1, 100, 0);
			//
			cout<<"id"<<' ';
			cout<<recv_buf1<<endl;///////////////////////
			
			numa=0;//char into int
			numb=0;//y表示位数 
			for(int i=0;i<100;i++)
			{
				if(recv_buf1[i]>='0'&&recv_buf1[i]<='9')
				{
					numb++;
				}
				else break;
			}
			numb0=numb;
			for(int i=0;i<numb;i++)
			{
				numa+=(recv_buf1[i]-48)*cal(numb0);
				numb0--;
			}

			
			
			//recv 2
			recv_len = recv(s_accept, recv_buf2, 100, 0);
			//
			cout<<"name"<<' ';
			cout<<recv_buf2<<endl;/////////////////////
			
			buyernow++;
cout<<"buyernow "<<buyernow<<endl;
			//the_seat  the_stts  the_tmns numa 
			buyer ** newspace=new buyer*[buyernow];
			if(arr_buyer!=NULL)
			{
				for(int i=0;i<buyernow-1;i++)
				{
					newspace[i]=arr_buyer[i];
				}
			}			
			buyer* newbuyer = nullptr;
			newbuyer =new buyer(numa,recv_buf2,the_stts,the_tmns,the_seat);
			delete[] arr_buyer; 
			
			newspace[buyernow-1]=newbuyer;
			

			arr_buyer=newspace;

			for(int i=0;i<buyernow;i++)
			{
				cout<<"id"<<i+1<<' ';
				cout<<arr_buyer[i]->m_id<<endl;
				cout<<"name "<<arr_buyer[i]->m_name<<endl;
			}

			continue;
		}
		if(choice1==2)
		{
			//recv 1
			recv_len = recv(s_accept, recv_buf1, 100, 0);
			//
			numa=0;//char into int
			numb=0;//y表示位数 
			for(int i=0;i<100;i++)
			{
				if(recv_buf1[i]>='0'&&recv_buf1[i]<='9')
				{
					numb++;
				}
				else break;
			}
			numb0=numb;
			for(int i=0;i<numb;i++)
			{
				numa+=(recv_buf1[i]-48)*cal(numb0);
				numb0--;
			}
			if(buyernow==0)
			{
				send_buf0[0]='0';
				send_len = send(s_accept, send_buf0, 100, 0);
			}
			for(int i=0;i<buyernow;i++)
			{
				if(arr_buyer[i]->m_id==numa)
				{
					send_buf0[0]='1';
					strcpy(send_buf2,arr_buyer[i]->m_name.c_str());
					send_buf3[0]=(char)(arr_buyer[i]->m_seat+48);
					send_buf3[1]=(char)(arr_buyer[i]->m_starting+48);
					send_buf3[2]=(char)(arr_buyer[i]->m_terminal+48);
					//send 0.0 ='1'
					send_len = send(s_accept, send_buf0, 100, 0);
					send_len = send(s_accept, recv_buf1, 100, 0);
					send_len = send(s_accept, send_buf2, 100, 0);
					send_len = send(s_accept, send_buf3, 100, 0);
					//
					break;
				}
				if(i==buyernow-1)
				{
					send_buf0[0]='0';
					//send 0.0 ='0'
					send_len = send(s_accept, send_buf0, 100, 0);
					//
				}
			}
		}

		if(choice1==3)
		{
			//recv 1
			recv_len = recv(s_accept, recv_buf1, 100, 0);
			//
			numa=0;//char into int
			numb=0;//y表示位数 
			for(int i=0;i<100;i++)
			{
				if(recv_buf1[i]>='0'&&recv_buf1[i]<='9')
				{
					numb++;
				}
				else break;
			}
			numb0=numb;
			for(int i=0;i<numb;i++)
			{
				numa+=(recv_buf1[i]-48)*cal(numb0);
				numb0--;
			}
			if(buyernow==0)
			{
				send_buf0[0]='0';
				send_len = send(s_accept, send_buf0, 100, 0);
			}
			for(int i=0;i<buyernow;i++)
			{
				if(arr_buyer[i]->m_id==numa)
				{
					send_buf0[0]='1';
					//send 0.0 ='1'
					send_len = send(s_accept, send_buf0, 100, 0);
					//
					for(int j=arr_buyer[i]->m_starting-1;j<arr_buyer[i]->m_terminal-1;j++)
					{
						arr_seat[arr_buyer[i]->m_seat-1][j]=0;
					}
					arr_buyer[i]==nullptr;
					for(int j=i;j<buyernow-1;j++)
					{
						arr_buyer[j]=arr_buyer[j+1];
						if(j==buyernow-2)
						{
							arr_buyer[j-1]=nullptr;
						}
					}
					buyernow--;
					break;
				}
				if(i==buyernow-1)
				{
					send_buf0[0]='0';
					//send 0.0 ='0'
					send_len = send(s_accept, send_buf0, 100, 0);
					//
					
				}
			}
		}
	}
	save(buyernow,arr_buyer,arr_seat);


	//关闭套接字
	closesocket(s_server);
	closesocket(s_accept);
	//释放DLL资源
	WSACleanup();	
		
	
	return 0;	
}
void initialization() {
	//初始化套接字库
	WORD w_req = MAKEWORD(2, 2);//版本号
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cout << "初始化套接字库失败！" << endl;
	}
	else {
		cout << "初始化套接字库成功！" << endl;
	}
	//检测版本号
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "套接字库版本号不符！" << endl;
		WSACleanup();
	}
	else {
		cout << "套接字库版本正确！" << endl;
	}
	//填充服务端地址信息

}
