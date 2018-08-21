#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<string>
#include <stack>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    delete ui;
    exit(0);
}

void MainWindow::on_actionAbout_triggered()
{

}

void MainWindow::on_BtnEncrypt_clicked()
{
    char defaultKey[62] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                        '1','2','3','4','5','6','7','8','9','0',
                        'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    std::string plainStr;
    std::string transKey;
    QString plainQStr;
    plainStr = ui->lineEditPlain->text().toStdString();
    transKey = ui->lineEditTransposeKey->text().toStdString();

    std::string tempStr;
    tempStr = plainStr;

    // step through the plain text, converting each character into the appropriate key
    for(unsigned long i = 0; i < 62; i++)
        // key: A-Z then 1-9, 0, a-z
        // this is fixed, so transKey[0-25] is A-Z respectively
        // etc.
        // This applies when transkey is unchanged, any changes will work appropriately
        for(unsigned long j = 0; j < plainStr.size(); j++){
            if(plainStr[j] == defaultKey[i]){
                tempStr[j] = transKey[i];
            }
        }
    plainStr = tempStr;

    ui->lineEditCipher->setText(plainQStr.fromStdString(plainStr));
}

void MainWindow::on_BtnDecrypt_clicked()
{
    char defaultKey[62] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                        '1','2','3','4','5','6','7','8','9','0',
                        'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    std::string cipherStr;
    std::string transKey;
    QString cipherQStr;
    cipherStr = ui->lineEditCipher->text().toStdString();
    transKey = ui->lineEditTransposeKey->text().toStdString();

    std::string tempStr;
    tempStr = cipherStr;

    // step through the plain text, converting each character into the appropriate key
    for(unsigned long i = 0; i < 62; i++)
        // key: A-Z then 1-9, 0, a-z
        // this is fixed, so transKey[0-25] is A-Z respectively
        // etc.
        // This applies when transkey is unchanged, any changes will work appropriately
        for(unsigned long j = 0; j < cipherStr.size(); j++){
            if(cipherStr[j] == transKey[i]){
                tempStr[j] = defaultKey[i];
            }
        }
    cipherStr = tempStr;

    ui->lineEditPlain->setText(cipherQStr.fromStdString(cipherStr));
}

void MainWindow::on_pushButtonEncrypt_clicked()
{
    std::string plainStr;
    QString plainQstr;
    plainStr = ui->lineEditPlainCeaser->text().toStdString();
    int rotation = ui->spinBoxRotation->value();

    std::string tempStr = plainStr;
    for(unsigned long i = 0; i < plainStr.size(); i++){
        if(rotation >= 0){
            tempStr[i] = (tempStr[i] + rotation) % 126;
            // printable characters ASCII 32-126 inclusive

            if((tempStr[i] >= 0) && (tempStr[i] < 32)){
                tempStr[i] += 31;
            }
        }
        // Rotation is negative
        else {
            tempStr[i] = (tempStr[i] + rotation) % 126;
            // printable characters ASCII 32-126 inclusive

            if((tempStr[i] >= 0) && (tempStr[i] < 32)){
                tempStr[i] = 126 -31 + tempStr[i];
            }
        }
    }
    plainStr = tempStr;

    ui->lineEditCipherCeaser->setText(plainQstr.fromStdString(plainStr));
}

void MainWindow::on_pushButtonDecrypt_clicked()
{
    std::string cipherStr;
    QString cipherQstr;
    cipherStr = ui->lineEditCipherCeaser->text().toStdString();
    int rotation = ui->spinBoxRotation->value();

    std::string tempStr = cipherStr;
    for(unsigned long i = 0; i < cipherStr.size(); i++){
        if(rotation >= 0){
            tempStr[i] = (tempStr[i] - rotation) % 126;
            // printable characters ASCII 32-126 inclusive

            if((tempStr[i] >= 0) && (tempStr[i] < 32)){
                tempStr[i] += 31;
            }
        }
        // Rotation is negative
        else {
            tempStr[i] = (tempStr[i] - rotation) % 126;
            // printable characters ASCII 32-126 inclusive

            if((tempStr[i] >= 0) && (tempStr[i] < 32)){
                tempStr[i] = 126 -31 + tempStr[i];
            }
        }
    }
    cipherStr = tempStr;

    ui->lineEditPlainCeaser->setText(cipherQstr.fromStdString(cipherStr));
}


void MainWindow::on_reverseButton_clicked()
{
        QString myString;
        myString =ui->lineEdit->text();

        std::string temp=myString.toStdString();
        //stack operator
        std::stack<char>reverseStack;
		//pushing the text into the stack
        for(int i=0; i<temp.size(); i++)
        {
            reverseStack.push(temp.at(i));
        }
        //clear
        temp.clear();
		//poping out the text
        while(!reverseStack.empty())
        {
            char mytop= reverseStack.top();

           temp.push_back(mytop);

           reverseStack.pop();
        }
        ui->reverseLineEdit->setText(myString.fromStdString(temp));


}

void MainWindow::on_pushButton_clicked()
{
   ui->lineEdit->clear();
   ui->reverseLineEdit->clear();
}
