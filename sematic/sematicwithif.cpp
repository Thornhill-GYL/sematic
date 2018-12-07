#include <iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<sstream>
using namespace std;
#define True_or_False 80
class lexword
{
	public:
	int num;
	char word[10];	
	int type;
} ;
typedef struct
{
	string name;
	int value;
}keep_data;
class Temp
{
public:
	char newtemp;
	int newtemp_num; 
	Temp()
	{
		newtemp='t';
		newtemp_num=1;
	};
};

class Label
{
public:
	char newlabel[6];
	int newlabel_num; 
	Label()
	{
		newlabel[0]='L';
		newlabel[1]='a';
		newlabel[2]='b';
		newlabel[3]='e';
		newlabel[4]='l';
		newlabel[5]='\0';
		newlabel_num=1;
	};
};
class fourpart
{
public:
	string op;
	keep_data strleft;
	keep_data strright;
	keep_data jumpnum;
	keep_data strtemp;
	bool input;
	int value;
	fourpart()
	{
		op = "";
		strleft.name = "";
		strright.name = "";
		jumpnum.name = "";
		strtemp.name = "";
		strtemp.value = 0;
		strleft.value = 0;
		strright.value = 0;
		jumpnum.value = 0;
	}

};
void newtemp();
void newlabel();
void Next(); 
void Before();
void A();
void B();
void C();
void D();
bool F(); 
void H();
void I();
void J();
void K();
void N();
void O();
void P();
void Q();
void R();
void S();
void T();
void U();
void X();
void Y();
void Z();
void putstart(int pop);
void putEqual(int pop);
void putAdd(int pop);
void putIfistrue();
void putIfisfalse();
int lookup(int num);
void equal_get(int line);
void op_get(int line);
void create_code_equal(int line);
void get_value(int line);
void judge_if(int line);
int judge_while(void);
void clear_if_flag(void);
int if_flag = 0, else_flag = 0, then_flag = 0, true_false = 0;
int sym_num=0,countword=0,flag=0;
int do_flag = 0;
int operator_flag = 0;
int operator_confirm = 0;
int next_times = 0;
int sort=0;
int putnum=0;
int labelorder[10]={0,0,0,0,0,0,0,0,0,0};
int labelorder_num=0;
int labelorder_f=0;
fourpart create[100];
lexword lw[400];
Temp ntemp;
Label nlabel;
ofstream fouterr("F:\\grammarerror.txt ", ios::out);//载入自己设定路径输入文件
ofstream four("F:\\fourout.txt ", ios::out);//载入自己设定路径输入文件 
ofstream fcreate("F:\\create.txt ", ios::out);
typedef struct 
{
	int stack[10];
	int first;
	int end;
}Four;
Four start;
Four Equal;
Four Add;

char control[8][4]={"j<","j>","j<=","j>=","j","jne","_","je"};
Four Ifistrue;
Four Ifisfalse;
Four Whiletrue;
Four Whilefalse;

typedef struct 
{
	int name[100];
	int name_count;
	int key[100];
	int key_count;
	int num[100];
	int num_count;
}symbol;
symbol symbollist;

void newtemp()
{
	ntemp.newtemp_num++;
} 

void newlabel()
{
	labelorder[labelorder_num++]=nlabel.newlabel_num;
	nlabel.newlabel_num++;
}

void Next()//得到下一个识别字符 
{
	if (sym_num < countword)
    {
        sym_num++;
		if (do_flag == 1)
		{
			next_times++;
		}
    }
}

void Before()
{
    if (sym_num > 0)
    {
        sym_num--;
    }
}

void putstart(int pop)
{
   start.end=0;
   four<<"("<<sort<<")";
   four<<"<";
   while(start.end!=pop-1)
   {
		 if(start.stack[start.end]==100)
		{
			four<<"_";
   		}
   		else
   		{
   			four<<lw[start.stack[start.end]].word;
		}
		   start.end++;
		   four<<",";
	}
	
   if(start.stack[start.end]==100)
		{
			four<<"_";
   		}
	//four<<lw[start.stack[start.end]].word;
	four<<">"<<endl;
	sort++;	
}

void putEqual(int pop)
{
	Equal.end = 1;
	char s[10] = ":=";
	string temp = "t";
	stringstream for_temp;
	four << "(" << sort << ")";
	four << "<";
	while (Equal.end != pop)
	{
		if (Equal.stack[Equal.end] == 100)
		{
			four << "_";
			if (create[sort].strright.name == "")
			{
				create[sort].strright.name = "";
			}
		}
		else if (Equal.stack[Equal.end] == 120)
		{

			four << ntemp.newtemp << ntemp.newtemp_num;

			for_temp << temp << ntemp.newtemp_num;
			//cout << for_temp.str();
			if (create[sort].strleft.name == "")
			{

				create[sort].strleft.name = for_temp.str();

			}
			newtemp();

		}
		else
		{
			four << lw[Equal.stack[Equal.end]].word;
			if (strcmp(lw[Equal.stack[Equal.end]].word, s) == 0)
			{
				create[sort].op = lw[Equal.stack[Equal.end]].word;


			}
			else
			{
				if (create[sort].strleft.name == "")
					create[sort].strleft.name = lw[Equal.stack[Equal.end]].word;
			}

		}
		Equal.end++;
		four << ",";
	}

	four << lw[Equal.stack[0]].word;
	create[sort].jumpnum.name = lw[Equal.stack[0]].word;
	four << ">" << endl;
	if(if_flag==0)
	{
	equal_get(sort);
	}
	else
	{
		if(then_flag==1&&true_false==1)
			equal_get(sort);
		else;
		if(else_flag==1&&true_false==-1)
			equal_get(sort);
		else;
	}
	sort++;
}

void putAdd(int pop)
{
	string temp = "t";
	stringstream for_temp;
	string more = "+";
	string less = "-";
	string both = "*";
	string half = "/";
	Add.end = 0;
	four << "(" << sort << ")";
	four << "<";
	while (Add.end != pop - 1)
	{

		four << lw[Add.stack[Add.end]].word;
		if ((lw[Add.stack[Add.end]].word == more) || (lw[Add.stack[Add.end]].word == less)
			|| (lw[Add.stack[Add.end]].word == both) || (lw[Add.stack[Add.end]].word == half))
		{
			create[sort].op = lw[Add.stack[Add.end]].word;
		}
		else
		{
			if (create[sort].strleft.name == "")
			{
				create[sort].strleft.name = lw[Add.stack[Add.end]].word;
			}
			else if (create[sort].strright.name == "")
			{
				create[sort].strright.name = lw[Add.stack[Add.end]].word;
			}
		}
		Add.end++;
		four << ",";
	}
	if (Add.stack[Add.end] == 120)
	{
		four << ntemp.newtemp << ntemp.newtemp_num;
		for_temp << temp << ntemp.newtemp_num;
		if (create[sort].strtemp.name == "")
		{

			create[sort].strtemp.name = for_temp.str();
		}
	}
	four << ">" << endl;
	if(if_flag==0)
	op_get(sort);
	else
	{
		if(then_flag==1&&true_false==1)
			op_get(sort);
		else;
	    if (else_flag == 1 && true_false == -1)
		{
			op_get(sort);
		}
		else;
	}
	sort++;
	operator_flag = 0;
	operator_confirm = 0;
}
void get_value(int line)
{
	string vain = "_";
	int right_flag = 0;
	for (int i = 1; i < sort; i++)
	{
		if (create[line].strleft.name == create[i].jumpnum.name)
		{

			create[line].strleft.value = create[i].jumpnum.value;
			break;
			

		}
	}
	for (int i = 1; i < sort; i++)
	{
		if (create[line].strright.name == create[i].jumpnum.name)
		{
			create[line].strright.value = create[i].jumpnum.value;
			
			right_flag = 1;
			

		}
	}
	if (right_flag == 0 && create[line].strright.name != "")
	{
		/*cout << create[line].strright.name;*/
		create[line].strright.value = atoi(create[line].strright.name.c_str());
		/*cout << create[line].strright.value;*/
	}

	cout << create[line].strleft.name;
	cout << create[line].strleft.value;
	cout << endl;
	cout << create[line].strright.name;
	cout << create[line].strright.value;
	cout << endl;
}
void op_get(int line)
{
	int middle_num = 0;
	string more = "+";
	string less = "-";
	string both = "*";
	string half = "/";
	if (create[line].op == more)
	{


		get_value(line);
		create[line].strtemp.value = create[line].strleft.value + create[line].strright.value;
		
	}
	else if (create[line].op == both)
	{
		get_value(line);
		create[line].strtemp.value = create[line].strleft.value * create[line].strright.value;
	}
	else if (create[line].op == less)
	{
		get_value(line);
		create[line].strtemp.value = create[line].strleft.value - create[line].strright.value;
		
	}
	cout << create[line].strtemp.name;
	cout << create[line].strtemp.value;
	cout << endl;
}
int compare(int line)
{
	int compare_flag = 0;
	int count_flag = 0;
	for (int i = 1; i < line; i++)
	{
		if (create[line].strleft.name == create[i].jumpnum.name)
		{
			create[line].strleft.value = create[i].jumpnum.value;
			count_flag++;

		}
		else
		{
			count_flag += 0;
		}
	}
	if (count_flag == 0)
	{
		compare_flag = 0;
	}
	else
	{
		compare_flag = 1;
	}
	return compare_flag;
}
void equal_get(int line)
{
	int key_num;
	int temp_key = 5;
	int temp_num = 0;
	for (int i = 0; i < symbollist.name_count; i++)
	{
		if (lw[symbollist.name[i]].word == create[line].jumpnum.name)
		{
			key_num = i;
			break;
		}
		else
		{
			key_num = -1;
		}
	}
	if (key_num != -1)
	{
		if (symbollist.key[key_num] == temp_key)
		{
			if (create[line].strleft.name == create[line - 1].strtemp.name)
			{
				create[line].jumpnum.value = create[line - 1].strtemp.value;
			}
			else if (compare(sort) == 1)
			{
				create[line].jumpnum.value = create[line].strleft.value;
			}
			else
			{
				temp_num = atoi(create[line].strleft.name.c_str());
				//printf("%d", temp_num);
				create[line].jumpnum.value = temp_num;
			}

		}
	}
	for (int i = 1; i < line; i++)
	{
		
		if (create[i].jumpnum.name== create[line].jumpnum.name  )
		{
			create[i].jumpnum.value = create[line].jumpnum.value;
			/*cout << create[i].jumpnum.name;
			cout << create[i].jumpnum.value;
			cout << endl;*/

		}
	}
	cout << create[line].jumpnum.name;
	cout << create[line].jumpnum.value;
	cout << endl;


}
typedef struct
{
	string name;
	int flag;
	int count;
}same;


void create_code_equal(int line)
{
	int i = 0, j = 0;
	string out_name[100];
	same same_judge[100];
	int out_num = 0;
	int out_flag = 0;
	int same_flag = 0;
	fcreate << create[1].jumpnum.name << "=" << create[1].jumpnum.value << endl;
	for (i = 2; i <sort; i++)
	{
		j = i - 1;
		while (j != 0)
		{
			if (create[i].jumpnum.name != create[j].jumpnum.name)
			{
				same_flag = 0;
			}
			else
			{
				same_flag = 1;
				break;
			}
			j--;
		}
		if (same_flag == 0 && create[i].jumpnum.name != "")
		{
			fcreate << create[i].jumpnum.name << "=" << create[i].jumpnum.value << endl;
		}

	}

}
void judge_if(int line)
{
	string plus = "j>";
	get_value(line);
	if (create[line].op == plus)
	{
		if (create[line].strleft.value > create[line].strright.value)
		{
			true_false = 1;
		
		}
		else
		{
			true_false = -1;
		}
	}
}
void clear_if_flag(void)
{
	if_flag = 0;
	else_flag = 0;
	then_flag = 0;
	true_false = 0;
}
int judge_while()
{
	string plus = "j>";
	int while_flag = 0;
	get_value(True_or_False);
	if (create[True_or_False].op == plus)
	{
		if (create[True_or_False].strleft.value > create[True_or_False].strright.value)
			while_flag = 1;
		else
			while_flag = -1;
	}
	return while_flag;
	


}
void putIfistrue()
{
	four << "(" << sort << ")";
	four << "<";
	four<<control[Ifistrue.stack[0]]<<","<<lw[Ifistrue.stack[1]].word<<","<<lw[Ifistrue.stack[2]].word<<",";
	four<<nlabel.newlabel<<nlabel.newlabel_num;
	four<<">"<<endl;
	create[sort].op = control[Ifistrue.stack[0]];
	create[sort].strleft.name = lw[Ifistrue.stack[1]].word;
	create[sort].strright.name = lw[Ifistrue.stack[2]].word;
	judge_if(sort);
	sort++;
}
void putWhiletrue()
{
	four << "(" << sort << ")";
	four << "<";
	four<<control[Whiletrue.stack[0]]<<","<<lw[Whiletrue.stack[1]].word<<","<<lw[Whiletrue.stack[2]].word<<",";
	four<<nlabel.newlabel<<nlabel.newlabel_num;
	create[True_or_False].op = control[Whiletrue.stack[0]];
	create[True_or_False].strleft.name = lw[Whiletrue.stack[1]].word;
	create[True_or_False].strright.name = lw[Whiletrue.stack[2]].word;
	four<<">"<<endl;
	sort++;
}

void putIfisfalse()
{
	four << "(" << sort << ")";
	four << "<";
	four<<control[Ifisfalse.stack[0]]<<","<<control[Ifisfalse.stack[1]]<<","<<control[Ifisfalse.stack[2]]<<",";
	four<<nlabel.newlabel<<nlabel.newlabel_num;
	four<<">"<<endl;
	sort++;
}
void putWhilefalse()
{
	four << "(" << sort << ")";
	four << "<";
	four<<control[Whilefalse.stack[0]]<<","<<control[Whilefalse.stack[1]]<<","<<control[Whilefalse.stack[2]]<<",";
	four<<nlabel.newlabel<<nlabel.newlabel_num;
	four<<">"<<endl;
	sort++;
}

//〈程序〉→start：AB#
void A()
{
	start.first=0;
	if (lw[sym_num].num == 1)//含有start
    {
    	start.stack[start.first++]=sym_num;
        Next();
        if(lw[sym_num].num==26)
        {
        	start.stack[start.first++]=sym_num;
		}
		else
		{
			 flag=1;
            fouterr<<"该程序start后缺少冒号"<<endl; 
		}
        Next();
        if (lw[sym_num].num == 37)//是标识符
        {
            //执行程序体
            start.stack[start.first++]=sym_num;
            start.stack[start.first++]=100;
            putstart(start.first);
            Next();
            B(); 
        }
        else
        {
            flag=1;
            fouterr<<"该程序start缺少方法名"<<endl; 
        }
    }
    else
    {
        flag=1;
        fouterr<<"该程序缺少关键字：start"<<endl; 
    }
}

//   B→CD
void B()// 
{
	 if (lw[sym_num].num == 4)//判断var
    {
        Next();
        C();
    }
    else if (lw[sym_num].num == 8)//判断begin
    {
        Next();
		D();
    }
    else
    {
        flag=1;
        fouterr<<"程序体缺少var或begin"<<endl;  
    }
}

//C→ var E|ε
//E→F：G；｜F：G；E
void C()//
{
    if (F())
    {
        Next();
        if (lw[sym_num].num == 26)//：
        {
        	Next();
            if (lw[sym_num].num == 5 || lw[sym_num].num == 6 || lw[sym_num].num == 7)//integer,bool,real
            {
                int j = sym_num;
                j = j - 2;
                lw[j].type = lw[sym_num].num;
				if (lw[sym_num].num == 5)
				{
					for (int i = 0; i < symbollist.name_count; i++)
						symbollist.key[i] = lw[sym_num].num;
				}
                
                j--;
                while (lw[sym_num].num == 27)
                {
                    j--;
                    lw[j].type = lw[sym_num].num;
                    symbollist.key[symbollist.key_count++]=lw[j].type;
                }
                Next();
                if (lw[sym_num].num == 28)
                {
                    Next();
                    if (lw[sym_num].num == 8)
                    {
                        Next();
                        D();
                    }
                    else if(lw[sym_num].num == 4)
                    {
                    	Next(); 
                        C();
                    }
                    else
                    {
                    	flag=1;
                        fouterr<< "变量定义后面缺少var或begin"<<endl; 
					}
                }
                else
                {
                	flag=1;
                    fouterr<< "变量定义后面缺少；"<<endl; 
                }
            }
            else
            {
                flag=1;
       			fouterr<< "变量定义缺少类型或类型定义错误"<<endl;
                return;
            }
        }
        else
        {
            flag=1;
       		fouterr<<"变量定义标识符后面缺少冒号"<<endl;       
        }
    }
    else
    {
        flag=1;
        fouterr<<"变量定义标识符出错"<<endl;   
    }

}

//D→ begin H end
void D()//
{
	H();
    if (flag == 0)
    {
        if (lw[sym_num].num == 9)
        {
            return;
        }
        else
        {
        	flag=1;
        	fouterr<<"复合句末尾缺少end"<<endl;
        }
    }
} 

//H→I；H｜I
void H()//
{
	I();
    if (flag==0)
    {
        Next();
        if (lw[sym_num].num == 28)
        {
            Next();
            H();
        }
    }
}

int lookup(int num)
{
	int i = 0;
	int flag = 0;
	for (int i = 0; i < symbollist.name_count; i++)
	{
		if (strcmp(lw[symbollist.name[i]].word, lw[num].word) == 0)
		{
			flag = 1;
			break;
		}
		else
			flag = 0;
	}
	return flag;
}

// I→J｜K
void I()//
{
	int flag_work=0;
	Equal.first=0;
	if (lw[sym_num].num == 37)
    {
    
		flag_work = lookup(sym_num);
		if(flag_work==1)
       {
         Equal.stack[Equal.first++]=sym_num;
		 Next();
         J();
       }
       else
       {
       	flag=1;
        fouterr<<"未定义变量"<<endl;  
	   }
    }
    else if (lw[sym_num].num == 8 || lw[sym_num].num == 14 || lw[sym_num].num == 10)
    {
		if (lw[sym_num].num == 14)
		{
			if_flag = 1;
		}
	
        K();
    }
    else 
    {
        Before();
    }
}

// J→A：＝N
void J()//
{
	if (lw[sym_num].num == 32)//:=
    {
    	Equal.stack[Equal.first++]=sym_num;
        Next();
		
        N();
    }
    else
    {
        flag=1;
        fouterr<<"赋值句变量后缺少：="<<endl; 
    }
}

//N→R｜Q
void N()//
{
	if (lw[sym_num].num == 12 || lw[sym_num].num == 13 || (lw[sym_num].num == 37&&lw[sym_num].type == 7))
    {
        Q();
    }
    else
    {
		Next();
		if (lw[sym_num].num == 19 || lw[sym_num].num == 20||lw[sym_num].num==21||lw[sym_num].num==22)
		{
			operator_flag = 1;
		}
		Before();
        R();
	
    }
}

//Q→X or Q｜X
void Q()//
{
	 X();
    if (flag == 0)
    {
        Next();
        if (lw[sym_num].num == 17)
        {
            Next();
            Q();
        }
        else
        {
            Before();
        }
    }
    else
    {
        return;
    }
}

//X→Y and X｜Y
void X()//
{
	Y();
    if (flag == 0)
    {
        Next();
        if (lw[sym_num].num == 36)
        {
            Next();
            X();
        }
        else
        {
            Before();
        }
    }
}

//Y→ not Y｜Z
void Y()//
{
	if (lw[sym_num].num == 18)
    {
    	Next();
        Y();
    }
    else
    {
        Z();
    }
}

//Z→B'｜A｜Q｜M
//M→A L A
//L→<|<＝ | ＝| >＝| >
//B'→ true｜false
void Z()//
{
	if (lw[sym_num].num == 12 || lw[sym_num].num == 13)
    {
        return;
    }
    else if (lw[sym_num].num == 37)
    {
    	int flag_work = lookup(sym_num);
		if(flag_work==1)
		{
         	Ifistrue.stack[Ifistrue.first++]=sym_num;
         	Whiletrue.stack[Whiletrue.first++]=sym_num;
         }
       	else
       	{
       		flag=1;
        	fouterr<<"未定义变量"<<endl;  
	   	}
        Next();
        if (lw[sym_num].num == 34 || lw[sym_num].num == 33 || lw[sym_num].num == 30 || lw[sym_num].num == 31 || lw[sym_num].num == 29 || lw[sym_num].num == 35)
        {
            Next();
            if (lw[sym_num].num == 37)
            {
            	flag_work = lookup(sym_num);
				if(flag_work==1)
         		{
         			Ifistrue.stack[Ifistrue.first++]=sym_num;
         			Whiletrue.stack[Whiletrue.first++]=sym_num;
        		}
       			else
       			{
       				flag=1;
        			fouterr<<"未定义变量"<<endl;  
	   			}
            }
            else
            {
                flag=1;
                fouterr<<"关系运算符后缺少标识符"<<endl; 
            }
        }
        else
        {
            Before();
        }
    }
    else if (lw[sym_num].num == 23)
    {
        Q();
        if (lw[sym_num].num == 24)
        {
            return;
        }
        else
        {
            flag=1;
            fouterr<<"布尔量中的布尔表达式缺少一个）"<<endl; 
        }
    }
    else
    {
        flag=1;
        fouterr<<"布尔量出错"<<endl;  
    }
}

//F→A，F｜A
bool F()//判断是否是标识符表 
{
	
    if (lw[sym_num].num == 37)
    {
    	symbollist.name[symbollist.name_count++]=sym_num;
        Next();
        if (lw[sym_num].num == 27)//,
        {
            Next();
            return F();
        }
        else
        {
            Before();
            return true;
        }
    }
    else
    {
        return false;
    }
}
 
//R→S+R｜S-R｜S
void R()//
{
	
	S();
    if (flag == 0)
    {
        Next();
        if (lw[sym_num].num == 19 || lw[sym_num].num == 20)
        {
			
			operator_confirm = 1;
			Add.first = 0;
			Add.stack[Add.first++] = sym_num;
            Next();
            R();
        }
        else
        {
            Before();
            return;
        }
    }
    else
    {
    	return;
    }
}

//S→T*S｜T/S｜T
void S()
{
	
	T();
    if (flag == 0)
    {
        Next();
        if (lw[sym_num].num == 21|| lw[sym_num].num == 22)
        {
			operator_confirm = 1;
			Add.first = 0;
			Add.stack[Add.first++] = sym_num;
            Next();
            S();
        }
        else
        {
            Before();
            return;
        }
    }
    else
    {
        return;
    }
}

//T→U｜（R）
void T()//
{
	if (lw[sym_num].num == 23)
    {
        Next();
        R();
        Next();
        if (lw[sym_num].num == 24)
        {
            return;
        }
        else
        {
            flag=1;
            fouterr<<"因子中算数表达式缺少）"<<endl;  
        }
    }
    else
    {
        U();
    }
}

//U→A｜CONSTANT｜FLOAT
void U()//
{
	int flag_work = 0;
	int tag = 0;
	int num_temp = 0;
	if (lw[sym_num].num == 2 || lw[sym_num].num == 3 || lw[sym_num].num == 37)
    {
    	if(lw[sym_num].num==2||lw[sym_num].num==3)
    	{
			if (operator_flag==1)
			{
				int a = Equal.first - 1;
				int temp = Equal.stack[a];
				flag_work = lookup(temp);
				if (flag_work == 1)
				{
					Equal.first--;
					Add.stack[Add.first++] = temp;
				}
				else
				{
					flag = 1;
					fouterr << "赋值变量未定义" << endl;
				}
				if (operator_confirm == 1)
				{
					Add.stack[Add.first++] = sym_num;
					Add.stack[Add.first++] = 120;
					putAdd(Add.first);
					Equal.stack[Equal.first++] = 120;
					Equal.stack[Equal.first++] = 100;
					putEqual(Equal.first);
				}
			}
			else
			{
				symbollist.num[symbollist.num_count++] = sym_num;
				Equal.stack[Equal.first++] = sym_num;
				Equal.stack[Equal.first++] = 100;
				putEqual(Equal.first);
			}
    		
		}
		else if (lw[sym_num].num == 37)
		{
			if (operator_flag == 1)
			{
				
				if (operator_confirm==1)
				{
					int a = Equal.first - 1;
					int temp = Equal.stack[a];
					flag_work = lookup(temp);
					if (flag_work == 1)
					{
						Equal.first--;
						Add.stack[Add.first++] = temp;
					}
					else
					{
						flag = 1;
						fouterr << "赋值变量未定义" << endl;
					}
					flag_work = lookup(sym_num);
					if (flag_work == 1)
					{
						Add.stack[Add.first++] = sym_num;
						Add.stack[Add.first++] = 120;
						putAdd(Add.first);
						Equal.stack[Equal.first++] = 120;
						Equal.stack[Equal.first++] = 100;
						putEqual(Equal.first);
					}
					else
					{
						flag = 1;
						fouterr << "赋值变量未定义" << endl;
					}
					
				}
				else
				{
					flag_work = lookup(sym_num);
					if (flag_work == 1)
					{
						Equal.stack[Equal.first++] = sym_num;
					}
					else
					{
						flag = 1;
						fouterr << "赋值变量未定义" << endl;
					}
				}
				
					
				
			}
			else
			{
				for (int i = 0; i < symbollist.name_count; i++)
				{
					if (strcmp(lw[symbollist.name[i]].word, lw[sym_num].word) == 0)
					{
						Equal.stack[Equal.first++] = sym_num;
						Equal.stack[Equal.first++] = 100;
						putEqual(Equal.first);
						flag_work = 1;
						tag = i;
						break;
					}
					else
						flag_work = 0;
				}
				if (flag_work == 1)
				{
					symbollist.num[symbollist.num_count++] = symbollist.num[tag];
				}
				else
				{
					flag = 1;
					fouterr << "赋值变量未定义" << endl;
				}
			}
			

		}
        return;
    }
    else
    {
        flag=1;
        fouterr<<"算数量出错或缺少算数量"<<endl; 
    }
}

// K→D｜O｜P
void K()
{
	if (lw[sym_num].num == 8)
    {
        Next();
        D();
    }
    else if (lw[sym_num].num == 14)
    {
		if_flag = 1;
    	Ifistrue.first=0;
    	Ifisfalse.first=0;
    	int q=sym_num,sort1;
    	q++;q++;
    	if(strcmp(lw[q].word,"<")==0)
    		Ifistrue.stack [Ifistrue.first++]=0;
    	else if(strcmp(lw[q].word,">")==0)
    		Ifistrue.stack [Ifistrue.first++]=1;
    	else if(strcmp(lw[q].word,">=")==0)
    		Ifistrue.stack [Ifistrue.first++]=3;
     	else if(strcmp(lw[q].word,"<=")==0)
    		Ifistrue.stack [Ifistrue.first++]=2;
		else if(strcmp(lw[q].word,"!=")==0)
    		Ifistrue.stack [Ifistrue.first++]=5;
		else if(strcmp(lw[q].word,"==")==0)
    		Ifistrue.stack [Ifistrue.first++]=7;
   		else
   		{
		}
		Ifisfalse.stack [Ifisfalse.first++]=4;
    	Ifisfalse.stack [Ifisfalse.first++]=6;
    	Ifisfalse.stack [Ifisfalse.first++]=6;
        Next();   
        O();
    }
    else if (lw[sym_num].num == 10)
    {
    	Whiletrue.first=0;
    	Whilefalse.first=0;
    	int q=sym_num,sort1;
    	q++;q++;
    	if(strcmp(lw[q].word,"<")==0)
    		Whiletrue.stack [Whiletrue.first++]=0;
    	else if(strcmp(lw[q].word,">")==0)
    		Whiletrue.stack [Whiletrue.first++]=1;
    	else if(strcmp(lw[q].word,">=")==0)
    		Whiletrue.stack [Whiletrue.first++]=3;
     	else if(strcmp(lw[q].word,"<=")==0)
    		Whiletrue.stack [Whiletrue.first++]=2;
		else if(strcmp(lw[q].word,"!=")==0)
    		Whiletrue.stack [Whiletrue.first++]=5;
		else if(strcmp(lw[q].word,"==")==0)
    		Whiletrue.stack [Whiletrue.first++]=7;
   		else
   		{
		}
		Whilefalse.stack [Whilefalse.first++]=4;
    	Whilefalse.stack [Whilefalse.first++]=6;
    	Whilefalse.stack [Whilefalse.first++]=6;
        Next();
        P();
    }
}

// O→ if Q then I| if Q then I else I
void O()//
{
	Q();
    if (flag == 0)
    {
        Next();
        if (lw[sym_num].num == 15)
        {
			then_flag = 1;
			else_flag = 0;
        	putIfistrue();
        	newlabel();
        	putIfisfalse();
        	newlabel();
            Next();
            four<<nlabel.newlabel<<labelorder[labelorder_f++]<<":"<<endl;
            I();
            Next();
            if (lw[sym_num].num == 16)
            {
				else_flag = 1;
				then_flag = 0;
            	putIfisfalse();
            	newlabel();
                Next();
                four<<nlabel.newlabel<<labelorder[labelorder_f++]<<":"<<endl;
                I();
				clear_if_flag();
                four<<nlabel.newlabel<<labelorder[labelorder_f++]<<":"<<endl;
            }
            else
            {
                Before();
                four<<nlabel.newlabel<<labelorder[labelorder_f]<<":"<<endl;
                return;
            }
        }
        else
        {
            flag=1;
        	fouterr<<"if...then语句缺少then"<<endl; 
        }
    }
    else
    {
        flag=1;
        fouterr<<"if语句布尔表达式出错"<<endl;  
    }
}

// P→ while Q do I
void P()
{
	labelorder_num = 0;
	labelorder_f = 0;
	newlabel();
	four << nlabel.newlabel << labelorder[labelorder_f] << ":" << endl;
	Q();
	if (flag == 0)
	{
		Next();
		if (lw[sym_num].num == 11)
		{
			putWhiletrue();
			newlabel();
			putWhilefalse();
			newlabel();
			Next();
			while (judge_while() == 1)
			{
				if (lw[sym_num].num == 8)
				{
					do_flag = 1;
					four << nlabel.newlabel << labelorder[++labelorder_f] << ":" << endl;
					Next();
					D();
					nlabel.newlabel_num = labelorder[0];
					putWhilefalse();
					four << nlabel.newlabel << labelorder[++labelorder_f] << ":" << endl;

				}
				else
				{
					four << nlabel.newlabel << labelorder[++labelorder_f] << ":" << endl;
					I();
					nlabel.newlabel_num = labelorder[0];
					four << nlabel.newlabel << labelorder[++labelorder_f] << ":" << endl;
				}

			}

		}
		else
		{
			flag = 1;
			fouterr << "while语句缺少do" << endl;
		}
		
	}
	
  
}


int main()
{
	char gettxt[1000];
	int i,j=0,k=0;
	symbollist.key_count=0;
    symbollist.name_count=0;
    symbollist.num_count=0;

	ifstream fin("F:\\shuchu.txt ", ios::in);//载入自己设定路径输入文件 
	for(i=0;i<1000;i++)
 		gettxt[i] =fin.get();//输入文件读取到数组a[]中
    fin.close();
    i=0;
	while(gettxt[i]=='<')
	{
		i++;k=0;
		if(gettxt[i+1]!=',')
		{
			lw[j].num=(gettxt[i]-'0')*10+(gettxt[i+1]-'0');
			i=i+3;
		}
		else 
		{
			lw[j].num=gettxt[i]-'0';
			i++;i++;
		}
		if(lw[j].num==30)
		{
			lw[j].word[k++]=gettxt[i];
 			i++;
		}
		while(gettxt[i]!='>')
 		{
 			lw[j].word[k++]=gettxt[i];
 			i++;
		}
		lw[j].word[k]='\0';
		i++;i++;
		j++;
	}
	countword=j;
	for(int x=0;x<j;j++)
	{
		lw[x].type=0;
	}
    A();
    if(flag==0)
        cout<<"编译成功"<<endl;
    else
        cout<<"编译出错"<<endl;
	four << "(" << sort++ << ")";
    four<<"<sys,_,_,_>"<<endl; 
	create_code_equal(sort);
 	fouterr.close();	
 	four.close();
	fcreate.close();
	system("pause");
 	return 0;
}






