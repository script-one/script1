token_t tokens[NMAX];
token_t token, *ptoken;   // current token (目前 token)
int tk, tk_top = 0, line = 1;
char *p, *lp;

// store the folowing variable for restore
token_t token0, *ptoken0;
char *p0, *lp0;
int tk0, tk_top0, line0;

void scan_save() { tk0 = tk; token0 = token; p0=p; lp0=lp; ptoken0 = ptoken; tk_top0 = tk_top; line0=line; }
void scan_restore() { tk = tk0; token = token0; p=p0; lp=lp0; ptoken = ptoken0; tk_top = tk_top0; line=line0; }

#define syntax_error() { printf("Error at line=%d, pos=%d. C halt at file=%s line=%d, tk=%d(%c) %.*s\n", line, (int)(p-lp), __FILE__, __LINE__, tk, (char)tk, token.len, token.str); exit(1); }

void scan() { // 詞彙解析 lexer
  tk = End;
  while (*p) {
    token.str = p;
    token.line = line;
    char ch = *p++;
    if (ch == '\n') { // 換行
      if (src) {
        printf("// %d: %.*s", line, (int) (p-lp), lp); // 印出該行
        lp = p;     // lp = p  = 新一行的原始碼開頭
        // printf("%s", le); // 印出上一行的所有目的碼
        // le = e;
      }
      ++line;
    }
    else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_') { // 取得變數名稱
      while ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || (*p >= '0' && *p <= '9') || *p == '_')
          p++;
      tk = Id;
      break;
    }
    else if (ch >= '0' && ch <= '9') { // 取得數字串
      while ((*p>='0' && *p<='9') || (*p=='.')) p++;
      tk = Num;
      break;
    }
    else if (ch == '\'') { // 字元或字串
      while (*p != '\'') p++;
      p++;
      tk = Str;
      break;
    } else if (ch == '/' && *p == '/') { // 註解  //... 
        ++p;
        while (*p != 0 && *p != '\n') ++p;
    } else if (ch == '/' && *p == '*') { // 註解 /*...*/
        ++p;
        while (!(*p =='*' && *(p+1) == '/')) {
          if (*p == '\n') line++;
          ++p;
        }
        p+=2;
    } else if (contain(" \n\r\t;", ch)) { // 忽略空格與逗點分號，繼續往前讀...
    } else { // 以下為運算元 =+-!<>|&^%*[?~, ++, --, !=, <=, >=, ||, &&, ~  ;{}()],:
      tk = ch;
      if (ch == '=') { if (*p == '=') { ++p; tk = Eq; } break; }
      else if (ch == '+') { if (*p == '+') { ++p; tk = Inc; } break; }
      else if (ch == '-') { if (*p == '-') { ++p; tk = Dec; } break; }
      else if (ch == '!') { if (*p == '=') { ++p; tk = Neq; } break; }
      else if (ch == '<') { if (*p == '=') { ++p; tk = Le; } else if (*p == '<') { ++p; tk = Shl; } break; }
      else if (ch == '>') { if (*p == '=') { ++p; tk = Ge; } else if (*p == '>') { ++p; tk = Shr; } break; }
      else if (ch == '|') { if (*p == '|') { ++p; tk = Lor; } else break; }
      else if (ch == '&') { if (*p == '&') { ++p; tk = Land; } else break; }
      else { break; } // 其他字元，單一個字即 token
    }
  }
  token.len = p-token.str;
  int kc = key_code(token.str, token.len);
  if (kc >= 0) tk = kc;
  token.tk = tk;
  debug("%.*s ", token.len, token.str);
  // debug("tk=%d ", tk);
  ptoken = &tokens[tk_top++];
  *ptoken = token;
}

/*
bool tk_match(token_t *t, char *str) {
    int len = strlen(str);
    return len == t->len && memcmp(str, t->str, len)==0;
}

bool match(char *str) {
    return tk_match(token, str);
}

bool member(char *a[], int len) {
    for (int i=0; i<len; i++) {
      if (match(a[i])) return true;
    }
    return false;
}
*/
token_t next() {
  token_t r=token; 
  scan();
  return r;
}

#define skip(t) ({token_t r=token; if (tk==t) next(); else syntax_error(); r; })
// #define skip_str(str) ({token_t r=token; if (match(str)) next(); else syntax_error(); r; })

void lex(char *source) {
    p = source;
    // src = 1;
    next();
    while (true) {
        token_t t = next();
        if (t.tk == End) break;
        printf("%d: %.*s\n", t.line, t.len, t.str);
    }
}

