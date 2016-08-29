#ifndef METALSLUG_MESSAGE_H
#define METALSLUG_MESSAGE_H

#include <iostream>
#include <string.h>
#include "User.h"

#include <vector>

class Message {
	private:
    int id;
    int timestamp;
		string from;
		string to;
		string content;

	public:
    //Constructor de Mensaje a un unico cliente.
    Message(unsigned long timestamp, string from, string to, string content);

    //Constructor de Mensaje to everyone.
    Message(unsigned long timestamp,string from,string content);

    /* Pre:
     * Post:
		 */
	string getTimestamp();

    /* Pre:
     * Post:
		 */
    string getFrom();

    /* Pre:
     * Post:
		 */
    string getTo();

    /* Pre:
     * Post:
		 */
    string getContent();

	/* Pre:
     * Post:
         */
	string serialize();

	bool isToUser(string username);

};


class MessagesList{
    private:
        std::vector<Message> lista_mensajes;
    public:
        MessageList();
    /* Pre:
		 * Post: devuelve una lista de mensajes, correspondientes
     *       al usuario especificado
		 */
    std::vector<Message> filter_messages_per_user(User user);
};


#endif //METALSLUG_MESSAGE_H
