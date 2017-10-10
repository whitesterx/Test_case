#include <iostream>
#include "Calc.h"
#include "gtest/gtest.h"

//Program can take either a string from command line argument or ask a user for manual input

using namespace std;

//Common auxiliary output function
void doEval(Calc& c) {
        try {
            cout.setf(ios::fixed);
            cout.precision(2);
            cout << c.evaluate() << endl;
        }
        catch (std::overflow_error e) {
            cout << c.getErrorString() << endl;
        }
        return;
}

int main(int argc, char *argv[]) {

    setlocale(LC_ALL,"Rus");

//Run Google tests
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();

    Calc instCalc;
    if(argc > 1) {
        instCalc.setString(string(argv[1]));
        cout << "Ïîëó÷åíà ñòðîêà " << argv[1] << endl;
        if (instCalc.isCorrect()) {
            doEval(instCalc);
        }
        else
            cout << instCalc.getErrorString() << endl;
    }

    else {
        cout << "Ââåäèòå ñòðîêó äëÿ âû÷èñëåíèÿ " << endl;
        string input;
        cin >> input;
        instCalc.setString(input);
        if (instCalc.isCorrect()) {
            doEval(instCalc);
        }
        else
            cout << "Íåêîððåêòíûé ââîä, ñòðîêà ñîäåðæèò íåäîïóñòèìîå âûðàæåíèå " << instCalc.getErrorString() << endl;
    }

    return 0;
}

