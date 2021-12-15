#pragma once
#include <regex>

using namespace std;

class MathUnit
{
public:
	enum Unit {
		add = 1, subtract = -1, multiply = 2, divide = -2, pow = 3, open_bracket, close_bracket, sin, cos, tg, ctg, binlog, ln, log, sqrt, negate, number, undefined
	};

private:
	Unit unit;
	double value = 0;

public:
	MathUnit(double val) {
		unit = Unit::number;
		value = val;
	}

	MathUnit(Unit unit_name) {
		unit = unit_name;
	}

	Unit type() {
		return unit;
	}

	double val() {
		return value;
	}

	friend ostream& operator<< (ostream& os, const MathUnit& mathUnit) {
		switch (mathUnit.unit) {
		case Unit::number: {
			string num = to_string(mathUnit.value);
			regex clearup("[.0]+$");
			num = regex_replace(num, clearup, "");; // clear up back zeros
			os << num << " ";
			break;
		}
		case Unit::add:
			os << "+ "; break;
		case Unit::subtract:
			os << "- "; break;
		case Unit::multiply:
			os << "* "; break;
		case Unit::divide:
			os << "/ "; break;
		case Unit::pow:
			os << "^ "; break;
		case Unit::open_bracket:
			os << "( "; break;
		case Unit::close_bracket:
			os << ") "; break;
		case Unit::negate:
			os << "-"; break;
		case Unit::sin:
			os << "sin "; break;
		case Unit::cos:
			os << "cos "; break;
		case Unit::tg:
			os << "tg "; break;
		case Unit::ctg:
			os << "ctg "; break;
		case Unit::binlog:
			os << "log2 "; break;
		case Unit::ln:
			os << "ln "; break;
		case Unit::log:
			os << "log "; break;
		case Unit::sqrt:
			os << "sqrt "; break;
		}
		return os;
	}
};

