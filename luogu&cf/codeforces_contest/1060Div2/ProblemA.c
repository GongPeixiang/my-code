#include<stdio.h>
int main(void)
{
	int  t = 0;
	scanf("%d",&t);
	int i,j,m;
	for (i = 0; i < t; i++){
		int cnt = 0;
		int n = 0, k = 0;
		scanf("%d %d",&n,&k);
		getchar();
		/*这个getchar()用来消耗掉scanf()的换行符!*/
		char str[1000];
		int protect[1000] = {};
		for (j = 0; j < n; j++){
			protect[j] = 0;
		}
		int judge = 0;
		fgets(str,sizeof(str),stdin);
		/*第一部分，从0~k-1*/
		for (j = 0; j < k-1; j++){
			judge = 1;
			for (m = 0; m < j; m++){
				if (str[m] == '1'){
					judge = 0;
				}
			}
			if (str[j]=='1' && judge==1 && protect[j]==0){
				cnt++;
				protect[j] = 1;
			}
		}
		for (j = k-1; j < n; j++){
			judge = 1;
			for (m = j+1-k; m < j; m++){
				if (str[m] == '1'){
					judge = 0;
				}
			}
			if (str[j]=='1' && judge==1 && protect[j]==0){
				cnt++;
				protect[j] = 1;
			}
		}
		printf("%d\n",cnt);
	}
	return 0;
}