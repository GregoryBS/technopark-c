#include "letter_io.h"

void free_mem(letter ltr)
{
    free(ltr.sender);
    free(ltr.receiver);
    free(ltr.theme);
    free(ltr.text);
}

int read_letter(letter *ltr)
{
    if (!ltr)
        return ERR_PARAM;

    int rc = read_text(&(ltr->sender), '\n');
    if (rc == OK)
    {
        rc = read_text(&(ltr->receiver), '\n');
        if (rc == OK)
        {
            rc = read_text(&(ltr->theme), '\n');
            if (rc == OK)
            {
                rc = read_text(&(ltr->text), '\0');
            }
        }
    }
    if (rc != OK)
        free_mem(*ltr);
    return rc;
}

int read_text(char **text, char delimiter)
{
    if (!text)
        return ERR_PARAM;

    int rc = OK, flag = OK;
    string s = { NULL, 0, 0, BUF_SIZE };
    char c = delimiter;
    while (rc == OK && flag == OK && (c = getc(stdin)) != EOF)
    {
        if (s.len == s.size)
        {
            char *tmp = (char*) realloc(s.data, (s.size + s.space) * \
                        sizeof(char));
            if (tmp)
            {
                s.data = tmp;
                s.size += s.space;
            }
            else
                rc = ERR_MEM;
        }
        if (rc == OK)
        {
            s.data[s.len] = c;
            s.len += 1;
        }
        if (c == delimiter)
            flag = !flag;
    }
    if (rc == OK)
    {
        if (s.len > 0)
        {
            *text = s.data;
            (*text)[s.len - 1] = '\0';
        }
        else
            rc = ERR_IO;
    }
    return rc;
}
