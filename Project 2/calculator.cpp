#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <locale>
#include <ctype.h>

// This is the token type, and contains all possible tokens in our language.
typedef enum {
    T_PLUS,
    T_MINUS,
    T_MULTIPLY,
    T_POWER,
    T_DIVIDE,
    T_OPENPAREN,
    T_CLOSEPAREN,
    T_OPENBRACKET,
    T_CLOSEBRACKET,
    T_EQUALS,
    T_SEMICOLON,
    T_M,
    T_PRINT,
    T_NUMBER,
    T_EOF
} token;

// This function will convert a token to a string, for display.
std::string tokenToString(token toConvert) {
    switch (toConvert) {
        case T_PLUS:
            return std::string("+");
        case T_MINUS:
            return std::string("-");
        case T_MULTIPLY:
            return std::string("*");
        case T_POWER:
            return std::string("**");
        case T_DIVIDE:
            return std::string("/");
        case T_OPENPAREN:
            return std::string("(");
        case T_CLOSEPAREN:
            return std::string(")");
        case T_OPENBRACKET:
            return std::string("[");
        case T_CLOSEBRACKET:
            return std::string("]");
        case T_EQUALS:
            return std::string("=");
        case T_SEMICOLON:
            return std::string(";");
        case T_M:
            return std::string("M");
        case T_PRINT:
            return std::string("print");
        case T_NUMBER:
            return std::string("number");
        case T_EOF:
            return std::string("EOF");
    }
}

// Throw this error when the parser expects a given token from the scanner
// and the next token the scanner finds does not match.
void mismatchError(int line, token expected, token found) {
    std::cerr << "Parse error: expected " << tokenToString(expected) << " found " << tokenToString(found) << " at line " << line << std::endl;
    exit(1);
}

// Throw this error when the parser encounters a token that is not valid
// at the beginning of a specific grammar rule.
void parseError(int line, token found) {
    std::cerr << "Parse error: found invalid token " << tokenToString(found) << " at line " << line << std::endl;
    exit(1);
}

// Throw this error when an invalid character is found in the input, or
// if a bad character is found as part of a print token.
void scanError(int line, char badCharacter) {
    std::cerr << "Scan error: found invalid character " << badCharacter << " at line " << line << std::endl;
    exit(1);
}

// Throw this error when the index for memory is out of bounds (less
// than 0 or greater than 99). ONLY THROW IF evaluate flag is true.
void indexError(int line, int index) {
    std::cerr << "Semantic error: index " << index << " out of bounds at line " << line << std::endl;
    exit(1);
}

// Throw this error when a division by zero occurs. ONLY THROW IF evaluate flag is true.
void divideError(int line) {
    std::cerr << "Semantic error: division by zero at line " << line << std::endl;
    exit(1);
}

class Scanner {
    // You are allowed to private fields to the scanner, and this may be
    // necessary to complete your implementation. However, this is not
    // required as part of the project specification.
private:
    int line_Number = 1;
    int number;
public:
	int getNumber();
    token nextToken(); 
    void eatToken(token);
    int lineNumber();
    int getNumberValue();
    
    // You may need to write a constructor for the scanner. This is not
    // required by the project description, but you may need it to complete
    // your implementation.
    // WRITEME
};

token Scanner::nextToken() {
    // This is a placeholder token, you will need to replace this code
    // with code to return the correct next token.
    
    char peek;
    
    while ( isspace(peek = std::cin.peek()) ) { //check to see if nextToken is whitespace
      if(peek == '\n') line_Number++;
      std::cin.get();                          //if so, consume
    }
    
    char c;
    c = std::cin.peek();
     
     switch (c) {
        case '-':
            return T_MINUS;
            
        case '+':
        	return T_PLUS;
        
        case '*':
            std::cin.get();
            char temp;
            temp = std::cin.peek();
            std::cin.putback ('*');
            
            if(temp == '*') return T_POWER;
            else 
              return T_MULTIPLY;
        
        case '/':
        	return T_DIVIDE;
        
        case ';':
        	return T_SEMICOLON;
       
        case 'M':	
        case 'm':
        	return T_M;
        	
        case '[':
        	return T_OPENBRACKET;
        	
        case ']':
        	return T_CLOSEBRACKET;
        	
        case '(':
        	return T_OPENPAREN;
        	
        case ')':
        	return T_CLOSEPAREN;
        	
        case '=':
        	return T_EQUALS;
        
        case 'P':
        case 'p':
            return T_PRINT;
        
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
             return T_NUMBER;
            
        case EOF:
            return T_EOF;
        
        default:
            scanError(lineNumber(),c);
            break;
    }
    
}

void Scanner::eatToken(token toConsume) {
    // This function consumes the next token.
    
    token foundToken = nextToken();
    
    if( foundToken == toConsume) 
      
      switch(toConsume) {
        case T_MINUS:
        case T_PLUS:
        case T_MULTIPLY:
        case T_DIVIDE:
        case T_SEMICOLON:
        case T_M:
        case T_EQUALS:
        case T_OPENPAREN:
        case T_CLOSEPAREN:
        case T_OPENBRACKET:
        case T_CLOSEBRACKET:
          std::cin.get();
          break;
        
        case T_POWER:
          std::cin.get();
          std::cin.get();
          break;
        
        case T_NUMBER:
        
        int temp;
        number = (std::cin.get() - 48);
                
        while ( isdigit(std::cin.peek()) ) { 
         temp = std::cin.get();
         temp = temp - 48;
         number = ((number * 10) + temp); 
                                 
         }          
          break;
         
         case T_PRINT:
           std::string print = "print";
           std::string cap_print = "PRINT";
           char p;
           for(int i = 0; i < 5; i++) {
             p = std::cin.get();
             if ((print[i] == p)  || (cap_print[i] == p)) continue;
             else 
               scanError(lineNumber(), p);
            }
           break;
        }
     
     else {
       mismatchError(lineNumber(), toConsume, foundToken);
       
     }
}

int Scanner::lineNumber() {
    return line_Number;
}

int Scanner::getNumber() {
    return number;
}

int Scanner::getNumberValue() {
    // This is also a placeholder, you will need to replace this code
    // with code to return the last number value that was scanned. This
    // will be used when evaluating expressions.
    
    // WRITEME
    return 0;
}

class Parser {
    // You are allowed to private fields to the parser, and this may be
    // necessary to complete your implementation. However, this is not
    // required as part of the project specification.
    
private:
    Scanner scanner;
    token lookahead;
    int value;
    int m [100] = { };
    
    // This flag indicates whether we should perform evaluation and throw
    // out-of-bounds and divide-by-zero errors. ONLY evaluate and throw these
    // errors if this flag is set to TRUE.
    bool evaluate;
    
    // You will need to add more methods for handling nonterminal symbols here.
    void Start();
    void Statement();
    void Statements();
    void Statements_1();
    void Expression();
    void SubAdd();
    void SubAdd_1();
    void MultDiv();
    void MultDiv_1();
    void Exp();
    void Exp_1(int *p); //takes a power as a parameter for right associativity
    void Paren();
    void match(token);
    

public:
    void parse();
    Parser(bool evaluate) : evaluate(evaluate) {
        // You may need to complete a Parser constructor here
        // WRITEME
    }
};

void Parser::match(token current_token) {
    if(current_token == lookahead) {
      scanner.eatToken(current_token);
      lookahead = scanner.nextToken();
     }
     else {
       mismatchError(scanner.lineNumber(),current_token , lookahead);
       
     }       
}

void Parser::parse() {
    // This is the entry point for the parser, which simply starts parsing
    // the grammar by calling the function for the start symbol.
    //set lookahead to nextToken()
    lookahead = scanner.nextToken();
    //call the start symbol
    Start();
    match(T_EOF);
}

void Parser::Start() {
    // This is an example of a recursive-descent function for a
    // non-terminal symbol. In this case, it is just a placeholder
    // which accepts infinite numbers of T_PLUS. You will need to
    // replace this with correct code for the real grammar start symbol.
    Statements();
    
}

// WRITEME (The rest of the nonterminal functions will need to be implemented here)
void Parser:: Statements() {
	Statement();
	Statements_1();   

}

void Parser:: Statements_1() {
   if(lookahead == T_SEMICOLON) {
   		match(T_SEMICOLON);
   		Statement();
   		Statements_1();
   	}
   	else {
   		//do nothing
   	}
   		

}

void Parser:: Statement() {
 
 switch(lookahead) {
 int tempVal;
        case T_M:
        	match(T_M);
        	match(T_OPENBRACKET);
        	Expression();
        	if( evaluate == true) {
        		tempVal= value;
        		}
        	match(T_CLOSEBRACKET);
        	match(T_EQUALS);
        	Expression();
        	if( evaluate == true) {
        		if( (tempVal<0) || (tempVal>99) ) indexError(scanner.lineNumber(), tempVal);
        		m[tempVal] = value;
        		}
        	break;
   		
   		case T_PRINT:
   			match(T_PRINT);
    		Expression();
    		if( evaluate == true ) {
    			std::cout << value << std::endl;
    			}
    		break;
    	
    	default:
    		parseError(scanner.lineNumber(), lookahead);
    		break;  
    	}

}

void Parser:: Expression() {
  SubAdd(); 
}

void Parser:: SubAdd() {
  MultDiv();
  SubAdd_1();
}

void Parser::SubAdd_1() {
	
  switch(lookahead) {
  int tempVal;
  int tempVal_2;
        case T_PLUS:
        	match(T_PLUS);
        	if( evaluate == true) {
        		tempVal = value;
        	    }
        	MultDiv();
        	if( evaluate == true) {
        		value = tempVal + value;
        		}
        	SubAdd_1();
        	break;
   		
   		case T_MINUS:
   			match(T_MINUS);
   			if( evaluate == true) {
   				tempVal_2 = value;
   				}
    		MultDiv();
    		if( evaluate == true) {
    			value = tempVal_2 - value;
    			}
        	SubAdd_1();
        	break;
    	
    	case T_SEMICOLON:
    	case T_EOF:
    	case T_CLOSEPAREN:
    	case T_CLOSEBRACKET:
    	  //epsilon
    		break; 
    		
    	default:
    		parseError(scanner.lineNumber(), lookahead);
    		break;
    }
}

void Parser::MultDiv() {
  Exp();
  MultDiv_1();
  
}

void Parser::MultDiv_1() {
switch(lookahead) {
int tempVal;
  case T_MULTIPLY:
        	match(T_MULTIPLY);
        	if( evaluate == true) {
        		tempVal = value;
        		}
        	Exp();
        	if( evaluate == true) {
        		value = tempVal * value;
        		}
        	MultDiv_1();
        	break;
   		
   		case T_DIVIDE:
   			match(T_DIVIDE);
   			if( evaluate == true) {
   				tempVal = value;
   				}
    		Exp();
    		if( evaluate == true) {
    			if (value == 0 ) divideError(scanner.lineNumber());
    			value = tempVal / value;
    			}
        	MultDiv_1();
        	break;
    	
    	case T_SEMICOLON:
    	case T_EOF:
    	case T_PLUS:
    	case T_MINUS:
    	case T_CLOSEPAREN:
    	case T_CLOSEBRACKET:
    	  //epsilon
    		break; 
    		
    	default:
    		parseError(scanner.lineNumber(), lookahead);
    		break;
    }
}

void Parser::Exp() {
 int p;
 int base;
  Paren();
  base = value;
  Exp_1(&p); 
  value = pow(base,p);
  
}

void Parser::Exp_1(int *p) {
int tempVal;
int q;
int base;
  if(lookahead == T_POWER) {
    match(T_POWER);
    Paren();
    if (evaluate == true) {
    base = value;
    }
    Exp_1(&q); 
    if(evaluate == true) {
    	*p = pow(base,q);
    }
 }
 else {
   //do nothing
   switch(lookahead) {
   		case T_SEMICOLON:
    	case T_EOF:
    	case T_PLUS:
    	case T_MINUS:
    	case T_MULTIPLY:
    	case T_DIVIDE:
    	case T_CLOSEPAREN:
    	case T_CLOSEBRACKET:
    	  //epsilon
    	break; 
    		
    	default:
    		parseError(scanner.lineNumber(), lookahead);
    		break;
    	}
    	
   if(evaluate == true) {
   	*p = 1; //default power is set to 1
   	
   }
 }
}
    
void Parser::Paren() {
   
  switch(lookahead) {
        case T_NUMBER:
        	match(T_NUMBER);
        	if( evaluate == true) {
        		value = scanner.getNumber();
        		}
        	break;
   		
   		case T_OPENPAREN:
   			match(T_OPENPAREN);
    		SubAdd();
    		match(T_CLOSEPAREN);
    		break;
    	
    	case T_M:
    		match(T_M);
    		match(T_OPENBRACKET);
    		SubAdd();
    		if( evaluate == true) {
    			if( (value<0) || (value>99) ) indexError(scanner.lineNumber(), value);
    			value = m[value];
    			}
    		match(T_CLOSEBRACKET);
    		break;
    	
    	default:
    		parseError(scanner.lineNumber(), lookahead);
    		break;
    		
   }
}
    
int main(int argc, char* argv[]) {
    if (argc == 2 && (strcmp(argv[1], "-s") == 0)) {
        Scanner scanner;
        while (scanner.nextToken() != T_EOF) {
            std::cout << tokenToString(scanner.nextToken()) << " ";
            scanner.eatToken(scanner.nextToken());
        }
        std::cout<<std::endl;
    } else if (argc == 2 && (strcmp(argv[1], "-e") == 0)) {
        Parser parser(true);
        parser.parse();
    } else {
        Parser parser(false);
        parser.parse();
    }
    return 0;
}
