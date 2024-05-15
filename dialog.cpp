#include "dialog.h"
#include "./ui_dialog.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
#include <QFile>
#include <QDialog>
#include <QtWidgets>
#include <QFileSystemModel>
#include <QCloseEvent>
#include <QDebug>
#include <QRadioButton>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->textEditOutput->setReadOnly(true);



      //  if(!folder_name.isEmpty()){

       // }
        /*  int lineno = 0;
    std::string line;
    while (getline(infile, line))
    {
        ++lineno;
        auto pos = line.find(argv[1]);
        if (pos != std::string::npos)
            std::cout << lineno << ":" << pos << ": " << line << '\n';
    }
    */


}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButtonRun_clicked()
{   //qDebug()<<"Run clicked";
    QString target;
    QString folder_name;
    QString error_message;
    QString output_message;
    QString output_path;

    target = ui->lineEditPattern->text();
    folder_name=ui->lineEditDirectory->text();
    if(target.isEmpty() || folder_name.isEmpty()){
        QMessageBox::information(this, tr("Field cannot be empty"), tr("Try again"));

        return;

    }
    if(ui->radioButton->isChecked()){
        recursionRequested(target,folder_name);
}
    else{
    //qDebug()<<"Folder is "<<folder_name.toStdString();
    for(auto &entry : std::filesystem::directory_iterator(folder_name.toStdString())){
        std::filesystem::path filePath=entry.path();
        if(!std::filesystem::is_directory(std::filesystem::status(filePath))){
            if(filePath.extension()==".csv" || filePath.extension()==".txt"
                || filePath.extension()==".docx" || filePath.extension()==".doc"){
      //          qDebug()<<"Found a file with correct extension: "<<filePath.generic_string();
                std::ifstream infile(entry.path());
                QFile inputFile(entry.path());
                inputFile.open(QIODevice::ReadOnly);
                if (!inputFile.isOpen())
                {   error_message.fromStdWString(entry.path().generic_wstring());
                    ui->textEditOutput->setText("Cannot open "+ error_message+'\n');
                    continue;
                }
                QTextStream stream(&inputFile);
                int lineno = 0;
                //std::string line;
                //for(QString line=stream.readLine();!line.isNull();line=stream.readLine())
               // while (getline(infile, line))
                QString line;
                while(stream.readLineInto(&line))
                {   //qDebug()<<"Reading line: "<<line;
                    ++lineno;
                    //auto pos = line.find(target.toStdString());
                    if (line.contains(target)){
                        output_path.fromStdWString(entry.path().generic_wstring());
                        output_message+=QString::number(lineno)+":"+":"+line+'\n'+output_path;
                        ui->textEditOutput->setText(output_message);
        //                qDebug()<<output_message;
                        //std::cout << lineno << ":" << pos << ": " << line << '\n';
                        //std::cout <<entry.path()<<std::endl;
                    }

                }


                //std::cout <<entry.path()<<std::endl;
            }
        }
        else //File is a directory
        { continue;}
    }
}
}

void Dialog::recursionRequested(QString target, QString folder_name){
    qDebug()<<"Recursion requested";
    QString error_message;
    QString output_message;
    QString output_path;
    for(auto &entry : std::filesystem::directory_iterator(folder_name.toStdString())){
        std::filesystem::path filePath=entry.path();
        if(!std::filesystem::is_directory(std::filesystem::status(filePath))){
            if(filePath.extension()==".csv" || filePath.extension()==".txt"
                || filePath.extension()==".docx" || filePath.extension()==".doc"){
                //          qDebug()<<"Found a file with correct extension: "<<filePath.generic_string();
                std::ifstream infile(entry.path());
                QFile inputFile(entry.path());
                inputFile.open(QIODevice::ReadOnly);
                if (!inputFile.isOpen())
                {   error_message.fromStdWString(entry.path().generic_wstring());
                    ui->textEditOutput->setText("Cannot open "+ error_message+'\n');
                    continue;
                }
                QTextStream stream(&inputFile);
                int lineno = 0;
                //std::string line;
                //for(QString line=stream.readLine();!line.isNull();line=stream.readLine())
                // while (getline(infile, line))
                QString line;
                while(stream.readLineInto(&line))
                {   //qDebug()<<"Reading line: "<<line;
                    ++lineno;
                    //auto pos = line.find(target.toStdString());
                    if (line.contains(target)){
                        output_path.fromStdWString(entry.path().generic_wstring());
                        output_message+=QString::number(lineno)+":"+":"+line+'\n'+output_path;
                        ui->textEditOutput->setText(output_message);
                        //                qDebug()<<output_message;
                        //std::cout << lineno << ":" << pos << ": " << line << '\n';
                        //std::cout <<entry.path()<<std::endl;
                    }

                }


                //std::cout <<entry.path()<<std::endl;
            }
        }
        else //File is a directory
        {
            for(auto& p: std::filesystem::recursive_directory_iterator(filePath)){
                std::filesystem::path recursivePath=p.path();
                if(recursivePath.extension()==".csv" || recursivePath.extension()==".txt"
                    || recursivePath.extension()==".docx" || recursivePath.extension()==".doc"){
                    QFile inputFile(entry.path());
                    inputFile.open(QIODevice::ReadOnly | QIODevice::Text);
                    if (!inputFile.isOpen())
                    {   error_message.fromStdWString(entry.path().generic_wstring());
                        ui->textEditOutput->setText("Cannot open "+ error_message+'\n');
                        continue;
                    }
                    QTextStream stream(&inputFile);
                    int lineno = 0;
                    //std::string line;
                    //for(QString line=stream.readLine();!line.isNull();line=stream.readLine())
                    // while (getline(infile, line))
                    QString line;
                    while(stream.readLineInto(&line))
                    {   //qDebug()<<"Reading line: "<<line;
                        ++lineno;
                        //auto pos = line.find(target.toStdString());
                        if (line.contains(target)){
                            output_path.fromStdWString(entry.path().generic_wstring());
                            output_message+=QString::number(lineno)+":"+":"+line+'\n'+output_path;
                            ui->textEditOutput->setText(output_message);
                            //      qDebug()<<output_message;
                            //std::cout << lineno << ":" << pos << ": " << line << '\n';
                            //std::cout <<entry.path()<<std::endl;
                        }

                    }

                }
            }
        }
    }
}
void Dialog::on_pushButtonClear_clicked()
{
    ui->lineEditPattern->clear();
    ui->lineEditDirectory->clear();
    ui->textEditOutput->clear();
    ui->radioButton->setChecked(false);
}

