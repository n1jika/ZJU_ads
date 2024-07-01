#include <stdio.h>
int main()
{
    float SOME_VALUE_0,SOME_VALUE_1;
    SOME_VALUE_0 = 0.1;
    SOME_VALUE_1 = 1000;
    float x = SOME_VALUE_0;
    float sum = 0.0f;
    for(int i = 0; i < SOME_VALUE_1; ++i) sum += x;
    printf("%f\n", sum - 100.0f);
    SOME_VALUE_0 = 0.125;
    SOME_VALUE_1 =  800;
    x = SOME_VALUE_0;
    sum = 0.0f;
    for(int i = 0; i < SOME_VALUE_1; ++i) sum += x;
    printf("%f\n", sum - 100.0f);
	return 0;
}
