#if defined WITH_CAN || defined WITH_SERIAL

#ifndef SKTCAN_H
#define SKTCAN_H

#include <QString>
#include <QThread>

#include "canframe.h"

namespace CanInternals
{
    class Socket
    {
        public:
            Socket (const QString &interfaceName);

        protected:
            int number;
            bool ready;
    };

    class WriteSocket : public Socket
    {
        public:
            WriteSocket (const QString &interfaceName);

            bool send (const CanFrame &frame);
    };
    extern WriteSocket writeSocket;

    class ReadSocket : public Socket
    {
        public:
            ReadSocket (const QString &interfaceName);

            CanFrame read ();
    };

    class ReadSocketThread : public QThread
    {
        Q_OBJECT
    public:
        ReadSocketThread (QString interfaceName);

    signals:
        void messageReceived (CanFrame frame);

    private:
        ReadSocket readSocket;

        void run ();
    };
    extern ReadSocketThread readSocketLoop;

}
#endif // SKTCAN_H

#endif
