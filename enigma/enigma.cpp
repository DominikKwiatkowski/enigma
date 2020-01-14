// enigma.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;
struct Node
{
	string slowo;
	int numer;
	Node*next = NULL;
};
struct Pole
{
	int tam;
	int spowrotem;
};
struct Rotor
{
	//int przesuniecie;
	Pole* tab;
	int liczbaPrzesuwajek;
	int*przesuwajki;
	//bool ruszony = false;
};
struct Reflector
{
	int*tab;
};
long long int pot(int a, int x)
{
	int wynik = 1;
	for (int i = 0; i < x; i++)
	{
		wynik *= a;
	}
	return wynik;
}
int koduj(string &slowo, int modulo)
{
	int mnoznik = 5;
	long long int wynik = 0;
	for (int i = slowo.size() - 1; i >= 0; i--)
	{
		wynik += (slowo[i] - '0') * mnoznik;
		mnoznik *= 5;
		wynik &= modulo - 1;
		if (i == 5)
			break;
	}
	return wynik;
}
int koduj2(char slowo[128], int modulo, int size)
{
	int mnoznik = 5;
	long long int wynik = 0;
	for (int i = size; i >= 0; i--)
	{
		wynik += (slowo[i] - '0') * mnoznik;
		mnoznik *= 5;
		wynik &= modulo - 1;

		if (i == 5)
			break;
	}
	return wynik;
}
void dodaj(string &slowo, int wartosc, Node tab[], int numer)
{
	if (tab[wartosc].slowo == slowo)
	{
		tab[wartosc].numer = numer;
	}
	else if (tab[wartosc].slowo == "")
	{
		tab[wartosc].numer = numer;
		tab[wartosc].slowo = slowo;
		tab[wartosc].next = NULL;
	}
	else if (tab[wartosc].next == NULL)
	{
		tab[wartosc].next = new Node;
		tab[wartosc].next->slowo = slowo;
		tab[wartosc].next->numer = numer;
		tab[wartosc].next->next = NULL;
	}
	else
	{
		Node*wezel = &tab[wartosc];
		while (wezel->next != NULL)
		{
			if (wezel->next->slowo == slowo)
			{
				wezel->next->numer = numer;
				return;
			}
			wezel = wezel->next;
		}
		wezel->next = new Node;
		wezel->next->slowo = slowo;
		wezel->next->numer = numer;
		wezel->next->next = NULL;
	}
}
int wartosc(string slowo, Node*tab, int wartosc)
{
	if (tab[wartosc].slowo == slowo)
	{
		return tab[wartosc].numer;
	}
	else if (tab[wartosc].slowo == "")
	{
		return -1;
	}
	else
	{
		Node wezel = tab[wartosc];
		while (wezel.next != NULL)
		{
			if (wezel.next->slowo == slowo)
			{
				return wezel.next->numer;
			}
			wezel = *wezel.next;
		}
		return -1;
	}
}


int przepuscLitere(Rotor*rotory[] , Reflector* reflektor, int liczba, int &liczbaRotorow, int liczbaLiter, int przesuniecie[])
{
	for (int i = 0; i < liczbaRotorow; i++)
	{
		int x = (liczba + przesuniecie[i]) % liczbaLiter;
		x = rotory[i]->tab[x].tam;
		liczba = (liczba + x) % liczbaLiter;
	}
	if (reflektor != NULL)
	{
		liczba = reflektor->tab[liczba];
	}
	for (int i = liczbaRotorow - 1; i >= 0; i--)
	{
		int x = (liczba + przesuniecie[i]) % liczbaLiter;
		x = rotory[i]->tab[x].spowrotem;
		liczba = (liczba + x) % liczbaLiter;
	}
	return liczba;
}
int main()
{
	std::ios::sync_with_stdio(false);
	int modulo = pot(2, 16);
	Node *tab = new Node[modulo];
	int liczbaLiter;
	int liczbaRotorow;
	int liczbaReflektorow;
	int ilosc;
	scanf_s("%d", &liczbaLiter);
	string*tablicaLiter = new string[liczbaLiter];

	for (int i = 0; i < liczbaLiter; i++)
	{
		cin >> tablicaLiter[i];
		int liczba = koduj(tablicaLiter[i], modulo);
		dodaj(tablicaLiter[i], liczba, tab, i);
	}

	scanf_s("%d", &liczbaRotorow);
	Rotor*tablicaRotorow = new Rotor[liczbaRotorow];

	for (int i = 0; i < liczbaRotorow; i++)
	{
		tablicaRotorow[i].tab = new Pole[liczbaLiter];
		for (int k = 0; k < liczbaLiter; k++)
		{
			string nazwa;
			cin >> nazwa;
			int j = wartosc(nazwa, tab, koduj(nazwa, modulo));
			tablicaRotorow[i].tab[k].tam = (j - k + liczbaLiter) % liczbaLiter;
			tablicaRotorow[i].tab[j].spowrotem = (k - j + liczbaLiter) % liczbaLiter;
		}
		scanf_s("%d", &tablicaRotorow[i].liczbaPrzesuwajek);
		tablicaRotorow[i].przesuwajki = new int[tablicaRotorow[i].liczbaPrzesuwajek];

		for (int k = 0; k < tablicaRotorow[i].liczbaPrzesuwajek; k++)
		{
			string nazwa;
			cin >> nazwa;
			int j = wartosc(nazwa, tab, koduj(nazwa, modulo));
			tablicaRotorow[i].przesuwajki[k] = j;
		}
	}

	scanf_s("%d", &liczbaReflektorow);
	Reflector*tablicaReflektorow = new Reflector[liczbaReflektorow];

	for (int i = 0; i < liczbaReflektorow; i++)
	{
		tablicaReflektorow[i].tab = new int[liczbaLiter];
		for (int j = 0; j < liczbaLiter; j++)
		{
			string nazwa;
			cin >> nazwa;
			int k = wartosc(nazwa, tab, koduj(nazwa, modulo));
			tablicaReflektorow[i].tab[j] = k;
		}
	}

	scanf_s("%d", &ilosc);
	for (int i = 0; i < ilosc; i++)
	{
		char slowoCheck[512];
		int nrRefl;
		scanf_s("%d", &liczbaRotorow);
		Rotor**rotory = NULL;
		int *przesuniecie = NULL;
		bool*ruszony = NULL;
		if (liczbaRotorow>0)
		{
			rotory = new Rotor*[liczbaRotorow];
			przesuniecie = new int[liczbaRotorow];
			ruszony = new bool[liczbaRotorow];
			ruszony[0] = true;
			for (int i = 1; i < liczbaRotorow; i++)
				ruszony[i] = false;
			for (int j = 0; j < liczbaRotorow; j++)
			{
				string nazwa;
				int numer;
				scanf_s("%d", &numer);
				rotory[j] = &tablicaRotorow[numer];
				cin >> nazwa;
				int k = wartosc(nazwa, tab, koduj(nazwa, modulo));
				przesuniecie[j] = k;
			}
		}
		scanf_s("%d", &nrRefl);
		Reflector* reflektor = NULL;
		if (nrRefl >= 0 && nrRefl<liczbaReflektorow)
		{
			reflektor = &tablicaReflektorow[nrRefl];
		}
		char slowo[512];
		char znak = 0;
		scanf_s("%c", &znak);
		int h = 0;
		while (znak != '$')
		{
			scanf_s("%c", &znak);
			if (znak < '0' || znak>'z')
			{
				h = 0;
				continue;
			}
			slowo[h] = znak;
			int g = 0;
			if (h > 128)
				g = h - 128;
			while (1)
			{
				for (int j = 0; j <= h - g; j++)
				{
					slowoCheck[j] = slowo[g + j];
				}
				slowoCheck[h - g + 1] = 0;
				int liczba = wartosc(slowoCheck, tab, koduj2(slowoCheck, modulo, h - g));
				if (liczba == -1)
				{
					g++;
					if (g > h)
					{
						h++;
						if (h > 512)
						{
							for (int j = 1; j < 128; j++)
							{
								slowo[j - 1] = slowo[384+j];
							}
							h--;
						}
						break;
					}
				}
				else
				{
					if (liczbaRotorow > 0)
					{
						przesuniecie[0]++;
						if (przesuniecie[0] >= liczbaLiter)
						{
							przesuniecie[0] -= liczbaLiter;
						}
						for (int j = 0; j < liczbaRotorow - 1; j++)
						{
							for (int k = 0; k < rotory[j]->liczbaPrzesuwajek; k++)
							{
								if (przesuniecie[j] == rotory[j]->przesuwajki[k])
								{
									if (ruszony[j])
									{
										przesuniecie[j+1]++;
										if (przesuniecie[j+1] >= liczbaLiter)
										{
											przesuniecie[j+1] -= liczbaLiter;
										}
										ruszony[j+1] = true;
										break;
									}
								}
							}
						}
					}
					liczba = przepuscLitere(rotory, reflektor, liczba, liczbaRotorow, liczbaLiter,przesuniecie);
					printf("%s", tablicaLiter[liczba].c_str());
					for (int j = 1; j < liczbaRotorow; j++)
					{
						ruszony[j] = false;
					}
					h = 0;
					break;
				}
			}
			if (slowo[h] == '$')
				break;
		}
		printf("\n");
		delete[]ruszony;
		delete[]przesuniecie;
		delete[]rotory;
	}
	delete[]tablicaLiter;
	return 0;
}