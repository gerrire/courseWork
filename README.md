# courseWork
Word Analyzer

🔧 Requirements
C++ compiler (C++11 or newer)
Input file data.txt MUST be in ANSI encoding (not UTF-8)
Russian text content (Cyrillic characters)

🚀 Usage
Create data.txt in ANSI encoding with Russian text
Example file content:
город окно ананас река

Compile and run:
g++ main.cpp -o analyzer
./analyzer

📊 Output Example
Результат по буквам:
[а] : 2
[р] : 1
[о] : 1

⚠️ Important
ANSI encoding is critical for Cyrillic processing
Valid words: length >1, first/last letters match (case-insensitive)

🔑 Features
Cyrillic support
Frequency sorting (high to low)
Alphabetical sorting for ties

Copy this text directly into README.md. No formatting needed.
