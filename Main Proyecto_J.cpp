#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ESTRUCTURAS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

struct tPolinomio{  //Estructura donde se guardarán los polinomios ya convertidos.
	int grado;
	vector<double>coef; 
};

struct tPolinomio_String{  //Estructura donde se guardarán los polinomios en forma de strings.
	vector<string>grado;
	vector<string>coef;
};

struct tPolinomio_Previo{ //Estructura donde se guardarán los polinomios un paso previo al final.
	vector<string>grado;
	vector<string>coef;
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FUNCIONES %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

string Eliminar_Espacios(string); //función que te permite eliminar los espacios en blanco de un string.
bool Caracteres_Desconocidos(string); //función que detecta caracteres desconocidos en el string.
tPolinomio_String Clasificacion(string); //función que clasifica los elementos del string.
string Convertir_A_String(vector<char>); // función que une un vector de chars en un sólo string.
double Convertir_A_Double(string); //función que convierte un string a un double.
int Encontrar_Grado(vector<string>); //función que encuentra el grado más alto entre los polinomios.
void Ordenar_Polinomios(vector<tPolinomio> &coef, vector<tPolinomio_String>); //función por referencia que ordena los polinomios.

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  MAIN  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


int main() {
	int Num_Poli, opcion, grado_maximo=0;
	string polinomio;
	bool seguridad;
	
	cout<<"Bienvenido a la calculadora de polinomios Poli_Express \"nombre por definirse\"..."<<endl;
	cout<<"----------------------------------------------------------------------------------"<<endl;
	do
	{
	do
	{
		seguridad=true; //se inicializa el booleano en "true".
		cout<<"Ingrese el numero de polinomios que desea sumar: ";
		cin>>Num_Poli;
		if(cin.fail() || Num_Poli<1) //si el numero ingresado no es un entero mayor a 0:
		{
			seguridad=false; //el booleano se convierte a falso
			cout<<endl<<"El dato ingresado no es un numero de polinomios valido. Vuelva a intentar: "<<endl;
			cout<<"----------------------------------------------------------------------------------"<<endl;
			cin.clear(); //se utiliza para eliminar el estado de fallo en el cin anterior.
			cin.ignore(1000, '\n'); // se ignoran los primeros 1000 caracteres del cin o hasta que se encuentre un enter.
			                        // Se utiliza el "1000" porque es un rango seguro, pero debe haber otra forma más elegante.
		}
	}
	while(seguridad==false); // se repide el "do" hasta que se ingrese correctamente el número de polinomios.
				
	cin.ignore(); //necesario para el getline.
	
	vector<tPolinomio>Polinomios(Num_Poli+1); // se crea el vector de estructuras donde se guardarán los polinomios finales más un espacio donde se guardará el polinomio resultado.
	vector<tPolinomio_String>Polinomios_String(Num_Poli); // se crea el vector de estructuras donde se guardarán los polinomios en forma de string.
	vector<int>Grados_Maximos(Num_Poli); //se crea el vector que almacena el mayor grado para cada polinomio.
	vector<tPolinomio_Previo>Polinomios_Previos(Num_Poli); //se crea el vector de estructuras que se utilizará previo al paso final.
	
	cout<<endl<<"----------------------------------------------------------------------------------"<<endl;
	cout<<"----------------------------------------------------------------------------------"<<endl;
	cout<<endl<<"Por favor ingresar los polinomios en alguna de las siguientes formas: \n1)axb+cxd+exf+... \n2)a*xb+c*xd+e*xf+..."<<endl; //se especifica las formas.
	
	cout<<endl<<"----------------------------------------------------------------------------------"<<endl;
		
	for(int i=0;i<Num_Poli;i++)
	{	
		cout<<"----------------------------------------------------------------------------------"<<endl;
		do
		{
			seguridad=true; // para cada iteración se inicializa el booleano en true. 
			cout<<"Ingrese el polinomio "<<i+1<<" :";
			getline(cin,polinomio); //se recibe la cadena con getline.
			polinomio=Eliminar_Espacios(polinomio); //Se llama a la función que elimina todos los espacios del string.
			seguridad=Caracteres_Desconocidos(polinomio); // La función Caracteres_Desconocidos retorna un booleano. Si es falso, existen caracteres desconocidos.	
			
			if(seguridad==false) //si la función encontró caracteres desconocidos:
			{
				cout<<"Se ha detectado un caracter desconocido. Por favor, ingresar de nuevo: "<<endl;
				cout<<"----------------------------------------------------------------------------------"<<endl;
				continue; //como el booleano es "false", comienza la siguiente iteración (nuevo intento).
			}
			
			Polinomios_String.at(i)=Clasificacion(polinomio); //la posición i del vector Polinomios_String se clasifica según sus elementos.
						
			for(int j=0;j<Polinomios_String.at(i).grado.size();j++) //para cada uno de los grados del Polinomio_String:
			{
				if(Polinomios_String.at(i).grado.at(j)=="-1") //si se encontró el valor "-1" por un error fatal durante la función :
				{
					seguridad=false; //el booleano cambia a "falso".
					break; //deja de revisar los demás grados.
				}
			}
			if(seguridad==false) //si el código encontró grados incompatibles (errores de redacción):
			{
				cout<<"Se ha detectado un error en su polinomio. Por favor, ingresar de nuevo: "<<endl;
				cout<<"----------------------------------------------------------------------------------"<<endl;
				continue; //como el booleano es "false", comienza la siguiente iteración (nuevo intento).
			}
			
			Grados_Maximos.at(i)=Encontrar_Grado(Polinomios_String.at(i).grado); //Se encuentra el grado máximo para cada uno de los polinomios.			
		}	
		while(seguridad==false); // se repite el "do" hasta que no haya ningún error. 		
	}
	
	for(int i=0;i<Num_Poli;i++) //para los (Num_Poli) polinomios que se han introducido:
	{
		if(Grados_Maximos.at(i)>grado_maximo) //entre los grados más altos de cada polinomio se elije al más alto.
		{
			grado_maximo=Grados_Maximos.at(i);
		}
	}
	
	cout<<"----------------------------------------------------------------------------------"<<endl;
	cout<<"El polinomio suma es de grado: "<<grado_maximo<<endl; //se imprime el grado más alto como el grado total del polinomio resultado.
	
	
	for(int i=0;i<=Num_Poli;i++) //para todos los vectores de estructura tPolinomio:
	{
		Polinomios.at(i).grado=grado_maximo; //todos marcan su campo grado con el valor del máximo grado.
		Polinomios.at(i).coef.resize(grado_maximo+1); //se crean (grado_maximo + 1) espacios libres (inicializados en 0) para llenar.		
	}
	
	Ordenar_Polinomios(Polinomios,Polinomios_String); //le llama a la función que rellena los campos de Polinomios con la información de Polinomios_String.
			
	
	for(int j=0;j<=grado_maximo;j++) //se realiza la suma del polinomio final grado por grado (Por eso primero se usa j y luego i).
	{
		for(int i=0;i<Num_Poli;i++)
		{
			Polinomios.at(Num_Poli).coef.at(j)=Polinomios.at(Num_Poli).coef.at(j)+Polinomios.at(i).coef.at(j);
		    //la posición j del nuevo polinomio es equivalente a la posición j del polinomio antes del cambio + la posición j de los polinomios i.
		}
	}
	
	int k=0; //se inicializa un entero que servirá como un interruptor para el primer coeficiente.
	cout<<"El resultado es: ";

	for(int j=0;j<=grado_maximo;j++) //para todos los elementos del polinomio resultado:
	{
		if(k==0 && Polinomios.at(Num_Poli).coef.at(j)!=0) //este if reconoce al primer coeficiente útil (no es 0).
		{
			if(j==0) //si equivale a la posición 0 (constante) sólo se imprime el coeficiente.
			{
				cout<<Polinomios.at(Num_Poli).coef.at(j);
			}
			else if(j==1) //si equivale a la posición 1 (x) se imprime el coeficiente y una x (no grado).
			{
				cout<<Polinomios.at(Num_Poli).coef.at(j)<<"x";
			}
			else //en cualquier otro caso, se imprime el coeficiente y su grado correspondiente.
			{
				cout<<Polinomios.at(Num_Poli).coef.at(j)<<"x"<<j;
			} 
			k=1; //Este paso sólo interesa para el primer término entonces el entero k cambia de valor.
			continue; //siguiente iteración para que no se repitan los datos.
		}
		else if(Polinomios.at(Num_Poli).coef.at(j)==0) //si algún coeficiente es 0, simplemente no se imprime.
		{
			continue;
		}
		else if(Polinomios.at(Num_Poli).coef.at(j)>=0) //si el coeficiente es mayor a cero, se imprime un '+'.
		{
			cout<<"+";
		}
		cout<<Polinomios.at(Num_Poli).coef.at(j)<<"x"; //se imprimern todos los demás coeficientes más una x.
		if(j>1) //si el grado del polinomio es mayor a 1 además se imprime el grado del polinomio.
		{
			cout<<j;
		}
		
	}
	cout<<endl<<"----------------------------------------------------------------------------------"<<endl;
		do
		{
			cout<<"Que desea hacer?: "<<endl;
			cout<<"1) Introducir nuevos polinomios.\n2) Salir."<<endl;
			cin>>opcion;
			if(opcion!=1 && opcion!=2)
			{
				cout<<"Opcion invalida. Intente de nuevo."<<endl;
				cout<<"----------------------------------------------------------------------------------"<<endl;
			}
		}
		while(opcion!=1 && opcion!=2);
	
	}
	while(opcion!=2);
	
	cout<<"----------------------------------------------------------------------------------"<<endl;
	cout<<"----------------------------------------------------------------------------------"<<endl;
	cout<<"Gracias por utilizarnos!";
	
return 0;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  ELIMINAR ESPACIOS  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

string Eliminar_Espacios(string texto)
{
	texto.erase(remove(texto.begin(),texto.end(), ' '),texto.end()); //"remove" elimina los espacios en blanco y texto.erase elimina los caracteres que sobran.
	return texto;
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  CARACTERES DESCONOCIDOS  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

bool Caracteres_Desconocidos(string texto)
{
	bool seguridad=true; // se inicializa el booleano en true.
	 
	for(int i=0;i<texto.length();i++)
	{
		int a=texto[i];
		if((a<48 || a>57) && a!=88 && a!=120 && a!=43 && a!=45 && a!=46 && a!=42) //si existen caracteres que no son números o distintos a (x,X,+,-,.,*):
		{
			seguridad=false; //el booleano se vuelve falso.
			break; // break para que se acabe la iteración apenas encuentre un caracter desconocido.
		}
	}	
	
	return seguridad; //se retorna el booleano (true si no hay caracteres desconocidos o false si sí los hay).
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  CONVERTIR A STRING   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

string Convertir_A_String(vector<char>caracteres)
{
	int tam=caracteres.size();
	char c[tam]; //se crea un array con la misma cantidad de elementos que el vector.
	for (int i=0;i<tam;i++)
	{
		c[i]=caracteres.at(i); //los valores del array se inicializan con los mismos valores del vector.
	}
	string texto(c,tam); //se forma un string de la combinacion de chars del array.
	
	return texto;
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  CLASIFICACIÓN  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

tPolinomio_String Clasificacion(string texto)
{
	tPolinomio_String p; //se crea la estructura donde se guardará la información.
	vector<char>auxiliar_grado; //vector auxiliar.
	vector<char>auxiliar_coef; //vector auxiliar.
	bool interruptor=true; //el interruptor marca true para leer coeficientes y false para leer grados.
	string cadena; //string auxiliar.
	
	for(int i=0;i<texto.length();i++) //Para todos los caracteres del string:
	{
		if(texto[i]=='x' || texto[i]=='X') //cada vez que se encuentre una x:
		{
			if ((texto[i-1]=='x' || texto[i-1]=='X') && i!=0) //Si antes ya había una 'x' (error de usuario), sólo se ignora.
			{
				continue;
			}
			if(interruptor==false) //si se debería haber estado leyendo un grado pero se encuentra una 'x' (error fatal):
			{
				p.grado.push_back("-1"); //se introduce un valor incompatible para marcar error.
				break;
			}
			else if(i==texto.length()-1) //si el último término es una x:
			{
				if(auxiliar_coef.empty()) //si no había ningún coeficiente antes de la x:
				{
					p.coef.push_back("1"); //el coeficiente y el grado es de 1.
					p.grado.push_back("1");
				}
				else //si existían más términos antes de la última x.
				{
					cadena=Convertir_A_String(auxiliar_coef); //los coeficientes anteriores se juntan en un sólo string.
					p.coef.push_back(cadena); //se almacena este string en p.
					p.grado.push_back("1"); //el grado del último término igual será 1.
				}
				break;
			}
			else if(auxiliar_coef.empty()) //Si no había ningún coeficiente antes de la x se toma el coeficiente como 1.
			{
				p.coef.push_back("1");
			}
			else //Caso contrario (se han ido almacenando los caracteres en el vector):
			{
				cadena=Convertir_A_String(auxiliar_coef); //se convierte a un sólo string todo el vector de caracteres.
				p.coef.push_back(cadena); //este nuevo string se introduce en el vector dentro de la estructura p.
				auxiliar_coef.clear(); //se borra la información del vector de coeficientes para poder recopilar nueva información.
			}
			interruptor=false; //Una vez reconocido el coeficiente, se procede a reconocer su grado.
			continue; //se salta a la siguiente iteración para no contar el caracter 'x' como parte del siguiente coeficiente.
		}
		
		else if (texto[i]=='+' || texto[i]=='-') //cada vez que se encuentre un '+' o un '-':
		{			
			if(i==0) // si el primer caracter es un signo no se marca una distinción entre grado y coeficiente entonces sólo se salta a la siguiente iteración.
			{
				auxiliar_coef.push_back(texto[i]);
				continue;
			}
			if(i==texto.length()-1) //si el último caracter es un signo (error fatal).
			{
				p.coef.push_back("0"); //se crea un nuevo coeficiente vacío para no generar posibles errores.
				p.grado.push_back("-1"); //Se introduce un valor incompatible para marcar error.
				break;
			}
			else if(texto[i-1]=='+' || texto[i-1]=='-') //si existen dos signos seguidos (error de usuario) se toma el primero como el real y se continúa.
			{
				continue;
			}
			else if(interruptor==true) //si se supone que se debe encontrar un coef pero se encuentra un signo: significa que el término anterior era constante (grado=0)
			{
				cadena=Convertir_A_String(auxiliar_coef); //los coeficientes que se fueron leyendo se convierten en un sólo string.
				p.coef.push_back(cadena); // este nuevo string se introduce en el vector de la estructura p.
				auxiliar_coef.clear(); // se borra la información del vector de coeficientes para poder recopilar nueva información.
				p.grado.push_back("0"); //el grado de ese término es 0 porque es constante.
				auxiliar_coef.push_back(texto[i]); //el signo es guardado para el siguiente coef.
				continue; //se salta a la siguiente iteración para empezar a leer el siguiente coeficiente.
			}
			else if(auxiliar_grado.empty()) //si no había ningún grado antes del signo se asume que el grado del coeficiente anterior es de 1.
			{
				p.grado.push_back("1");
				auxiliar_coef.push_back(texto[i]); //se guarda el signo para el próximo coef.
			}
			else //caso contrario (Se han ido almacenando los caracteres en el vector):
			{
				cadena=Convertir_A_String(auxiliar_grado); //se convierte a un sólo string todo el vector de caracteres.
				p.grado.push_back(cadena); //este nuevo string se introduce en el vector dentro de la estructura p.
				auxiliar_grado.clear(); //se borra la información del vector de grados para poder recopilar nueva información.
				auxiliar_coef.push_back(texto[i]); //se guarda el signo para el próximo coef.
			}
			interruptor=true; //Una vez reconocido el grado, se procede a reconocer el siguiente coeficiente.
			continue;
		}
		else if(texto[i]=='*') //si el caracter es un asterisco sólo se pasa al siguiente.
		{
			continue;
		}
		
		else if(i==texto.length()-1) //cuando se encuentra el último número en el string:
		{
			if(interruptor==false) //si se estaba leyendo el último grado:
			{
				auxiliar_grado.push_back(texto[i]); //se hace push_back del último número.
				cadena=Convertir_A_String(auxiliar_grado); //Se convierte a un sólo string todo el vector de caracteres.			
				p.grado.push_back(cadena); // se almacena el último grado.
			}
			else if(interruptor==true) //si se estaba leyendo el último coeficiente:
			{
				auxiliar_coef.push_back(texto[i]); //se hace push_back del último número.
				cadena=Convertir_A_String(auxiliar_coef); //Se convierte a un sólo string todo el vector de caracteres.
				p.coef.push_back(cadena); //se almacena el último coef.
				p.grado.push_back("0"); //el último grado es cero.
			}
			
			break;
		}
		
		else if(interruptor==false) //Cuando el interruptor es falso se leen grados.
		{
			auxiliar_grado.push_back(texto[i]);
		}
		else if(interruptor==true) //Cuando el interruptor es verdadero se leen coeficientes.
		{
			auxiliar_coef.push_back(texto[i]);
		}
	}
	
	return p;	
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  CONVERTIR A DOUBLE  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

double Convertir_A_Double(string texto)
{
	double x= stod(texto);
	return x;
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  ENCONTRAR EL GRADO  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

int Encontrar_Grado(vector<string>polinomios)
{
	int x=0;
	int aux;
	
	for(int i=0;i<polinomios.size();i++)
	{
		aux= Convertir_A_Double(polinomios.at(i));
		if(aux>x)
		{
			x=aux;
		}
	}
	
	return x;
};


void Ordenar_Polinomios(vector<tPolinomio> &Polinomios, vector<tPolinomio_String> Polinomios_String)
{
	for(int i=0; i<Polinomios_String.size();i++)
	{
		for(int j=0;j<Polinomios_String.at(i).coef.size();j++)
		{
			int x=Convertir_A_Double(Polinomios_String.at(i).grado.at(j));
			Polinomios.at(i).coef.at(x)=Convertir_A_Double(Polinomios_String.at(i).coef.at(j));
		}
	}
};