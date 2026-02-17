
int MyStrlen(const char *str)
{
    int ilength = 0;

    while(*str != '\0')
    {
        ilength++;

        str++;
    }

    return ilength;
}


char *MyStrcpy(char *dest, const char *src)
{
    char *start = dest;

    while (*src != '\0')
    {
        *dest = *src;

        src++;
        dest++;
    }
    
    *dest = '\0';

    return start;
}


char *MyStrncpy(char *dest, const char *src, int num)
{
    char *start = dest;

    while (num > 0 && *src != '\0')
    {
        *dest = *src;

        src++;
        dest++;
        num--;
    }
    
    while (num > 0)
    {
        *dest++ = '\0';
        num--;
    }

    return start;
}


char *Mystrcat(char *dest, char *src)
{
    char *start = dest;

    while (*dest != '\0')
    {
        dest++;
    }
    
    while (*src != '\0')
    {
        *dest = *src;
        dest++;                
        src++;
    }

    *dest = '\0';

    return start;
}


int Mystrcmp(const char *str1, const char *str2)
{
    while (*str1 != '\0' && *str2 != '\0')
    {
        if (*str1 != *str2)
        {
            return (unsigned char)*str1 - (unsigned char)*str2;
        }
        str1++;
        str2++;
    }

    return (unsigned char)*str1 - (unsigned char)*str2;
}

int Mystrncmp(const char *str1, const char *str2, int n)
{
    while (n > 0 && *str1 != '\0' && *str2 != '\0')
    {
        if (*str1 != *str2)
        {
            return (unsigned char)*str1 - (unsigned char)*str2;
        }
        str1++;
        str2++;
        n--;
    }

    if(n == 0)
    {
        return 0;
    }

    return (unsigned char)*str1 - (unsigned char)*str2;
}

