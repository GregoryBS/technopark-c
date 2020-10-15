#include "letter_io.h"
#include "spam.h"

int main(void)
{
    setbuf(stdout, NULL);
    letter ltr = { NULL, NULL, NULL, NULL };
    int rc = read_letter(&ltr);
    if (rc != OK)
    {
        printf("Error while reading!\n");
        return rc;
    }
    
    bool flag = false;
    rc = is_spam(&ltr, &flag);
    if (rc == OK)
    {
        if (flag == true)
            printf("Letter is spam!\n");
        else
            printf("Letter is not spam.\n");
    }
    else
        printf("Error while checking letter!\n");
    free_mem(&ltr);

    return rc;
}
