#include <iostream>
#include <mqtt/client.h>  // broker.emqx.io
#include <ostream>  // std::cout.
using namespace std;
int main ()   
{
 // Define an Ip address pointing to a broker. In this case, the localhost on port 1883.
    std::string ip = "localhost:1883";
    // Then, define an ID to be used by the client when communicating with the broker.
    std::string id = "consumer";

   
    mqtt::client client(ip, id, mqtt::create_options(MQTTVERSION_5));
    client.connect();
    client.subscribe("in");
    client.start_consuming();
 
    bool running = true;
    while (running)
    {
        // Construct a message pointer to hold an incoming message.
        mqtt::const_message_ptr messagePointer;
 
        
        if (client.try_consume_message(&messagePointer))
        {
    
            std::string messageString = messagePointer -> get_payload_str();
            std::cout << messageString << std::endl;
 
            
            // we then break the loop and exit the program if a `quit` is received.
            if (messageString == "quit")
            {
                running = false;
            } 
        }
    }
 
    return 0;


}