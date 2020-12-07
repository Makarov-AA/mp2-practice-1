#include <string>
#include <stdio.h>
#include <fstream> 
#include<iostream>

#include "TTable.h"
#include "TScanTable.h"
#define _CRT_SECURE_NO_WARNINGS

#include "TSortTable.h"
#include "TArrayHash.h"
#include "TTreeTable.h"
#include "TTable.h"

using namespace std;

void printTable(int maxLenght, string *table, TTable<string, string> *tb, int *count) {
	int j;
	int k;
	*count = 0;
	for (j = 0; j < (maxLenght + 6) * 3 + 3; j++) {
		if (!(j % (maxLenght + 7))) table[0] += "+";
		else table[0] += "-";

		if (!(j % (maxLenght + 7))) table[2] += "+";
		else table[2] += "-";

	}

	for (j = 0; j < (maxLenght + 6) * 3 + 3; j++) {
		if (!(j % (maxLenght + 7))) table[1] += "|";
		else {
			if (j == 2) {
				table[1] += "Key";
				j += 2;
			}
			else if (maxLenght + 9 == j) {
				table[1] += "Value";
				j += 4;
			}
			/*else if ((maxLenght + 8) * 2 == j) {
				table[1] += "Periodicity";
				j += 10;
			}*/
			else table[1] += " ";
		}
	}

	table[0] += "+";
	table[1] += "|";
	table[2] += "+";
	k = 3;
	for (tb->reset(); !tb->isEnd(); tb->goNext()) {
		for (j = 0; j < ((maxLenght + 6) * 3 + 3); j++) {
			if (!(j % (maxLenght + 7))) table[k] += "|";
			else {
				if (j == 2) {
					table[k] += tb->getCurr().getKey();
					j += tb->getCurr().getKey().size() - 1;
				}
				else if (maxLenght + 9 == j) {
					table[k] += tb->getCurr().getValue();
					j += tb->getCurr().getValue().size() - 1;
				}
				else table[k] += " ";
			}
		}
		table[k] += "|";
		k++;
		(*count)++;
	}
	for (j = 0; j < (maxLenght + 6) * 3 + 3; j++) {
		if (!(j % (maxLenght + 7))) table[k] += "+";
		else table[k] += "-";
	}
	table[k] += "+";
}

void entryTable(int size, string *mas, TTable<string, string> *tb) {
	TTabRecord<string, string> record;
	for (int j = 0; j < size; j++) {
		record.setKey(mas[j]);
		record.setValue(mas[j]);
		tb->insertRecord(record);
	}
}
void getMaxSize(int *maxLenght, TTable<string, string> *tb) {
	for (tb->reset(); !tb->isEnd(); tb->goNext()) {
		if (tb->getCurr().getKey().size() > *maxLenght)
			*maxLenght = tb->getCurr().getKey().size();
	}
}


int main() {
	TTable<string, string> *usedata = nullptr;
	TScanTable<string, string> *a;
	TSortTable<string, string> *b;
	TArrayHash<string, string> *c;
	TTreeTable<string, string> *d;
	FILE *file;
	string tmpMas[1000];
	string table[1000];
	string instruction;
	int i = 0;
	int maxLenght = 0;
	int counter;
	a = new TScanTable<string, string>();
	b = new TSortTable<string, string>();
	c = new TArrayHash<string, string>();
	d = new TTreeTable<string, string>();
	fopen_s(&file, "text.txt", "r");
	ifstream ifs(file);
	while (!ifs.eof()) {
		ifs >> tmpMas[i];
		i++;
	}


	while (true) {
		cout << "instruction : ";
		std::getline(cin, instruction);
		string tmp = instruction.substr(0, instruction.find_first_of(" "));

		if (instruction.size()) {
			if (tmp == "help") {
				string help = "SHOW  -- show databases\nUSE 'database'  -- use databese\nFIND 'key'  -- find record\nDELETE 'key'  -- delete record\nINSERT'Key'  -- insert record\nPRINT -- print database";
				cout << help << endl;
			}
			if (tmp == "show" || tmp == "Show" || tmp == "SHOW") {
				string show = "SCANTABLE\nSORTTABLE\nHASHTABLE\nTREETABLE";
				cout << show << endl;
			}

			if (tmp == "use" || tmp == "Use" || tmp == "USE") {
				a->clear();
				b->clear();
				c->clear();
				d->clear();
				tmp = instruction.substr(instruction.find_first_of(" ") + 1, instruction.size());
				if (tmp == "scanTable" || tmp == "ScanTable" || tmp == "scantable" || tmp == "SCANTABLE") {
					entryTable(i, tmpMas, a);
					getMaxSize(&maxLenght, a);
					printTable(maxLenght, table, a, &counter);
					usedata = a;
				}
				if (tmp == "sortTable" || tmp == "SortTable" || tmp == "sorttable" || tmp == "SORTTABLE") {
					entryTable(i, tmpMas, b);
					getMaxSize(&maxLenght, b);
					printTable(maxLenght, table, b, &counter);
					usedata = b;
				}

				if (tmp == "hashTable" || tmp == "HashTable" || tmp == "hashtable" || tmp == "HASHTABLE") {
					entryTable(i, tmpMas, c);
					getMaxSize(&maxLenght, c);
					printTable(maxLenght, table, c, &counter);
					usedata = c;
				}

				if (tmp == "treeTable" || tmp == "TreeTable" || tmp == "treetable" || tmp == "TREETABLE") {
					entryTable(i, tmpMas, d);
					getMaxSize(&maxLenght, d);
					printTable(maxLenght, table, d, &counter);
					usedata = d;
				}

				for (int j = 0; j < counter + 4; j++) {
					cout << table[j] << endl;
					table[j] = "";
				}
			}
			else if (tmp == "find" || tmp == "Find" || tmp == "FIND") {
				tmp = instruction.substr(instruction.find_first_of(" ") + 1, instruction.size());
				bool tmpb = usedata->findRecord(tmp);
				cout << "Record found : " << tmpb << endl;
			}
			else if (tmp == "delete" || tmp == "Delete" || tmp == "DELETE") {
				tmp = instruction.substr(instruction.find_first_of(" ") + 1, instruction.size());
				bool tmpb = usedata->findRecord(tmp);
				usedata->delRecord(tmp);
				cout << "Record delete : " << tmpb << endl;
			}
			else if (tmp == "print" || tmp == "Print" || tmp == "PRINT") {
				getMaxSize(&maxLenght, usedata);
				printTable(maxLenght, table, usedata, &counter);
				for (int j = 0; j < counter + 4; j++) {
					cout << table[j] << endl;
					table[j] = "";
				}
			}
			else if (tmp == "insert" || tmp == "Insert" || tmp == "INSERT") {
				tmp = instruction.substr(instruction.find_first_of(" ") + 1, instruction.size());
				TTabRecord<string, string> tmpR;
				tmpR.setKey(tmp);
				tmpR.setValue(tmp);
				usedata->insertRecord(tmpR);
			}
		}
	}





	//entryTable(i, tmpMas , b);
	//getMaxSize(&maxLenght, b);
	//printTable(maxLenght, table, b);


	return 0;
}