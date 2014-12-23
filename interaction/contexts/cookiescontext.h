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

    CookiesContext(QVector<Record> records)
        : records (records), resultMessage() { }

    QVector<Record> records;
    QString resultMessage;
};

}
}

#endif // COOKIESCONTEXT_H
