#include "scanner.h"

// putback() puts its argument back into the Token_stream's buffer
void Token_stream::putback(Token t)
{
    if (full) error("putback into a full buffer");
    buffer = t;             // copy t to buffer
    full = true;            // buffer is now full
}

Token Token_stream::get()
{
    if (full) {             // do we already have a Token ready?
        full = false;       // remove token from buffer
        return buffer;
    }
    char ch;
    cin.get(ch);            // cin.get() does NOT skip whitespace
    while (isspace(ch)) {
        if (ch == '\n') return Token(print);
        cin.get(ch);
    }
    switch (ch) {
    case '(': case ')': case '+': case '-': case '*': case '/': case '=': case 'q':
        return Token(ch);   // let each character represent itself
    default:
    if (isdigit(ch)) {
	string s;
	s += ch;
	while (cin.get(ch) && (isdigit(ch) || ch == '.')) s += ch;
	cin.unget();
	/* if (regex_match() */
	    return Token(number, stod(s));
	/* else */
    }
    if (isalpha(ch)/*   */) {
	string s;
	s += ch;
	while (cin.get(ch) && (isalpha(ch) || isdigit(ch)/*   */)) s += ch;
	cin.unget();
        if (s == "var") return Token(variable);	    
        if (s == "const") return Token(constant);	    
        /* if (regex_match() */
            return Token(name, s);
        /* else */
    }
        error("Bad token");
    }
}

