#include "gtest/gtest.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "../model/message.h"
#include "../model/User.h"
//__________________________________________________________________________________
// Test structure:
//TEST(test_case_name, test_name) {
//... test body ...
//}

MessagesList* messagesList = new MessagesList();

User* user1 = new User("user1","password",123);
User* user2 = new User("user2","password",123);

Message* messageToUser1 = new Message(0,"from","user1","content of test message");
Message* messageToEveryone = new Message(1,"from","content of test message");
Message* messageToUser2 = new Message(2,"from","user2","content of test message");


messagesList->addMessage(messageToUser1);
messagesList->addMessage(messageToEveryone);
messagesList->addMessage(messageToUser2);

TEST(Messages, newMessage){
    Message* msg = new Message(1,"from","to","content");
    ASSERT_EQ(msg->getFrom(),"from");
    ASSERT_EQ(msg->getTo(),"to");
    ASSERT_EQ(msg->getContent(),"content");
}

TEST(MessagesListTests, newMessagesList){
    MessagesList* messagesList1 = new MessagesList();
    unsigned long esperado = 0;
    size_t realsize = messagesList1->size();
    ASSERT_EQ(esperado,realsize);
}


TEST(FilteringMessages, filteringToUser1) {

    std::vector<Message* > messagesToUser1 = messagesList->filterMessagesPerUser(user1);
    ASSERT_EQ(2, messagesToUser1.size());

}

TEST(FilteringMessages, filteringToUser2) {
    std::vector<Message* > messagesToUser2 = messagesList->filterMessagesPerUser(user2);
    ASSERT_EQ(2, messagesToUser2.size());

}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
