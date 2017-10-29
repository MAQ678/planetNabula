#include<bits/stdc++.h>
using namespace std;
#define pb      push_back
#define _       ios_base::sync_with_stdio(false);
#define ct      cin.tie(NULL);
#define ll      long long
#define eps     1e-10
#define ms(n,i) memset(n,i,sizeof n)
#define pi      2*acos(0)
#define inf     1<<30
#define fr(i,n) for(i=0;i<n;i++)
#define fr1(i,n)for(i=1;i<=n;i++)
#define abs(x)  ((x<0)?-(x):x)
#define MAX 30005
#define sp(i)      cout<<fixed<<setprecision(i)
//STL
typedef      vector<int> vi;
typedef      vector<ll> vl;
typedef      pair<int,int>ii;
#define mp      make_pair
#define ft      first
#define sd      second
#define IT      iterator
#define pr(c,x) ((c).find(x)!=(c).end())
#define sz(a) int((a).size())
#define all(c)  c.begin(), c.end()
#define tr(c,i) for(__typeof((c).begin()) i=(c).begin();i!=c.end();i++)
#define vpresent(c,x) (find(all(c),x)!=(c).end())
#define eb      emplace_back
//


//input output
#define sf      scanf
#define pf      printf

#define sf1(a)  sf("%d",&a)
#define sf2(a,b)  sf("%d%d",&a,&b)
#define sf3(a,b,c)   sf("%d%d%d",&a,&b,&c)

#define nl cout<<"\n"
//eof

//seg tree
#define lc      (s+e)>>1
#define rc      (lc)+1
#define Ln      n<<1
#define Rn      (Ln)|1
//end of seg tree
ll M=100000007;
inline ll pow(ll n,ll m)
{
    ll z=1;
    while(m--)z*=n;
    return z;
}

inline ll bigmod(ll b,ll p)
{
    ll res=1;
    for(;p;p>>=1,b=b*b%M)if(p&1)res=res*b%M;
    return res;
}
inline ll InverseM(ll n)
{
    return bigmod(n,M-2);
}




//int dx[]={1,0,-1,0};int dy[]={0,1,0,-1}; //4 Direction
//int dx[]={1,1,0,-1,-1,-1,0,1};int dy[]={0,1,1,1,0,-1,-1,-1};//8 direction
//int dx[]={2,1,-1,-2,-2,-1,1,2};int dy[]={1,2,2,1,-1,-2,-2,-1};//Knight Direction
//int dx[]={2,1,-1,-2,-1,1};int dy[]={0,1,1,0,-1,-1}; //Hexagonal Direction

vector<string> plainString;
vector<int> stringLength, revSValue;

void breakOnSpace(string s)
{
	stringstream ss;
	ss << s;
	while(ss>>s){
		plainString.pb(s);
		stringLength.pb(s.length());
	}
	ss.clear();
}
int TakeInput()
{
	string plainText;
	int v;
	cout<<"Enter the plain-text: ";
	getline(cin,plainText);
	cout<<"Give the value of v: ";
	cin>>v;
	breakOnSpace(plainText);
    return v;
}


int calcRevBinary()
{
	int charValue,revCharValue,minimum=inf;
	string bitString, residue;
	for(string s:plainString)
	{
	  //  cout<<s<<endl;
		for(char ch:s)
		{
			charValue = (int)ch;
			bitString = bitset<8>(charValue).to_string();
			reverse(all(bitString));
		//	cout<<ch<<" "<<bitString<<endl;
			revCharValue = bitset<8> (string(bitString)).to_ulong();
			//if(revCharValue == charValue)
			//	residu
			revSValue.pb(revCharValue);
			if(revCharValue>=8)
                minimum = min(minimum,revCharValue);
		}
	}
	return  minimum;
}
vector<int> unChanged;

int pOGen(string s)
{
    int result = bitset<8> (string(s)).to_ulong();
    result++;   //2's complement
    return bitset<8> (result).to_ulong();   //check if exceed to 9 th bit
}

int phaseOne(int val, int x)
{
    bitset<4> quo (val/x);
    bitset<4> rem (val%x);
  //  cout<<quo.to_string()<<endl;
    quo.flip();//1st complement
    rem.flip();//||
    string s=quo.to_string();
  //  cout<<s<<endl;
    s+=rem.to_string();
    return pOGen(s);
//    int result = bitset<8> (string(s)).to_ulong();
//    result++;   //2's complement
//    return bitset<8> (result).to_ulong();   //check if exceed to 9 th bit

}
int phaseExtra(int val)
{
    bitset<8> al (val);
    al.flip();
    return pOGen(al.to_string());
}
int gen2(int val)
{
    return val+plainString.size();
}
int phaseTwo(int val, int x,int type)
{
    if(type == 1)
    {
        return gen2(val);
    }
    bitset<4> quo (val/x);
    bitset<4> rem (val%x);
    string s=quo.to_string();
    s+=rem.to_string();
    return gen2(bitset<8>(string(s)).to_ulong());
}

int phaseS(int val, int& v,int minimum)
{
    if(v>0)
        {
            v--;
            return phaseOne(val, minimum);
        }
    else
    {
        int got=phaseTwo(val, minimum,0);
     //   cout<<val<<" "<<got<<endl;
        return got;
    }
}

string calcRemQuo(int minimum,int v)
{
    string cipherText;
    int got;
    for(int val:revSValue)
    {
     //   cout<<(char)val<<endl;
        if((val%minimum>=16)||(val/minimum>=16))
        {
            unChanged.pb(val);
            if(v>0) got = phaseExtra(val),v--;
            else got = phaseTwo(val,minimum,1);
      //      cout<<got<<endl;
            cipherText+=(char)got;
        }
        else
        {
            got=phaseS(val,v,minimum);
     //       cout<<got<<endl;
            cipherText+=(char)got;
        }

    }
   /* for(int val:unChanged)
    {
        got=phaseS(val,v,minimum);
      //  cout<<got<<endl;
        cipherText+=(char)got;
    }
    */
    return cipherText;
}


void print(string cipherText)
{
    cout<<"Cipher-Text is: "<<cipherText<<endl;
}

ll keyGen(int divisor)
{
    ll val=plainString.size();
    string revDiv=bitset<64>(divisor).to_string();
    ///reverse(all(revDiv));
   // cout<<revDiv<<endl;
   // cout<<bitset<64>(string(revDiv)).to_ulong()<<endl;
   ll z=0,twoP=1;
   for(char ch:revDiv)
   {
       if(ch=='1')z+=twoP;
       twoP<<=1;
   }
  // cout<<z<<endl;
   val^= z;
//cout<<ak.to
  //  val^=ak.to_ulong();

    bitset<64>wk (val);
    wk.flip();
    revDiv=wk.to_string();
    val=0,twoP=1;
   for(char ch:revDiv)
   {
       if(ch=='1')val+=twoP;
       twoP<<=1;
   }

    //val=wk.to_ulong();
    val++;

    return val;

}
int frstCom(int val)
{
    bitset<8>ak (val);
    ak.flip();
    return ak.to_ulong();
}

string calcRemQuo1(int m,int v)
{
    string cT,after,Quo,Rem;
    int left=v,qr,val,i,ck;
    fr(i,revSValue.size())
    {
        val=revSValue[i];
        ck=0;
        if((val%m>15)||(val/m>15))
        {
            qr=val;
           val^=v;
          // cout<<i<<" "<<val<<" ";
           after+=(char)val;
           ck=1;

        }
        else
        {
            Quo=bitset<4>(val/m).to_string();
            Rem=bitset<4>(val%m).to_string();
            qr=bitset<8>(string(Quo+Rem)).to_ulong();
        }
        if(i<(v-1))
            qr=frstCom(qr);
        qr^=v;
       // cout<<qr<<" ";
        cT+=(char)qr;

        /*val=revSValue[i];
       // else
        {
            qr=val;

            if(i<(v-1))
            {
                bitset<8>ak (val);
                ak.flip();
                qr=ak.to_ulong();
            }
            qr^=v;
            cout<<val<<" "<<qr<<" kdkfdf ";
            cT+=(char)qr;
        }
        */
    }
//    cout<<cT;nl;
   // nl;
    cT+=after;
  //  cout<<cT;nl;
    return cT;
}

string table4(int v)
{
    string cT;
    for(int val:stringLength)
    {
        val^=v;
        bitset<8>ak (val);
        ak.flip();
        val=ak.to_ulong();
        //cout<<val<<" ";
        cT+=(char)val;
    }
   // cout<<cT<<"555"<<endl;
    //nl;
    return cT;
}
//The secret code is @Nabu$%2#*()
int main()
{
       // freopen("D:\\Coding\\in.txt","r",stdin);
        //freopen("D:\\out.txt","w",stdout);
	int v = TakeInput();
	int minimum = calcRevBinary();
	string cipherText = calcRemQuo1(minimum, v);
	string tab4=table4(v);

	//cipherText=table4(v)+cipherText;
	cout<<"Cipher-Text is: ";
	cout<<tab4<<endl;
	cout<<cipherText<<endl;

	cout<<"Key is: "<<keyGen(minimum)<<endl;

	//for(char ch:tab4)cout<<ch<<" ";
	//for(char ch:cipherText)cout<<ch<<" ";
	//print(tab4+cipherText);
    return 0;
}
