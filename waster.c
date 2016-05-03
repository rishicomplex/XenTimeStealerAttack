#include <stdio.h>

typedef long long int ll;
#define LARGE 1000000000000LL

int main() {
	ll sum = 0;
	ll i;
	for(i = 0; i < LARGE; i++) {
		sum += i;
	}
	printf("%lld\n", sum);
	return 0;
}
