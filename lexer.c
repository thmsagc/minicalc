#include "lexer.h"

static Buffer *buffer;
static Token *tok = NULL;
static long pos = 0;

void InicializaLexer(char *arqFonte) {
    buffer = CriaBuffer(arqFonte);

    pos = 0;

    tok = (Token*) malloc(sizeof(Token));

    if (tok == NULL) {
        fprintf(stderr, "Erro alocando memoria para o token\n");
        exit(2);
    }

    tok->tipo = TOKEN_EOF;
    tok->valor = 0;
}

bool eof() {
    return !(pos < buffer->tam - 1);
}

char* TextoToken(long ini, long fim) {
    char *str = (char*) malloc(fim - ini + 1);

    if (str == NULL) {
        fprintf(stderr, "Erro alocando memoria\n");
        exit(1);
    }

    for (int i = 0; i + ini < fim; ++i) {
        str[i] = buffer->cont[i + ini];
    }

    str[fim - ini] = '\0';

    return str;
}

bool simbolo(char c) {
    return (c == '(' || c == ')' || c == '[' || c == ']'  || c == '+' || c == '-'  || c == '*' || c == '/' || c == '%' || c == '^' || c == '=' || c == ';' || c == '&' || c == '<' || c == '!' || c  == ',' || c == '{' || c == '}');
}

// função: ProximoToken
//
// Dado o arquivo-fonte, obtem e retorna o próximo token
Token* ProximoToken() {
    // TODO: obtem o proximo token da entrada e preenche tok

    // pula espaços em branco
    while (!eof() && isspace(buffer->cont[pos]))
        pos++;

    if (eof()) {
        tok->tipo = TOKEN_EOF;
        tok->valor = 0;
    } else if (isalpha(buffer->cont[pos])) {
        long initPos = pos;
        while (!eof() && !isspace(buffer->cont[pos]) && !simbolo(buffer->cont[pos]))
            pos++;
        // texto do token: entre initPos e pos-1 no buffer
        char *texto = TextoToken(initPos, pos);
        if (isKeyword(texto))
        {
            tok->tipo = TOKEN_KEYWORD;
            strcpy(tok->nome, texto);
		}
		else
		{
            tok->tipo = TOKEN_IDENTIFIER;
            strcpy(tok->nome, texto);
		}
        free(texto);
    } else if (isdigit(buffer->cont[pos])) {
        long initPos = pos;
        // TODO: verificar se existe erro léxico no final do literal inteiro
        while (!eof() && isdigit(buffer->cont[pos]))
            pos++;    

	char *texto = TextoToken(initPos, pos);
	tok->tipo = TOKEN_LITERAL;
	tok->valor = atoi(texto);
	free(texto);       

    } else if(buffer->cont[pos] == '/' && buffer->cont[pos+1] == '/'){
    	long initPos = pos;
		while (!eof() && buffer->cont[pos] != '\n')
			pos++;
		char *texto = TextoToken(initPos, pos); 
		printf("Comentário: %s\n", texto);
		free(texto);
		ProximoToken();
    } else if (simbolo(buffer->cont[pos])) {
        switch (buffer->cont[pos]) {
            case '(':
                tok->tipo = TOKEN_OPENPARENTHESES;
                break;
            case ')':
                tok->tipo = TOKEN_CLOSEPARENTHESES;
                break;
            case '[':
                tok->tipo = TOKEN_OPENBRACKETS;
                break;
            case ']':
                tok->tipo = TOKEN_CLOSEBRACKETS;
                break;
            case '{':
                tok->tipo = TOKEN_OPENKEYS;
                break;
            case '}':
                tok->tipo = TOKEN_CLOSEKEYS;
                break;
            case '+':
                tok->tipo = TOKEN_ADD;
                break;
            case '-':
                tok->tipo = TOKEN_SUB;
                break;
            case '*':
                tok->tipo = TOKEN_MUL;
                break;
            case '/':
                tok->tipo = TOKEN_DIV;
                break;
            case '%':
                tok->tipo = TOKEN_MOD;
                break;
            case '^':
                tok->tipo = TOKEN_POW;
                break;
            case ';':
                tok->tipo = TOKEN_SEMICOLON;
                break;
            case '&':
                tok->tipo = TOKEN_AND;
                break;
            case '<':
                tok->tipo = TOKEN_LESS;
                break;
            case '!':
                tok->tipo = TOKEN_NEG;
                break;
            case ',':
                tok->tipo = TOKEN_COMMA;
                break;
            default:
                fprintf(stderr, "Simbolo não esperado: %c\n", buffer->cont[pos]);
        }
        tok->valor = 0;
        pos++;
    } else {
        tok->tipo = TOKEN_ERROR;
        tok->valor = 0;
        fprintf(stderr, "ERRO LÉXICO: '%c' NÃO ESPERADO\n", buffer->cont[pos]);
        pos++;
    }

    return tok;
}

void FinalizaLexer() {
    DestroiBuffer(buffer);
    free(tok);
}

bool isKeyword(char* text){

	char *keywords[] = {"printf", "printint", "return", "int"};
	
	for(int i = 0; i < 4; i++){
		if(strcmp(text, keywords[i]) == 0)
			return true;
	}
	return false;
}
