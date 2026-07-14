#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int  t = 0;
	scanf("%d",&t);
	int i,j,k;
	for (i = 0; i < t; i++){
		int n = 0;
		scanf("%d",&n);
		int *num = NULL;
		num = (int *) calloc((n+1),sizeof(int));
		for (j = 1; j <= n; j++){
			scanf("%d",&num[j]);
		}
		int cnt = 0;
		int *judge = NULL;
		judge = (int *) calloc((n+1),sizeof(int));
		for (j = 2; j < n; j += 2){
			if (num[j]<=num[j-1] || num[j]<=num[j+1]){
					judge[j] = 0;
			}else{
					judge[j] = 1;
			}
		}
		if (n%2 == 0){
			if (num[n] <= num[n-1])
				judge[n] = 0;
		}

		for (j = 2; j < n; j += 2){
			if (judge[j] == 0){
				int max = num[j];
				for (k = j-1; k >= 1; k--){
					if (num[k] > max){
						max = num[k];
					}
				}
				num[j] = max;
				judge[j] = (num[j]>num[j-1] && num[j]>num[j+1]);
			}else{
				continue;
			}
		}
		if (n%2 == 0){
			int max = num[n];
			for (j = 1; j < n; j++){
				if (num[j] > max){
					max = num[j];
				}
			}
			num[n] = max;
			judge[n] = (num[n] > num[n-1]);
		}

		if(n%2 == 0){
			if(judge[n] == 0){
				while(num[n-1] >= num[n]){
					num[n-1]--;
					cnt++;
				}
			}
		}
		for (j = n-1; j >= 1; j--){
			if (j%2 == 1){
				continue;
			}else{
				if (judge[j] == 1){
					continue;
				}else{
					while (num[j-1] >= num[j]){
						num[j-1]--;
						cnt++;
					}
					while (num[j+1] >= num[j]){
						num[j+1]--;
						cnt++;
					}
				}
			}
		}
		printf("%d\n",cnt);
		free(judge);
		free(num);
	}

	return 0;
}