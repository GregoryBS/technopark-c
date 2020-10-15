#include "spam.h"

int is_spam(letter *ltr, bool *flag)
{
    if (!flag || !ltr)
        return ERR_PARAM;
    if (ltr->sender == NULL || ltr->theme == NULL || ltr->text == NULL)
        return ERR_PARAM;

    char *flag1 = NULL, *flag2 = NULL, *flag3 = NULL;
    flag1 = strstr(ltr->sender, SPAM);
    flag2 = strstr(ltr->theme, SPAM);
    flag3 = strstr(ltr->text, SPAM);
    if (flag1 || flag2 || flag3)
        *flag = true;
    else
        *flag = false;

    return OK;
}
