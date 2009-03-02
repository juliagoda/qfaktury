QFaktury to darmowy system fakturujÄ…cy pracujÄ…cy w systemach Windows, Linux i Mac OS.
UmoÅ¼liwia on drukowanie faktur, faktur pro forma i korekt. UmoÅ¼liwia zarzÄ…dzanie bazÄ… faktur, towarÃ³w 
i kontrahentÃ³w.

compilacja na windows: 
cmake -G "MinGW Makefiles"
make


integracja z jakas ksiazka adresowa???

    // connect slots
	connect(actionForum, SIGNAL (activated ()), this, SLOT(forum()));
	connect(applyFiltrBtn, SIGNAL (clicked()), this, SLOT(rereadHist()));
	connect(plikDane_firmyAction, SIGNAL(activated()), this, SLOT(daneFirmyClick()));
	connect(plikKoniecAction, SIGNAL(activated()), this, SLOT(close()));
	connect(kontrahenciDodajAction, SIGNAL(activated()), this, SLOT(kontrClick()));
	connect(kontrahenciUsunAction, SIGNAL(activated()), this, SLOT(kontrDel()));
	connect(kontrahenciEdycjaAction, SIGNAL(activated()), this, SLOT(kontrEd()));
	connect(fakturyDodajAction, SIGNAL(activated()), this, SLOT(newFra()));
	connect(fakturyUsunAction, SIGNAL(activated()), this, SLOT(delFHist()));
	connect(fakturyEdAction, SIGNAL(activated()), this, SLOT(editFHist()));
	connect(tableH, SIGNAL(doubleClicked(int,int,int,QPoint)), this, SLOT(editFHist()));
	connect(pomocO_QtAction, SIGNAL(activated()), this, SLOT(aboutQt()));
	connect(pomocO_programieAction, SIGNAL(activated()), this, SLOT(oProg()));
	connect(tableK, SIGNAL(doubleClicked(int,int,int,QPoint)), this, SLOT(kontrEd()));
	connect(plikUstawieniaAction, SIGNAL(activated()), this, SLOT(settClick()));
	connect(tabWidget2, SIGNAL(currentChanged(QWidget*)), this, SLOT(tabChanged(QWidget*)));
	connect(pomocPomocAction, SIGNAL(activated()), this, SLOT(pomoc()));
	connect(towaryDodajAction, SIGNAL(activated()), this, SLOT(towaryDodaj()));
	connect(towaryEdycjaAction, SIGNAL(activated()), this, SLOT(towaryEdycja()));
	connect(towaryUsunAction, SIGNAL(activated()), this, SLOT(towaryUsun()));
	connect(tableT, SIGNAL(doubleClicked(int,int,int,QPoint)), this, SLOT(towaryEdycja()));
	connect(fakturyKorektaAction, SIGNAL(activated()), this, SLOT(newKor()));
	connect(fakturyPFormaAction, SIGNAL(activated()), this, SLOT(newPForm()));
	connect(prevPageAction, SIGNAL(activated()), this, SLOT(prevPage()));
	connect(nextPageAction, SIGNAL(activated()), this, SLOT(nextPage()));