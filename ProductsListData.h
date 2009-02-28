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
	QString codeX() const {
		return code;
	}
	QString currX() const {
		return curr;
	}
	QString pkwiuX() const {
		return pkwiu;
	}
private:
	QString code;
	QString curr;
	QString pkwiu;
};
