#include<iostream>
#include<cmath>
using namespace std;

const int INF=1e9;
int n,a[1000011],l,r,f[10001][1001];

void prepare();
int getans(int l,int r);
int getans_ST(int l,int r);

int main()
{
    cin>>n;
    for (int i=1;i<=n;i++) cin>>a[i];
    prepare();
    while(1) {
        cin>>l>>r;
        cout<<getans_ST(l,r)<<endl;
    }
}

void prepare()
{
    for (int i=1;i<=n;i++) f[i][0]=a[i]; //��ʼ����iλ����iλ�����ֵΪa[i]����
    for (int j=1; 1+(1<<j)-1<=n; j++) {
    //i��СΪ1����i(min)+2^j-1�ܱ������г�Ϊ2^k���У���С�ڵ���n��
        for (int i=1; i<n; i++) {        //ö�ٱ�ͷ��
            if (i+(1<<j)-1<=n)           //���i+2^j-1��Խ�磬��Ƚ������������ֵ��
                f[i][j]=max(f[i][j-1], f[i+(1<<(j-1))][j-1]);
        }
    }
}

int getans(int l,int r)
{
    int ans=-INF;   //��ans��ʼ��������С��
    for (int j=log(r-l+1)/log(2); j>=0; j--) {
    //�˴�ע��log(n)��ָlog10(n)������Ӧ�û��׹�ʽ���㡣
    //����Ϊ��j=log2(r-l+1),��Ϊ�˼������nС������2^k��
        if (l+(1<<j)-1<=r) {        //�ж��Ƿ�Խ��
            ans=max(ans, f[l][j]);  //�Ƚϳ����ֵ
            l+=(1<<j);
            //�Ƚ������ֵ��Ӧ������������Ƚ����е��Ҷˣ��ԱȽ���һ�����С�
        }
    }
    return ans;
}

int getans_ST(int l,int r)
{
    int k=(int)log(r-l+1.0)/log(2.0);       //�������k��
    return max(f[l][k],f[r-(1<<k)+1][k]);   //�Ƚϳ����������е����ֵ��
}
