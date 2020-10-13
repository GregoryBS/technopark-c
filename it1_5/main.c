#include "letter_io.h"
#include "func.h"

int main(void)
{
    setbuf(stdout, NULL);
    letter ltr = { NULL, NULL, NULL, NULL };
    int rc = read_letter(&ltr);
    if (rc == OK)
    {
        int flag = FALSE;
        rc = is_spam(ltr, &flag);
        if (rc == OK)
        {
            if (flag == TRUE)
                printf("Letter is spam!\n");
            else
                printf("Letter is not spam.\n");
        }
        else
            printf("Error while checking letter!\n");
        free_mem(ltr);
    }
    else
        printf("Error while reading!\n");
    return rc;
}