#include<iostream>
#include<fstream>


int main(){

std::ifstream fin("daten.txt");
std::ofstream fout("datensumme.txt");
int zahl1;
int zahl2;
while(fin >> zahl1 >> zahl2) {
    int sum = zahl1 + zahl2;
    // std::cout << "The Sum of " << zahl1 << " and " << zahl2 << " is " << sum << std::endl;
    fout << sum << std::endl;
}

fin.close();
fout.close();
}
