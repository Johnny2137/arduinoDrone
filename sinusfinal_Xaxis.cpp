#include <iostream>

int main() {
    float A, B, C;
    
      
	//Ustaw moc, tutaj tez bedzie mozna stale zmieniac P
     // Ustaw moc silnikow A i B na P, jak chcesz miec reszte do dopisz po prostu C i D
    float P =1; //ustaw se jaka moc chcesz
    A = P;
    B = P;
    
        //A i B to nasze silniki, wiem ze mamy 4, ale wystarczy to skopiowac i dac C i D zeby miec stabliizacje w 2 osiach
    //ponizej zrobilem tylko dla osi X, 
    
	//C okresla jaka chceny roznice mocy miedzy silnikami A i B, moze to byc zaleznosc sinusowa, cosinusowa, albo cokolwiek tam chcemy
    // Get input for C, tego nie bedzie bo bierzemy to z sinusa
    std::cout << "Enter value for C (-1 to 1): ";
    std::cin >> C;
    //zamiast tego co powyzej, oblicz zadana roznice mocy, np C=sin(x)
    //C=0.5*sin(x) albo C=P*sin(x)


    
    //sprowadz roznice do zakresu od -1 do 1
    C = std::max(-1.0f, std::min(1.0f, C));
    
    // C= roznica, ustawia moce aby spelnic rownanie A - B = C
	A += C;
	B -= C;
	
	
	//muj specjalny sos, zapewnia ze zamiast probowac zwiekszyc moc silnika ponad 1, program zmniejszy moc tego drugiego silnika
	if (A>1 || B>1) {
		float wykroczenie = (std::max(A,B) -1);
		A= A - wykroczenie;
		B= B - wykroczenie;
	}
	if (A<0 || B<0) {
		float wykroczenie =  (std::min(A,B));
		A= A - wykroczenie;
		B= B - wykroczenie;
	}
		
	
    // Opcjonalne: Obetnij A i B do zakresu od 0 do 1, wydaje mi sie ze powyzszy program juz temu zapobiega
    A = std::max(0.0f, std::min(1.0f, A));
    B = std::max(0.0f, std::min(1.0f, B));


    // Output the results
    std::cout << "A: " << A << std::endl;
    std::cout << "B: " << B << std::endl;

    return 0;
}
