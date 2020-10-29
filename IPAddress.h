#ifndef IPADDRESS_H
#define IPADDRESS_H

/**
 * IP��ַ�����ؼ� ����:feiyangqingyun(QQ:517216493) 2017-8-11
 * 1:������IP��ַ,�Զ������
 * 2:�����IP��ַ
 * 3:֧�ְ���СԲ���Զ��л�
 * 4:֧���˸���Զ��л�
 * 5:֧��IP��ַ����
 * 6:�����ñ���ɫ/�߿���ɫ/�߿�Բ�ǽǶ�
 */

#include <QWidget>

class QLabel;
class QLineEdit;

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT IPAddress : public QWidget
#else
class IPAddress : public QWidget
#endif

{
    Q_OBJECT
        Q_PROPERTY(QString ip READ getIP WRITE setIP)

public:
    explicit IPAddress(QWidget* parent = 0);

protected:
    bool eventFilter(QObject* watched, QEvent* event);

private:
    QLabel* labDot1;    //��һ��СԲ��
    QLabel* labDot2;    //�ڶ���СԲ��
    QLabel* labDot3;    //������СԲ��

    QLineEdit* txtIP1;  //IP��ַ���������1
    QLineEdit* txtIP2;  //IP��ַ���������2
    QLineEdit* txtIP3;  //IP��ַ���������3
    QLineEdit* txtIP4;  //IP��ַ���������4

    QString ip;         //IP��ַ
    QString bgColor;    //������ɫ
    QString borderColor;//�߿���ɫ
    int borderRadius;   //�߿�Բ�ǽǶ�

private slots:
    void textChanged(const QString& text);

public:
    //��ȡIP��ַ
    QString getIP()                 const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    //����IP��ַ
    void setIP(const QString& ip);
    //���
    void clear();

    //���ñ�����ɫ
    void setBgColor(const QString& bgColor);
    //���ñ߿���ɫ
    void setBorderColor(const QString& borderColor);
    //���ñ߿�Բ�ǽǶ�
    void setBorderRadius(int borderRadius);

};

#endif // IPADDRESS_H