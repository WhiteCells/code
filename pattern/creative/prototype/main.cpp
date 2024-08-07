#include "email.h"

int main(int argc, char *argv[]) {
    Email *mail = new Email("hello", "world");
    mail->getEmailInfo();

    Email *mail2 = mail->clone();
    mail2->changeText("HELLO");
    mail2->changeAttachment("HELLO");
    mail2->getEmailInfo();

    return 0;
}