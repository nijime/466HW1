#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

double mean(vector<double>);
double variance(vector<double>);
vector<double> getFreqs(string);
string encrypt(string, string);
vector<string> getCaesar(int, string);

int main() {
	vector<double> frequencies{ 0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074 };
	string ptext = "ethicslawanduniversitypolicieswarningtodefendasystemyouneedtobeabletothinklikeanattackerandthatincludesunderstandingtechniquesthatcanbeusedtocompromisesecurityhoweverusingthosetechniquesintherealworldmayviolatethelawortheuniversitysrulesanditmaybeunethicalundersomecircumstancesevenprobingforweaknessesmayresultinseverepenaltiesuptoandincludingexpulsioncivilfinesandjailtimeourpolicyineecsisthatyoumustrespecttheprivacyandpropertyrightsofothersatalltimesorelseyouwillfailthecourseactinglawfullyandethicallyisyourresponsibilitycarefullyreadthecomputerfraudandabuseactcfaaafederalstatutethatbroadlycriminalizescomputerintrusionthisisoneofseverallawsthatgovernhackingunderstandwhatthelawprohibitsifindoubtwecanreferyoutoanattorneypleasereviewitsspoliciesonresponsibleuseoftechnologyresourcesandcaenspolicydocumentsforguidelinesconcerningproper";
	
	// part A
	cout << "A)" << endl;
	cout << variance(frequencies) << endl;

	// part B
	cout << "B)" << endl;
	vector<double> ptextFreq = getFreqs(ptext);
	
	for (int i = 0; i < 26; i++) {
		cout << (char)('a' + i) << ": " << ptextFreq[i] << endl;
	}
	
	cout << "Plain text variance: " << variance(ptextFreq) << endl;

	// part C
	cout << "C)" << endl;

	vector<string> keys{ "yz", "xyz", "wxyz", "vwxyz", "uvwxyz" };
	
	cout << "KEY : FREQUENCY VARIANCE" << endl;
	for (int i = 0; i < keys.size(); i++) {
		cout << keys[i] << " : " << variance(getFreqs(encrypt(ptext, keys[i]))) << endl;
	}
	
	// part D
	cout << "D)" << endl;
	cout << "KEY : MEAN OF THE VARIANCES" << endl;
	
	for (int i = 0; i < keys.size(); i++) {
		string ctext = encrypt(ptext, keys[i]);
		
		vector<string> caesars = getCaesar(keys[i].length(), ctext);
		double varSum = 0.0;
		
		for (string caesar : caesars) {
			double var = variance(getFreqs(caesar));
			
			varSum += var;
		}

		cout << keys[i] << " : " << varSum / keys[i].size() << endl;
	}


	// part E
	cout << "E)" << endl;
	cout << "Mean variances assuming different key lengths: " << endl;


	for (int i = 2; i < 6; i++) {
		string ctext = encrypt(ptext, keys[4]);

		vector<string> caesars = getCaesar(i, ctext);
		double varSum = 0.0;

		for (string caesar : caesars) {
			double var = variance(getFreqs(caesar));

			varSum += var;
		}

		cout << i << " : " << varSum / i << endl;
	}
	
	
	getchar();
}



double mean(vector<double> v) {
	double sum = 0;
	for (int i = 0; i < v.size(); i++) {
		sum += v[i];
	}
	return sum / v.size();
}

double variance(vector<double> v) {
	double sum = 0;
	double avg = mean(v);
	for (int i = 0; i < v.size(); i++) {
		sum += (v[i] - avg) * (v[i] - avg);
	}
	return sum / v.size();
}

vector<double> getFreqs(string text) {
	vector<double> freqs(26);
	for (int i = 0; i < text.length(); i++) {
		freqs[text[i] - 'a']++;
	}
	for (int i = 0; i < freqs.size(); i++) {
		freqs[i] /= text.length();
	}
	return freqs;

}

string encrypt(string text, string key) {
	string toReturn = "";
	for (int i = 0; i < text.length(); i++) {
		toReturn += ((text[i] - 'a') + (key[i % key.length()] - 'a')) % 26 + 'a';
	}
	return toReturn;
}

vector<string> getCaesar(int keySize, string text) {
	vector<string> toReturn;

	for (int i = 0; i < keySize; i++) {
		string thisCaesar = "";

		for (int j = 0; j < text.length(); j = j + 6) {
			thisCaesar += text[i + j];
		}

		toReturn.push_back(thisCaesar);
	}

	return toReturn;
}