//============================================================================
// Name        : Week4_Overload4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <numeric>
#include <cmath>
#include <sstream>
using namespace std;

class Rational {
public:

	Rational() {
		p = 0;
		q = 1;
	}

	Rational(const int &numerator, const int &denominator) {
		if (numerator > 0 && denominator > 0) {
			p = numerator / gcd(numerator, denominator);
			q = denominator / gcd(numerator, denominator);
		}
		if (numerator == 0) {
			p = 0;
			q = 1;
		}
		if (numerator < 0 && denominator < 0) {
			p = abs(numerator) / gcd(abs(numerator), abs(denominator));
			q = abs(denominator) / gcd(abs(numerator), abs(denominator));
		}
		if ((denominator > 0 && numerator < 0)
				|| (denominator < 0 && numerator > 0)) {
			p = -(abs(numerator) / gcd(abs(numerator), abs(denominator)));
			q = abs(denominator) / gcd(abs(numerator), abs(denominator));
		}
	}

	int Numerator() const {
		return p;
	}

	int Denominator() const {
		return q;
	}

private:
	int p, q;
};

bool operator==(const Rational &r1, const Rational &r2) {
	if ((r1.Numerator() == r2.Numerator())
			&& (r1.Denominator() == r2.Denominator())) {
		return true;
	} else {
		return false;
	}
}

Rational operator+(const Rational &r1, const Rational &r2) {
	return Rational(
			(r1.Numerator() * r2.Denominator()
					+ r2.Numerator() * r1.Denominator()),
			(r1.Denominator() * r2.Denominator()));
}

Rational operator-(const Rational &r1, const Rational &r2) {
	return Rational(
			(r1.Numerator() * r2.Denominator()
					- r2.Numerator() * r1.Denominator()),
			(r1.Denominator() * r2.Denominator()));
}

Rational operator*(const Rational &r1, const Rational &r2) {
	return Rational(r1.Numerator() * r2.Numerator(),
			r1.Denominator() * r2.Denominator());
}

Rational operator/(const Rational &r1, const Rational &r2) {
	return Rational(r1.Numerator() * r2.Denominator(),
			r1.Denominator() * r2.Numerator());
}

ostream& operator<<(ostream &stream, const Rational &r) {
	stream << r.Numerator() << '/' << r.Denominator();
	return stream;
}

istream& operator>>(istream &stream, Rational &r) {
	int p, q ;
	char c ;
	if(!stream){
		return stream;
	}
	stream >> p;
	if(!stream){
		return stream;
	}
	stream >> c;
	if( c != '/'){
		return stream;
	}
	stream >> q;
	if(!stream){
		return stream;
	}
	r = Rational(p, q);
	return stream;
}

int main() {
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("");
        Rational r;
        bool correct = !(input >> r);
        if (!correct) {
            cout << "Read from empty stream works incorrectly" << endl;
            return 3;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 4;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 5;
        }
    }

    {
        istringstream input1("1*2"), input2("1/"), input3("/4");
        Rational r1, r2, r3;
        input1 >> r1;
        input2 >> r2;
        input3 >> r3;
        bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
        if (!correct) {
            cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
                 << r1 << " " << r2 << " " << r3 << endl;

            return 6;
        }
    }

    cout << "OK" << endl;
    return 0;
}
