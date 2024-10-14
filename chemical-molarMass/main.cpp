// chemical - molarMass
// TODO: calculate more substance in one runtime
#include <bits/stdc++.h>
using namespace std;

map<string, int> datum;
map<string, int> brktdatum;
map<string, int> mp;

// now only for frequently-used elements in senior high school
void ini() {
	mp["H"] = 1;
	mp["C"] = 12;
	mp["N"] = 14;
	mp["O"] = 16;
	mp["Na"] = 23;
	mp["Mg"] = 24;
	mp["Al"] = 27;
	mp["P"] = 31;
	mp["S"] = 32;
	mp["Cl"] = 35/*.5*/;
	mp["K"] = 39;
	mp["Ca"] = 40;
	mp["Mn"] = 55;
	mp["Fe"] = 56;
	mp["Cu"] = 64;
	mp["Zn"] = 65;
	mp["Br"] = 80;
	mp["Ag"] = 108;
	mp["I"] = 127;
	mp["Ba"] = 137;
}

inline int chrForm(const char chr) {
	if(chr >= 'A' && chr <= 'Z') return 1;
	if(chr >= 'a' && chr <= 'z') return 2;
	if(chr >= '0' && chr <= '9') return 3;
	if(chr == '(') return 8;
	if(chr == ')') return 9;
	else return -1;
}

int main() {
	ini();
	int ans = 0;
	string line;
	getline(cin, line);
    const int len = line.length();
	bool ifbrkt = false;    // for brackets as brkt
	int brktVal, brktAdd;
	int fltAmt = 0;    // for Cl 35.5 float as flt
	int i = 0;
	string thisStr;
	int amt;
	while(i < len) {
		// check formi & formii
		int formi = chrForm(line[i]), formii = i+1==len ? 1 : chrForm(line[i+1]);
		if(formi == -1 || formii == -1)
			{printf("NailERROR1"); return -1; }
		if(formi == 8) {
			ifbrkt = true;
			brktAdd = 0;
			i ++;
			continue;
		}
		if(formi == 9) {
			if(!ifbrkt)
				{printf("NailERROR2"); return -1; }
			ifbrkt = false;
			i ++;
			if(i != len && chrForm(line[i]) == 3) {
				brktVal = line[i] - '0';
				i ++;
				while(chrForm(line[i]) == 3) {
					brktVal *= 10;
					brktVal += line[i] - '0';
					i ++;
				}
			}
			else brktVal = 1;
			ans += brktAdd * (brktVal - 1);
			auto it = brktdatum.begin();
			while(it != brktdatum.end()) {
				datum[it->first] += it->second * (brktVal - 1);
				if(it->first == "Cl") fltAmt += it->second * (brktVal - 1);
				++ it;
			}
			brktdatum.clear();
			continue;
		}
		if(formi != 1)
			{printf("NailERROR3"); return -1; }
		
		// get thisStr & amt
		if(i + 1 == len || formii != 2) {
			thisStr = line[i];
			i ++;
		}
		else if(formii == 2) {
			thisStr = line.substr(i, 2);
			i += 2;
		}
		if(mp.find(thisStr) == mp.end())
			{printf("NailERROR4"); return -1; }
		if(i != len && chrForm(line[i]) == 3) {
			amt = line[i] - '0';
			i ++;
			while(chrForm(line[i]) == 3) {
				amt *= 10;
				amt += line[i] - '0';
				i ++;
			}
		}
		else amt = 1;

		// calculate
		if(ifbrkt) {
			brktAdd += mp[thisStr] * amt;
			brktdatum[thisStr] += amt;
		}
		ans += mp[thisStr] * amt;
		datum[thisStr] += amt;
		if(thisStr == "Cl") fltAmt += amt;
	}

	// output
	printf("> %d", ans + fltAmt / 2);
	fltAmt % 2 ? printf(".5\n") : printf("\n");
	bool fst = true;
	auto it = datum.begin();
	while(it != datum.end()) {
		thisStr = it -> first; amt = it -> second;
		if(fst) {
			printf("> (");
			fst = false;
		}
		else printf(" + (");
		if(thisStr == "Cl")
			printf("Cl)35.5 * %d", amt);
		else {
			cout << thisStr;
			printf(")%d * %d", mp[thisStr], amt);
		}
		++ it;
	}
	printf("\n");
	return 0;
}