#include "nlp.h"

int main()
{
    char buf[30000];

    FILE* fr = fopen("text.txt", "r");
	fread(buf, sizeof(char), 30000, fr);

	text_t text = text_new(buf);
	text_toSentences(text);

	FILE* fw = fopen("result.txt", "w");

	text_sortSentences(text);
	text_writeToFile(text, fw);


	text_free(text);

	fclose(fr);
	fclose(fw);

    return 0;
}
