/* Vivek Jain : 201202182
   Ashish Kumar : 201202100
 */

#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;
typedef struct poss{
	int board_white[27];
	int board_black[27];
	float heu;
	int both;
	int di1;
	int di2;
	int di3;
	int di4;
	int barw;
	int barb;
}poss;
vector<poss> all; 
vector<poss> all2;
int dice_1;
int dice_2;
void recurse(int white[],int black[],int r1,int r2,int due_r1,int due_r2,int due_r3,int due_r4,int barw,int barb,int cond)
{
	int i;
	int no_black=0;
	int flag=0;
	for(i=24;i>=1;i--)
	{
		if(white[i]>0)
		{

			if(r1!=0)
			{
				int b_fl=0,cnt=0,cntt=0;
				if(barw==0)
				{
					for(int j=1;j<=6;j++)
					{
						cnt+=white[j];		
					}
					for(int j=1;j<=24;j++)
						cntt+=white[j];
					if(cnt==cntt)
						b_fl=1;	
				}	
				//if not bear off
				if(b_fl==0)
				{
					if(i-r1>=1)
					{
						no_black=0;
						if(black[i-r1]<2)
						{


							white[i]--;
							white[i-r1]++;
							flag=1;
							if(black[i-r1]==1)
							{
								no_black=1;
								black[i-r1]--;
								barb++;
							}
							recurse(white,black,0,r2,i,due_r2,i-r1,due_r4,barw,barb,cond);
							if(no_black==1)
							{
								black[i-r1]++;
								barb--;
							}
							//cout << white[i] << endl;
							white[i]++;
							white[i-r1]--;

						}
					}
				}
				else
				{
					//if not bear off
					if(i-r1>=1)
					{
						no_black=0;
						if(black[i-r1]<2)
						{


							white[i]--;

							flag=1;
							white[i-r1]++;

							if(black[i-r1]==1)
							{
								no_black=1;

								black[i-r1]--;
								barb++;
							}
							recurse(white,black,0,r2,i,due_r2,i-r1,due_r4,barw,barb,cond);
							white[i]++;
							if(no_black==1)
							{
								black[i-r1]++;
								barb--;
							}
							//cout << white[i] << endl;
							white[i-r1]--;
						}
					}
					else// bear off
					{
						int jl,fjl=0;
						for(jl=i+1;jl<25;jl++)
						{
							if(white[jl]>0)
							{
								fjl=1;
								break;
							}
						}
						if(fjl==0)
						{
							white[i]--;
							flag=1;
							recurse(white,black,0,r2,i,due_r2,-1000,due_r4,barw,barb,cond);
							white[i]++;
						}
					}	
				}
			}
			if(r2!=0)
			{
				int b_fl=0,cnt=0,cntt=0;
				if(barw==0)
				{
					for(int j=1;j<=6;j++)
					{
						cnt+=white[j];
					}
					for(int j=1;j<=24;j++)
					{
						cntt+=white[j];
					}
					if(cnt==cntt)
						b_fl=1;
				}
				if(b_fl==0)
				{
					if(i-r2>=1)
					{
						no_black=0;
						if(black[i-r2]<2)
						{

							flag=1;
							white[i]--;
							white[i-r2]++;
							if(black[i-r2]==1)
							{
								no_black=1;
								black[i-r2]--;
								barb++;
							}

							recurse(white,black,r1,0,due_r1,i,due_r3,i-r2,barw,barb,cond);
							white[i]++;
							white[i-r2]--;
							if(no_black==1)
							{
								black[i-r2]++;
								barb--;
							}
						}
					}
				}
				else
				{
					if(i-r2>=1)
					{
						no_black=0;
						if(black[i-r2]<2)
						{

							flag=1;
							white[i]--;
							white[i-r2]++;
							if(black[i-r2]==1)
							{
								no_black=1;
								black[i-r2]--;
								barb++;
							}

							recurse(white,black,r1,0,due_r1,i,due_r3,i-r2,barw,barb,cond);
							white[i]++;
							white[i-r2]--;
							if(no_black==1)
							{
								black[i-r2]++;
								barb--;
							}
						}
					}
					else
					{
						int jl,fjl=0;
						for(jl=i+1;jl<=24;jl++)
						{
							if(white[jl]>0)
							{
								fjl=1;
								break;
							}
						}
						if(fjl==0)
						{

							white[i]--;
							recurse(white,black,r1,0,due_r1,i,due_r3,-1000,barw,barb,cond);
							white[i]++;
						}
					}

				}

			}

		}
	}
	if((r1==0 && r2==0))
	{
		if(r1==0 && r2==0)
		{
			poss a;
			int j;
			for(j=1;j<=24;j++)
			{
				a.board_white[j]=white[j];
				a.board_black[j]=black[j];
			}
			a.heu=0;
			a.both=1;
			a.di1=due_r1;
			a.di2=due_r2;
			a.di3=due_r3;
			a.di4=due_r4;
			a.barb=barb;
			a.barw=barw;

			int white_blot=0;
			int black_blot=0;
			for(j=1;j<=24;j++)
			{
				if(a.board_white[j]==1)
					white_blot++;
				if(a.board_black[j]==1)
					black_blot++;
			}
			int anchor_white_outer=0;
			int anchor_white=0;
			int anchor_black=0;
			int turn=0;
			int pip=0;
			for(j=1;j<=24;j++)
			{
				if(a.board_white[j]>0)
				{
					pip+=(j)*a.board_white[j];
				}
			}
			vector<int> pos_anchor_white;
			for(j=1;j<=24;j++)
			{
				if(a.board_white[j]>=2)
				{
					if(j==20)
						turn++;
					if(j==18)
						turn++;
					if(j<=24 && j>=18)
						anchor_white_outer++;
					anchor_white++;
					pos_anchor_white.push_back(j);
				}
				if(a.board_black[j]>=2)
				{
					anchor_black++;
				}
			}
			//checking for contact 
			int contact=0;
			int ai=0;
			for(j=24;j>=1;j--)
			{
				if(a.board_white[j]>0)
				{
					for(ai=j-1;ai>=1;ai--)
					{
						if(a.board_black[ai]>0)
						{
							contact=1;
							break;
						}
					}
					break;
				}
			}
			//level 1
			if(cond==0)
			{
				float eval=0;
				if(contact==1)
				{
					eval=.025*(anchor_white-anchor_black)+0.02525*(black_blot-white_blot)+.025*(barb-barw)-0.0025*pip;
				}
				else
				{
					eval-=0.0025*pip;
				}
				a.heu=eval;
				all.push_back(a);
			}
			//level 2
			else if(cond==1)
			{
				float eval=0;
				if(contact==1)
				{
					//cout<<"here"<<endl;
					//eval=-0.055*white_blot+black_blot+(anchor_white_outer-turn)*2+3*turn+anchor_white-0.5*pip;	
					eval=.025*(anchor_white-anchor_black)+0.02525*(black_blot-white_blot)+.025*(barb-barw)-0.0025*pip;
					//	cout<<eval<<endl;
				}
				else
				{
					//cout<<"here"<<endl;
					eval-=0.0025*pip;

				}
				a.heu=eval;
				//all.push_back(a);
				all2.push_back(a);
			}

		}
	}
	else if((r1!=0 || r2!=0))
	{
		if(r1==0)
		{
			poss a;
			int j;
			for(j=1;j<=24;j++)
			{
				a.board_white[j]=white[j];
				a.board_black[j]=black[j];
				a.heu=0;
				a.both=3;
				a.di1=due_r1;
				a.di2=due_r2;
				a.di3=due_r3;
				a.di4=due_r4;
				a.barb=barb;
				a.barw=barw;
			}
			int white_blot=0;
			int black_blot=0;
			for(j=1;j<=24;j++)
			{
				if(a.board_white[j]==1)
					white_blot++;
				if(a.board_black[i]==1)
					black_blot++;
			}
			int anchor_white_outer=0;
			int anchor_white=0;
			int anchor_black=0;
			int turn=0;
			int pip=0;
			for(j=1;j<=24;j++)
			{
				if(a.board_white[j]>0)
				{
					pip+=(j)*a.board_white[j];
				}
			}
			vector<int> pos_anchor_white;
			for(j=1;j<=24;j++)
			{
				if(a.board_white[j]>=2)
				{
					if(j==20)
						turn++;
					if(j==18)
						turn++;
					if(j<=24 && j>=18)
						anchor_white_outer++;
					anchor_white++;
					pos_anchor_white.push_back(j);
				}
				if(a.board_black[j]>=2)
				{
					anchor_black++;
				}
			}
			//checking for contact 
			int contact=0;
			int ai=0;
			for(j=24;j>=1;j--)
			{
				if(a.board_white[j]>0)
				{
					for(ai=j;ai>=1;ai--)
					{
						if(a.board_black[ai]>0)
						{
							contact=1;
							break;
						}
					}
					break;
				}
			}
			//level 1
			if(cond==0)
			{
				float eval=0;
				if(contact==1)
				{
					eval=.025*(anchor_white-anchor_black)+0.02525*(black_blot-white_blot)+.025*(barb-barw)-0.0025*pip;
				}
				else
				{
					eval-=0.0025*pip;
				}
				a.heu=eval;
				all.push_back(a);
			}
			//level 2
			else if(cond==1)
			{
				float eval=0;
				if(contact==1)
				{
					//cout<<"here"<<endl;
					//eval=-0.055*white_blot+black_blot+(anchor_white_outer-turn)*2+3*turn+anchor_white-0.5*pip;	
					eval=.025*(anchor_white-anchor_black)+0.02525*(black_blot-white_blot)+.025*(barb-barw)-0.0025*pip;
					//cout<<eval<<endl;
				}
				else
				{
					eval-=0.0025*pip;
				}
				a.heu=eval;
				//all.push_back(a);
				all2.push_back(a);
			}


			/*int eval=0;
			  eval=-2*white_blot+black_blot+(anchor_white_outer-turn)*2+3*turn+anchor_white;
			  a.heu=eval;
			  if(cond==0)
			  all.push_back(a);
			  else if(cond==1)
			  all2.push_back(a);*/


		}
		else if(r2==0)
		{
			poss a;
			int j;
			for(j=1;j<=24;j++)
			{
				a.board_white[j]=white[j];
				a.board_black[j]=black[j];
				a.heu=0;
				a.both=2;
				a.di1=due_r1;
				a.di2=due_r2;
				a.di3=due_r3;
				a.di4=due_r4;
				a.barb=barb;
				a.barw=barw;
			}
			int white_blot=0;
			int black_blot=0;
			for(j=1;j<=24;j++)
			{
				if(a.board_white[j]==1)
					white_blot++;
				if(a.board_black[i]==1)
					black_blot++;
			}
			int anchor_white_outer=0;
			int anchor_white=0;
			int anchor_black=0;
			int turn=0;
			int pip=0;
			vector<int> pos_anchor_white;
			for(j=1;j<=24;j++)
			{
				if(a.board_white[j]!=0)
				{
					pip+=(j)*a.board_white[j];
				}
			}
			for(j=1;j<=24;j++)
			{
				if(a.board_white[j]>=2)
				{
					if(j==20)
						turn++;
					if(j==18)
						turn++;
					if(j<=24 && j>=18)
						anchor_white_outer++;
					else
						anchor_white++;
					pos_anchor_white.push_back(j);
				}
				if(a.board_black[j]>=2)
				{
					anchor_black++;
				}
			}
			//checking for contact 
			int contact=0;
			int ai=0;
			for(j=24;j>=1;j--)
			{
				if(a.board_white[j]>0)
				{
					for(ai=j;ai>=1;ai--)
					{
						if(a.board_black[ai]>0)
						{
							contact=1;
							break;
						}
					}
					break;
				}
			}
			//level 1
			if(cond==0)
			{
				float eval=0;
				if(contact==1)
				{
					eval=.025*(anchor_white-anchor_black)+0.02525*(black_blot-white_blot)+.025*(barb-barw)-0.0025*pip;
				}
				else
				{
					eval-=0.0025*pip;
				}
				a.heu=eval;
				all.push_back(a);
			}
			//level 2
			else if(cond==1)
			{
				float eval=0;
				if(contact==1)
				{
					//cout<<"here"<<endl;
					//eval=-0.055*white_blot+black_blot+(anchor_white_outer-turn)*2+3*turn+anchor_white-0.5*pip;	
					eval=.025*(anchor_white-anchor_black)+0.02525*(black_blot-white_blot)+.025*(barb-barw)-0.0025*pip;
					//cout<<eval<<endl;
				}
				else
				{
					eval-=0.0025*pip;
				}
				a.heu=eval;
				//all.push_back(a);
				all2.push_back(a);
			}

			/*int eval=0;
			  eval=-2*white_blot+black_blot+(anchor_white_outer-turn)*2+3*turn+anchor_white+0.5*pin;
			  a.heu=eval;
			  if(cond==0)
			  all.push_back(a);
			  else if(cond==1)
			  all2.push_back(a);*/


		}

	}

}
int main()
{
	int a[35]={0};
	int b[35]={0};
	int white[37]={0};
	int black[37]={0};
	int r1;
	int r2;
	int barw=0;
	int barb=0;
	vector<pair <float,int> > all3;
	vector<pair <int,int> > dice;
	dice.push_back(make_pair(1,1));
	dice.push_back(make_pair(1,2));
	dice.push_back(make_pair(1,3));
	dice.push_back(make_pair(1,4));
	dice.push_back(make_pair(1,5));
	dice.push_back(make_pair(1,6));
	dice.push_back(make_pair(2,2));
	dice.push_back(make_pair(2,3));
	dice.push_back(make_pair(2,4));
	dice.push_back(make_pair(2,5));
	dice.push_back(make_pair(2,6));
	dice.push_back(make_pair(3,3));
	dice.push_back(make_pair(3,4));
	dice.push_back(make_pair(3,5));
	dice.push_back(make_pair(3,6));
	dice.push_back(make_pair(4,4));
	dice.push_back(make_pair(4,5));
	dice.push_back(make_pair(4,6));
	dice.push_back(make_pair(5,5));
	dice.push_back(make_pair(5,6));
	dice.push_back(make_pair(6,6));
	//string name;
	/*	for(int i=1;i<=24;i++)
		{
		cin >> white[25-i];
		if(white[25-i]<0)
		black[25-i]=-white[25-i];
		}*/
	int state=0;
	for(int i=1;i<=24;i++)
		cin >> a[i];
	for(int i=1;i<=12;i++)
	{
		if(a[i]>0)
			white[25-i]=a[i];
		if(a[i]<0)
			black[25-i]=-a[i];

	}	
	for(int i=13;i<=24;i++)
	{
		if(a[i]>0)
			white[25-i]=a[i];
		if(a[i]<0)
			black[25-i]=-a[i];
	}
	char name[10000];
	//string name;
	//cin >> name;	
	char c;
	getchar();
	c=getchar();
	int kc=0;
	while(c!='\n')
	{
		name[kc]=c;
		kc++;
		c=getchar();
	}
	cin >> r1 >> r2;
	dice_1=r1;
	dice_2=r2;
	for(int i=0;i<kc;i++)
	{
		//cout<<name[i]<<endl;
		if(name[i]=='a')
		{
			barw++;
		}
		else if(name[i]=='b')
		{
			barb++;
		}
	}
	int no_black=0;
	if(barw==0)
	{
		recurse(white,black,r1,r2,0,0,0,0,barw,barb,0);
	}
	else if(barw==1)
	{
		if((black[25-r1]<2) && (25-r1)>=1)
		{
			if(black[25-r1]==1)
			{
				no_black=1;
				black[25-r1]--;
			}
			white[25-r1]++;
			if(no_black==1)
			{
				recurse(white,black,0,r2,25,0,25-r1,0,barw-1,barb-1,0);
			}
			else
			{
				recurse(white,black,0,r2,25,0,25-r1,0,barw-1,barb,0);
			}
			if(no_black==1)
			{
				black[25-r1]++;
				no_black=0;
			}
			white[25-r1]--;

		}
		if(black[25-r2]<2 && (25-r2)>=1)
		{
			if(black[25-r2]==1)
			{
				black[25-r2]--;
				no_black=1;
			}
			white[25-r2]++;
			if(no_black==1)
			{
				recurse(white,black,r1,0,0,25,0,25-r2,barw-1,barb-1,0);
			}
			else
			{
				recurse(white,black,r1,0,0,25,0,25-r2,barw-1,barb,0);
			}
			if(no_black==1)
			{
				black[25-r2]++;
				no_black=0;
			}
			white[25-r2]--;
		}
	}
	else
	{
		if((black[25-r1]<2) && (25-r1)>=1)
		{
			if(black[25-r1]==1)
			{
				black[25-r1]--;
			}
			white[25-r1]++;

		}
		if(black[25-r2]<2 && (25-r2)>=1)
		{
			if(black[25-r2]==1)
			{
				black[25-r2]--;
			}
			white[25-r2]++;
		}
		recurse(white,black,0,0,25,25,25-r1,25-r2,barw-2,barb-2,0);
	}

	//	cout << all.size() << endl;
	int max=-100000;
	int maxindex=0;
	int yes=0;
	for(int i=0;i<all.size();i++)
	{
		if(all[i].both==1)
		{
			yes=1;
			break;
		}	
	}

	if(yes==1)
	{
		for(int i=0;i<all.size();i++)
		{
			if(all[i].both!=1)
				all.erase(all.begin()+i);
		}
	}
	else if(yes==0)
	{
		int tr=0;
		if(r1>r2)
			tr=3;
		else if(r2>r1)
			tr=2;
		int no=0;
		for(int i=0;i<all.size();i++)
		{
			if(all[i].both==tr)
			{
				no=1;	
				break;
			}
		}
		if(no==1)
		{
			for(int i=0;i<all.size();i++)
			{
				if(all[i].both!=tr)
					all.erase(all.begin()+i);
			}	
		}
	}
	int i,j,k;
	//cout << all.size() << endl;
		//for(i=0;i<all.size();i++)
		//{
	/*	for(j=1;j<=24;j++)
		{
			cout << all[2].board_black[25-j] << " " ;
		}
		cout<<endl;
		for(j=1;j<=24;j++)
		{
			cout << all[2].board_white[25-j] << " " ;
		}

			cout<<endl<<all[2].barb<<endl;
			cout<<all[2].barw<<endl;
			cout << all[2].heu ;
			cout << endl;
		//}*/
	for( i=0;i<all.size();i++)
	{
		int white_temp[25];
		int black_temp[25];
		for(int ti=1;ti<25;ti++)
		{
			white_temp[ti]=all[i].board_black[25-ti];
			black_temp[ti]=all[i].board_white[25-ti];
		}

		for( j=0;j<dice.size();j++)
		{
			int e_flag=0;
			if(all[i].barb==0)
			{
				recurse(white_temp,black_temp,dice[j].first,dice[j].second,0,0,0,0,all[i].barb,all[i].barw,1);
			}
			else if(all[i].barb==1)
			{
				if((black_temp[25-dice[j].first]<2) && (25-dice[j].first)>=1)
				{
					/*if(i==2)
					{
						cout<<dice[j].first<<" "<<dice[j].second<<endl;
					}*/
					if(black_temp[25-dice[j].first]==1)
					{
						e_flag=1;
						black_temp[25-dice[j].first]--;
					}
					white_temp[25-dice[j].first]++;
					if(e_flag==1)
					{
						/*if(i==2)
						{
							cout<<"1"<<endl;
						}*/
						recurse(white_temp,black_temp,0,dice[j].second,25,0,25-dice[j].first,0,all[i].barb-1,all[i].barw-1,1);
					}
					else
					{
						/*if(i==2)
						{
							cout<<"2"<<endl;
						}*/
						//        recurse(white,black,0,r2,25,0,barw-1,barb,0);
						recurse(white_temp,black_temp,0,dice[j].second,25,0,25-dice[j].first,0,all[i].barb-1,all[i].barw,1);
					}
					if(e_flag==1)
					{
						black_temp[25-dice[j].first]++;
						e_flag=0;
					}
					white_temp[25-dice[j].first]--;

				}
				if(black_temp[25-dice[j].second]<2 && (25-dice[j].second)>=1)
				{
					if(black_temp[25-dice[j].second]==1)
					{
						e_flag=1;
						black_temp[25-dice[j].second]--;
					}
					white_temp[25-dice[j].second]++;
					if(e_flag==1)
					{
						recurse(white_temp,black_temp,dice[j].first,0,0,25,0,25-dice[j].second,all[i].barb-1,all[i].barw-1,1);
					}
					else
					{
						/*if(i==2)
						{
							cout<<"12"<<endl;
						}*/

						recurse(white_temp,black_temp,dice[j].first,0,0,25,0,25-dice[j].second,all[i].barb-1,all[i].barw,1);
						/*if(i==2)
						{
							cout<<"12i"<<endl;
						}*/

					}
					white_temp[25-dice[j].second]--;
					if(e_flag==1)
					{
						black_temp[25-dice[j].second]++;
						e_flag=0;
					}
				}

			}
			else
			{
				if((black_temp[25-dice[j].first]<2) && (25-dice[j].first)>=1)
				{
					if(black_temp[25-dice[j].first]==1)
					{
						black_temp[25-dice[j].first]--;
					}
					white_temp[25-dice[j].first]++;

				}
				if(black_temp[25-dice[j].second]<2 && (25-dice[j].second)>=1)
				{
					if(black_temp[25-dice[j].second]==1)
					{
						black_temp[25-dice[j].second]--;
					}
					white_temp[25-dice[j].second]++;
				}
				recurse(white_temp,black_temp,0,0,25,25,25-dice[j].first,25-dice[j].second,all[i].barb-2,all[i].barw-2,1);

			}
			yes=0;
			for(int t=0;t<all2.size();t++)
			{
				if(all2[t].both==1)
				{
					yes=1;
					break;
				}	
			}
			if(yes==1)
			{

				for(int  t=0;t<all2.size();t++)
				{
					if(all2[t].both!=1)
						all2.erase(all2.begin()+t);
				}
			}
			else if(yes==0)
			{
				int tr=0;
				if(r1>r2)
					tr=3;
				else if(r2>r1)
					tr=2;
				int no=0;
				for(int t=0;t<all2.size();t++)
				{
					if(all2[t].both==tr)
					{
						no=1;	
						break;
					}
				}
				if(no==1)
				{
					for(int t=0;t<all2.size();t++)
					{
						if(all2[t].both!=tr)
							all2.erase(all2.begin()+t);
					}	
				}
			}
				
			float min=9999;
			int minindex=0;
			int f;
			for( k=0;k<all2.size();k++)
			{
				if(all2[k].heu<min)
				{
					min=all2[k].heu;	
					minindex=k;
				}
				//		for(f=1;f<=24;f++)
				//			cout << all2[k].board_white[f] << " ";
				//		cout << endl;
			}

			state+=all2.size();
			if(all2.size()>0)
			{
				if(dice[j].second==dice[j].first)
					all3.push_back(make_pair(all2[minindex].heu,1));
				else
					all3.push_back(make_pair(all2[minindex].heu,0));
				all2.erase(all2.begin(),all2.end());
			}
		}
	//	cout << state;
	//		cout << endl;
		float ans=0;
		for(k=0;k<all3.size();k++)
		{
			if(all3[k].second==1)
			{
				ans+=(all3[k].first*1.0)*0.027777;
				//		cout << all3[k].first << endl;
				//cout << ans << endl; 
			}
			else
			{
				ans+=(all3[k].first*1.0)*0.05555555;

				//		cout << all3[k].first << endl;
			}
			//cout << "ans: " << ans << endl; 
		}
		all[i].heu=ans;

		//		cout << ans << " " << all[i].heu << endl;
		all3.erase(all3.begin(),all3.end());
		//cout << all2.size() <<endl;

	}
	if(all.size()>0)
	{
		float maxin=-10000;
		int maxindex1=0;
		for(int i=0;i<all.size();i++)
		{
			/*for(int j=1;j<=24;j++)
			  {
			  cout<<all[i].board_white[25-j]<<" ";
			  }*/
			//cout << all[i].heu <<endl;
			if(all[i].heu>maxin)
			{
				maxin=all[i].heu;
				maxindex1=i;
			}
		}
		int fl=0;
		if(all[maxindex1].di1==25)
		{
			if(all[maxindex1].di3==0)
			{
				//cout<<"Pass"<<endl;
				fl++;
			}
			else
			{
				cout<<"Z"<<" "<<25-all[maxindex1].di3<<endl;
			}
		}
		else
		{
			if(all[maxindex1].di3!=-1000)
			{
				if(all[maxindex1].di1==0)
				{
					//cout<<"Pass"<<endl;
					fl++;
				}
				else
				{
					//cout<<"first"<<endl;
					cout<<25-all[maxindex1].di1<<" "<<25-all[maxindex1].di3<<endl;
				}
			}
			else
			{
				if(all[maxindex1].di1==0)
				{
					fl++;
					//cout<<"Pass"<<endl;
				}
				else
				{
					cout<<25-all[maxindex1].di1<<" "<<"O"<<endl;
				}
			}

		}
		if(all[maxindex1].di2==25)
		{
			if(all[maxindex1].di4==0)
			{
				fl++;
				//cout<<"Pass"<<endl;
			}
			else
			{
				cout<<"Z"<<" "<<25-all[maxindex1].di4<<endl;
			}
		}
		else
		{
			if(all[maxindex1].di4!=-1000)
			{
				if(all[maxindex1].di2==0)
				{
					fl++;
					//cout<<"Pass"<<endl;
				}
				else
				{
					//cout<<"Second"<<endl;
					cout<<25-all[maxindex1].di2<<" "<<25-all[maxindex1].di4<<endl;
				}
			}
			else
			{
				if(all[maxindex1].di2==0)
				{
					fl++;
					//cout<<"Pass"<<endl;
				}
				else
				{
					cout<<25-all[maxindex1].di2<<" "<<"O"<<endl;
				}
			}

		}
		for(int f=0;f<fl;f++)
		{
			cout<<"pass"<<endl;
		}

		//}
	}
	else
	{
		cout<<"pass"<<endl<<"pass"<<endl;
	}
	//	cout << all2.size() <<endl;
	//	cout << "Whites position after my move " << endl;
	/*	if(all.size()>0)
		{

		for(int j=1;j<=12;j++)
		{
		cout << all[maxindex].board_white[13-j] << " " ;
		}
		cout << endl;
		for(int j=13;j<=24;j++)
		{
		cout << all[maxindex].board_white[j] << " " ;
		}
		cout << endl;
		cout << "Ends Here" <<endl ;
		vector<int> greater;
		for(int i=1;i<=24;i++)
		{
		if(all[maxindex].board_white[i]>white[i])
		greater.push_back(i);

		}
		int k=0,l=0;
		char s,p;

		}*/

	return 0;
}
