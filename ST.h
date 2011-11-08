struct symrec
{
char *name; /* name of symbol */
struct symrec *next; /* link ﬁeld */
};

typedef struct symrec symrec;
symrec *sym_table = (symrec *)0;
symrec *putsym ();
symrec *getsym ();

symrec * putsym ( char *sym_name )	//puts ident in table
{
symrec *ptr;
ptr = (symrec *) malloc (sizeof(symrec));
ptr− >name = (char *) malloc (strlen(sym name)+1);
strcpy (ptr− >name,sym name);
ptr− >next = (struct symrec *)sym table;
sym table = ptr;
return ptr;
}

//returns pointer to an identifier
symrec * getsym ( char *sym_name )
{
symrec *ptr;
for (ptr = sym table; ptr != (symrec *) 0;
ptr = (symrec *)ptr− >next)
if (strcmp (ptr− >name,sym_name) == 0)
return ptr;
return 0;
}

