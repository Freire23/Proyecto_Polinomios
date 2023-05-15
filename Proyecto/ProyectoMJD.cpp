#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

struct tPolinomio{  //Estructura donde se guardarán los polinomios ya convertidos.
	int grado;
	vector<double>coef; 
};
void mostrarPolinomio(const tPolinomio &pol);
bool Caracteres_Desconocidos(string);
string Eliminar_Espacios(string);
string Eliminar_mas_inicial(string texto);

int main() {
	const int grado_minimo = 0;
    const int grado_maximo = 1000;
    vector<double> coeficientes(grado_maximo - grado_minimo + 1, 0.0);
	int Num_Poli;
	int grado=0;
	bool seguridad;
    string polinomio;
    tPolinomio Polinomio;
    cout<<"Bienvenido a la calculadora de polinomios Poli_Express"<<endl;
	cout<<"----------------------------------------------------------------------------------"<<endl;
	for (int i=0; i<=1000; i++) {
		Polinomio.coef.push_back(0);
	}
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
	
	Polinomio.grado = -1; // Inicializar a -1 para detectar si se encontró algún término
    Polinomio.coef = vector<double>(1001, 0.0); // El tamaño debe ser 101 para permitir índices de 0 a 1000
	
	int grado_m=0;
	cout<<endl<<"**Una vez haya ingresado su polinomio, presione doble enter para avanzar a su siguiente polinomio**"<<endl<<endl;
	cout<<"**Ingresar el polinomio de la forma: a*xb + c*xd + ...**"<<endl<<endl;
    for (int k = 0; k < Num_Poli; k++) { // Iterar las veces que se desea para leer polinomios
    	do {
    		seguridad=true;
        	cin.ignore();
			string polinomio;
       		cout << "Ingrese el polinomio #" << k+1 << " : ";
       		getline(cin, polinomio);
       		seguridad=Caracteres_Desconocidos(polinomio);
       		if(seguridad==false) //si la función encontró caracteres desconocidos:
			{
				cout<<"El polinomio NO se ingreso de la forma correcta. Por favor, ingresar de nuevo el polinomio: "<<endl;
				continue;
			}
			polinomio=Eliminar_Espacios(polinomio);
			polinomio=Eliminar_mas_inicial(polinomio);
        	if (polinomio.empty()) {
          	  cout << "El polinomio ingresado esta vacio." << endl;
          	  return 0;
        	}

        	size_t inicio = 0;
        	size_t fin = polinomio.find("+", inicio);

			// este algoritmo para separar el string del polinomio en sus respectivos coeficientes con grados y sumarlos se realizo con ayuda de Chatgpt

        	while (fin != string::npos) {
            	string termino = polinomio.substr(inicio, fin - inicio);
            	inicio = fin + 1;
            	fin = polinomio.find("+", inicio);

            	size_t pos_x = termino.find("*x");
            	if (pos_x != string::npos) {
                	double coeficiente = stod(termino.substr(0, pos_x));
                	int grado = stoi(termino.substr(pos_x + 2));
                	coeficientes[grado - grado_minimo] += coeficiente; // Sumar coeficiente existente
                	grado_m=max(grado_m, grado); //actualizar el grado maximo
            	}
            	else { // Leer el término independiente o coeficiente con exponente 0
                	double coeficiente = stod(termino);
                	coeficientes[0] += coeficiente; // Sumar coeficiente existente
                	grado_m=max(grado_m, grado); //actualizar el grado maximo
            	}
        	}

        	string ultimo_termino = polinomio.substr(inicio);
        	size_t pos_x = ultimo_termino.find("*x");
        	if (pos_x != string::npos) {
            	double coeficiente = stod(ultimo_termino.substr(0, pos_x));
            	int grado = stoi(ultimo_termino.substr(pos_x + 2));
            	coeficientes[grado - grado_minimo] += coeficiente; // Sumar coeficiente existente
            	grado_m=max(grado_m, grado); //actualizar el grado maximo
        	}
        	else { // Leer el término independiente o coeficiente con exponente 0
            	double coeficiente = stod(ultimo_termino);
            	coeficientes[0] += coeficiente; // Sumar coeficiente existente
            	grado_m=max(grado_m, grado); //actualizar el grado maximo
        	}
    	}
    	while(seguridad==false); // se repite el "do" hasta que no haya ningún error.
    }
	Polinomio.grado=grado_m;
	for (int i=0; i<=grado_m; i++) {
		Polinomio.coef.at(i)=Polinomio.coef.at(i)+coeficientes[i];
	}
	cout << endl << "El polinomio suma es de grado "<<Polinomio.grado<<":"<<endl;
	mostrarPolinomio(Polinomio);
	

    return 0;
}

//funcion para eliminar espacios
string Eliminar_Espacios(string texto)
{
	texto.erase(remove(texto.begin(),texto.end(), ' '),texto.end()); //"remove" elimina los espacios en blanco y texto.erase elimina los caracteres que sobran.
	return texto;
};

//funcion para eliminar un + si este se encuentra al inicio del string
string Eliminar_mas_inicial(string texto)
{
	vector <char> v1;
	for (char c: texto)
	{
		v1.push_back(c);
	}
	texto="";
	if (v1.at(0)=='+') 
	{
		for (int i=1; i<v1.size(); i++)
			texto=texto+v1.at(i);
	}
	else 
	{
		for (int i=0; i<v1.size(); i++)
			texto=texto+v1.at(i);
	}
	return texto;
};


//funcion de validacion
bool Caracteres_Desconocidos(string texto)
{
	bool seguridad=true; // se inicializa el booleano en true.
	vector<char> t;
	for (char c: texto) {
		t.push_back(c);
	}
	 
	for(int i=0;i<t.size();i++)
	{
		if((t.at(i)<48 || t.at(i)>57) && t.at(i)!='x' && t.at(i)!='+' && t.at(i)!='-' && t.at(i)!='.' && t.at(i)!='*' && t.at(i)!=' ') //si existen caracteres que no son números distintos a (x,X,+,-,.):
		{
			seguridad=false; //el booleano se vuelve falso.
			break; // break para que se acabe la iteración apenas encuentre un caracter desconocido.
		}		
		
	}	
	
	return seguridad; //se retorna el booleano (true si no hay caracteres desconocidos o false si sí los hay).
};

//funcion que muestra un polinomio por pantalla
void mostrarPolinomio(const tPolinomio &pol) {
    cout << setprecision(2) << fixed;
    for (int i = pol.grado; i >= 0; i--) {
        if (pol.coef[i] != 0) {
            if (i != pol.grado) {
                cout << (pol.coef[i] > 0 ? " + " : " - ");
                cout << abs(pol.coef[i]);
            } else {
                cout << pol.coef[i];
            }
            if (i > 1) {
                cout << "*x" << i;
            } else if (i == 1) {
                cout << "*x";
            }
        }
    }
    cout << endl;
}