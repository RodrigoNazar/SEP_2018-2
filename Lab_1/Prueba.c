# include <stdio.h>
# include <stdlib.h>


/* ESTE ES UN COMENTARIO QUE NO EJECUTA EL PROGRAMA */

//FUNCIONES: void (no retorna nada)

void imprimeBasura()
{
	printf("\nSuma = %d",2+3);
	printf("\nEstamos dentro de una funcion");
}

void imprimeSuma(int a, int b)
{
	int sum = a+b;
	printf("\nEstamos sumando %d con %d, y el resultado es: %d",a,b, sum);
}


int main(){

	printf("\nHello World!\n");
	
	printf("\n******************\n");

	printf("\nMi rut es: %d.%d.%d-%d\n",19, 566, 950, 3);

	printf("\n******************\n");

	printf("\nEste es un numero decimal: %f",32.2);

	printf("\nEste es un numero muy grande: %ld",12345678);

	printf("\nEste es un numero muy chico: %lf",0.000001);

	printf("\nEste es un caracter: %c",'c'); //Necesariamente el caracter debe estar en '' comillas simples

	printf("\nEste es un string: %s","Hello World");

	printf("\nEl numero 16 en hexadecimal es: %x",16);

	puts("\nThis is my C programm");

	printf("\n******************\n");

	int age;

	age = 21;
	
	double pi=3.141592;

	printf("\nMi edad es: %d",age);

	printf("\nPi = %lf",pi);

	printf("\n******************\n");
	
	/*OPERACIONES:

	+, -, *, / (Division entera), % */
	
	int a=23,b=37;
	int suma;
	suma=a+b;

	printf("\n23+37 = %d",suma);

	int c=11,d=2;
	int division,resto;
	division=c/d;
	resto=c%d;
	
	printf("\nDivision: %d\nResto: %d",division,resto);

	printf("\n******************\n");

	//USUARIO E IF STATEMENTS

	int edad;

	printf("\n\nIngrese su edad: ");

	scanf("%d",&edad);

	if (edad>=18) {
		printf("\nUsted es mayor de edad!");
	}
	// Tambien esta else if(){} y los iguales se miran con ==
	else {
		printf("\nUsted es menor de edad!");
	}

	printf("\n******************\n");

	// Ternarios (Expresion logica) ? (retorno si es verdad):(retorno si es mentira)

	int mayor;
	mayor =(edad>age)?edad:age;
	
	printf("\nEl mayor es: %d",mayor);

	printf("\n******************\n");
	
	//SWITCH, entra en el case sólo si la variable ingresada es lo que se indica

	switch(edad){

		case 18:
			printf("\nHolas");
			break;
		default:
			printf("\nInvalido");
	}

	printf("\n******************\n");

	//LOOPS

	int i=0;

	do {
		printf("\nEl valor de i en el do-while loop es: %d",i);
		i++;
	} while (i<=10);

	printf("\n******************");

	int j=0;

	while(j<=10){
	
	printf("\nEl valor de j en el while loop es: %d",j);
	j++;
	}
	
	// do while corre primero el codigo sin revisar la condicion al principio, en cambio en el while se revisa la condicion y despues se ejecuta el codigo

	printf("\n******************");
	
	for(int a=0 ; a<=10 ; a++) /* (inicializacion ; condicion ; incremento), en la inicializacion podemos usar variables no declaradas*/
	{
	
	printf("\nEl valor de a en el for loop es: %d",a);

	}

	printf("\n******************\n");

	imprimeBasura();
	imprimeBasura();

	imprimeSuma(edad,age);

	
	printf("\n******************\n");

	



	return 0;
	


}