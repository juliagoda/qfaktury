#include <QString>

/* Class used in the Products list
 *
 */
class ProductsListData {
public:
	ProductsListData() {
	}
	ProductsListData(QString c1, QString c2, QString c3) {
		code = c1;
		if (code == "")
			code = "-";
		curr = c2;
		if (curr == "")
			curr = "-";
		pkwiu = c3;
		if (pkwiu == "")
			pkwiu = "-";
	}
	QString getCode() const {
		return code;
	}
	QString getQuantityType() const {
		return curr;
	}
	QString getPkwiu() const {
		return pkwiu;
	}

	QString toString() {
		return	"ProductsListData \n[" + getCode() + "\n" + getQuantityType() + "\n" + getPkwiu() + "]\n";
	}
private:
	QString code;
	QString curr;
	QString pkwiu;
};
