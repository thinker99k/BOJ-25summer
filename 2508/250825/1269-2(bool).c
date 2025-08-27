#include <stdio.h>
#include <stdint.h>
#include <string.h>

char arr[100000001];

int numa, numb, ans, x;

int main() {
    memset(arr, 1, 100000001);

    scanf("%d %d\n", &numa, &numb);
    ans = numa;

    for (int i = 0; i < numa; i++) {
        scanf("%d", &x);
        getchar();
        arr[x] = -1;
    }

    for (int i = 0; i < numb; i++) {
        scanf("%d", &x);
        ans += (int) arr[x];
    }

    printf("%d", ans);
}