#include <iostream>

int main() {
    float A, B, C, D, DiffX, DiffY;
    
      
	//Ustaw moc, tutaj tez bedzie mozna stale zmieniac P
     // Ustaw moc silnikow A i B na P, jak chcesz miec reszte do dopisz po prostu C i D
    float P =0.1; //ustaw se jaka moc chcesz
    A = P;
    B = P;
    C = P;
    D = P;
    
        //A i B to nasze silniki, wiem ze mamy 4, ale wystarczy to skopiowac i dac C i D zeby miec stabliizacje w 2 osiach
    //ponizej zrobilem tylko dla osi X, 
    
	//DiffX okresla jaka chceny roznice mocy miedzy silnikami A i B, moze to byc zaleznosc sinusowa, cosinusowa, albo cokolwiek tam chcemy
    // Get input for DiffX, tego nie bedzie bo bierzemy to z sinusa
    std::cout << "Enter value for DiffX (-1 to 1): ";
    std::cin >> DiffX;
    //zamiast tego co powyzej, oblicz zadana roznice mocy, np C=sin(x)
    //C=0.5*sin(x) albo C=P*sin(x)


    
    //sprowadz roznice do zakresu od -1 do 1
    DiffX = std::max(-1.0f, std::min(1.0f, DiffX));
    
    // DiffX= roznica, ustawia moce aby spelnic rownanie A - B = DiffX
	A += DiffX;
	B -= DiffX;
	
	
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
    
    
    
    
    
    //to samo ale dla Y
    
    std::cout << "Enter value for DiffY (-1 to 1): ";
    std::cin >> DiffY;
    
    //sprowadz roznice do zakresu od -1 do 1
    DiffY = std::max(-1.0f, std::min(1.0f, DiffY));
    
    // DiffY= roznica, ustawia moce aby spelnic rownanie A - B = DiffY
	C += DiffY;
	D -= DiffY;
	
	
	//muj specjalny sos, zapewnia ze zamiast probowac zwiekszyc moc silnika ponad 1, program zmniejszy moc tego drugiego silnika
	if (C>1 || D>1) {
		float wykroczenie = (std::max(C,D) -1);
		C= C - wykroczenie;
		D= D - wykroczenie;
	}
	if (C<0 || D<0) {
		float wykroczenie =  (std::min(C,D));
		C= C - wykroczenie;
		D= D - wykroczenie;
	}
		
	
    // Opcjonalne: Obetnij A i B do zakresu od 0 do 1, wydaje mi sie ze powyzszy program juz temu zapobiega
    C = std::max(0.0f, std::min(1.0f, C));
    D = std::max(0.0f, std::min(1.0f, D));


    // Output the results
    std::cout << "C: " << C << std::endl;
    std::cout << "D " << D<< std::endl;

    return 0;
}
