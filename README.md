

# DNA to Protein Translation

This C++ project reads a FASTA file containing DNA sequences, converts them into mRNA, and then translates the mRNA into protein sequences.
## Features

- **Read FASTA File**: Parses a FASTA file to extract DNA sequences.
- **Convert DNA to mRNA**: Transcribes DNA sequences to mRNA by substituting thymine (T) with uracil (U).
- **Translate mRNA to Protein**: Translates mRNA sequences into proteins using a codon table.

## Files

- `main.cpp`: Contains the main implementation including functions to read FASTA files, convert DNA to RNA, and translate RNA to proteins.

## Compilation

To compile the project, use a C++ compiler like `g++`:

```bash
g++ -o dna_to_protein main.cpp
```

## Usage

Ensure you have a FASTA file named `sequence` in the same directory. The file should follow the FASTA format:

```
>header1
sequence1
>header2
sequence2
...
```

Run the compiled executable:

```bash
./dna_to_protein
```

## Example Output

```
Header: header1
DNA: ATGCGTACGTAGC... (truncated)
mRNA: AUGCGUACGUAGC... (truncated)
Protein: MCR*... (truncated)
```

## Dependencies

No external dependencies; standard C++ libraries are used.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
