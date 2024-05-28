#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Map
{
    char symbol;
    int number;
    static const int count = 26;
};

Map* createMap();
void writeMapToFile(string, Map*);
void displayContentFileWithMap(string, Map*);
void encoding(string, string, Map*);
void decoding(string, string, Map*);
Map* createDictionary(string);
int encodeChar(char, Map*);
char decodeChar(int, Map*);

int main()
{
    Map* map = createMap();
    writeMapToFile("codes.txt",map);
    displayContentFileWithMap("codes.txt");
    encoding("input.txt", "result.txt", map);
    decoding("result.txt", "output.txt", map);
    delete[] map;
    return 0;
}

Map* createMap()
{
    Map* map = new Map[Map::count];
    for (int i = 0; i < Map::count; i++) {
        map[i].symbol = 'A' + i;
        map[i].number = Map::count - i;
        std::cout << "Letter: " << map[i].symbol << ", Code: " << map[i].number << std::endl;
    }
    return map;
}

void writeMapToFile(string fileName, Map* map)
{
    ofstream fout(fileName,ios::binary);
    if (!fout.is_open())
    {
        throw runtime_error("Stream does not open");
    }

    for (int i = 0; i < Map::count; i++) {
        fout.write((char*)&map[i],sizeof(Map));
    }
    fout.close();
}

void displayContentFileWithMap(string fileName)
{
    ifstream in(fileName,ios::binary);
    if (!in.is_open())
    {
        throw runtime_error("Stream does not open");
    }
    Map* map = new Map[Map::count];
    
    int numMaps = 0;
    string line;
    while (getline(in.read((char*)&map[numMaps],sizeof(Map)), line)) {
        cout << line << endl;
    }
    in.close();
}

Map* createDictionary(string fileName)
{
    Map* map = new Map[Map::count];
    ifstream in(fileName);
    if (!in.is_open())
    {
        throw runtime_error("Stream does not open");
    }

    for (int i = 0; i < Map::count; i++) {
        string dummy;
        in >> dummy >> map[i].symbol >> dummy >> map[i].number;
    }
    in.close();
    return map;
}

int encodeChar(char symbol, Map* map)
{
    for (int i = 0; i < Map::count; i++)
    {
        if (map[i].symbol == toupper(symbol))
        {
            return map[i].number;
        }
        else 
        {
            return int(symbol);
        }
    }
    return -1; 
}

void encoding(string input, string output, Map* map)
{
    ifstream fin(input);
    ofstream fout(output);
    if (!fin.is_open() || !fout.is_open())
    {
        throw runtime_error("Stream does not open");
    }
    char c;
    while (fin.get(c))
    {
        int encodedValue = encodeChar(c, map);
        if (encodedValue != -1) {
            fout << encodedValue << ' '; 
        }
        else {
            fout << c;
        }
    }
    fin.close();
    fout.close();
}

bool isNumber(const string& str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] < '0' || str[i] > '9') 
            return false;
    }
    return true;
}

void decoding(string input, string output, Map* map)
{
    ifstream fin(input);
    ofstream fout(output);
    if (!fin.is_open() || !fout.is_open())
    {
        throw runtime_error("Stream does not open");
    }
    string item;
    while (fin >> item)
    {
        if (isNumber(item)) {
            int num = stoi(item); 
            fout << decodeChar(num, map);
        }
        else {
            fout << item; 
        }
    }
    fin.close();
    fout.close();
}

char decodeChar(int item, Map* map)
{
    for (int i = 0; i < Map::count; i++)
    {
        if (map[i].number == item)
        {
            return map[i].symbol;
        }
    }
    return ' '; 
}
