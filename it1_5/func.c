#include "func.h"

int is_spam(letter ltr, int *flag)
{
    if (!flag)
        return ERR_PARAM;
    if (ltr.sender == NULL || ltr.theme == NULL || ltr.text == NULL)
        return ERR_PARAM;

    char *flag1 = NULL, *flag2 = NULL, *flag3 = NULL;
    flag1 = strstr(ltr.sender, SPAM);
    flag2 = strstr(ltr.theme, SPAM);
    flag3 = strstr(ltr.text, SPAM);
    if (flag1 || flag2 || flag3)
        *flag = TRUE;
    else
        *flag = FALSE;

    return OK;
}