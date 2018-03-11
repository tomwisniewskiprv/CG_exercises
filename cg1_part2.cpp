/* Pierwsz zajêcia grafika komputerowa */

#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

inline int rng(int range) {
	return rand() % range;
}

void zadanie11() {

	srand(time(NULL));
	int numbers;

	do {
		cout << "Podaj liczby" << endl;
		cout << "> ";
		cin >> numbers;

		if (cin.fail() || numbers < 1) {
			cin.clear();	// clear failbit , eofbit
			cin.sync();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // !important for Visual Studio compiler...
		}
		else {
			break;
		}

	} while (1);

	vector<int> randomNumbers;

	for (int i = 0; i < numbers; i++) {
		randomNumbers.push_back(rng(1000));
	}
	for (int i = 0; i < randomNumbers.size(); i++) {
		cout << randomNumbers[i] << " ";
	}
	cout << endl;
}


int main() {

	zadanie11();

	system("pause");
	return 0;
}