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
    for (int i=1;i<=n;i++) f[i][0]=a[i]; //初始化第i位到第i位的最大值为a[i]本身。
    for (int j=1; 1+(1<<j)-1<=n; j++) {
    //i最小为1，故i(min)+2^j-1能遍历所有长为2^k序列，且小于等于n。
        for (int i=1; i<n; i++) {        //枚举表头。
            if (i+(1<<j)-1<=n)           //如果i+2^j-1不越界，则比较两端序列最大值。
                f[i][j]=max(f[i][j-1], f[i+(1<<(j-1))][j-1]);
        }
    }
}

int getans(int l,int r)
{
    int ans=-INF;   //将ans初始化成无限小。
    for (int j=log(r-l+1)/log(2); j>=0; j--) {
    //此次注意log(n)是指log10(n)，所以应用换底公式计算。
    //至于为何j=log2(r-l+1),是为了计算出比n小的最大的2^k。
        if (l+(1<<j)-1<=r) {        //判断是否越界
            ans=max(ans, f[l][j]);  //比较出最大值
            l+=(1<<j);
            //比较完最大值，应将左端移至所比较序列的右端，以比较下一个序列。
        }
    }
    return ans;
}

int getans_ST(int l,int r)
{
    int k=(int)log(r-l+1.0)/log(2.0);       //求出最大的k。
    return max(f[l][k],f[r-(1<<k)+1][k]);   //比较出两个序列中的最大值。
}
