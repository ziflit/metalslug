#ifndef METALSLUG_MESSAGE_H
#define METALSLUG_MESSAGE_H

#include <string>

class Message {
	private:
		int id;
		string from;
		string to;
		string message_content;

	public:
		/* Pre: 
		 * Post: 
		 */
		string retrieve_sender();

		/* Pre: 
		 * Post: 
		 */
		string retrieve_recipient();

		/* Pre: 
		 * Post: 
		 */
		string retrieve_message();

};


class MessageList{
	private:
         /* como guardamos los mensajes? */
	public:
		/* Pre: 
		 * Post: devuelve una lista de mensajes, correspondientes
		 *       a un usuario especifico 
		 */
		MessageList retrieve_messages_to_user(User user);

};


#endif //METALSLUG_MESSAGE_H