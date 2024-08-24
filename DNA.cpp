#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>

struct Fasta
{
    std::string header;
    std::string sequence;
};

std::vector<Fasta> readFasta(const std::string &filename)
{
    std::vector<Fasta> entries;

    std::ifstream file(filename);

    std::string line;
    Fasta curr;

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return entries;
    }

    while (std::getline(file, line))
    {
        if (line[0] == '>')
        {
            if (!curr.header.empty())
            {
                entries.push_back(curr);
            }
            curr.header = line.substr(1);
            curr.sequence.clear();
        }
        else
        {
            curr.sequence += line;
        }
    }

    if (!curr.header.empty())
    {
        entries.push_back(curr);
    }
    file.close();
    return entries;
}

std::string DNAtoRNA(const std::string &dna)
{
    std::string complement;
    std::string mrna;

    for (char base : dna)
    {
        switch (base)
        {
        case 'G':
            complement += 'C';
            break;
        case 'C':
            complement += 'G';
            break;
        case 'A':
            complement += 'T';
            break;
        case 'T':
            complement += 'A';
            break;
        default:
            complement += 'N';
        }
    }

    for (char base : complement)
    {
        mrna += (base == 'T') ? 'U' : base;
    }

    return mrna;
};

std::string translateRNA(const std::string &rna)
{
    std::unordered_map<std::string, char> codonTable = {
        {"UUU", 'F'}, {"UUC", 'F'}, {"UUA", 'L'}, {"UUG", 'L'}, {"CUU", 'L'}, {"CUC", 'L'}, {"CUA", 'L'}, {"CUG", 'L'}, {"AUU", 'I'}, {"AUC", 'I'}, {"AUA", 'I'}, {"AUG", 'M'}, {"GUU", 'V'}, {"GUC", 'V'}, {"GUA", 'V'}, {"GUG", 'V'}, {"UCU", 'S'}, {"UCC", 'S'}, {"UCA", 'S'}, {"UCG", 'S'}, {"CCU", 'P'}, {"CCC", 'P'}, {"CCA", 'P'}, {"CCG", 'P'}, {"ACU", 'T'}, {"ACC", 'T'}, {"ACA", 'T'}, {"ACG", 'T'}, {"GCU", 'A'}, {"GCC", 'A'}, {"GCA", 'A'}, {"GCG", 'A'}, {"UAU", 'Y'}, {"UAC", 'Y'}, {"UAA", '*'}, {"UAG", '*'}, {"CAU", 'H'}, {"CAC", 'H'}, {"CAA", 'Q'}, {"CAG", 'Q'}, {"AAU", 'N'}, {"AAC", 'N'}, {"AAA", 'K'}, {"AAG", 'K'}, {"GAU", 'D'}, {"GAC", 'D'}, {"GAA", 'E'}, {"GAG", 'E'}, {"UGU", 'C'}, {"UGC", 'C'}, {"UGA", '*'}, {"UGG", 'W'}, {"CGU", 'R'}, {"CGC", 'R'}, {"CGA", 'R'}, {"CGG", 'R'}, {"AGU", 'S'}, {"AGC", 'S'}, {"AGA", 'R'}, {"AGG", 'R'}, {"GGU", 'G'}, {"GGC", 'G'}, {"GGA", 'G'}, {"GGG", 'G'}};

    std::string protein;

    for (size_t i = 0; i < rna.length(); i += 3)
    {
        std::string codon = rna.substr(i, 3);

        if (codonTable.find(codon) != codonTable.end())
        {
            protein += codonTable[codon];
        }
        else
        {
            protein += 'X';
        }
    }
    return protein;
};

int main()
{
    std::string filename = "sequence";

    std::vector<Fasta> entries = readFasta(filename);

    for (const auto &entry : entries)
    {
        std::cout << "Header: " << entry.header << std::endl;

        std::string mrna = DNAtoRNA(entry.sequence);
        std::string protein = translateRNA(mrna);

        std::cout << "DNA: " << entry.sequence.substr(0, 50) << "..." << std::endl;
        std::cout << "mRNA: " << mrna.substr(0, 50) << "..." << std::endl;
        std::cout << "Protein: " << protein.substr(0, 50) << "..." << std::endl;
    }
}