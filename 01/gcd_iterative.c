#include <stdio.h>

int gcd(int m, int n) {
    int r;
    do {
        r = m % n;
        m = n;
        n = r;
    } while (r != 0);
    return m;
}

int main() {
    int m, n;

    printf("Type in m...\n");
    scanf("%d", &m);

    printf("Type in n...\n");
    scanf("%d", &n);

    printf("GCD: %d.\n", gcd(m, n));

    return 0;
}
