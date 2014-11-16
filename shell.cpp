// Megan Worley

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

#define __NR_GlobalDef 315
#define __NR_SaveVariable 316
#define __NR_GetVariable 317
#define __NR_NextVariable 318

// Default prompt
string PROMPT = "svsh > ";

// Token type definitions.
const string KEYWORD = "keyword";
const string VARIABLE = "variable";
const string STRING = "string";
const string WORD = "word";
const string METACHAR = "metachar";

// Keyword definitions.
const string COMMENT = "#";
const string ASSIGNMENT = "=";
const string DEFPROMPT = "defprompt";
const string CD = "cd";
const string LISTJOBS = "listjobs";
const string BYE = "bye";
const string RUN = "run";
const string ASSIGNTO = "assignto";
const string BG = "<bg>";

vector<string> tokens; // Stores the seperately parsed tokens after the tokenize call, but before classification.
int tokenPosition; // Stores the index of the current token being scanned.
string previousLine;

// Breaks a line into separate tokens, storing them into the tokens vector.
// Params:
// 	line - The line of input to scan.
bool tokenize(const string &line) {
	size_t curPos, lastPos = 0;
	while (true) {
		// Preserves white space within strings; otherwise break the input at whitespace.
		if (line[lastPos] == '"') {
			curPos = line.find_first_of('"', lastPos+1);
			if (curPos == string::npos) {
				curPos = line.find_first_of(' ', lastPos);
			}
			else {
				curPos = line.find_first_of(' ', curPos);
			}
		} 
		else {
			curPos = line.find_first_of(' ', lastPos);
		}
		if (curPos == string::npos) {
			curPos = line.length();
			if (curPos != lastPos) {
				string token(line.begin()+lastPos, line.begin()+curPos);
				tokens.push_back(token);
			}
			break;
		}
		else { 
			if (curPos != lastPos) {
				string token(line.begin()+lastPos, line.begin()+curPos);
				tokens.push_back(token);
			}
		}
		lastPos = curPos + 1;
	}
}

// Scans a line of input, breaking it into tokens and classifying it into an appropriate category.  As per the suggestions on the 
// project webpage, the parser must call this function repeatedly until scan returns false, indicating end of line.  Each call to 
// the scanner populates the token and type variables.
// Params:
//	line - The line of input to scan.
//	token - Reference to a token; this will be assigned to the scanned token.
//	type - Reference to a type; this will be assigned to the scanned token's type.
// Returns:
//	true if another token was successfully parsed; false if the end of line has been reached.
bool scan(const string &line, string &token, string &type) {
	// Tokenizes a line of input and prepares it for classification.
	if (tokens.size() == 0 || line != previousLine) {
		tokens.clear();
		tokenize(line);
		tokenPosition = 0;
		previousLine = line;
	}
	// Check for end of line.
	if (tokenPosition == tokens.size()) {
		tokens.clear();
		tokenPosition = 0;
		return false;		
	}

	token = tokens[tokenPosition++];
	// Detect keywords
	if (token == DEFPROMPT || token == CD || token == LISTJOBS || token == BYE 
		|| token == RUN || token == ASSIGNTO || token == BG) {
		type = KEYWORD;
	}
	// Variables
	else if (token[0] == '$' && token.length() > 1) {
		bool isVar = true;
		for (int i = 1; i < token.length(); i++) {
			char c = token[i];
			if (!isalnum(c)) {
				isVar = false;	
			}
		}
		if (isVar) type = VARIABLE;
		else type = WORD;

	}
	// Strings
	else if (token[0] == '"' && token[token.length()-1] == '"') {
		string extracted(token.begin() + 1, token.begin() + token.length()-1);
		token = extracted;
		type = STRING;	
	}
	// Metachars
	else if (token.length() == 1 && (token == "#" || token == "=")) {
		type = METACHAR;
	}
	// Words
	else {
		type = WORD;
	}
	return true;
}

// Pareser stuff
// typedef void (*state_fn)(string, string, state_fn); // cant do this *sadface*
typedef void* (*state_fn)(string token_type, string token, bool* done, bool* error); // this solution is horrible...

void* null_state(string token_type, string token, bool* done, bool* error);
void* comment_state(string token_type, string token, bool* done, bool* error);
void* defprompt_state(string token_type, string token, bool* done, bool* error);
void* cd_state(string token_type, string token, bool* done, bool* error);
void* arg_state(string token_type, string token, bool* done, bool* error);
void* set_state(string token_type, string token, bool* done, bool* error);
void* assign_state(string token_type, string token, bool* done, bool* error);
void* end_state(string token_type, string token, bool* done, bool* error);

vector<string> exec_params;
string assign_to;

// state every line starts in
void* null_state(string token_type, string token, bool* done, bool* error){
  cerr << "null state" << endl;
  if (token_type == METACHAR) {
    if (token == COMMENT) {
      return (void*)(*comment_state);
    }
  }
  if (token_type == KEYWORD) {
    if (token == BYE) {
      *done = true;
      return (void*)(null_state);
    }
    if (token == DEFPROMPT) {
      return (void*)(defprompt_state);
    }
    if (token == CD) {
      return (void*)(cd_state);
    }
    if (token == RUN) {
      exec_params.clear();
      if (tokenPosition == tokens.size()) {
        *error = true;
        return (void*)(end_state);
      }
      return (void*)(arg_state);
    }
  }
  if (token_type == VARIABLE) {
    assign_to = token;
    return (void*)(set_state);
  }
  *error = true;
}

// should never be called except in error
void* end_state(string token_type, string token, bool* done, bool* error) {
  cerr << "end state" << endl;
  *error = true;
}

// special consumer state, only for comments
void* comment_state(string token_type, string token, bool* done, bool* error){
  cerr << "comment state" << endl;
  return (void*)(comment_state);
}

void* defprompt_state(string token_type, string token, bool* done, bool* error){
  cerr << "defprompt state" << endl;
  if (token_type == STRING) {
    PROMPT = token;
  } else {
    *error = true;
  }
  return (void*)(end_state);
}

void* cd_state(string token_type, string token, bool* done, bool* error) {
  cerr << "cd state" << endl;
  if (token_type == WORD) {
    if (!chdir(token.c_str())) {
      return (void*)(end_state);
    }
  }
  *error = true;
}

void* arg_state(string token_type, string token, bool* done, bool* error) {
  cerr << "arg state" << endl;
  if (token_type == WORD || token_type == STRING) {
    // TODO: expand token from system vars
    exec_params.push_back(token);
    if (tokenPosition != tokens.size()) {
      return (void*)(arg_state);
    }
    cerr << "EXEC" << endl;
    const char **args = new const char*[exec_params.size()+1];
    for (int i = 0; i < exec_params.size()+1; ++i) {
      args[i] = exec_params[i].c_str();
    } 
    args[exec_params.size()+1] = NULL;

    pid_t pid = fork();
    if (pid == 0) {
      execv(args[0], (char**)args);
      exit(0);
    } else {
      int status;
      wait(&status);
      return (void*)(end_state);
    }
  }
  if (token_type == KEYWORD && token == BG) {
    if (tokenPosition != tokens.size()) {
      *error = true;
      return (void*)(end_state);
    }
    // TODO: fork then exec fn
    cerr << "FORK + EXEC" << endl;
  }
  *error = true;
}

void* set_state(string token_type, string token, bool* done, bool* error) {
  cerr << "set state" << endl;
  if (token_type == METACHAR && token == ASSIGNMENT) {
    return (void*)(assign_state);
  }
  assign_to = "";
  *error = true;
}

void* assign_state(string token_type, string token, bool* done, bool* error) {
  if (token_type == STRING) {
    int err = syscall(__NR_SaveVariable, assign_to.c_str(), token.c_str()); //works?
    if (err != 0) {
      assign_to = "";
      return (void*)(end_state);
    }
  }
  assign_to = "";
  *error = true;
}

int main() {
	string input;
	bool done = false;
  cout << PROMPT;
  while(getline(cin, input)) {
		string token;
		string type;
    bool error = false;
		state_fn curr_state = null_state;
    while (scan(input, token, type)) {
			cout << tokenPosition << "/" << tokens.size() << ": Token Type = " << type << "	Token = " << token << endl;
		  curr_state = (state_fn)(curr_state(type, token, &done, &error));
      if (error) {
        cerr << "ERROR!" << endl;
        break;
      }
    }
    if (done) {
      cout << "bye!" << endl;
      break;
    }
	  cout << PROMPT;
	}
	return 0;
}
