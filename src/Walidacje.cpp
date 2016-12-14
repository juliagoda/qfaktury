#include <QMessageBox>
#include <QMap>
#include <QChar>
#include <QList>
#include <QDebug>
#include "Walidacje.h"

Walidacje* Walidacje::m_instance = nullptr;

Walidacje::Walidacje(QObject *parent) : QObject(parent)
{
    m_instance = this;
}


Walidacje::~Walidacje() {

    m_instance = nullptr;
}

Walidacje* Walidacje::instance()
{
    return m_instance;
}

bool Walidacje::validateAccount(QString text)
{
    QRegExp masks("^([A-Z]{2})?[0-9]{2}(\\s|-)?([0-9]{4}(\\s|-)?){5}[0-9]{4}$");

    if (!masks.exactMatch(text)) {

        QMessageBox::critical(
                0,
                "QFaktury",
                trUtf8("Źle podany rachunek bankowy. Wymagany format to \"SSXX-XXXX-XXXX-XXXX-XXXX-XXXX-XXXX\" lub \"XXXXXXXXXXXXXXXXXXXXXXXXXX\" lub \"XX XXXX XXXX XXXX XXXX XXXX XXXX\" lub \"SSXX XXXX XXXX XXXX XXXX XXXX XXXX\"  gdzie X oznacza cyfrę (zawsze jest 26 X), a S oznacza dużą literę"));

        return false;
    }
    return true;
}

bool Walidacje::validateEmail(QString text)
{
    // uppercase and lowercase Latin letters A to Z and a to z;
    // digits 0 to 9;
    // special characters !#$%&'*+-/=?^_`{|}~;
    // dot ., provided that it is not the first or last character unless quoted, and provided also that it does not appear consecutively unless quoted (e.g. John..Doe@example.com is not allowed but "John..Doe"@example.com is allowed);
    // space and "(),:;<>@[\] characters are allowed with restrictions (they are only allowed inside a quoted string, as described in the paragraph below, and in addition, a backslash or double-quote must be preceded by a backslash);
    // comments are allowed with parentheses at either end of the local-part; e.g. john.smith(comment)@example.com and (comment)john.smith@example.com are both equivalent to john.smith@example.com.
    // hyphen -, provided that it is not the first or last character.

    // niepewne czy wszystkie znaki sa dobrze backslashed
    QString form2 = QRegExp::escape("\"(),:;<>@[\\]");
    QRegExp masks("^([^(-\\.\\s)]{1})([(.+)(\"){1}]?)([^" + form2 + "]*)@{1}([^" + form2 + "]*)([(\"){1}(.+)]?)([^-\\.\\s]{1})$");

    if (!masks.exactMatch(text)) {

        QMessageBox::critical(
                0,
                "QFaktury",
                trUtf8("Źle podany adres email. Dozwolone są duże litery, małe litery, cyfry, specjalne znaki !#$%&'*+-/=?^_`{|}~, znak . (pod warunkiem że nie znajduje się na początku lub na końcu, a jak już to w znakach \"\"), znak - (o ile nie znajduje się na początku lub końcu) oraz znaki specjalne jak spacja,\"(),:;<>@[\\] (pod warunkiem że znajdują się w znakach \"\")"));

        return false;
    }

    return true;
}

bool Walidacje::validateIDCard(QString text)
{
    QRegExp masks("^([A-Z]{3}[0-9]{6})$");

    if (!masks.exactMatch(text)) {

        QMessageBox::critical(
                0,
                "QFaktury",
                trUtf8("Źle podany numer dowodu osobistego. Wymagany format dowodu to AAAXXXXXX, gdzie X oznacza cyfrę, a A oznacza dużą literę"));

        return false;
    }

    return true;
}

bool Walidacje::validateNIP(QString text)
{
    QRegExp masks("^(([0-9]{3})-([0-9]{2})-([0-9]{2})-([0-9]{3}))|(([0-9]{3})-([0-9]{3})-([0-9]{2})-([0-9]{2}))$");

    if (!masks.exactMatch(text)) {

        QMessageBox::critical(
                0,
                "QFaktury",
                trUtf8("Źle podany numer NIP. Wymagany format NIP to XXX-XXX-XX-XX lub XXX-XX-XX-XXX, gdzie X oznacza cyfrę"));

        return false;
    }

    return true;
}

bool Walidacje::validatePass(QString text)
{
    QRegExp masks("^([A-Z]{2}[0-9]{7})$");

    if (!masks.exactMatch(text)) {

        QMessageBox::critical(
                0,
                "QFaktury",
                trUtf8("Źle podany numer seryjny paszportu. Wymagany format dowodu to AAXXXXXXX, gdzie X oznacza cyfrę, a A oznacza dużą literę"));

        return false;
    }

    return true;
}

bool Walidacje::validatePESEL(QString text)
{
    QRegExp masks("^([0-9]{11})$");

    if (!masks.exactMatch(text)) {

        QMessageBox::critical(
                0,
                "QFaktury",
                trUtf8("Źle podany PESEL. Wymagany format to XXXXXXXXXXX (11 razy), gdzie X oznacza cyfrę"));

        return false;
    }

    return true;
}

bool Walidacje::validatePkwiu(QString text)
{
    QRegExp masks("^([0-9]{2}){1}(\\.([0-9]{1,2}){1})?(\\.([0-9]{1,2}){1})?(\\.([0-9]{1}){1})?$");

    if (!masks.exactMatch(text)) {

        QMessageBox::critical(
                0,
                "QFaktury",
                trUtf8("Źle podany numer PKWiU. Wymagany format to XX(.XX.XX.X) , gdzie X oznacza cyfrę, a część w nawiasie oznacza opcjonalną postać. Przykładowo więc może to też być XX.X czy XX.XX.XX"));

        return false;
    }

    return true;
}

bool Walidacje::validateRegon(QString text)
{
    QRegExp masks("^(([0-9]{7})|([0-9]{9}))$");

    if (!masks.exactMatch(text)) {

        QMessageBox::critical(
                0,
                "QFaktury",
                trUtf8("Źle podany REGON. Wymagany format to XXXXXXXXX (9 razy), gdzie X oznacza cyfrę"));

        return false;
    }

    return true;
}

bool Walidacje::validateTel(QString text)
{

    QRegExp masks("^((\\+([0-9]{2}))|(0)){1}([0-9]{5,20})$");

    if (!masks.exactMatch(text)) {

        QMessageBox::critical(
                0,
                "QFaktury",
                trUtf8("Źle podany numer telefonu. Wymagany format to +XX(X od 5 do 20) lub 0(X od 5 do 20), gdzie X oznacza cyfrę."));

        return false;
    }

    return true;
}

bool Walidacje::validateWebsite(QString text)
{
    QRegExp masks("^(https?://)?(www\\.)?(([0-9a-z]+)((-)*))+(\\.){1}((([a-z0-9]+)((/)*)((\\.)*))+)$");

    if (!masks.exactMatch(text)) {

        QMessageBox::critical(
                0,
                "QFaktury",
                trUtf8("Źle podany adres internetowy. Format pozwala na umieszczenie opcjonalnie http:// jak i www. Wymagany jest adres strony domowej"));

        return false;
    }

    return true;
}

bool Walidacje::validateZip(QString text)
{
    QRegExp masks("^([0-9]{2})-([0-9]{3})$");

    if (!masks.exactMatch(text)) {

        QMessageBox::critical(
                0,
                "QFaktury",
                trUtf8("Źle podany kod pocztowy. Wymagany format to XX-XXX, gdzie X oznacza cyfrę"));

        return false;
    }


    return true;
}

bool Walidacje::checkSumNIP(QString text)
{
    QString removedHyph = text.remove("-");
    QVector<int> list;
    QVector<int> numbersCheck = validateNumb(6,5,7,2,3,4,5,6,7);

    for (int i = 0; i < removedHyph.length(); i++)
    {
        list.append(removedHyph.at(i).digitValue());
    }

    int sum = 0;

    for (int i = 0; i < removedHyph.length() - 1; i++)
    {
        sum += list.at(i) * numbersCheck.at(i);
    }

    sum %= 11;


    if (sum == list.last()) return true;
    else {
        QMessageBox::critical(
                0,
                "QFaktury",
                trUtf8("Weryfikator cyfry kontrolnej NIP wykrył niepoprawny numer NIP. Sprawdź kolejność wpisanych liczb."));
        return false;
    }
}

bool Walidacje::checkSumREGON(QString text)
{
    QVector<int> list;
    QVector<int> numbersCheck;

    if (text.length() == 7) {
        numbersCheck = validateNumb(2,3,4,5,6,7);
    }

    if (text.length() == 9) {
        numbersCheck = validateNumb(8,9,2,3,4,5,6,7);
    }

    for (int i = 0; i < text.length(); i++)
    {
        list.append(text.at(i).digitValue());
    }

    int sum = 0;

    for (int i = 0; i < text.length() - 1; i++)
    {
        sum += list.at(i) * numbersCheck.at(i);
    }

    sum %= 11;


    if (sum == list.last()) return true;
    else {
        QMessageBox::critical(
                0,
                "QFaktury",
                trUtf8("Weryfikator cyfry kontrolnej REGON wykrył niepoprawny numer. Sprawdź kolejność wpisanych liczb."));
        return false;
    }
}

bool Walidacje::checkSumPESEL(QString text)
{
    QVector<int> list;
    QVector<int> numbersCheck = validateNumb(9,7,3,1,9,7,3,1,9,7,1);

    for (int i = 0; i < text.length(); i++)
    {
        list.append(text.at(i).digitValue());
    }

    int sum = 0;

    for (int i = 0; i < text.length() - 1; i++)
    {
        sum += list.at(i) * numbersCheck.at(i);
    }

    sum %= 10;


    if (sum == list.last()) return true;
    else {
        QMessageBox::critical(
                0,
                "QFaktury",
                trUtf8("Weryfikator cyfry kontrolnej PESEL wykrył niepoprawny numer. Sprawdź kolejność wpisanych liczb."));
        return false;
    }
}

bool Walidacje::checkSumAccount(QString text)
{

    if (symbols().contains(text.at(0)) && symbols().contains(text.at(1))) {

    QString trimmedText = text;
    if (text.contains(QRegExp("(\\s)"))) trimmedText = text.remove(" ");
    if (text.contains(QRegExp("(-)"))) trimmedText = text.remove("-");

    qDebug() << "numer rachunku po trymowaniu: " << trimmedText;
    QVector<int> list;


    for (int i = 4; i < trimmedText.length(); i++)
    {
        list.append(trimmedText.at(i).digitValue());
    }

    list.append(symbols().value(trimmedText.at(0)));
    qDebug() << "numer z rachunku po przeniesieniu i przekształceniu: " << symbols().value(trimmedText.at(0));
    list.append(symbols().value(trimmedText.at(1)));
    qDebug() << "numer z rachunku po przeniesieniu i przekształceniu: " << symbols().value(trimmedText.at(1));
    list.append(trimmedText.at(2).digitValue());
    qDebug() << "numer z rachunku po przeniesieniu i przekształceniu: " << trimmedText.at(2);
    list.append(trimmedText.at(3).digitValue());
    qDebug() << "numer z rachunku po przeniesieniu i przekształceniu: " << trimmedText.at(3);


    QString desc1 = "";
    QString desc2 = "";

    for (int i=0; i < list.size(); i++) {


       if (i >= list.size()/2) {
           desc2 += QString::number(list.at(i));
           qDebug() << "desc2: " << desc2;
       } else {
           desc1 += QString::number(list.at(i));
           qDebug() << "desc1: " << desc1;
       }
    }

    long sum = desc1.toLong(); // zamienić na ulong
    sum %= 97;
    QString res = QString::number(sum) + desc2;
    qDebug() << "res: " << res;
    long reslong = res.toLongLong();
    reslong %= 97;
    qDebug() << "wynik: " << reslong;



    if (reslong == 1) return true;
    else {
        QMessageBox::critical(
                0,
                "QFaktury",
                trUtf8("Weryfikator konta bankowego IBAN wykrył niepoprawny numer. Sprawdź kolejność wpisanych liczb."));
        return false;
    }
    } else {
        return true;
    }
}

bool Walidacje::checkSumIDCard(QString text)
{

    QVector<int> numbersCheck = validateNumb(7,3,1,7,3,1,7,3);

    QString transferedText = text;

    int first = symbols().value(transferedText.at(0));
    int second = symbols().value(transferedText.at(1));
    int third = symbols().value(transferedText.at(2));


    QVector<int> list;

    list.append(first);
    list.append(second);
    list.append(third);


    for (int i = 4; i < text.length(); i++)
    {
        list.append(transferedText.at(i).digitValue());
    }

    int sum = 0;

    for (int i = 0; i < text.length() - 1; i++)
    {
        sum += list.at(i) * numbersCheck.at(i);
    }

    sum %= 10;

    QByteArray byteArray = text.toLocal8Bit();
    byteArray = byteArray.remove(0,3);
    byteArray = byteArray.remove(1,5);
    int result = byteArray.toInt();

    if (sum == result) return true;
    else {
        QMessageBox::critical(
                0,
                "QFaktury",
                trUtf8("Weryfikator polskiego dowodu osobistego wykrył niepoprawny numer. Sprawdź kolejność wpisanych znaków. Możesz także zgłosić błąd numeru dowodu w odpowiednim Urzędzie Miasta lub Gminy."));
        return false;
    }
}

bool Walidacje::checkSumPass(QString text) {

    QVector<int> numbersCheck = validateNumb(7,3,9,1,7,3,1,7,3);

    QString transferedText = text;

    int first = symbols().value(transferedText.at(0));
    int second = symbols().value(transferedText.at(1));


    QVector<int> list;

    list.append(first);
    list.append(second);


    for (int i = 2; i < text.length(); i++)
    {
        list.append(transferedText.at(i).digitValue());
    }

    int sum = 0;

    for (int i = 0; i < text.length(); i++)
    {
        sum += list.at(i) * numbersCheck.at(i);
    }

    sum %= 10;

    if (sum == 0) return true;
    else {
        QMessageBox::critical(
                0,
                "QFaktury",
                trUtf8("Weryfikator numeru seryjnego paszportu wykrył niepoprawny numer. Sprawdź kolejność wpisanych znaków. Możesz także zgłosić błąd numeru paszportu w najbliższym Urzędzie Wojewódzkim."));
        return false;
    }

}

bool Walidacje::isEmptyField(QLineEdit *field, QString title)
{
    if (field->text().isEmpty())
    {
        QMessageBox::critical(
                0,
                "QFaktury",
                trUtf8("Firma nie może zostać zapisana, pownieważ brakuje wymaganych danych w polu - ") + title);
        return true;
    }

    return false;
}


bool Walidacje::isEmptyField(QString input, QString title)
{
    if (input.isEmpty())
    {
        QMessageBox::critical(
                0,
                "QFaktury",
                trUtf8("Firma nie może zostać zapisana, pownieważ brakuje wymaganych danych w polu - ") + title);
        return true;
    }

    return false;
}
