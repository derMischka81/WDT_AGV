#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cstdio>
#include <QMessageBox>
#include <QTimer>

#include "../../include/wdt_dio.h"

#define __UI_ONLY__  ( 0 )  // testing without linking library

#if ( __UI_ONLY__ )

#define CAN_RegisterReceived(idx, pfnHandler)  1
#define CAN_RegisterStatus(idx, pfnHandler)  1
#define CAN_Setup(idx, lpSetup, cbSetup)  1
#define CAN_Start(idx)  1
#define CAN_Stop(idx)  1
#define CAN_Send(idx, lpMsg, cbMsg)  1

#else

#if defined(_WIN64)
#pragma comment(lib, "WDT_DIO64.lib")
#else defined(_WIN32)
#pragma comment(lib, "WDT_DIO32.lib")
#endif

#endif

static Ui::MainWindow*  gMainUi;
static MainWindow*  gMainWindow;
static QLineEdit*  gEditData[8];

static DWORD  gCntTx;
static DWORD  gCntRx;
static DWORD  gStatus;


static __inline
void __ErrMsg(const QString& errMsg)
{
    QMessageBox::critical(0, "ERROR", errMsg);
}

static __inline
void __CAN0_Status(DWORD status)
{
    gStatus = status;
    return ;
}

static void __CAN0_Received(CAN_MSG *lpMsg, DWORD cbMsg)
{
    gMainUi->labelRx->setText(QString::number(++gCntRx));

    if ( lpMsg->flags & CAN_MSG_DATA_LOST )
    {
        gMainWindow->Append("CAN_MessageGet, CAN_MSG_DATA_LOST\r\n");
    }
    static const char  fmt[] = "%03x, %d, %02x %02x %02x %02x %02x %02x %02x %02x";
    char  log[sizeof(fmt)];
    unsigned  len = std::snprintf(log, sizeof(log), fmt,
      lpMsg->id, lpMsg->len
    , lpMsg->data[0], lpMsg->data[1], lpMsg->data[2], lpMsg->data[3]
    , lpMsg->data[4], lpMsg->data[5], lpMsg->data[6], lpMsg->data[7]
    );
    gMainWindow->Append(log);
    return ;
}

void MainWindow::Append(const QString &str)
{
    emit this->AppendText(str);
    return ;
}

void MainWindow::SlotAppendText(const QString &str)
{
    this->ui->plainTextEdit->appendPlainText(str);
    return ;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
    connect(this,SIGNAL(AppendText(QString)),this,SLOT(SlotAppendText(QString)));
    printf("[ ] CAN_SETUP=%lu, CAN_MSG=%lu\n", sizeof(CAN_SETUP), sizeof(CAN_MSG));

#if ( __UI_ONLY__ )
    this->setWindowTitle(this->windowTitle() +"   <-- TEST UI");
#endif

    gMainWindow = this;
    gMainUi = this->ui;

    this->timer = new QTimer();
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(on_timer()));
    this->timer->setInterval(250);  // msec

    this->ui->lineEditRate->setText(QString::number(500000));  // default 500k
    this->ui->lineEditId->setText(QString::number(001));
    this->ui->lineEditDLC->setText(QString::number(8));

    gEditData[0] = this->ui->lineEditData0; gEditData[0]->setText(QString::number(30));
    gEditData[1] = this->ui->lineEditData1; gEditData[1]->setText(QString::number(31));
    gEditData[2] = this->ui->lineEditData2; gEditData[2]->setText(QString::number(32));
    gEditData[3] = this->ui->lineEditData3; gEditData[3]->setText(QString::number(33));
    gEditData[4] = this->ui->lineEditData4; gEditData[4]->setText(QString::number(34));
    gEditData[5] = this->ui->lineEditData5; gEditData[5]->setText(QString::number(35));
    gEditData[6] = this->ui->lineEditData6; gEditData[6]->setText(QString::number(36));
    gEditData[7] = this->ui->lineEditData7; gEditData[7]->setText(QString::number(37));

    return ;
}

MainWindow::~MainWindow()
{
    delete this->timer;  this->timer = 0;
    delete this->ui;  this->ui = 0;
    return ;
}

void MainWindow::on_pushButtonStart_clicked()
{
    if ( ! CAN_RegisterReceived(0, __CAN0_Received) )
    {
        __ErrMsg("CAN_RegisterReceived --> FAILED\n");
        return ;
    }
    if ( ! CAN_RegisterStatus(0, __CAN0_Status) )
    {
        __ErrMsg("CAN_RegisterStatus --> FAILED\n");
        return ;
    }

    CAN_SETUP  setup;
    //
    setup.bitRate = this->ui->lineEditRate->text().toInt();
    setup.recvConfig = CAN_MSG_USE_ID_FILTER;  // all
    setup.recvId = 0;  // all
    setup.recvMask = 0;  // all

    if ( ! CAN_Setup(0, &setup, sizeof(setup)) )
    {
        __ErrMsg("CAN_Setup --> FAILED\n");
        return ;
    }

    if ( ! CAN_Start(0) )
    {
        __ErrMsg("CAN_Start --> FAILED\n");
        return ;
    }

    this->ui->pushButtonStart->setEnabled(false);
    this->ui->pushButtonStop->setEnabled(true);
    this->ui->pushButtonSend->setEnabled(true);
    this->timer->start();
    return ;
}

void MainWindow::on_pushButtonStop_clicked()
{
    if ( ! CAN_Stop(0) )
    {
        __ErrMsg("CAN_Stop --> FAILED\n");
        return ;
    }
    this->ui->pushButtonStop->setEnabled(false);
    this->ui->pushButtonSend->setEnabled(false);
    this->ui->pushButtonStart->setEnabled(true);
    this->timer->stop();
    return ;
}

static void __UpdateGuiStatus(DWORD status)
{
    // CAN controller has entered a Bus Off state.
    //
    if ( status & CAN_STATUS_BUS_OFF )
    {
        // Handle Error Condition here
        //
        gMainUi->labelBusOff->setEnabled(true);

        // Clear CAN_STATUS_BUS_OFF Flag
        //
        status &= ~(CAN_STATUS_BUS_OFF);
    }
    else
    {
        gMainUi->labelBusOff->setEnabled(false);
    }

    // CAN controller error level has reached warning level.
    //
    if ( status & CAN_STATUS_EWARN )
    {
        // Handle Error Condition here
        //
        gMainUi->labelEWARN->setEnabled(true);

        // Clear CAN_STATUS_EWARN Flag
        //
        status &= ~(CAN_STATUS_EWARN);
    }
    else
    {
        gMainUi->labelEWARN->setEnabled(false);
    }

    // CAN controller error level has reached error passive level.
    //
    if ( status & CAN_STATUS_EPASS )
    {
        // Handle Error Condition here
        //
        gMainUi->labelEPASS->setEnabled(true);

        // Clear CAN_STATUS_EPASS Flag
        //
        status &= ~(CAN_STATUS_EPASS);
    }
    else
    {
        gMainUi->labelEPASS->setEnabled(false);
    }

    // This is the mask for the CAN Last Error Code (LEC).
    //
    if ( status & CAN_STATUS_LEC_MASK )
    {
        gMainUi->labelSTUFF->setEnabled(false);
        gMainUi->labelFORM ->setEnabled(false);
        gMainUi->labelACK  ->setEnabled(false);
        gMainUi->labelBit1 ->setEnabled(false);
        gMainUi->labelBit0 ->setEnabled(false);
        gMainUi->labelCRC  ->setEnabled(false);

        // Handle Error Condition here
        //
        switch ( status & CAN_STATUS_LEC_MASK )
        {
        case CAN_STATUS_LEC_STUFF : gMainUi->labelSTUFF->setEnabled(true);  break;
        case CAN_STATUS_LEC_FORM  : gMainUi->labelFORM ->setEnabled(true);  break;
        case CAN_STATUS_LEC_ACK   : gMainUi->labelACK  ->setEnabled(true);  break;
        case CAN_STATUS_LEC_BIT1  : gMainUi->labelBit1 ->setEnabled(true);  break;
        case CAN_STATUS_LEC_BIT0  : gMainUi->labelBit0 ->setEnabled(true);  break;
        case CAN_STATUS_LEC_CRC   : gMainUi->labelCRC  ->setEnabled(true);  break;
        }

        // Clear CAN_STATUS_LEC_MASK Flag
        //
        status &= ~(CAN_STATUS_LEC_MASK);
    }

    // Unhandled
    //
    if ( 0 != status )
    {
        //printf("ERROR: Unhandled, %x\n", status);
    }
    return ;
}

void MainWindow::on_timer()
{
    static DWORD  previous;

    if ( previous != gStatus )
    {
        previous = gStatus;
        //
        __UpdateGuiStatus(previous);
    }
    return ;
}

void MainWindow::on_pushButtonSend_clicked()
{
    bool  ok;
    CAN_MSG  txMsg;

    memset(&txMsg, 0, sizeof(txMsg));

    ok = false;
    txMsg.id = this->ui->lineEditId->text().toInt(&ok, 16);
    if ( ! ok )
    {
        __ErrMsg("ID --> FAILED");
        return ;
    }

    if ( this->ui->checkBoxEXT->isChecked() )
    {
        txMsg.flags = CAN_MSG_EXTENDED_ID;
    }
    else
    {
        txMsg.flags = 0;
    }

    txMsg.len = (BYTE) this->ui->lineEditDLC->text().toInt();
    //
    if ( 8 < txMsg.len )
    {
        txMsg.len = 8;
        this->ui->lineEditDLC->setText(QString::number(8));
    }

    unsigned  i;
    for ( i=0; txMsg.len > i; ++i )
    {
        txMsg.data[i] = gEditData[i]->text().toInt(&ok, 16);
        if ( ! ok )
        {
            __ErrMsg(QString("DATA, %d --> FAILED").arg(QString::number(i)));
            return ;
        }
    }

    if ( ! CAN_Send(0, &txMsg, sizeof(txMsg)) )
    {
        __ErrMsg("CAN_MessageSet --> FAILED, %d\r\n");
        return ;
    }

    this->ui->labelTx->setText(QString::number(++gCntTx));

    return ;
}
