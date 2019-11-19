#include <QCoreApplication>
#include <QtNetwork>

static int count = 0;

static void getNumber()
{
    QNetworkAccessManager manager;
    QString url = "https://www.instagram.com/p/B5ANKyQIZCT/";
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(url)));
    QEventLoop event;
    QObject::connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    QString html = response->readAll();
    QRegularExpression re("meta content=\"(?<count>(\\w+)) mentions J’aime");
    int newCount = re.match(html).captured("count").toInt();
    if (newCount > count){
        qDebug() << "YEAHHHHH UN NOUVEAU LIKE !";
        count = newCount;
        qDebug() << "Il y a maintenant" << count << "likes sur la photo :)";
    }
    else qDebug() << "Il y a toujours" << newCount << "likes sur la photo !";
}

int main(int argc, char *argv[])
{
    QTimer timer;
    timer.setInterval(10000);
    QCoreApplication a(argc, argv);
    timer.start();
    QObject::connect(&timer, &QTimer::timeout, getNumber);

    return a.exec();
}
