/* neatvi configuration file */

/* access mode of new files */
#define MKFILE_MODE		0644

/* map file names to file types */
static struct filetype {
	char *ft;		/* file type */
	char *pat;		/* file name pattern */
} filetypes[] = {
	{"c", "\\.[hc]$"},				/* C */
	{"roff", "\\.(ms|tr|roff|tmac|[1-9])$"},	/* troff */
	{"tex", "\\.tex$"},				/* tex */
	{"msg", "letter$|mbox$|mail$"},			/* email */
	{"md", "\\.(md|txt)$"},                         /* markdown */
	{"mk", "Makefile$|makefile$|\\.mk$"},		/* makefile */
	{"sh", "build|\\.sh$"},				/* shell script */
	{"nm", "\\.nm$"},				/* neatmail */
};

/* syntax highlighting patterns */
static struct highlight {
	char *ft;		/* the filetype of this pattern */
	int att[16];		/* attributes of the matched groups */
	char *pat;		/* regular expression */
	int end;		/* the group ending this pattern */
} highlights[] = {
	{"c", {5}, "\\<(signed|unsigned|char|short|int|long|float|double|void|struct|enum|union|typedef)\\>"},
	{"c", {5}, "\\<(static|extern|register)\\>"},
	{"c", {4}, "\\<(return|for|while|if|else|do|sizeof|goto|switch|case|default|break|continue)\\>"},
	{"c", {2 | SYN_IT}, "//.*$"},
	{"c", {2 | SYN_IT}, "/\\*([^*]|\\*+[^*/])*\\*+/"},
	{"c", {6}, "^#[ \t]*[a-zA-Z0-9_]+"},
	{"c", {0, SYN_BD}, "([a-zA-Z][a-zA-Z0-9_]+)\\(", 1},
	{"c", {4}, "\"([^\"]|\\\\\")*\""},
	{"c", {4}, "'([^\\]|\\\\.)'"},
	{"c", {4}, "[-+]?\\<(0[xX][0-9a-fA-F]+|[0-9]+)\\>"},

	{"roff", {4, 0, 5 | SYN_BD, 4 | SYN_BD, 5 | SYN_BD, 4 | SYN_BD},
		"^[.'][ \t]*((SH.*)|(de) (.*)|([^ \t\\]{2,}))?.*$", 1},
	{"roff", {2 | SYN_IT}, "\\\\\".*$"},
	{"roff", {3}, "\\\\{1,2}[*$fgkmns]([^[(]|\\(..|\\[[^]]*\\])"},
	{"roff", {3}, "\\\\([^[(*$fgkmns]|\\(..|\\[[^]]*\\])"},
	{"roff", {3}, "\\$[^$]+\\$"},

	{"tex", {4 | SYN_BD, 0, 3, 0, 5},
		"\\\\[^[{ \t]+(\\[([^]]+)\\])?(\\{([^}]*)\\})?"},
	{"tex", {3}, "\\$[^$]+\\$"},
	{"tex", {2 | SYN_IT}, "%.*$"},

	/* mail */
	{"msg", {6 | SYN_BD}, "^From .*20..$"},
	{"msg", {6 | SYN_BD, 4 | SYN_BD}, "^Subject: (.*)$"},
	{"msg", {6 | SYN_BD, 2 | SYN_BD}, "^From: (.*)$"},
	{"msg", {6 | SYN_BD, 5 | SYN_BD}, "^To: (.*)$"},
	{"msg", {6 | SYN_BD, 5 | SYN_BD}, "^Cc: (.*)$"},
	{"msg", {6 | SYN_BD}, "^[A-Z][-A-Za-z]+: .+$"},
	{"msg", {2 | SYN_IT}, "^> .*$"},

	/* markdown */
	{"md", {0}, "^[[:space:]]{4}.*"},
	{"md", {4}, "^[[:space:]]*#+[[:space:]].*"},
	{"md", {4}, "^[[:space:]]*-+$"},
	{"md", {4}, "^[[:space:]]*=+$"},
	{"md", {8}, "^[[:space:]]*```.*"},
	{"md", {3}, "`[^`]+`"},
	{"md", {7}, "\\*\\*[^*]+\\*\\*"},
	{"md", {7 | SYN_IT}, "\\*[^`*]+\\*"},
	{"md", {7 | SYN_IT}, "~~[^`~]+~~"},
	{"md", {7 | SYN_IT}, "__[^`_]+__"},
	{"md", {7 | SYN_IT}, "_[^`_]+_"},
	{"md", {0, 7, 5}, "\\[([^]]+)]\\(([^)]+)\\)"},
	{"md", {0, 7, 5}, "\\[([^]]+)]\\[([^)]+)]"},

	/* makefile */
	{"mk", {0, 3}, "([A-Za-z_][A-Za-z0-9_]*)[ \t]*="},
	{"mk", {3}, "\\$\\([a-zA-Z0-9_]+\\)"},
	{"mk", {2 | SYN_IT}, "#.*$"},
	{"mk", {0, SYN_BD}, "([A-Za-z_%.]+):"},

	/* shell script */
	{"sh", {2}, "#!.*$"},
	{"sh", {2 | SYN_IT}, "#.*$"},
	{"sh", {4}, "\"([^\"]|\\\\\")*\""},
	{"sh", {4}, "\'[^\']*\'"},

	/* status bar */
	{"---", {7 | SYN_BD, 4, 1}, "^(\".*\").*(\\[[wr]\\]).*$"},
	{"---", {7 | SYN_BD, 4, 4}, "^(\".*\").*(L[0-9]+) +(C[0-9]+).*$"},
	{"---", {7 | SYN_BD}, "^.*$"},
};

/* how to hightlight current line (hll option) */
#define SYN_LINE		(SYN_BGMK(11))

/* how to hightlight text in the reverse direction */
#define SYN_REVDIR		(SYN_BGMK(7))

/* right-to-left characters (used only in dircontexts[] and dirmarks[]) */
#define CR2L		"????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????"
/* neutral characters (used only in dircontexts[] and dirmarks[]) */
#define CNEUT		"-!\"#$%&'()*+,./:;<=>?@^_`{|}~ "

/* direction context patterns; specifies the direction of a whole line */
static struct dircontext {
	int dir;
	char *pat;
} dircontexts[] = {
	{-1, "^[" CR2L "]"},
	{+1, "^[a-zA-Z_0-9]"},
};

/* direction marks; the direction of a few words in a line */
static struct dirmark {
	int ctx;	/* the direction context for this mark; 0 means any */
	int dir;	/* the direction of the matched text */
	int grp;	/* the nested subgroup; 0 means no groups */
	char *pat;
} dirmarks[] = {
	{+0, +1, 1, "\\\\\\*\\[([^]]+)\\]"},
	{+1, -1, 0, "[" CR2L "][" CNEUT CR2L "]*[" CR2L "]"},
	{-1, +1, 0, "[a-zA-Z0-9_][^" CR2L "\\\\`$']*[a-zA-Z0-9_]"},
	{+0, +1, 0, "\\$([^$]+)\\$"},
	{+0, +1, 1, "\\\\[a-zA-Z0-9_]+\\{([^}]+)\\}"},
	{-1, +1, 0, "\\\\[^ \t" CR2L "]+"},
};

/* character placeholders */
static struct placeholder {
	char *s;	/* the source character */
	char *d;	/* the placeholder */
	int wid;	/* the width of the placeholder */
} placeholders[] = {
	{"???", "-", 1},
	{"???", "-", 1},
};
