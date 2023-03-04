#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"


using namespace std;

int main() {
    test_remove_iterator();
    testAll();
    testAllExtended();

    cout << "Test over" << endl;
    system("pause");
}

