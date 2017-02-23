#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

using namespace std;

void hello_world(void)
{
	cout << "Hello World!" << endl;
}

void ninety_nine(void)
{
	for (int i = 99; i > 1; --i)
		cout << i << " bottles of beer on the wall, "
		     << i << " bottles of beer.\n"
		     << "Take one down and pass it around, "
		     <<	 i << " bottles of beer on the wall.\n\n";

	cout << "1 bottle of beer on the wall, 1 bottle of beer.\n"
	     << "Take one down and pass it around, no more bottles of beer on the wall.\n\n"
	     << "No more bottles of beer on the wall, no more bottles of beer.\n"
	     << "Go to the store and buy some more, 99 bottles of beer on the wall.\n";
}
void quine(char *source, size_t size)
{
	size_t i = 0;
	fwrite(source, size, 1, stdout);
	printf("\n");
}
void syntax_error(void)
{
	fprintf(stderr, "Syntax error at position 0, aborting.\n");
	exit(1);
}
void io_error(void)
{
	fputc(0, NULL);
}
void call_itself(void)
{
	call_itself();
}
void loop(void)
{
	while (1);
}
void divide(void)
{
	int d = 0;
	int r = 1 / d;
}
int hq9(string source, bool option = true)
{
	int last, before_last;
	if (source.empty())
	{
		cerr << "HQ9 + -, HQ9++, and HQ9 + interpreter, Version 9.9, (C) melikamp 2011."
		     << endl << "Usage: hq9 + -i [+] <source file name>" << endl
		     << "I interpret the given HQ9 + - source file(HQ9++ and HQ9 + if + option is given."
		     << endl;
		exit(1);
	}

	last = before_last = -1;

	for (string::iterator it = source.begin();it!=source.end();++it)
	{
		switch (*it)
		{
			case 'H':
			case 'h':
				hello_world();
				break;

			case 'Q':
			case 'q':
				cout << source << endl;
				break;

			case '9':
				ninety_nine();
				break;

			case '+':
				break;

			case '-':
				if (option) break;

				if (last == -1)
					syntax_error();

				switch ((unsigned char)last)
				{
					case 'H':
					case 'h':
						io_error();
						break;

					case 'Q':
					case 'q':
						call_itself();
						break;

					case '9':
						loop();
						break;

					case '+':
						if (before_last != '+')
							divide();

						break;
				}

				break;
		}

		before_last = last;
		last = *it;
	}
}
