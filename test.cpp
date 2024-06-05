#include <iostream>
#include <math.h>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string.h>
#include <unordered_map>
#include <random>


using namespace std;

float A = (sqrt(5) - 1) / 2;

struct Data{
  string university; //0
  long long userID;
  string username;  //2
  int numberTweets;
  int friendsCount;
  int followersCount;
  string createdAt; //6
  Data(){
    userID = -1;
    username = "";
  }
};

vector<Data> csvRead(string filename){
  vector<Data> dataset;

  ifstream file(filename);
  string line, word;

  if(file.is_open()){
    Data data;
    getline(file, line);
    while(getline(file, line)){
      cout<<line<<endl;
      Data data;
      stringstream s(line);
      getline(s, word, ',');
      data.university = word;
      getline(s, word, ',');
      data.userID = stoll(word);
      getline(s, word, ',');
      data.username = word;
      getline(s, word, ',');
      data.numberTweets = stoi(word);
      getline(s, word, ',');
      data.friendsCount = stoi(word);
      getline(s, word, ',');
      data.followersCount = stoi(word);
      getline(s, word, ',');
      data.createdAt = word;
      dataset.push_back(data);
    }
  }
  return dataset;
}

//Polinomial hash

long long hs(string& str, int n){
  const int a = 7;

  long long hash_value = 0;
  long long p_pow = 1;
  for (char c : str) {
    hash_value = (hash_value + (c - 'a' + 1) * p_pow) % n;
    p_pow = (p_pow * a) % n;
  }
  return hash_value;
}

unsigned long long h1(long long k, int n) {
  return k%n;
}

unsigned long long h2(long long k, int n) {
  float a = (float)k*A;
  a -= (int)a;
  return n*a;
}

unsigned long long linear_probing(long long k, int n, long long i) {
  return (h1(k, n) + i) % n;
}

unsigned long long quadratic_probing(long long k, int n, long long i) {
  return (h1(k, n) + i + 2*i*i) % n;
}

unsigned long long double_hashing(long long k, int n, long long i) {
  return (h1(k, n) + i*(h2(k, n)+1)) % n;
}

struct LinkedListNode {

  Data data;
  LinkedListNode* next;
  bool empty;

  LinkedListNode(){
    empty = 1;
    next = nullptr;
  }

  void insertData(Data pData){
    empty = 0;
    data = pData;
  }
};

struct HashTable {
  int size;
  Data* table;
  unsigned long long (*hashing_method)(long long, int, long long);

  HashTable(int size, unsigned long long (*hashing_method)(long long, int, long long)) : size(size), hashing_method(hashing_method) {
    table = new Data[size];
    for (int i = 0; i < size; i++) {
      table[i] = Data();
    }
  }

  void insert(Data data) {
    long long key = data.userID;
    //string key = data.username;
    int i = 0;
    long long hash = hashing_method(key, size, i);
    while (table[hash].userID != -1) {
      i++;
      hash = hashing_method(key, size, i);
      if(data.userID == 1218138993067529984){
        cout<<data.username<<hash<<endl;
      }
    }
    table[hashing_method(key, size, i)] = data;
  }

  bool search(Data data) {
    long long key = data.userID;
    //string key = data.username;
    int i = 0;
    while (table[hashing_method(key, size, i)].userID != key && table[hashing_method(key, size, i)].userID != -1) {
      i++;
    }
    return table[hashing_method(key, size, i)].userID == key;
  }
};


struct HashTableAbierto {
  int size;
  LinkedListNode* table;
  unsigned long long (*hashing_method)(long long, int, long long);

  HashTableAbierto(int size, unsigned long long (*hashing_method)(long long, int, long long)) : size(size), hashing_method(hashing_method) {
    table = new LinkedListNode[size];
    for (int i = 0; i < size; i++) {
      table[i] = LinkedListNode();
    }
  }

  void insert(Data data) {
    unsigned long long key = data.userID;
    //string key = data.username;
    LinkedListNode currNode = table[hashing_method(key, size, 0)];

    while(currNode.empty != 1){
      LinkedListNode* next = currNode.next;
      currNode = *next;
    }
    LinkedListNode* newNode = new LinkedListNode();
    newNode->insertData(data);
    currNode.next = newNode;
  }

  bool search(Data data) {
    unsigned long long key = data.userID;
    //string key = data.username;
    LinkedListNode currNode = table[hashing_method(key, size, 0)];
    while(currNode.empty != 1){
      if(data.userID == currNode.data.userID){
        return true;
      }
      else{
        LinkedListNode* next = currNode.next;
        currNode = *next;

      }
    }
    return false;
  }
};


int main() {
  int N = 22000;
  HashTable ht_linear(N, linear_probing);
  HashTable ht_quadratic(N, quadratic_probing);
  HashTable ht_double(N, double_hashing);
  HashTableAbierto hAbierto(N, double_hashing);
  unordered_map<unsigned long long, Data> um;
  //unordered_map<string, Data> um;

  vector<Data> dataset = csvRead("universities_followers_int64.csv");

  
  ofstream file("linear_insert.csv");
  for (int i = 0; i < dataset.size(); i++) {
    auto start = chrono::high_resolution_clock::now();
    ht_linear.insert(dataset[i]);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << i+1 << ", " << duration << "\n";
  }
  file.close();
  std::cout << "Linear probing listo" << std::endl;

  file.open("quadratic_insert.csv");
  for (int i = 0; i < dataset.size(); i++) {
    auto start = chrono::high_resolution_clock::now();
    ht_quadratic.insert(dataset[i]);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << i+1 << ", " << duration << "\n";
  }
  file.close();
    std::cout << "quadratic probing listo" << std::endl;

  file.open("double_insert.csv");
  for (int i = 0; i < dataset.size(); i++) {
    auto start = chrono::high_resolution_clock::now();
    ht_double.insert(dataset[i]);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << i+1 << ", " << duration << "\n";
  }
  file.close();
    std::cout << "double hashing listo" << std::endl;

  file.open("unordered_map_insert.csv");
  for (int i = 0; i < dataset.size(); i++) {
    auto start = chrono::high_resolution_clock::now();
    um[dataset[i].userID] = dataset[i];
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << i+1 << ", " << duration << "\n";
  }
  file.close();
    std::cout << "unordered_map listo" << std::endl;

    file.open("hashingAbierto.csv");
  for (int i = 0; i < dataset.size(); i++) {
    auto start = chrono::high_resolution_clock::now();
    hAbierto.insert(dataset[i]);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    file << i+1 << ", " << duration << "\n";
  }
  file.close();
    std::cout << "hashing cerrado liz taylor" << std::endl;


                //BUSQUEDA

// Search in ht_linear
file.open("linear_search.csv");
for (int i = 0; i < dataset.size(); i++) {
  auto start = chrono::high_resolution_clock::now();
  ht_linear.search(dataset[i]);
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
  file << i << ", " << duration << "\n";
}
file.close();

std::cout << "linear busqueda listo" << std::endl;

// Search in ht_quadratic
file.open("quadratic_search.csv");
for (int i = 0; i < dataset.size(); i++){
  auto start = chrono::high_resolution_clock::now();
  ht_quadratic.search(dataset[i]);
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
  file << i << ", " << duration << "\n";
}
file.close();

std::cout << "quadratic busqueda listo" << std::endl;

// Search in ht_double
file.open("double_search.csv");
for (int i = 0; i < dataset.size(); i++){
  auto start = chrono::high_resolution_clock::now();
  ht_double.search(dataset[i]);
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
  file << i << ", " << duration << "\n";
}
file.close();

std::cout << "double busqueda listo" << std::endl;

// Search in um
file.open("unordered_map_search.csv");
for (int i = 0; i < dataset.size(); i++){
  auto start = chrono::high_resolution_clock::now();
  um.find(dataset[i].userID);
  //um.find(dataset[i].username);
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
  file << i << ", " << duration << "\n";
}
file.close();

std::cout << "unordered_map busqueda listo" << std::endl;

return 0;
}