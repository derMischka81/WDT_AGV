#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cstdio>
#include <QMessageBox>
#include "QLabelClick.h"

#include "../../include/wdt_dio.h"

#define __UI_ONLY__  ( 0 )  // testing without linking library

#if ( __UI_ONLY__ )

#define InitDIO()  1
#define DIReadLine(ch)  1
#define DIReadPort()  0xabcd
#define DOWriteLine(ch, value)
#define DOWritePort(value)
#define DOWriteLineChecked(ch, value)
#define DOWritePortChecked(value)

#else

#if defined(_WIN64)
#pragma comment(lib, "WDT_DIO64.lib")
#elif defined(_WIN32)
#pragma comment(lib, "WDT_DIO32.lib")
#endif

#endif

struct __ItemBit
{
    QLabel*         label;
    unsigned int    value;
};
static __ItemBit  gDiBits[0x10];
static __ItemBit  gDoBits[0x10];

static unsigned const  gDiBitsLen = sizeof(gDiBits)/sizeof(*gDiBits);
static unsigned const  gDoBitsLen = sizeof(gDoBits)/sizeof(*gDoBits);

static __ItemBit* const  gDiBitsEnd = gDiBits +gDiBitsLen;
static __ItemBit* const  gDoBitsEnd = gDoBits +gDoBitsLen;

struct __ItemPort
{
    QLineEdit*      edit;
    unsigned int    value;
};
static __ItemPort  gDiPort;
static __ItemPort  gDoPort;


static __inline
void __ErrMsg(const QString& errMsg)
{
    QMessageBox::critical(0, "ERROR", errMsg);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);

#if ( __UI_ONLY__ )
    this->setWindowTitle(this->windowTitle() +"   <-- TEST UI");
#endif

    gDiBits[0x00].label = this->ui->labelPortDiBit0;
    gDiBits[0x01].label = this->ui->labelPortDiBit1;
    gDiBits[0x02].label = this->ui->labelPortDiBit2;
    gDiBits[0x03].label = this->ui->labelPortDiBit3;
    gDiBits[0x04].label = this->ui->labelPortDiBit4;
    gDiBits[0x05].label = this->ui->labelPortDiBit5;
    gDiBits[0x06].label = this->ui->labelPortDiBit6;
    gDiBits[0x07].label = this->ui->labelPortDiBit7;
    gDiBits[0x08].label = this->ui->labelPortDiBit8;
    gDiBits[0x09].label = this->ui->labelPortDiBit9;
    gDiBits[0x0A].label = this->ui->labelPortDiBitA;
    gDiBits[0x0B].label = this->ui->labelPortDiBitB;
    gDiBits[0x0C].label = this->ui->labelPortDiBitC;
    gDiBits[0x0D].label = this->ui->labelPortDiBitD;
    gDiBits[0x0E].label = this->ui->labelPortDiBitE;
    gDiBits[0x0F].label = this->ui->labelPortDiBitF;
    gDiPort.edit = this->ui->lineEditPortDiValue;

    gDoBits[0x00].label = this->ui->labelPortDoBit0;
    gDoBits[0x01].label = this->ui->labelPortDoBit1;
    gDoBits[0x02].label = this->ui->labelPortDoBit2;
    gDoBits[0x03].label = this->ui->labelPortDoBit3;
    gDoBits[0x04].label = this->ui->labelPortDoBit4;
    gDoBits[0x05].label = this->ui->labelPortDoBit5;
    gDoBits[0x06].label = this->ui->labelPortDoBit6;
    gDoBits[0x07].label = this->ui->labelPortDoBit7;
    gDoBits[0x08].label = this->ui->labelPortDoBit8;
    gDoBits[0x09].label = this->ui->labelPortDoBit9;
    gDoBits[0x0A].label = this->ui->labelPortDoBitA;
    gDoBits[0x0B].label = this->ui->labelPortDoBitB;
    gDoBits[0x0C].label = this->ui->labelPortDoBitC;
    gDoBits[0x0D].label = this->ui->labelPortDoBitD;
    gDoBits[0x0E].label = this->ui->labelPortDoBitE;
    gDoBits[0x0F].label = this->ui->labelPortDoBitF;
    gDoPort.edit = this->ui->lineEditPortDoValue;
    gDoPort.edit->setText("0x0000");


	if ( ! InitDIO() )
	{
		__ErrMsg("InitDIO --> FAIL");
	}

    return ;
}

MainWindow::~MainWindow()
{
    delete ui;
    return ;
}

static void __ItemBit_InverseDoBit(unsigned int index)
{
    if ( gDoBitsLen < index ) { return ; }

    __ItemBit* const  bit = gDoBits +index;  // current
    bit->value = ! (bit->value);
    bit->label->setText(QString::number(bit->value));

    gDoPort.value = (gDoPort.value & (~(0x01 << index))) | (bit->value << index);

    char  buf[8];

    std::snprintf(buf, sizeof(buf), "0x%04X", gDoPort.value);
    gDoPort.edit->setText(buf);
    return ;
}
void MainWindow::on_labelPortDoBit0_clicked() { __ItemBit_InverseDoBit(0x00); }
void MainWindow::on_labelPortDoBit1_clicked() { __ItemBit_InverseDoBit(0x01); }
void MainWindow::on_labelPortDoBit2_clicked() { __ItemBit_InverseDoBit(0x02); }
void MainWindow::on_labelPortDoBit3_clicked() { __ItemBit_InverseDoBit(0x03); }
void MainWindow::on_labelPortDoBit4_clicked() { __ItemBit_InverseDoBit(0x04); }
void MainWindow::on_labelPortDoBit5_clicked() { __ItemBit_InverseDoBit(0x05); }
void MainWindow::on_labelPortDoBit6_clicked() { __ItemBit_InverseDoBit(0x06); }
void MainWindow::on_labelPortDoBit7_clicked() { __ItemBit_InverseDoBit(0x07); }
void MainWindow::on_labelPortDoBit8_clicked() { __ItemBit_InverseDoBit(0x08); }
void MainWindow::on_labelPortDoBit9_clicked() { __ItemBit_InverseDoBit(0x09); }
void MainWindow::on_labelPortDoBitA_clicked() { __ItemBit_InverseDoBit(0x0A); }
void MainWindow::on_labelPortDoBitB_clicked() { __ItemBit_InverseDoBit(0x0B); }
void MainWindow::on_labelPortDoBitC_clicked() { __ItemBit_InverseDoBit(0x0C); }
void MainWindow::on_labelPortDoBitD_clicked() { __ItemBit_InverseDoBit(0x0D); }
void MainWindow::on_labelPortDoBitE_clicked() { __ItemBit_InverseDoBit(0x0E); }
void MainWindow::on_labelPortDoBitF_clicked() { __ItemBit_InverseDoBit(0x0F); }

void MainWindow::on_pushButtonChnDi_clicked()
{
    unsigned int const  index = this->ui->comboBoxChn->currentIndex();

    if ( gDiBitsLen < index ) { return ; }

    BOOL const  data = DIReadLine((BYTE) index);

    this->ui->labelChnRead->setText(QString::number(data));
    return ;
}

void MainWindow::on_pushButtonChnDo_clicked()
{
    unsigned int const  index = this->ui->comboBoxChn->currentIndex();

    if ( gDoBitsLen < index ) { return ; }

    BOOL const  data = this->ui->comboBoxChnDo->currentIndex();

    __ItemBit* const  bit = gDoBits +index;  // current

    bit->label->setText(QString::number(data));

    bit->value = data;
    gDoPort.value = (gDoPort.value & (~(0x01 << index))) | (bit->value << index);

    char  buf[8];

    std::snprintf(buf, sizeof(buf), "0x%04X", gDoPort.value);
    gDoPort.edit->setText(buf);

    DOWriteLineChecked(index, data);
    return ;
}

void MainWindow::on_pushButtonPortDi_clicked()
{
    WORD  value;
    char  buf[8];

    gDiPort.value = value = DIReadPort();

    std::snprintf(buf, sizeof(buf), "0x%04X", value);
    gDiPort.edit->setText(buf);

    buf[1] = '\0';

    for (__ItemBit* bit = gDiBits; gDiBitsEnd > bit; ++bit, value >>= 1 )
    {
        bit->value = value & 0x01;
        buf[0] = '0' + bit->value;
        bit->label->setText(buf);
    }
    return ;
}

void MainWindow::on_pushButtonPortDo_clicked()
{
    DOWritePortChecked((WORD)gDoPort.value);
    return ;
}

static
void __ItemBit_DoPortUpdated(void)
{
    bool  ok;
    char  buf[2];
    unsigned int  value;

    value = gDoPort.edit->text().toInt(&ok, 16);

    if ( ! ok ) { return ; }

    gDoPort.value = value;

    buf[1] = '\0';

    for ( __ItemBit* bit = gDoBits; gDoBitsEnd > bit; ++bit, value >>= 1 )
    {
        bit->value = value & 0x01;
        buf[0] = '0' + bit->value;
        bit->label->setText(buf);
    }
    return ;
}
void MainWindow::on_lineEditPortDoValue_textChanged(QString )
{
    __ItemBit_DoPortUpdated();
    return ;
}
