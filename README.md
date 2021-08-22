c-candy
=======
C-Candy is a string and data structures library for C.

Currently only 4 types are defined. Please refer to the concerned documentation page for the API, from the table below.

## Documentation
| Type | Description | Documentation |
|-|-|-|
| STRING | Mutable string | [STRING](docs/String.md) |
| STR_ITERATOR | String iterator | [STR_ITERATOR](docs/StringIterator.md) |
| LIST | Dynamic array | [LIST](docs/List.md) |
| TUPLE | Tuple | [TUPLE](docs/Tuple.md) |
| STACK | Linked stack | [STACK](docs/Stack.md) |


## Examples

### Longest word in a sentence

#### Using plain C:

```c
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* get_longest_word(const char *s)
{
	int i, lw_start, lw_end;
			
	int n = strlen(s);
	int ls = -1;
	int lw_len = 0;

	for(i = 0; i <= n; ++i)
	{
		if(s[i] == ' ' || s[i] == '\0')
		{
			if(i-ls-1 > lw_len)
			{
				lw_start = ls + 1;
				lw_end = i;
				lw_len = lw_end - lw_start;				
			}
			ls = i;
		}
	}

	char *lw = (char*)calloc(lw_len + 1, sizeof(char));
	if(lw == NULL) return NULL;

	for(i = lw_start; i < lw_end; ++i)
		lw[i-lw_start] = s[i];	
	
	lw[lw_end-lw_start] = '\0';
	return lw;
}
	
int main(int argc, char **argv)
{
	const char *s = "The quick brown fox jumps over the lazy dog";
	char *lw = get_longest_word(s);

	printf("Longest word = %s\n", lw);
	return 0;
}
```

#### Using C-Candy:

```c
#include <stdlib.h>
#include <stdio.h>
#include <c-candy/str.h>

STRING* get_longest_word(STRING *s)
{
	int i, n;
	
	int lwi = 0;
	STRING **parts = str_split_whitespace(s, 100, &n);
	if(n < 1) return NULL;
	
	for(i = 1; i < n; ++i)
		if(str_len(parts[i]) > str_len(parts[lwi])) 
			lwi = i;
	
	STRING *lw = str_copy(parts[lwi]);
	for(i = 0; i < n; ++i) str_dump(parts[i]);
	free(parts);

	return lw;
}

int main(int argc, char **argv)
{
	STRING *s = string("The quick brown fox jumps over the lazy dog");
	STRING *lw = get_longest_word(s);
	
	printf("Longest word = %s\n", cstr(lw));
	
	str_dump_multi(s, lw);
	return 0;
}
```
