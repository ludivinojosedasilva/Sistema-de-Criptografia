#include <iostream>
#include <fstream>
#include <vector>
#include <utility> // for std::pair
#include <cctype>  // for isalpha
using namespace std;

const int SHIFT = 5;
const string TABLE_FILE = "substitution_table.txt";

// Função para gerar a tabela de substituição
vector<pair<char, char>> generateTable() {
    vector<pair<char, char>> table;

    for (char c = 'A'; c <= 'Z'; ++c) {
        char sub = 'A' + (c - 'A' + SHIFT) % 26;
        table.emplace_back(c, sub);
    }
    for (char c = 'a'; c <= 'z'; ++c) {
        char sub = 'a' + (c - 'a' + SHIFT) % 26;
        table.emplace_back(c, sub);
    }

    return table;
}

// Salva a tabela em arquivo .txt
void saveTable(const vector<pair<char, char>>& table) {
    ofstream out(TABLE_FILE);
    for (const auto& p : table) {
        out << p.first << ' ' << p.second << '\n';
    }
    out.close();
}

// Carrega a tabela do arquivo
vector<pair<char, char>> loadTable(bool reverse = false) {
    vector<pair<char, char>> table;
    ifstream in(TABLE_FILE);
    char original, encoded;

    while (in >> original >> encoded) {
        if (reverse)
            table.emplace_back(encoded, original);
        else
            table.emplace_back(original, encoded);
    }

    in.close();
    return table;
}

// Função genérica de substituição
string substituteText(const string& input, const vector<pair<char, char>>& table) {
    string output = input;

    for (size_t i = 0; i < output.length(); ++i) {
        for (const auto& p : table) {
            if (output[i] == p.first) {
                output[i] = p.second;
                break;
            }
        }
    }

    return output;
}

int main() {
    cout << "=== Sistema de Criptografia com Tabela de Substituição ===\n";

    vector<pair<char, char>> table = generateTable();
    saveTable(table);

    string input;
    cout << "Digite o texto para criptografar: ";
    getline(cin, input);

    string encrypted = substituteText(input, table);
    cout << "\nTexto criptografado: " << encrypted << "\n";

    vector<pair<char, char>> decodeTable = loadTable(true);
    string decrypted = substituteText(encrypted, decodeTable);
    cout << "Texto descriptografado: " << decrypted << "\n";

    return 0;
}
