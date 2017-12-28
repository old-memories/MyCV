#include "SetSEWidget.h"

SetSEWidget::SetSEWidget(QWidget *parent)
	:
	QDialog(parent)
{
	code = QTextCodec::codecForName("gb18030");
	
	k0 = new QPlainTextEdit(QString::number(1));
	k1 = new QPlainTextEdit(QString::number(1));
	k2 = new QPlainTextEdit(QString::number(1));
	k3 = new QPlainTextEdit(QString::number(1));
	k4 = new QPlainTextEdit(QString::number(1));
	k5 = new QPlainTextEdit(QString::number(1));
	k6 = new QPlainTextEdit(QString::number(1));
	k7 = new QPlainTextEdit(QString::number(1));
	k8 = new QPlainTextEdit(QString::number(1));
	k9 = new QPlainTextEdit(QString::number(1));
	k10 = new QPlainTextEdit(QString::number(1));
	k11 = new QPlainTextEdit(QString::number(1));
	k12 = new QPlainTextEdit(QString::number(1));
	k13 = new QPlainTextEdit(QString::number(1));
	k14 = new QPlainTextEdit(QString::number(1));
	k15 = new QPlainTextEdit(QString::number(1));
	k15 = new QPlainTextEdit(QString::number(1));
	k16 = new QPlainTextEdit(QString::number(1));
	k17 = new QPlainTextEdit(QString::number(1));
	k18 = new QPlainTextEdit(QString::number(1));
	k19 = new QPlainTextEdit(QString::number(1));
	k20 = new QPlainTextEdit(QString::number(1));
	k21 = new QPlainTextEdit(QString::number(1));
	k22 = new QPlainTextEdit(QString::number(1));
	k23 = new QPlainTextEdit(QString::number(1));
	k23 = new QPlainTextEdit(QString::number(1));
	k24 = new QPlainTextEdit(QString::number(1));


	applyButton = new QPushButton(QString(code->toUnicode("ºÃ")));
	cancelButton = new QPushButton(QString(code->toUnicode("È¡Ïû")));
	connect(applyButton, SIGNAL(clicked(bool)), this, SLOT(on_clicked_applyButton()));
	connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(on_clicked_cancelButton()));

	gridLayout = new QGridLayout();

	gridLayout->addWidget(k0, 0, 0, 1, 1);
	gridLayout->addWidget(k1, 0, 1, 1, 1);
	gridLayout->addWidget(k2, 0, 2, 1, 1);
	gridLayout->addWidget(k3, 0, 3, 1, 1);
	gridLayout->addWidget(k4, 0, 4, 1, 1);

	gridLayout->addWidget(k5, 1, 0, 1, 1);
	gridLayout->addWidget(k6, 1, 1, 1, 1);
	gridLayout->addWidget(k7, 1, 2, 1, 1);
	gridLayout->addWidget(k8, 1, 3, 1, 1);
	gridLayout->addWidget(k9, 1, 4, 1, 1);

	gridLayout->addWidget(k10, 2, 0, 1, 1);
	gridLayout->addWidget(k11, 2, 1, 1, 1);
	gridLayout->addWidget(k12, 2, 2, 1, 1);
	gridLayout->addWidget(k13, 2, 3, 1, 1);
	gridLayout->addWidget(k14, 2, 4, 1, 1);

	gridLayout->addWidget(k15, 3, 0, 1, 1);
	gridLayout->addWidget(k16, 3, 1, 1, 1);
	gridLayout->addWidget(k17, 3, 2, 1, 1);
	gridLayout->addWidget(k18, 3, 3, 1, 1);
	gridLayout->addWidget(k19, 3, 4, 1, 1);

	gridLayout->addWidget(k20, 4, 0, 1, 1);
	gridLayout->addWidget(k21, 4, 1, 1, 1);
	gridLayout->addWidget(k22, 4, 2, 1, 1);
	gridLayout->addWidget(k23, 4, 3, 1, 1);
	gridLayout->addWidget(k24, 4, 4, 1, 1);



	



	gridLayout->addWidget(applyButton, 6, 0, 1, 2);
	gridLayout->addWidget(cancelButton, 6, 2, 1, 2);


	this->setLayout(gridLayout);


	
}



void SetSEWidget::on_clicked_applyButton() {
	std::vector<char> kernal;
	kernal.push_back(char(k0->toPlainText().toInt()));
	kernal.push_back(char(k1->toPlainText().toInt()));
	kernal.push_back(char(k2->toPlainText().toInt()));
	kernal.push_back(char(k3->toPlainText().toInt()));
	kernal.push_back(char(k4->toPlainText().toInt()));
	kernal.push_back(char(k5->toPlainText().toInt()));
	kernal.push_back(char(k6->toPlainText().toInt()));
	kernal.push_back(char(k7->toPlainText().toInt()));
	kernal.push_back(char(k8->toPlainText().toInt()));
	kernal.push_back(char(k9->toPlainText().toInt()));
	kernal.push_back(char(k10->toPlainText().toInt()));
	kernal.push_back(char(k11->toPlainText().toInt()));
	kernal.push_back(char(k12->toPlainText().toInt()));
	kernal.push_back(char(k13->toPlainText().toInt()));
	kernal.push_back(char(k14->toPlainText().toInt()));
	kernal.push_back(char(k15->toPlainText().toInt()));
	kernal.push_back(char(k16->toPlainText().toInt()));
	kernal.push_back(char(k17->toPlainText().toInt()));
	kernal.push_back(char(k18->toPlainText().toInt()));
	kernal.push_back(char(k19->toPlainText().toInt()));
	kernal.push_back(char(k20->toPlainText().toInt()));
	kernal.push_back(char(k21->toPlainText().toInt()));
	kernal.push_back(char(k22->toPlainText().toInt()));
	kernal.push_back(char(k23->toPlainText().toInt()));
	kernal.push_back(char(k24->toPlainText().toInt()));
	
	emit applySE(kernal);
	this->close();
}
void SetSEWidget::on_clicked_cancelButton() {
	this->close();
}



