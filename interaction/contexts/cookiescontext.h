#ifndef COOKIESCONTEXT_H
#define COOKIESCONTEXT_H

#include <QVector>
#include <QString>
#include "../context.h"
#include "qtBlokLib/cookies.h"

namespace Interaction {
namespace Contexts {

class CookiesContext : public Context
{
public:
    struct Record {
        Record (Cookie *cookie, QString text)
            : cookie (cookie), value (-1), text (text)
        { }
        Record ()
            : Record (nullptr, "ЗАПРЕЩЕНО")
        { }

        Cookie *cookie;
        int value;
        QString text;
    };

    CookiesContext(QVector<Record> records,
                   QString successMessageText = "Параметры записаны",
                   QString failureMessageText = "Ошибка записи параметров")
        : records (records), resultMessage(),
          successMessageText (successMessageText),
          failureMessageText (failureMessageText)
    { }

    QVector<Record> records;
    QString resultMessage;

    QString successMessageText;
    QString failureMessageText;
};

}
}

#endif // COOKIESCONTEXT_H
