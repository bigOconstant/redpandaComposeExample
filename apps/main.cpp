#include <iostream>
#include <cpr/cpr.h>

#include "kafka/KafkaConsumer.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using std::cout;
using std::endl;
using rapidjson::Document;
int main(int argc, char **argv) {


    std::string brokers = std::getenv("KAFKAURL");
    kafka::Topic topic  = std::getenv("KAFKATOPIC");

    Document d;
     try {

        // Create configuration object
        kafka::Properties props ({
            {"bootstrap.servers", brokers},
        });

        // Create a consumer instance.
        kafka::KafkaAutoCommitConsumer consumer(props);

        // Subscribe to topics
        consumer.subscribe({topic});

        // Read messages from the topic.
        std::cout << "% Reading messages from topic: " << topic << std::endl;
        while (true) {
            auto records = consumer.poll(std::chrono::milliseconds(100));
            for (const auto& record: records) {
                // In this example, quit on empty message
                if (record.value().size() == 0) return 0;

                if (!record.error()) {
                    //std::cout << "% Got a new message..." << std::endl;
                    
                    d.Parse(record.value().toString().c_str());
                    cout<<d["message"].GetString()<<" ";
                   
                   
                    //std::cout << "    Value [" << record.value().toString() << "]" << std::endl;
                } else {
                    std::cerr << record.toString() << std::endl;
                }
            }
        }

        // consumer.close(); // No explicit close is needed, RAII will take care of it

    } catch (const kafka::KafkaException& e) {
        std::cerr << "% Unexpected exception caught: " << e.what() << std::endl;
    }
  
  return 0;
}
