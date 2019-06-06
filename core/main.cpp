#include <iostream>

#include "network/server.h"
#include "network/client.h"
#include "intermediary/thread.h"

using namespace std;
using namespace core::network;
using namespace core::intermediary;

int main()
{
//    Client client;

//    if(client.connect("192.168.1.110", 5000))
//    {
//        uint8_t data;

//        for(int i = 0; i < 10; ++i)
//        {
//            cout << "count: " << client.available() << endl;

//            if(client.readByte(data))
//                cout << " " << (char)data << endl;

//            client.write((uint8_t *)"c", 1);

//            Thread<void>::sleepMilliseconds(100);
//        }

//        client.close();

//        return 0;
//    }

//    cout << "Connection error!" << endl;







    Server server;

    if(server.run(10, 5000))
    {
        uint8_t data;

        //while(true)
        {
            Socket *client = server.accept();

//            if(client == NULL)
//            {
//                Thread<void>::sleepMilliseconds(100);

//                continue;
//            }

            if(client != NULL)
            {
                cout << "IPv4 address:" << client->__getIP() << endl;

                for(int i = 0; i < 10; ++i)
                {
                    client->write((uint8_t *)"s", 1);

                    cout << "count: " << client->available() << endl;

                    if(client->readByte(data))
                        cout << " " << (char)data << endl;

                    Thread<void>::sleepMilliseconds(1000);
                }

                delete client;
            }
        }

        server.stop();

        return 0;
    }

    return 1;
}
















////#include <iostream>
////#include "unittests/console_consolemenu/checkingrun.h"

//#include "intermediary/thread.h"
////#include "basic/list.h"


//int main()
//{
//	core::intermediary::Thread<void>::sleepMicroseconds(100);

////	core::basic::List<int> list;

////	list.pushBack(1);
////	list.pushBack(2);
////	list.pushBack(3);
////	list.pushBack(4);
////	list.pushBack(5);
////	list.pushBack(6);

////	list.pushFront(7);
////	list.pushFront(8);
////	list.pushFront(9);
////	list.pushFront(10);
////	list.pushFront(11);
////	list.pushFront(12);

////	list.insert(0, 1);
////	list.insert(list.getSize(), 1);



//	//core::unittests::console_consolemenu::CheckingRun::assert();



//	return 0;
//}
