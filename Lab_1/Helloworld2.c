# include <stdio.h>

int factorial(int a)
{
	if (a<1)
	{
		return 1;
	}
	else{
		return a*factorial(a-1);
	}

}
int fibonacci(int a)
{
	if (a==0)
	{
		return 0;
	}
	else if (a==1){
		return 1;
	}
	else{
		return fibonacci(a-2)+fibonacci(a-1);
	}

}

int suma_digitos(int n){
    if (n/10==0){
        return n;
	}
    else{
        return suma_digitos(n/10)+suma_digitos(n%10);
	}
}

int elevado(int b, int e){
    if (e==0){
        return 1;
	}
    else{
        return b*elevado(b,e-1);
	}
}

int multiplicado(int a,int b){
    if (b==0){
        return 0;
	}
    else{
        return a+multiplicado(a,b-1);
	}
}


void main(){

	printf("\n       *******************\n       *  Hello, World!  *\n       *******************\n");

	printf("\n\n***********************************\n*                                 *\n* Bienvenido al portal recursivo! *\n*                                 *\n***********************************");
	
	printf("\n\nAqui podra hacer distintos computos de manera recursiva, las opciones son: \n1) Factorial\n2) Fibonacci\n3) Suma de los digitos de un numero\n4) Elevar un numero a otro\n5) Multiplicar dos numeros");

	int opcion;
	
	printf("\n\nIngrese una opcion: ");

	scanf("%d",&opcion);

	if (opcion==1){
		int numero;
		printf("\n\nEligio la opcion Factorial, a que numero quiere calcular su factorial?: ");
		scanf("%d",&numero);
		printf("\n\n El resultado de %d! es: %d\n",numero,factorial(numero));
	}

	else if(opcion==2){
		int numero;
		printf("\n\nEligio la opcion Fibonacci, que elemento de la sucesion quiere obtener?: ");
		scanf("%d",&numero);
		printf("\n\nEl elemento que ocupa la posicion %d de la sucesion de Fibonacci es: %d\n",numero,fibonacci(numero));

	}

	else if(opcion==3){
		int numero;
		printf("\n\nEligio la opcion Suma de los Digitos de un numero, la suma de los elementos de que numero desea calcular?: ");
		scanf("%d",&numero);
		printf("\nLa suma de los elementos del numero %d es: %d\n",numero,suma_digitos(numero));

	}

	else if(opcion==4){
		int base,exponente;
		printf("\n\nEligio la opcion Elevado, cual es la base de su operacion?: ");
		scanf("%d",&base);
		printf("\nY cual es el exponente?: ");
		scanf("%d",&exponente);
		printf("\nFinalmente %d elevado a %d es: %d\n",base,exponente,elevado(base,exponente));
	
	}
	
	else if (opcion==5){
		int a,b;
		printf("\n\nEligio la opcion Multiplicar, que numero desea multiplicar?: ");
		scanf("%d",&a);
		printf("\nCon que otro numero?: ");
		scanf("%d",&b);
		printf("\nFinalmente %d multiplicado con %d es: %d\n",a,b,multiplicado(a,b));
	}

	return 0;


}