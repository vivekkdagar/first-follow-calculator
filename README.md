# first-follow-calculator
Calculates first and follow sets for context-free grammars (Predictive parsing and LL(k) or LL(*) parsing).

# Grammar First and Follow Set Calculator

This project is a simple implementation of a tool to calculate the First and Follow sets for a given context-free grammar. The concept of First and Follow sets is fundamental in the field of formal language theory and compiler construction.

## Concept

In the theory of formal languages, a context-free grammar (CFG) consists of a set of production rules, each defining how one symbol can be replaced by another. The First set of a symbol in a CFG represents all possible terminal symbols that can begin a string derived from that symbol. Similarly, the Follow set represents all possible terminal symbols that can immediately follow occurrences of a non-terminal symbol in any string derived from the grammar.

The calculation of First and Follow sets is essential in various areas of computer science, especially in compiler design and parsing algorithms. These sets are used in predictive parsing, LL(1) parsing table construction, and syntax-directed translation, among other applications.

## Input Grammar Format

The grammar is entered in the following format:

Each production rule is represented as a string where:
- The left-hand side (LHS) symbol is followed by "=".
- The right-hand side (RHS) symbols are concatenated without spaces, separated by non-terminal symbols or terminals.

For example:
```
S=ACB
A=da
B=g
C=h
```

- Non-terminal symbols are represented by uppercase letters (e.g., S, A, B, C).
- Terminals can be lowercase letters or special characters (e.g., da, g, h).

Ensure that the grammar adheres to the context-free grammar format and does not contain any ambiguous or left-recursive rules, as this tool does not handle such cases.

The input grammar should be provided within the source code of the program by modifying the `production` array in the `main` function.

```c
strcpy(production[0], "S=ACB");
strcpy(production[1], "S=CbB");
strcpy(production[2], "S=Ba");
strcpy(production[3], "A=da");
strcpy(production[4], "A=BC");
strcpy(production[5], "B=g");
strcpy(production[6], "B=#");
strcpy(production[7], "C=h");
strcpy(production[8], "C=#");
```

Each production rule is added using the `strcpy` function with the appropriate index in the `production` array.

Ensure that the grammar provided is well-formed and adheres to the syntax described above for accurate calculation of First and Follow sets.

## Usecase

- **Compiler Construction:** First and Follow sets are used in compiler construction to perform syntax analysis and generate parsers for programming languages.
- **Parsing Algorithms:** These sets are utilized in parsing algorithms such as LL(1) and predictive parsing to efficiently analyze the syntax of input strings.
- **Error Detection:** By analyzing the First and Follow sets, potential errors in a grammar can be identified, aiding in the debugging process during compiler development.

This project provides a simple tool to calculate the First and Follow sets of a given context-free grammar, enabling developers and students to better understand and analyze the syntax of programming languages and other formal languages.