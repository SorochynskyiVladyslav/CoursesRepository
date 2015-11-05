#include <stdio.h>
#include <string.h>
#include <math.h>
char * process(char * resultStr, const char * text[], int linesNum, const char * extraStr)
{
	const char * line;
	int i, j, flag, index=-1, index1=0;
	for (i = 0; i < linesNum; i++)
	{
		line = text[i];
		flag = 1;
		for (j = -1; j == -1 || j < strlen(line) && flag == 1; j++)
		{
			if (j == -1 || line[j] == ' ' )
			{
				if (line[j + 1] == 'e' || line[j + 1] == 'y' || line[j + 1] == 'u' || line[j + 1] == 'i' || line[j + 1] == 'o' || line[j + 1] == 'a' || line[j + 1] == 'E' || line[j + 1] == 'U' || line[j + 1] == 'I' || line[j + 1] == 'O' || line[j + 1] == 'A')
					flag = flag;
				else
					flag = 0;
			}
		}
		for (j = 1; j < (strlen(line)+1) && flag == 1; j++)
		{
		    if (line[j]==' ' || j == strlen(line))
            {
               if ((line[j - 1] != 'e' && line[j - 1] != 'y' && line[j - 1] != 'u' && line[j - 1] != 'i' && line[j - 1] != 'o' && line[j - 1] != 'a' && line[j - 1] != 'E' && line[j - 1] != 'U' && line[j - 1] != 'I' && line[j - 1] != 'O' && line[j - 1] != 'A') && ((line[j - 1] <= 122 && line[j - 1] > 97) || (line[j - 1] > 65 && line[j - 1] <= 90)))
                flag = flag;
               else
                flag = 0;
            }

		}

		if (flag == 1)
		{
		    index = i;
			i = linesNum;
			j = sprintf(resultStr, "%i ", index);
			resultStr[j] = ' ';
			resultStr[j + 1] = '\0';
		}
		else if (i==(linesNum-1))
        {
            j = sprintf(resultStr, "-1 \0");
        }
	}
			j = -1;
			flag = 0;
			while ((j == -1 || j<strlen(extraStr)) && index1==0)
			{
			    if (flag == 1)
                {
                    if ((line[j - 1] != 'e' && line[j - 1] != 'y' && line[j - 1] != 'u' && line[j - 1] != 'i' && line[j - 1] != 'o' && line[j - 1] != 'a' && line[j - 1] != 'E' && line[j - 1] != 'U' && line[j - 1] != 'I' && line[j - 1] != 'O' && line[j - 1] != 'A') && ((line[j - 1] <= 122 && line[j - 1] > 97) || (line[j - 1] > 65 && line[j - 1] <= 90)))
                    {
                        index1 = j - 1;
                    }
                    else
                    {
                        flag = 0;
                    }
                }
				if ((j == -1 || extraStr[j] == ' ') && index1 == 0)
				{
					if (extraStr[j + 1] == 'e' || extraStr[j + 1] == 'y' || extraStr[j + 1] == 'u' || extraStr[j + 1] == 'i' || extraStr[j + 1] == 'o' || extraStr[j + 1] == 'a' || extraStr[j + 1] == 'E' || extraStr[j + 1] == 'U' || extraStr[j + 1] == 'I' || extraStr[j + 1] == 'O' || extraStr[j + 1] == 'A')
						{
						    flag = 1;
						    index = j + 1;
						}
					else
						flag = 0;
				}
				j++;
				while (extraStr[j] != ' ' && extraStr[j] != '\0' )
                {
                    j++;
                }
			}
			if (flag==1 && (line[j - 1] != 'e' && line[j - 1] != 'y' && line[j - 1] != 'u' && line[j - 1] != 'i' && line[j - 1] != 'o' && line[j - 1] != 'a' && line[j - 1] != 'E' && line[j - 1] != 'U' && line[j - 1] != 'I' && line[j - 1] != 'O' && line[j - 1] != 'A') && ((line[j - 1] <= 122 && line[j - 1] > 97) || (line[j - 1] > 65 && line[j - 1] <= 90)))
			{
			    index1 = j;
			}
			if (index1 != 0)
            {
                for (j=index; j<(index1+1); j++)
                {
                    resultStr[strlen(resultStr)]=extraStr[j];
                    resultStr[strlen(resultStr) + 1] = '\0';
                }
            }
			else
				strcat(resultStr, "NULL");



	return resultStr;
}
