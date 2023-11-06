#include <iostream>                         // Zugriff auf Ausgabefunktionen wie cout, cin
#include <fstream>                          // Zugriff auf Funktionen zum Lesen und Schreiben von Dateien
#include <cstdlib>                          // Zugriff auf Funktionen zum KOnvertieren von Zeichenketten in Zahen oder Generieren von Zufallszahlen
#include <cmath>                            // Zugriff auf mathematische Funktionen
#include <list>                             // Zugriff auf doppeltverkettete Listen
#include <algorithm>                        // Zugriff auf Alorithmen zum  Sortieren, Suchen und Co.
#include <iterator>                         // Zugriff auf Iteratoren, z.B Dereferenzierungsoperator "*", Inkrementoperator "++"
using namespace std;                        // ist eine Direktive, damit nicht immer std:: vor den Elementen des Namensraumes angegeben werden muss

// Aufgabe 2a)

/*Die Funktion `print` nimmt eine konstante Referenz auf eine
  Liste von Doubles entgegen. Sie verwendet die `std::copy`-Funktion, 
  um die Elemente der Liste von ihrem Anfang bis zum Ende zu kopieren. 
  Die kopierten Elemente werden dann mithilfe eines `ostream_iterator` 
  auf die Standardausgabe (`cout`) ausgegeben, wobei jedes Element in 
  einer neuen Zeile erscheint.*/

void print(list<double> const &list)        
{
    std::copy(list.begin(),
            list.end(),
            ostream_iterator<double>(cout, "\n"));
}

int main () {
  double value;
  double sum = 0;
  int count = 0;
  double var = 0;
  double var_count = 0;                       // Varianz
  double var_count_bessel = 0;                // Besselvarianz
  double mean_val;                            // Durchschnitt
  list<double> store_mean;
  list<double> store_variance;
  list<double> store_variance_bessel;
  double store_arr[9] = {0,0,0,0,0,0,0,0,0};
  ifstream inFile ("datensumme.txt");
  ofstream outFileM;                          // zum Schreiben von Daten in die Datei
  ofstream outFileV;
  outFileM.open ("mittelwerte.txt");
  outFileV.open ("varianzen.txt");
  if (inFile.is_open())
  {

/*  use one looop to compute mean value and variance by storing 
    the input number in an array of length 9
    and refillling this array for the next sequence of numbers*/

    while( !inFile.eof() )                      // die Schleife läuft solange das Ende vom inFile (datensumme.txt) noch nicht erreicht wurde
    {
      inFile >> value;                          // der kommende Wert wird als "value" eingelesen
      if (inFile.eof()) {break;}                // ist die inFile-Datei zu Ende, ist hier schluss
      store_arr[count] = value;                 // der gelesene Wert wird im Array "store_arr" and der Stelle "count" gespeichert
      count++;                                  //    und der Zähler wird erhöht
      if (count==9){                            // nach neun eingelesenen Zahlen, werden Mittelwert und Varianzen berechnet
        double store_sum = 0;                   // Berechnung des Mittelwerts: erst Summe, dass Teilen
        for (int j=0; j<9; j++) {
          store_sum += store_arr[j];
        }
        mean_val = store_sum/9;
        outFileM << mean_val << "\n";           // Mittelwerte speichern in outFileM (mittelwerte.txt)
        store_mean.push_back(mean_val);         // fügt Mittelwert (mean_val) am Edne des Vektors (store_mean) hinzu
        var_count = 0.0;                        // Berechnung der Varianz: erst Differenz, dann Quadrieren und Teilen
        var_count_bessel = 0.0;                 // Berechnung der Bessel-korrigierten Varianz: ", Teilchen durch n-1 (why: bei kleinen Stichproben)
        for (int i=0; i<9; i++) {
          double diff = store_arr[i]-mean_val;
          double var = pow(diff, 2);
          var_count += var/9;
          var_count_bessel += var/8;
        }
        outFileV << var_count << "\n";          // Varianzen speichern in outFileV
        store_variance.push_back(var_count);
        store_variance_bessel.push_back(var_count_bessel);
        count = 0;                              // Zähler zurücksetzen um nächste 9 Werte zu verrechnen
      }
    }
  outFileM.close();                             // Dateien schließen um sicherzustellen, dass alle Daten auf die Datei geschrieben werden
  outFileV.close();
  }
  inFile.close();

// Aufgabe 2b)

/*  compute mean of the means (mean(store_mean = means_of_mean)), 
  variance (mean(store_var) = means_of_var), and 
  bessel-variance (mean(store_variance_bessel) = mean_of_variances_bessel)*/

  double mean_of_means = 0;                     // Iniziere Variable mean_of_means
  for (list<double>::iterator it = store_mean.begin(); it != store_mean.end(); it++){ // it-Iterator iterieret durhc Liste "store_mean". Die Schleife läuft von Anfang bis Ende der Liste
    mean_of_means += *it/26;                    // nach Ende der Liste, wird der Durchschnitt berechnet
    }                                           // *it gibt den Wert zurück, auf den der Iterator "it" zeigt

  double mean_of_variances = 0;
  for (list<double>::iterator it = store_variance.begin(); it != store_variance.end(); it++){
    mean_of_variances += *it/26;
    }
  double mean_of_variances_bessel = 0;
  for (list<double>::iterator it = store_variance_bessel.begin(); it != store_variance_bessel.end(); it++){
    mean_of_variances_bessel += *it/26;
    }
  cout << mean_of_means << "\n";                // gibt den Mittelwert der Mittelwerte (mean_of_means) in der Konsole aus
  cout << mean_of_variances << "\n";
  cout << mean_of_variances_bessel << "\n";
}