# include <stdio.h>
void print_stars(int);

int main()
{
int i;
for (i= 0; i < 5; i++)
print_stars(5);
return 0;
}
void print_stars (int n)
{
int i;
for (i= 0; i < n; i++)
printf ("*");
printf ("\n");
}