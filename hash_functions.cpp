/*Ya, el resumen de la reunión:
- Próxima semana toca tablas hash. Les pedí que hicieran una comparación experimental. Para ello les dan una implementación propia (puede ser la que usaron el año pasado cuando tomaron el curso)
 y la comparen con el unordered map de la STL. Pueden usar las funciones hash del archivo que acabo de compartir
- La idea es que generen un experimento como el siguiente: Dada una tabla hash con valores ya insertados (piensen en una cantidad alta de valores random, como 10 mil o más) 
probar cuánto se demora buscar una cantidad x de valores, donde esa cantidad x sea las potencias de dos entre 2^10 hasta 2^15, por ejemplo. Con ello generan un CSV
- El CSV se toma luego con un script en python que genera las gráficas de manera automática. @Cano y @Seba Aguayo dicen que tienen scripts listos para esto. Puedo pasárselos para no reinventar todo
*/



#include <iostream>
#include <math.h>

using namespace std;

float A = (sqrt(5) - 1) / 2;

/**********************/
/*** Funciones hash ***/
/**********************/

// Método de la división
// k: clave a la cual aplicaremos la función hash
// n: tamaño de la tabla hash
int h1(int k, int n) {
  return k%n;
}


// Método de la multiplicación
// k: clave a la cual aplicaremos la función hash
// n: tamaño de la tabla hash
int h2(int k, int n) {
  float a = (float)k*A;
  a -= (int)a; // Esta línea implementa la operación módulo 1 (%1)
  
  return n*a;
}



/****************************************************/
/*** Métodos de Open addressing o hashing cerrado ***/
/****************************************************/

// Linear probing
// k: clave a la cual aplicaremos la función hash
// n: tamaño de la tabla hash
// i: número del intento
int linear_probing(int k, int n, int i) {
  // Utilizando el método de la multiplicación
  return (h1(k, n) + i) % n;
}


// Quadratic probing
// k: clave a la cual aplicaremos la función hash
// n: tamaño de la tabla hash
// i: número del intento
int quadratic_probing(int k, int n, int i) {
  // Utilizando el método de la multiplicación
  return (h1(k, n) + i + 2*i*i) % n;
}

// Double hashing
// k: clave a la cual aplicaremos la función hash
// n: tamaño de la tabla hash
// i: número del intento
int double_hashing(int k, int n, int i) {
  // Utilizando como primer método el método de la multiplicación y luego el
  // método de la división
  return (h1(k, n) + i*(h2(k, n)+1)) % n;
}

int main(int argc, char** argv) {

  if(argc != 3) {
    cerr << "Ejecución: " << argv[0] << " <tamaño tabla hash> <clave a insertar>" << endl;
    exit(EXIT_FAILURE);
  }
  
  int n = atoi(argv[1]);
  int k = atoi(argv[2]);

  // Imprimiremos los primeros 20 intentos
  // Esos 20 intentos representan las primeras 20 posiciones que se visitarán en
  // la tabla hash utilizando Hashing cerrado u Open Addressing
  cout << "Linear probing   \tQuadratic\tDouble" << endl;
  cout << "\tprobing  \tprobing  \thashing" << endl;
  for(int i=0; i<20; i++) {
    cout << i << "\t";
    cout << linear_probing(k, n, i) << "\t\t"; 
    cout << quadratic_probing(k, n, i) << "\t\t"; 
    cout << double_hashing(k, n, i) << endl; 
  }

  return EXIT_SUCCESS;

}
