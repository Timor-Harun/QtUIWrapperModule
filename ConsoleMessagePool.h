#pragma once

#include <QString>
#include <QVector>
enum  MessageType {
	Info = 0,
	Warning = 1,
	Error = 2
};
//Message of Console
typedef struct Message
{
	//called Info can be presented as : function_something(...) in Line xx
	QString         calledInfo;
	//main content of message
	QString         message;
	//type of message (Info,Warning,Error)
	MessageType     type;

	Message() {}
	Message(QString     _calledInfo,
			QString     _message,
			MessageType _type) :
			calledInfo(_calledInfo),
			message(_message),
			type(_type)
	{}

	bool serach(QString content)
	{
		int calledInfoPos = this->calledInfo.indexOf(content);
		int messagePos = this->message.indexOf(content);

		bool calledInfoMatched = false;
		bool messageMatched = false;

		int contentSize = content.size();
		if (calledInfoPos != -1)
		{
			calledInfoMatched = true;
		}
		if (messagePos != -1)
		{
			messageMatched = true;
		}
		return calledInfoMatched || messageMatched;
	}

}Message;

class ConsoleMessagePool
{
private:
	QVector<Message> pool;
public:
	void pushMessage(const Message& msg);

	bool isEmpty();

	Message getLastMessage();
};

