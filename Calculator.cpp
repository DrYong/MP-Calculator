#include<iostream>     //��׼���������ͷ�ļ���
#include<cstdlib>     //��׼exit()��������ͷ�ļ���
#include<iomanip>     //��׼����ʽͷ�ļ���
#include<stack>     //��׼ջͷ�ļ���
#include<gmpxx.h>     //GMP������ͷ�ļ���
#include<windows.h>    //Windowsͷ�ļ���
using namespace std;     //�����ռ䡣
stack<mpf_class> A;     //����ջ (����Ч����)��
stack<char> B;     //�ַ�ջ (�������)��
void color(unsigned long);     //������ɫ���á�
void about(void);    //���ڼ�������
void run(void);     //������㺯����
unsigned long priority(char);     //��������ȼ���
mpf_class computing(char);     //�����㺯����
mpf_class fmod(mpf_class, mpf_class);     //�Զ�����ģ���㺯����
mpf_class pow(mpf_class, unsigned long);     //�Զ���˷����㺯����
const mpf_class Max("1e+768",2560);     //2560λ���������Χ���ÿ�ѧ��������ʾ��
const mpf_class Min("-1e+768",2560);     //2560λ���������Χ���ÿ�ѧ��������ʾ��
const mpf_class PI("3.1415926535897932384626433832795",128);     //PI�ĸ߾���ֵ��
//////////////////////////////////////////////////////////////////////////////////////////
int main(){
    system("cls");   //����������������DOS���
    about();    //���ڼ�������
    for(;;)   //����ѭ����
        run();   //���û�����㺯����
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
void color(unsigned long x){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x|0);
}
//////////////////////////////////////////////////////////////////////////////////////////
void about(){
    color(8);    //���������������ɫ��
    cout<<"Calculator 2.6 Author: HuaJun Liu"<<endl;
}
//////////////////////////////////////////////////////////////////////////////////////////
mpf_class fmod(mpf_class x, mpf_class y){     //�Զ�����ģ���㺯����
    mpf_class n(0,2560);
    if(x<0)
        n=ceil(x/y);     //���XС����������ȡ����
    else
        n=floor(x/y);     //���X������������ȡ����
    return x-n*y;
}
//////////////////////////////////////////////////////////////////////////////////////////
mpf_class pow(mpf_class x, unsigned long y){    //�Զ���˷����㺯����
    unsigned long n;
    if(y>=0)
        n=(unsigned long)y;    //ǿ������ת���ɳ����͡�
    else
        n=(unsigned long)(-y);
    for(mpf_class z=mpf_class(1);;x*=x){    //�ȵݹ����Ч��ѭ�������㷨��
        if((n&1)!=0)
            z*=x;
        if((n>>=1)==0)
            return (y<0?mpf_class(1)/z:z);    //��ֹѭ������������ֵ��
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
void run(){
    int c=0,d=0,bk=0;
    mpf_class P(0,2560),Z(0,2560),Re(0,2560);
    char ch=0,ab=0;     //"ab"�������������һ�ν�ջ�������ֻ����������
    cin.clear(); cin.sync();      //�����������
    while(!A.empty())
        A.pop();       //�������ջ��
    while(!B.empty())
        B.pop();       //��������ջ��
    color(8);    //���������������ɫ��
    cout<<"Import: ";
    while(cin){      //����������Ƿ���á�
        color(7);    //���������������ɫ��
        cin.get(ch);      //������ʽ�����ܶ�ȡ�ո�������з����س�������
        switch(ch){
        case '(':
            if(ab!='A'){     //������ǰ���������֡�
                B.push(ch); bk++;
                break;
            }
            color(4);    //���������������ɫ��
            cerr<<"Expression Error"<<endl;
            return;
        case ')':
            if(bk!=0 && ab=='A'){    //�����ջ�б�������������������ǰ���������֡�
                while(B.top()!='('){
                    try{     //�쳣���塣�������׳��쳣����䣩
                        A.push(computing(B.top()));    //��������쳣�������ڲ����׳��쳣��
                    }catch(mpf_class){     //���񲢴����쳣��
                        color(4);    //���������������ɫ��
                        cerr<<"Divisor Is Zero"<<endl;
                        return;
                    }
                    B.pop();     //�������ջ��
                }
                B.pop(); bk--;     //�����ų�ջ��
                break;
            }
            color(4);    //���������������ɫ��
            cerr<<"Expression Error"<<endl;
            return;
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '^':
            if(ch=='-' && ab!='A'){     //����һ�ν�ջ�������������ǰ'-'Ϊ������š�
                cin.putback(ch);     //�˺�������ǰ�ַ��ͻص��������С�
                if(cin>>P){          //����ȡ�������Ƿ���Ч��
                    A.push(P); ab='A';     //��ȡ�����ֽ�ջ��"ab"������¼������
                    break;
                }
                color(4);    //���������������ɫ��
                cerr<<"Invalid Number"<<endl;
                return;
            }else if(ab!='A'){     //�����ǰ����������֡�
                color(4);    //���������������ɫ��
                cerr<<"Expression Error"<<endl;
                return;
            }
            while(!B.empty() && B.top()!='('){   //�����ջΪ�ջ�ջ��Ԫ��Ϊ������ʱֹͣѭ����
                c=priority(B.top());
                d=priority(ch);
                if(c>=d){
                    try{     //�쳣���塣�������׳��쳣����䣩
                        A.push(computing(B.top()));    //��������쳣�������ڲ����׳��쳣��
                    }catch(mpf_class){     //���񲢴����쳣��
                        color(4);    //���������������ɫ��
                        cerr<<"Divisor Is Zero"<<endl;
                        return;
                    }
                    B.pop();
                }else
                    break;     //����ѭ����
            }
            B.push(ch); ab='B';     //�������ջ��"ab"������¼������
            break;
        case 'A':
            if(ab=='A'){     //��Ƿ�ǰ����������֡�
                Re=A.top(); A.pop();     //������ջ��ջ��Ԫ�ظ���Re��Ȼ���ջ��
                A.push(abs(Re));     //abs(x) x�ľ���ֵ��
                break;
            }
            color(4);    //���������������ɫ��
            cerr<<"Expression Error"<<endl;
            return;
        case 'S':
            if(ab=='A'){     //��Ƿ�ǰ����������֡�
                Re=A.top(); A.pop();     //������ջ��ջ��Ԫ�ظ���Re��Ȼ���ջ��
                A.push(sqrt(Re));     //sqrt(x) x��ƽ������
                break;
            }
            color(4);    //���������������ɫ��
            cerr<<"Expression Error"<<endl;
            return;
        case 'P':
            if(ab!='A'){     //��Ƿ�ǰ��������ַ�����Ϊ�ա�
                A.push(PI); ab='A';      //��ȡ�����ֽ�ջ��"ab"������¼������
                break;
            }
            color(4);    //���������������ɫ��
            cerr<<"Expression Error"<<endl;
            return;
        case '\n':
        case '\r':
        case '=':
            if(B.empty() && A.empty()){
                system("cls");
                about();     //�������ӡ���������˵����
                return;
            }else if(bk!=0 || ab!='A'){    //�Ⱥ�ǰ���ܳ��������źͲ���û�����֡�
                color(4);    //���������������ɫ��
                cerr<<"Expression Error"<<endl;
                return;
            }
            while(!B.empty()){
                try{     //�쳣���塣�������׳��쳣����䣩
                    A.push(computing(B.top()));    //��������쳣�������ڲ����׳��쳣��
                }catch(mpf_class){     //���񲢴����쳣��
                    color(4);    //���������������ɫ��
                    cerr<<"Divisor Is Zero"<<endl;
                    return;
                }
                B.pop();
            }
            Z=A.top(); A.pop();	  //������һ������ջ��
            if(Max>Z && Min<Z){     //������Ƿ񳬳�������ݷ�Χ��
                color(8);    //���������������ɫ��
                cout<<"Amount: ";
                color(2);    //���������������ɫ��
                cout<<fixed<<setprecision(4)<<Z<<endl;
                return;
            }
            color(4);    //���������������ɫ��
            cerr<<"Overflow Error"<<endl;
            return;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.':
            cin.putback(ch);     //�˺�������ǰ�ַ��ͻص��������С�
            if(ab=='A'){     //��һ�ν�ջ��������֣���˵�����ʽ����
                color(4);    //���������������ɫ��
                cerr<<"Expression Error"<<endl;
                return;
            }else if(cin>>P){      //����ȡ�������Ƿ���Ч��
                A.push(P); ab='A';      //��ȡ�����ֽ�ջ��"ab"������¼������
                break;
            }
            color(4);    //���������������ɫ��
            cerr<<"Invalid Number"<<endl;
            return;
        case 'Q':
            exit(1);    //�˳�����
        default:
            color(4);    //���������������ɫ��
            cerr<<"Invalid Character"<<endl;
            return;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
unsigned long priority(char x){
    switch(x){
    case '+':
    case '-': return 0;     //����������ȼ����Ϊ���֡�
    case '*':
    case '/':
    case '%': return 1;     //����������ȼ����Ϊ���֡�
    case '^': return 2;     //����������ȼ����Ϊ���֡�
    default: exit(1);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
mpf_class computing(char x){
    mpf_class a(0,2560),b(0,2560);
    switch(x){
    case '+':
        b=A.top(); A.pop();     //������ջ��ջ��Ԫ�ظ���b��Ȼ���ջ��
        a=A.top(); A.pop();     //������ջ��ջ��Ԫ�ظ���a��Ȼ���ջ��
        return a+b;
    case '-':
        b=A.top(); A.pop();     //������ջ��ջ��Ԫ�ظ���b��Ȼ���ջ��
        a=A.top(); A.pop();     //������ջ��ջ��Ԫ�ظ���a��Ȼ���ջ��
        return a-b;
    case '*':
        b=A.top(); A.pop();     //������ջ��ջ��Ԫ�ظ���b��Ȼ���ջ��
        a=A.top(); A.pop();     //������ջ��ջ��Ԫ�ظ���a��Ȼ���ջ��
        return a*b;
    case '/':
        b=A.top(); A.pop();     //������ջ��ջ��Ԫ�ظ���b��Ȼ���ջ��
        a=A.top(); A.pop();     //������ջ��ջ��Ԫ�ظ���a��Ȼ���ջ��
        if(b!=0)
            return a/b;
        throw b;    //�׳��쳣��
    case '%':
        b=A.top(); A.pop();     //������ջ��ջ��Ԫ�ظ���b��Ȼ���ջ��
        a=A.top(); A.pop();     //������ջ��ջ��Ԫ�ظ���a��Ȼ���ջ��
        if(b!=0)
            return fmod(a,b);     //�Զ�����ģ���㺯����
        throw b;    //�׳��쳣��
    case '^':
        b=A.top(); A.pop();     //������ջ��ջ��Ԫ�ظ���b��Ȼ���ջ��
        a=A.top(); A.pop();     //������ջ��ջ��Ԫ�ظ���a��Ȼ���ջ��
        return pow(a,b.get_ui());    //�Զ���˷����㺯����
    default: exit(1);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
