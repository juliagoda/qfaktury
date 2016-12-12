#ifndef WALIDACJE_H
#define WALIDACJE_H
#include <QObject>
#include <QRegExp>
#include <QLineEdit>


class Walidacje : public QObject
{
    Q_OBJECT
public:
    explicit Walidacje(QObject *parent = 0);
    ~Walidacje();
    static Walidacje * instance();
    bool validateNIP(QString);
    bool validatePESEL(QString);
    bool validatePass(QString);
    bool validateAccount(QString);
    bool validateEmail(QString);
    bool validateWebsite(QString);
    bool validateTel(QString);
    bool validatePkwiu(QString);
    bool validateIDCard(QString);
    bool validateRegon(QString);
    bool validateZip(QString);
    bool isEmptyField(QLineEdit*,QString);
    bool isEmptyField(QString,QString);
    bool checkSumNIP(QString);
    bool checkSumREGON(QString);
    bool checkSumPESEL(QString);
    bool checkSumAccount(QString);
    bool checkSumIDCard(QString);
    bool checkSumPass(QString);


private:
    static Walidacje * m_instance;

signals:

public slots:
};

#endif // WALIDACJE_H
