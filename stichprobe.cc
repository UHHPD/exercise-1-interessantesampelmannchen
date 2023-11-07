#include <iostream>
#include <fstream>
#include <cmath>

double mean(){
    std::ifstream fin("datensumme.txt");
    int zahl1;
    int counter = 0;
    double sum = 0;

    while(fin >> zahl1){
            sum += zahl1;
            ++counter;
            // std::cout << "Zahl: " << zahl1 << " sum: " << sum << std::endl;
        }
        double mean_value = sum / counter;
        fin.close();
        return mean_value;
    }

double variance(double mean_value){
    std::ifstream fin("datensumme.txt");
    int zahl1;
    int counter = 0;
    double variance = 0.0;

    while (fin >> zahl1){
        variance += (zahl1 - mean_value) * (zahl1 - mean_value);
        ++counter;
        //std::cout << "Zahl: " << zahl1 << " Var: " << variance << std::endl;
    }
    fin.close();
    return variance / counter;
    
}

int main(){
    //std::ifstream fin("datensumme.txt");
    double mean_function_value = mean();
    std::cout << "\n" << "Mean of datensumme.txt: \t\t" << mean_function_value << std::endl;
    std::cout << "Variance of datensumme.txt: \t\t" << variance(mean_function_value) << std::endl;
    std::cout << "Standard deviation of datensumme.txt: \t" << sqrt(variance(mean_function_value)) << "\n" << std::endl;
}

