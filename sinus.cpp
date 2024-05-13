#include <iostream>

void calculateAB(float C, float& A, float& B) {
    // Ustaw moc silnikow A i B na P
    float P =1;
    A = P;
    B = P;
    
    // C= roznica, ustaw moce aby spelnic rownanie A - B = C
	A += C;
	B -= C;
	
	
    // Obetnij A i B do zakresu od 0 do 1, trzeba by to inaczej zrobic zeby zachowac roznice
    A = std::max(0.0f, std::min(1.0f, A));
    B = std::max(0.0f, std::min(1.0f, B));
}

int main() {
    float A, B, C;

    // Get input for C, tego nie bedzie bo bierzemy to z sinusa
    std::cout << "Enter value for C (-1 to 1): ";
    std::cin >> C;
    //zamiast tego co powyzej, oblicz zadana roznice mocy, np C=sin(x)
    //C=0.5*sin(x) albo C=P*sin(x)

    // Calculate A and B based on C
    calculateAB(C, A, B);

    // Output the results
    std::cout << "A: " << A << std::endl;
    std::cout << "B: " << B << std::endl;

    return 0;
}
