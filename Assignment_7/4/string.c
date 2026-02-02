
int MyStrlen(const char *str)
{
    int i = 0;
    int ilength = 0;


    while(*str != '\0')
    {
        ilength++;

        str++;
    }

    return ilength;
}