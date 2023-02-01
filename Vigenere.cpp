#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

struct NGramStats {
private:
    int lastOccurrence = 0;
    int occurrences = 0;
    vector<int> separations;

public:
    void occur(int index) {
        occurrences++;
        int separation = index - lastOccurrence;
        if (lastOccurrence != 0)
            separations.push_back(separation);

        lastOccurrence = index;
    }

    vector<int> getSeparations() {
        return separations;
    }

    int getOccurrences() {
        return occurrences;
    }

    string str() {
        string toReturn = "";
        toReturn += "Ocurrences: " + to_string(occurrences);
        toReturn += " | Separations: ";
        for (int i = 0; i < separations.size(); i++) {
            toReturn += to_string(separations[i]) + " ";
        }
        return toReturn;

    }
};

/* HELPER FUNCTION HEADERS */

map<string, NGramStats> getRepeatedNGrams(int, string);
void printNMostCommon(int, map<string, NGramStats>);
void printNMostCommon(int, map<char, double>);
string decrypt(string, string);
vector<string> getCaesar(int, string);
map<char, double> getCharFrequencies(string);
int countOccurrences(string, string);
int countCommonWords(string);

/* MAIN CODE */
int main()
{
    string ctext = "OBRGXIMYAZZAWCATBNMUYYHAZNVGFCXPVVSIJSVLKIFAVGBIECAZSBWGRGRQWUCHMMOCYEFLGQQNKFSHQMGYALNKCIJQVEKVWXNFOYFYQBESGOYTXMAYTXSISNBPMSGOJBKFWRUTTMLSBNQMLLRGFNZUAWHZLBRVZGHUVZMCKJEHSLSWGXCNZYEXRIMLPXRIXNUXRNSNRPHFDHBMAYWKHTKNGNUXRNJUVGMYNYEYNLYYGPGYFSBNQQWUCHMMSLRWTFDYQRNOJUEWNLVUZIDHWXLHTLKNEXMALBRQGUMMGXCUFXLHTLLLRTROJYFIDHLIGADLUBVXENSCALVCDFFIQCFAHISILUXXZXNUAMZAWISRNOJYKMQYECGRSBWHAHLUFBBPDPWLJBRYOCYEAYSVYXSISPRKSNZYPHMMWKHXMWWMGAZNEOFMDHKORMGOKNUHTAZQRAZPWBRTQXGZFMTJAXUTRNWCAPZLUFRODLFYFLGUKHRODLTYRGRYWHNLRIUCNMDXOCGAKIFAQXKUQMVGZFDBVLSIJSGADLWCFGNCFMGTMWWISTBIMHGKXBSPVGFVWHRYHNWXSKNGHLBENHYYQPZLXUEXNHDSBGDQZIXGNQKNUXCCKUFMQIMMRYEYUNFHEUDIAZVUJWNGQYSFVSDNZYFNOLWGRBLJGLGTMWWISKZJAXVMXCFVEBMAAHTBSNGUPENMWCGBRIFFLHMYOBBBRNZIEHTAZFLTBKMUVGSYVQVMGNZYROHFKISPZLOBBVZHLBBKNOYBYRTHVYELSUFXGADJJISBSUTFRPZSGZPTQLQCAZHNGHGADMCCYEEODARGDLSFQHDMFIGKZCKYNLDWGHQEDPQHRBSBWLNKDBAMFNOJDSJTFIFMYHZXWXZHQYLBNGSQAWRHMWWQNKHMVYPEZLWXUXVCDFAHSQSMGXOLWWVHTMLCZXHHOUVMHHYZBKQYAHSHQWWGRGSMFIEPHFDBRMTLFBVLZLESOTBEXIEYQYKBFNOJDCRLAOLWEHRMWMGADYFYZRRZJIAMHYJQVMGIMNQXKUQNUXUUDORHENAGRMGULCFUDCFANEHNLFRTGYSXBYXIMLBIOIFYAMGUKWBNMNWXSHQGGLRMGUFYVMGYJHHFDLAWNEROHYEBNLANLHQNZYABBYKNPTKWMFNMHIFMJBSBJYTTQXLIPHLGAMFTQCSN";

	// print most common 2, 3, 4 substrings
    printNMostCommon(2, getRepeatedNGrams(2, ctext));
    printNMostCommon(2, getRepeatedNGrams(3, ctext));
    printNMostCommon(2, getRepeatedNGrams(4, ctext));



    string testKey = "AANTZA";
    int mostWords = 10;

	// brute force 2 of the remaining 3 characters and count common words to find likely-successful character combinations
    for (int i = 0; i < 26; i++) {
		char firstChar = 'A' + i;
		testKey[0] = firstChar;
        
        for (int j = 0; j < 26; j++) {
            char secondChar = 'A' + j;
            testKey[1] = secondChar;
            
            string decrypted = decrypt(ctext, testKey);
			int commonWords = countCommonWords(decrypted);
            if (commonWords > mostWords) { // only print the key if is more successful in finding words than previous keys
                mostWords = commonWords;
                cout << "(" << commonWords << " words found)" << endl;
                cout << testKey << endl;
                cout << decrypted << "\n\n\n\n";
            }
        }
    }

    // decrypt with suspected key
	cout << decrypt(ctext, "SUNTZU") << endl;
    

    // wait to close window
    getchar();
}


/* HELPER DEFINITIONS */

map<string, NGramStats> getRepeatedNGrams(int n, string text) {
    double totalNGrams = 0.0;
    map<string, NGramStats> toReturn;

    // build map with total ocurrences
    for (int i = 0; i < text.length() - n; i++) {
        totalNGrams++;
        string thisSubStr = text.substr(i, n);

        if (toReturn.find(thisSubStr) == toReturn.end())
            toReturn[thisSubStr] = NGramStats();


        toReturn[thisSubStr].occur(i);

    }

    return toReturn;

}

void printNMostCommon(int n, map<string, NGramStats> freqMap) {
    // sort freqMap
    vector<pair<string, NGramStats> > pairs;
    for (auto& it : freqMap) {
        pairs.push_back(it);
    }

    sort(pairs.begin(), pairs.end(),
        [](pair<string, NGramStats> a, pair<string, NGramStats> b) {
            return a.second.getOccurrences() >= b.second.getOccurrences();
        });


    int numPrinted = 0;

    // print sorted vector
    for (auto& it : pairs) {
        cout << it.first << " : " << it.second.str() << endl;
        numPrinted++;
        if (numPrinted > n) break;
    }
}


void printNMostCommon(int n, map<char, double> freqMap) {
    // sort freqMap
    vector<pair<char, double>> pairs;
    for (auto& it : freqMap) {
        pairs.push_back(it);
    }

    sort(pairs.begin(), pairs.end(),
        [](pair<char, double> a, pair<char, double> b) {
            return a.second >= b.second;
        });


    int numPrinted = 0;

    // print sorted vector
    for (auto& it : pairs) {
        cout << it.first << " : " << it.second << endl;
        numPrinted++;
        if (numPrinted > n) break;
    }
}


string decrypt(string text, string key) {
    string toReturn = "";
    int keyIndex = 0;
    for (int i = 0; i < text.length(); i++) {
        int charIndex = text[i] - 'A';
        int keyCharIndex = key[keyIndex] - 'A';
        int decryptedCharIndex = (charIndex - keyCharIndex) % 26;

        if (decryptedCharIndex < 0) decryptedCharIndex += 26;

        toReturn += (char)(decryptedCharIndex + 'A');
        keyIndex = (keyIndex + 1) % key.length();
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

map<char, double> getCharFrequencies(string text) {
    map<char, double> toReturn;
    double totalChars = 0.0;

    // count total occurrences for each character
    for (int i = 0; i < text.length(); i++) {
        totalChars++;
        char thisChar = text[i];

        if (thisChar < 65 || thisChar > 90) continue;

        if (toReturn.find(thisChar) == toReturn.end()) {
            toReturn[thisChar] = 1.0;
            continue;
        }

        toReturn[thisChar]++;
    }

    // convert totals to frequency
    for (auto& it : toReturn) {
        it.second /= totalChars;
    }

    return toReturn;
}

int countOccurrences(string text, string toFind) {
    int count = 0;
    for (int i = 0; i < text.length() - toFind.length(); i++) {
        if (text.substr(i, toFind.length()) == toFind)
            count++;
    }
    return count;
}
int countCommonWords(string text) {
    int total = 0;
    total += countOccurrences(text, "THE");
    total += countOccurrences(text, "OF");
    total += countOccurrences(text, "AND");
    total += countOccurrences(text, "YOU");

    return total;
}