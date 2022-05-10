# april hexdump
---
## Intro
This repository is an implementation of hexdump in util-linux version 2.37.2. Hexdump is printer file contents or user input in hexadecimal, decimal, octal, or ASCII!! In the future, I will improve the inconvenience or add functions that are not in the existing hexdump.

## Dependency
- make
```
sudo apt install make - y
```

- gcc
```
sudo apt install gcc -y
```

## How to build and run
1. Clone this repository
```
git clone https://github.com/aprilJade/april-hexdump.git
```
2. Build using make
```
cd april-hexdump
make
```
3. Use it!
```
./april-hexdump [options] <file>...
```

## Differences from hexdump
- I hope it doesn't make any difference now.

## Implemented Features
- Hexdump with standard input
  - With no option
  - Option -b: print one-byte octal
  - Option -c: print one-byte character
  - Option -C: print Canonical hex + ASCII
  - Option -d: print two-bytes decimal
  - Option -o: print two-bytes octal
  - Option -x: print two-bytes hexadecimal
- Hexdump with file input
  - With no option
  - Option -b: print one-byte octal
  - Option -c: print one-byte character
  - Option -C: print Canonical hex + ASCII
  - Option -d: print two-bytes decimal
  - Option -o: print two-bytes octal
  - Option -x: print two-bytes hexadecimal
  - Mutiple file input
- Error message
  - When input file is not exist
  - When input invalid option
  - When fail to read files

## Todo
- Implement
  - Skip overlapped line
  - Option -n \<length>\: Print only length bytes of input
  - Option -s \<offset>\: Skip offset bytes from the beginning
  - Option -h: Print detailed instruction
  - Option -V: Print version of program
  - Double dash options (ex: --version, --help, ...)
- Beautify README for readability
- To choose whether the document's language is English or Korean